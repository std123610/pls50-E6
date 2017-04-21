#include <stdio.h>

/*
* Christos Stavrakis
* A.M.: 123610
*
* Examination 1, exersise 4:
* Bus Presentation and Reservation Program
*/


int  checkBusPlateValidity(char *);
int  initializeBus(char *, int , int *, int , int , int);
int  reserveSeat(int , int , int arr[]);
void checkSeatReservation(int , int arr[]);
void reserveSeatStrategy(int , int arr[]);
void reserveFirstWindowSeatStrategy(int , int arr[]);
void printBusEmptySeats(int , int arr[]);
void reserveSeatShowAll(int , int arr[]);
void cancelSeatToBus(int , int arr[]);
void readFromFile(char f[], int , char s[]);
void printBusStatusGraph(int , int arr[], char *, int , int);
void saveBusStatusGraphToFile(char f[], int , int arr[], char *, int, int);


int main(int argc, char *argv[]) {
	
	
	int  chars = 15;
	char str[chars];  /* holds the string that will be readen from bus.txt */
	char input_choice;  /* holds the current user's input choice 0 - 8 */
	char txtFileToRead[] = "bus.txt";  /* name of input file */
	char txtFileToWrite[] = "layout.txt"; /* name of output file */
	
	const int  maxSeatsNum = 53;     /* initial constants: Max seat number  			*/
	const int  theseisPerRow = 4;    /* initial constants: Max seat number per row  	*/
	const int  theseisPerColumn = 2; /* initial constants: Max seat number per column  	*/
	const int  lastRowSeatsNum = 5;  /* initial constants: Max seat number at last row  */
	
	
	readFromFile(txtFileToRead, chars, &str);  /* Read input file to get the plate and seats number */
	
    char *p = strtok (str, " "); 
    char *array[3]; /* To store the two separate values (bus-plate and seats-number) from file bus.txt */

    int i = 0; 
    while ( p != NULL){
        array[i++] = p;
        p = strtok (NULL, " ");
    }
    char *plate = array[0]; /* The plate of bus inside bus.txt file */
    char *ptr;
    long theseis = strtol(array[1], &ptr, 10);  /* The number of seats inside bus.txt file */
    int  myBus[theseis];
    
    initializeBus(plate, theseis, &myBus, theseisPerRow, lastRowSeatsNum, maxSeatsNum); /* Initialize bus */
    
    do{
		/* Print initial choices for user */
		printf("\n0. Quit\n1. Show all empty seats\n2. Reserve seat\n3. Reserve first window seat\n4. Cancel reservation\n");
		printf("5. Check seat reservation\n6. Show all reserved seats\n7. Show Bus status\n8. Save to file\n");
		scanf(" %c", &input_choice);
		
		switch(input_choice){
			case '0':
				break;
			case '1':
				//Show all seats
				printBusEmptySeats(theseis, &myBus);
				break;
			case '2':
				//Show Reserve seat
				reserveSeatStrategy(theseis, &myBus);
				break;
			case '3':
				//Reserve first window seat
				reserveFirstWindowSeatStrategy(theseis, &myBus);
				break;
			case '4':
				//Cancel reservation
				cancelSeatToBus(theseis, &myBus);
				break;
			case '5':
				//Check seat reservation
				checkSeatReservation(theseis, &myBus);
				break;
			case '6':
				//Show all reserved seats
				reserveSeatShowAll(theseis, &myBus);
				break;
			case '7':
				//Show Bus status
				printBusStatusGraph(theseis, &myBus, plate, theseisPerRow, theseisPerColumn);
				break;
			case '8':
				//Save to file
				saveBusStatusGraphToFile(txtFileToWrite, theseis, &myBus, plate, theseisPerRow, theseisPerColumn);
				break;
			default:
				printf("Please give a valid choice..(0 - 8)\n");
		}
		
	}while(input_choice != '0');
    
	return 0;
}

