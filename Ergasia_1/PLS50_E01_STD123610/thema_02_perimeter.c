#include <stdio.h>
#include <math.h> /* we need the M_PI , pow and sqrt functions */

/*
* Christos Stavrakis
* A.M.: 123610
*
* Examination 1, exersise 2:
* Calculate Perimeter of a given shape
*/

float calcSquarePerimeter (float);
float calcRectanglePerimeter (float, float);
float calcRightTrianglePerimeter (float, float);
float calcCirclePerimeter (float);
void printSquarePerimeter();
void printRectanglePerimeter();
void printRightTrianglePerimeter();
void printCirclePerimeter();



int main(int argc, char *argv[]) {
	
	char action;
	printf("This is a program that calculates perimeter for different geometric shapes \ngiven proper dimensions.\n");
	printf("Choose one of the following shapes, to calculate perimeter.\n");
	
	do{
	
		printf("0. Quit\n1. Square\n2. Rectangle\n3. Right Triangle\n4. Circle\n");
		scanf(" %c", &action); /* action should be char in order to handle the letters input, as a user's action. */
		
		/* Calculate perimeter for selected shape */
		if(action == '0'){
			break;
		}else if(action == '1'){
			printSquarePerimeter();
		}else if(action == '2'){
			printRectanglePerimeter();
		}else if(action == '3'){
			printRightTrianglePerimeter();
		}else if(action == '4'){
			printCirclePerimeter();
		}else{
			printf("Please give a valid choice..(0, 1, 2, 3 or 4)\n");
		}		
		
	}while(action != '0');
	
	return 0;
}

void printSquarePerimeter(){
	float side = 0;
	printf("Square: Dwse plevra:");
	scanf(" %f", &side);
	printf("Perimeter is: %.2f\n", calcSquarePerimeter(side));
}
void printRectanglePerimeter(){
	float length, width = 0;
	printf("Rectangle: Dwse mikos kai platos (e.g. 3.25 2.55):");
	scanf("%f %f", &length, &width);
	printf("Perimeter is: %.2f\n", calcRectanglePerimeter(length, width));
}
void printRightTrianglePerimeter(){
	float side1, side2 = 0;
	printf("Right Triangle: Dwse katheti_1 kai katheti_2 plevra (e.g. 3.25 2.55):");
	scanf("%f %f", &side1, &side2);
	printf("Perimeter is: %.2f\n", calcRightTrianglePerimeter(side1, side2));	
}
void printCirclePerimeter(){
	float rad = 0;
	printf("Circle: Dwse aktina:");
	scanf(" %f", &rad);
	printf("Perimeter is: %.2f\n", calcCirclePerimeter(rad));
}

/* Calculates square's perimeter, given the side */
float calcSquarePerimeter (float side){
	return 4 * side;
}

/* Calculates rectangle's perimeter, given the length and the width */
float calcRectanglePerimeter (float length , float width){
	return (2 * width) + (2 * length);
}

/* Calculates triengles's perimeter, given the two vertical sides */
float calcRightTrianglePerimeter (float side1, float side2){
	double ypoteinousa = sqrt(pow(side1,2) + pow(side2,2));
	return side1 + side2 + ypoteinousa;
}

/* Calculates circle's perimeter, given the two vertical sides */
float calcCirclePerimeter (float rad){
	return 2 * M_PI * rad;
}
