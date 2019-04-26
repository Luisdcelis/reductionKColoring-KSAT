# reduction from KColoring to KSAT
 This code compute the reduction from coloring a graph problem to SAT problem (in DIMACS format for SAT CNF)  
   
 Dimacs format for SAT CNF:  
      c COMMENTS  
      p cnf numVARIABLES numCLAUSES  
      A,B,C,D,E,F  -> 1,2,3,4,5,6  
      (A v ¬B v C) -> 1 -2 3 0 (Add a 0 behind to indicate the end of the clause)  
      (B v D v E)  -> 2 4 5 0  
      (D V F)      -> 4 6 0  