/* Initialize bus seats with 0 (empty), but also returns error message if the initial data are wrong */
int initializeBus(char *plate, int theseis, int myBus[theseis], int theseisPerRow, int lastRowSeatsNum, int maxSeatsNum){
	
	if(checkBusPlateValidity(plate) == 0){ /* check if but plate consists of 3 letters and 4 numbers */
		printf("The bus plate given from input file, is not valid!\n");
		printf("The plate should be like XXX1234.\n");
		exit(1);
		
	}else if( theseis > maxSeatsNum ){ /* check if seats given from file are not bigge than 53 */
		printf("The seats given from file, are not valid!\n");
		printf("The seats should be maximum %d.\n", maxSeatsNum);
		exit(1);
		
	}else if((theseis - lastRowSeatsNum) % theseisPerRow != 0){ /* check if seats are follow (4 x N) + 5 , N >= 0 type. */
		printf("The seats given from file, are not valid!\n");
		printf("The seats should follow the rule (%d x N) + %d , N >= 0 rows.\n", 
				theseisPerRow, 
				lastRowSeatsNum
			);
		exit(1);
	}else{ /* the initial values are all valid so initialize bus. */
		int j = 0;
	    for(j ; j < theseis; ++j){ /* Initialize all the seats, as empty (=0) */
	    	myBus[j] = 0;
		}
		printf("Bus initialized.\n");
	}
}

/* Validates the bus plate, and return true if is valid or false. */
int checkBusPlateValidity(char *plate){
	
	int i;
	int letters = 0;
	int numbers = 0;
	for (i = 0; i < sizeof(plate); ++i) {
        if (isalpha(plate[i])) {
	    	++letters;
		} else if (isdigit(plate[i])) {
		   ++numbers;
		} else {
		}
    }
    
    /* Plate validation. Should be like  XXX1234, so only 3 letters and 4 numbers are valid*/
    if(letters == 3 && numbers == 4){
    	return 1;
	}
	return 0;
}


void checkSeatReservation(int theseis, int myBus[theseis]){
	
	int seatToCheck = 0;
	printf("\nGive seat number(to check):");
	scanf(" %d", &seatToCheck);
	
	if(seatToCheck > theseis || seatToCheck < 1){
		printf("Wrong seat!Available seats: 1 - %d\n", theseis);
	}else if(myBus[seatToCheck - 1] == 0){
		printf("The seat is empty!\n");
	}else{
		printf("The seat is reserved!\n");
	}
}

void cancelSeatToBus(int theseis, int myBus[theseis]){
	
	int seatToCancel = 0;
	printf("\nGive seat number(to cancel):");
	scanf(" %d", &seatToCancel);
	
	if(seatToCancel > theseis || seatToCancel < 1){
		printf("Wrong seat!Available seats: 1 - %d\n", theseis);
	}else if(myBus[seatToCancel -1] == 0){
		printf("The seat is already canceled!\nChoose another seat please.\n");
	}else{
		myBus[seatToCancel -1] = 0;
		printf("The seat canceled!\n");
	}
	
}

/* Make the reservation of given seat, but also it handles the errors that may happen from this action*/
void reserveSeatStrategy(int theseis, int myBus[theseis]){
	
	int seatToBuy = 0;
	printf("\nGive seat number(to reserve):");
	scanf(" %d", &seatToBuy);
	
	if(seatToBuy > theseis || seatToBuy < 1){
		printf("Wrong seat!Available seats: 1 - %d\n", theseis);
	}else if(myBus[seatToBuy -1] == 1){
		printf("The seat is not reserved!\nChoose another seat please.\n");
	}else{
		reserveSeat(seatToBuy, theseis, myBus);
	}
	
}

/*  It is rensposible to find the first available seat near window, but also to handle the error message. */
void reserveFirstWindowSeatStrategy(int theseis, int myBus[theseis]){
	
	int windowSeatNumber = 0;
	int theseisPerRow = 4;
	
	if(myBus[0] == 0){  /* Check only the first seat here */
		windowSeatNumber = 1;
	}else{  
		int i = 1;
		for(i; i < theseis - 4; ++i){ /* Check all the window seats here, except first and last seat. */
			if( i % theseisPerRow == 0){
				if(myBus[i - 1] == 0){
					windowSeatNumber = i;
					break;
				}else if(myBus[i] == 0){
					windowSeatNumber = i + 1;
					break;
				}				
			}
		}
		
		/* Check only the last seat here and none previous seat was set. */
		if(windowSeatNumber == 0 && myBus[theseis - 1] == 0){
			windowSeatNumber = theseis;
		}
	}
	
	if(windowSeatNumber == 0){ /* if none of window seat is avalilable for reservation, print appropriate message. */
		printf("Sorry no window seats, available!");
	}else{ /* else do the reservation. */
		reserveSeat(windowSeatNumber, theseis, myBus);
	}
	
}

