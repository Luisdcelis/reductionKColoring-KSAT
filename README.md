# reduction from KColoring to KSAT
 This code compute the reduction from coloring a graph problem to SAT problem (in DIMACS format for SAT CNF)  
   
 Dimacs format for SAT CNF:  
&nbsp;&nbsp;&nbsp;c COMMENTS  
&nbsp,&nbsp;&nbsp;p cnf numVARIABLES numCLAUSES  
&nbsp;&nbsp;&nbsp;A,B,C,D,E,F  -> 1,2,3,4,5,6  
&nbsp;&nbsp;&nbsp;(A v ¬B v C) -> 1 -2 3 0 (Add a 0 behind to indicate the end of the clause)  
&nbsp;&nbsp;&nbsp;(B v D v E)  -> 2 4 5 0  
&nbsp;&nbsp;&nbsp;(D V F)      -> 4 6 0  
