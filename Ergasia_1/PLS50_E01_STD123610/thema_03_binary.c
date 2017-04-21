#include <stdio.h>
#include <stdlib.h>

/*
* Christos Stavrakis
* A.M.: 123610
*
* Examination 1, exersise 3:
* Binary Presentation for a given number
*/


int main(int argc, char *argv[]) {
	
	int i, input_number;
	const int divider = 2;
	const int one_as_char = 49;
	const int zero_as_char = 48;
	
	do{
		
		/* Wait for user to give the number */ 
		printf("Give number (0 to quit): ");
		scanf(" %d", &input_number);
		
		 
		if(input_number < 0){ /* If number is negative return error message */
			printf("Give only positive numbers.\n");
			
		}else if(input_number == 0){ /* If number is zero exit programm */
			printf("Exit.\n");
			
		}else{ /* If number is positive, calculate the binary presentation  */
			printf("Binary number of %d is: ", input_number);
		
			for(i = 0; input_number > 0; ++i){ /* while number not 0, then divide him with 2 and take the modulo */
				putchar((input_number % divider == 1)? one_as_char : zero_as_char);  /* print proper character 1 or 0 */
				input_number /=  divider; /*reassign the input_number with the division of this numbrer by 2 */
			} /*  at the end the input number become zero, so the while it stops */
		}
		
	}while(input_number != 0);	
	
	return 0;
}