/* It shows all reserved seats, plus the total amount of them */
void reserveSeatShowAll(int theseis, int myBus[theseis]){
	
	int reservedSeats = 0;
	int k=0;
	printf("\nReserved seats: \n");
	for(k; k < theseis; ++k){
		
		if(myBus[k] == 1){
			if( reservedSeats > 0 ){
				printf(",");	
			}
			printf("%d", k+1);
			++reservedSeats;
		}
	}	
	printf("\n");
	printf("\nTotal reserved: %d\n", reservedSeats);
}

/* Performs the reservation action */
int reserveSeat(int seatNumber, int theseis, int myBus[theseis]){
	
	myBus[seatNumber - 1] = 1;
	
	if(myBus[seatNumber - 1] == 1){
		printf("Seat %d, reserved succesfully!\n", seatNumber);
		return 1;	
	}
	return 0;
}

/* It reads the given file, and updates the given string */
void readFromFile(char filename[], int chars, char string[chars]){
	
	FILE * file;
	file = fopen( filename , "r");
	if (file) {
		while(fgets(string, chars, file)){}
	    fclose(file);
	}else{
		printf("Error opening file! %s\n", filename);
    	exit(1);
	}
}

/* It shows all the empty seats of the bus */
void printBusEmptySeats(int theseis, int myBus[theseis]){
	int k = 0;
	int emptySeats = 0;
	printf("\nEmpty seats: \n");
	for(k; k < theseis; ++k){
		
		if(myBus[k] == 0){ /* if the seat is empty */
			if( emptySeats > 0 ){ /* put comma inside numbers, but not from the beginning */
				printf(",");	
			}
			printf("%d", k+1); /* print the seat number */
			++emptySeats;
		}
	}	
	/* Print info message at the end */
	printf("\n");
	printf("\nTotal empty seats: %d\n", emptySeats);
}

/* It shows a nice presentation of bus, with all reserved and empty seats, plus some info like the plate number */
void printBusStatusGraph(int theseis, int myBus[theseis], char *plate, int theseisPerRow, int theseisPerColumn){
	
	printf("Pinakida: %s\n", plate);
    printf("Theseis: %d\n", theseis);
    
	int l = 1;
	/* check all seats except last five */
    for(l; l < theseis - 4; ++l){
    
    	printf("%c", ((myBus[l - 1] == 0)? '_':'*')); /* if seat is empty print '_' else '*' */
    	
    	if( l % theseisPerColumn == 0 && l % theseisPerRow != 0){ /* If we are in passageway then print empty scrin*/
    		printf(" ");
		}else if( l % theseisPerRow == 0){ /* if we are on the end of the row, then print end line character '\n' */
    		printf("\n");
		}
	}
	
	/* check last five seats */
	for(l; l < theseis + 1; ++l){
		printf("%c", ((myBus[l - 1] == 0)? '_':'*'));
	}
	printf("\n");
}

/* It saves the current bus presentation to a given file */
void saveBusStatusGraphToFile(char filename[], int theseis, int myBus[theseis], char *plate, int theseisPerRow, int theseisPerColumn){
	
	FILE * file;
	file = fopen( filename , "w+");
	if (file) {
		
		
	    fprintf(file, "plate: %s\n", plate);
    	fprintf(file, "Theseis: %d\n", theseis);
    	
    	/* prints the bus presentation */
		int l = 1;
    	for(l; l < theseis - 4; ++l){
    
	    	fprintf(file, "%c", ((myBus[l - 1] == 0)? '_':'*'));
	    	
	    	if( l % theseisPerColumn == 0 && l % theseisPerRow != 0){
	    		fprintf(file, " ");
			}else if( l % theseisPerRow == 0){
	    		fprintf(file, "\n");
			}
		}
		
		/* last five seats */
		for(l; l < theseis + 1; ++l){
			fprintf(file, "%c", ((myBus[l - 1] == 0)? '_':'*'));
		}
		
		/* print info */
		fprintf(file, "\n");
		fclose(file);
		printf("Saved to file %s.\n", filename);
	}else{
		/* print errors */
		printf("Error opening file! %s\n", filename);
    	exit(1);
	}
}
