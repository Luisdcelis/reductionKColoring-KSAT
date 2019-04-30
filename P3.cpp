// Dimacs format for SAT CNF:
//      c COMMENTS
//      p cnf numVARIABLES numCLAUSES
//      A,B,C,D,E,F -> 1,2,3,4,5,6
//      (A v ¬B v C) -> 1 -2 3 0 (Add a 0 behind to indicate the end of the clause)
//      (B v D v E) -> 2 4 5 0
//      (D V F) -> 4 6 0

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include "cronometro.hpp"

using namespace std;

typedef list<int> adj;
typedef vector<adj> graph;


graph petersenGraph()
{
    graph G;
    int v0[] = {1, 5, 4};
    adj l(v0, v0 + sizeof(v0)/sizeof(int));
    G.push_back(l);
    int v1[] = {0, 2, 6};
    l = adj(v1, v1 + sizeof(v1)/sizeof(int));
    G.push_back(l);
    int v2[] = {1, 3, 7};
    l = adj(v2, v2 + sizeof(v2)/sizeof(int));
    G.push_back(l);
    int v3[] = {2, 4, 8};
    l = adj(v3, v3 + sizeof(v3)/sizeof(int));
    G.push_back(l);
    int v4[] = {0, 3, 9};
    l = adj(v4, v4 + sizeof(v4)/sizeof(int));
    G.push_back(l);
    int v5[] = {0, 7, 8};
    l = adj(v5, v5 + sizeof(v5)/sizeof(int));
    G.push_back(l);
    int v6[] = {1, 8, 9};
    l = adj(v6, v6 + sizeof(v6)/sizeof(int));
    G.push_back(l);
    int v7[] = {2, 5, 9};
    l = adj(v7, v7 + sizeof(v7)/sizeof(int));
    G.push_back(l);
    int v8[] = {3, 5, 6};
    l = adj(v8, v8 + sizeof(v8)/sizeof(int));
    G.push_back(l);
    int v9[] = {4, 6, 7};
    l = adj(v9, v9 + sizeof(v9)/sizeof(int));
    G.push_back(l);

    return G;
}

graph testGraph()
{
    graph G;
    int v0[] = {1, 2};
    adj l(v0, v0 + sizeof(v0)/sizeof(int));
    G.push_back(l);
    int v1[] = {0, 2, 3};
    l = adj(v1, v1 + sizeof(v1)/sizeof(int));
    G.push_back(l);
    int v2[] = {0, 1};
    l = adj(v2, v2 + sizeof(v2)/sizeof(int));
    G.push_back(l);
    int v3[] = {1};
    l = adj(v3, v3 + sizeof(v3)/sizeof(int));
    G.push_back(l);

    return G;
}

graph complexTimeGraph(int n)
{
    // Makes a graph with n nodes and all connected with each others
    graph G;
    vector<int> v;

    for(int i = 0; i < n; i++)
    {
        v.clear();
        for(int j = 0; j < n; j++)
        {
            if(j != i)
                v.push_back(j);
        }
        adj l(v.begin(), v.end());
        G.push_back(l);
    }
    return G;
}

bool operatorIN(int i, list<int> V)
{
    list<int>::iterator it = find(V.begin(),V.end(),i);
    if(it == V.end())
        return false;
    else
        return true;
}

void redKCOL_KSAT(ofstream& f, graph G, int numColors)
{
    int numVar = G.size()*numColors;
    list<int> nodosVisitados;
    string res = "";

    for(int nodoAct = 0; nodoAct < G.size(); nodoAct++)
    {
        for(int i = numColors*nodoAct; i < (numColors*nodoAct)+numColors; i++)
        {
            // Un nodo tiene que ser uno de los K colores
            res = res + to_string(i+1) + " ";
        }
        res = res + "0\n";

        for(int i = numColors*nodoAct; i < (numColors*nodoAct)+numColors-1; i++)
        {
            for(int j = i+1; j <= (numColors*nodoAct)+numColors-1; j++)
            {
                // Un nodo no puede tener dos colores distintos al mismo tiempo
                res = res + "-" + to_string(i+1) + " -" + to_string(j+1) + " 0\n";
            }
        }
        adj::iterator it = G[nodoAct].begin(); 
        for(int posAct = 0; posAct < G[nodoAct].size(); posAct++)
        { 
            //Un nodo no puede tener el mismo color que su adyacente
            
            if(operatorIN(*it, nodosVisitados)) // Si la posAct es un nodo visitado
            {
                if(!operatorIN(nodoAct, G[*it])) // si el par que estamos haciendo no ha sido realizado
                {
                    // hacemos el par
                    for(int i = numColors*nodoAct, j = numColors*(*it); i < (numColors*nodoAct)+numColors; i++, j++)
                    {
                        res = res + "-" + to_string(i+1) + " -" + to_string(j+1) + " 0\n";
                    }

                }
                //si es un nodo visitado y el par ha sido realizado no tenemos nada que hacer
            }
            else
            {
                //hacemos el par
                for(int i = numColors*nodoAct, j = numColors*(*it); i < (numColors*nodoAct)+numColors; i++, j++)
                {
                    res = res + "-" + to_string(i+1) + " -" + to_string(j+1) + " 0\n";
                }
            }
            it++;
        }
        nodosVisitados.push_back(nodoAct);
    }
    f << "p cnf " << numVar << " " << count(res.begin(), res.end(), '\n') << "\n" << res;
     
}

int main(int argc, char const *argv[])
{
    graph G;
    cronometro c;
    ofstream f;
    int numColors = 3;


    // If  you  want to test the complexity time of the algorithm: 
    // for(int i  = 5; i <= 100; i +=5)
    // {
    //     G = complexTimeGraph(i);
    //     f.open("output.cnf");

    //     c.activar();
    //     redKCOL_KSAT(f, G, numColors);
    //     c.parar();

    //     f.close();
    //     cout << "time for " << G.size() << " nodes and " << numColors << " colors: " << c.tiempo() << endl;
    // }


    // If you want to do the reduction to one concrete graph:
    G = petersenGraph();
    f.open("output.cnf");

    c.activar();
    redKCOL_KSAT(f, G, numColors);
    c.parar();

    f.close();
    cout << "time for " << G.size() << " nodes and " << numColors << " colors: " << c.tiempo() << endl;

    return 0;
}