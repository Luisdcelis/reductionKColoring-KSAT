# reduction from KColoring to KSAT
 This code compute the reduction from coloring a graph problem to SAT problem (in DIMACS format for SAT CNF)  
   
 Dimacs format for SAT CNF:  
 &nbsp;c COMMENTS  
 &nbsp;p cnf numVARIABLES numCLAUSES  
 &nbsp;A,B,C,D,E,F  -> 1,2,3,4,5,6  
 &nbsp;(A v ¬B v C) -> 1 -2 3 0 (Add a 0 behind to indicate the end of the clause)  
&nbsp;(B v D v E)  -> 2 4 5 0  
&nbsp;(D V F)      -> 4 6 0  
