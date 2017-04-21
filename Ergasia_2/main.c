#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Christos Stavrakis
* A.M.: 123610
*
* Examination 2, exersise 1:
* Bus Presentation and Reservation Program V 2.0
*/

struct passenger {
	char *name;
	unsigned short telephone[10];
	unsigned int seat_num;
};


void readInitialDataFromFile(char *, char *, int *, struct passenger *);
void initializeBus(struct passenger *, int);

int main(int argc, char *argv[]) {

	int  input_choice;
	int  seats;
	char license[8] = {'\0'};
	char fileNameRead[] = "bus.txt";
	char fileNameWrite[] = "layout.txt";
	struct passenger myBus[seats];

	readInitialDataFromFile(fileNameRead, license, &seats, myBus);
	printf("%s %d\n", myBus[0].name, myBus[0].seat_num);


    do{
		/* Print initial choices for user */
		printf("1. emfanish synolikoy plhthous kenwn thesewn kai twn arithmwn tous\n");
		printf("2. krathsh theshs me sygkekrimeno arithmo\n");
		printf("3. anazhthsh gia to an einai krathmenh thesh me sygkekrimeno arithmo\n");
		printf("4. akyrwsh krathshs theshs me sygkekrimeno arithmo\n");
		printf("5. emfanish listas krathmenwn thesewn taksinomhmenhs kata arithmo theshs\n");
		printf("0. termatismos\n");
		scanf(" %d", &input_choice);

		switch(input_choice){
			case 1:
				//Show all seats
				break;
			case 2:
				//Reserve seat
				break;
			case 3:
				//Check seat reservation
				break;
			case 4:
				//Cancel reservation
				break;
			case 5:
				//Show Bus status
				break;
			case 0:
				// Prepare to exit
				break;
			default:
				printf("Please give a valid choice..(0 - 5)\n");
		}

	}while(input_choice != 0);

	return 0;
}


void readInitialDataFromFile(char *filename, char *license, int *bus_seats, struct passenger *bus){

	int chars = 64;
	int cur_line = 0;
	int cur_pass = 0;

	char line[chars];
	char onoma[20];
	char full_name[40];
	char epitheto[20];
	char telephone_num[10];
	unsigned int seat_num;

	FILE * file_in;
	file_in = fopen( filename , "r");
	if (file_in) {
		while(fgets(line, chars, file_in) != NULL ){
			if(cur_line == 0){
				sscanf (line, "%s %d \n", license, bus_seats);

				initializeBus(bus, *bus_seats);
			}else{
				sscanf (line, "%s %s %d %s \n",
					&epitheto,
					&onoma,
					&seat_num,
					&telephone_num
				);

    			strcpy(full_name, epitheto);
    			strcat(full_name, " ");
    			strcat(full_name, onoma);

				//strcpy(bus[seat_num].name, full_name);

				//bus[(int)seat_num].seat_num = seat_num;
				//strcpy(bus[seat_num].telephone, telephone_num);

				//bus[seat_num].telephone = ;
				//int i = 0;
				//for(i ; i < 10; ++i){
			    //	printf("%lu\n", telephone_num[i]);
				//}

			}
			cur_line++;
		}
	    fclose(file_in);
	}else{
		printf("Error opening file! %s\n", filename);
    	exit(1);
	}
}


void initializeBus(struct passenger *myBus, int theseis){

	struct passenger passenger_default = {
		"\0", {0,0,0,0,0,0,0,0,0,0}, 0
	};

	int i = 0;
	for(i ; i < theseis; ++i){
    	myBus[i] = passenger_default;
	}
	printf("Bus initialized.\n");
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
