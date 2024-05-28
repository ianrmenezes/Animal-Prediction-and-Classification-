menezesIanA1: menezesIanA1.o menezesIanA1Main.o 
     gcc menezesIanA1.o menezesIanA1Main.c -o menezesIanA1 
menezesIanA1.o: menezesIanA1.c givenA1.h 
     gcc -Wall -std=c99 -c menezesIanA1.c  
menezesIanA1Main.o: menezesIanA1Main.c givenA1.h 
     gcc -Wall -std=c99 -c menezesIanA1Main.c  
clean: 
 	 rm *.o menezesIanA1