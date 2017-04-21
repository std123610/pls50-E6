#include <stdio.h>
#include <string.h>

/*
* Christos Stavrakis
* A.M.: 123610
*
* Examination 1, exersise 1:
* Calculate the arithmetic operation between two numbers
*/


int main(int argc, char *argv[]) {
	
	int error = 0;  /* error counter */
	float x, y, result; /* input variables x,y and result of the operation, are all float numbers */
	char myOperator, *err_message;  
	
	
	/* Print proper message and take input variables */ 
	printf( "\nDwse: arithmo praksi arithmo (e.g. 3 + 2) \n" );
	/* Take the two input numbers plus the operator */
	scanf( "%f %c %f", &x, &myOperator, &y );

	/* Choose and perform operation, according the given operator and input variables */
	if(myOperator == '+'){  
		result = x + y;
	}else if(myOperator == '-'){
		result = x - y;
	}else if(myOperator == '*'){
		result = x * y;
	}else if(myOperator == '/'){
		if(y == 0.0){   /* you cannot devide by zero! */
			++error;    /*  increase by one the error counter */
			err_message = "Division by zero!";
		}else{
			result = x / y;  
		}
	}else{
		++error;  /* the operator is not proper, so increase by one the error counter */
		err_message = "Not a proper arithmetic operator!";
	}
	
	/* Handle Error Messages */
	if(error == 0){ /* if error counter is zero */
		printf( "Result: %.2f",  result); /* Print result with two decimal digits */
	}else{  /* else */
		printf( "Error: %s",  err_message); /* Print error message */
	}
		
	return 0;
}
