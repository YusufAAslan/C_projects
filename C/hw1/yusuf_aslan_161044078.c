#include <stdio.h>

//Defining some macros to change it easily

#define CLASS1_COUNT 5			
#define CLASS2_COUNT 5

// I Defined this small  macro to avoid dividing by zero situations
#define AVOIDING_VALUE 0.011	






//Start of main function 

int main()
{

	//Declerate variables that will be use down in the code 
	double m , x , b ; 	// m :is the slop 
	double x1 = 0 , y1 = 0 , x2 = 0 , y2 = 0 , sum_of_x_in_class1 = 0 , sum_of_y_in_class1 = 0 , sum_of_x_in_class2 = 0 , sum_of_y_in_class2 = 0 ;
	double class1_x_cordinate , class1_y_cordinate , class2_x_cordinate , class2_y_cordinate ;
	double mid_x,mid_y , sep_line_slope , sep_line_b , sep_y , test_b , test_x , test_y ;
	double test_slope , equa_of_ave_point , equa_of_test_point ;
	int i = 0, j = 0 ,check = 0 , flag = 0; // will be use as a counters and checking conditions


	/*1.Find the average point for each class by taking sum of cordinates / count.  */	


	//Read class1 data from user and find sum of cordinates for class 1

	while(flag != CLASS1_COUNT)
	{

		printf("line %d > ",j);//Printing style  like in pdf example  

		scanf("%lf%lf",&class1_x_cordinate,&class1_y_cordinate);
		
		sum_of_x_in_class1 += class1_x_cordinate;// sum of x coordinates of calss1
		sum_of_y_in_class1 += class1_y_cordinate;// sum of y coordinates of calss1
		
		flag++;			
		j++;//Counter to count from zero to end of class1

	}



	//Read class2 data from user and find sum of cordinates for class 2

	while (i != CLASS2_COUNT)
	{
		
		printf("line %d > ",j);//Printing style  like in pdf example  
			
		scanf("%lf%lf",&class2_x_cordinate,&class2_y_cordinate);

		sum_of_x_in_class2 += class2_x_cordinate;// sum of x coordinates of calss2
		sum_of_y_in_class2 += class2_y_cordinate;//sum of y coordinates of calss2
		
		j++;//Counter to continue counting from end of class1 to end of class2
		i++;
	}

	x1 = sum_of_x_in_class1 / CLASS1_COUNT;//average point's x coordinate for class1.
	y1 = sum_of_y_in_class1 / CLASS1_COUNT;//average point's y coordinate for class1.
	
	x2 = sum_of_x_in_class2 / CLASS2_COUNT;//average point's x coordinate for class2.
	y2 = sum_of_y_in_class2 / CLASS2_COUNT;//average point's y coordinate for class2.

	////////////////////////////////////////////////////////////////////////////////////////



	/*2.Finding the line connecting the two average points by using this equation y  = mx + b)*/


	//Find the slope in 2 cases 

	if ((x2 - x1) == 0 && (y2 - y1) != 0)//In this condition we check zero situation in the denominator and avoid it
	{
		m = AVOIDING_VALUE;
	}
	else
	{
		m = ((y2 - y1)/(x2 - x1));// Normal equation of the slope of line between average points.
	}
	
	b = (y1 - (m * x1));	//finding value of b from the equation(y = mx + b).
	
	equa_of_ave_point = ((m * x1) + b);//line equation that links between two average points(y  = mx + b)
	//////////////////////////////////////////////////////////////////////////////////////////



	/* 3.Finding the midpoint cordinates of the connecting line*/
	
	mid_x = ((x1 + x2) / 2);//x coordeiate of midpoint.
	mid_y = ((y1 + y2) / 2);//y coordinte of midpoint.

	///////////////////////////////////////////////////////////////////////////////////


	/*4.Finding  the perpendicular separating line which passes through the midpoint.*/



	sep_line_slope = (1 / m) * (-1);//the slope fo the line seperating two average points(we take one over the slope of the line which is perpendicular to the seperating line and multiply of with minus one and)

	sep_line_b = (mid_y - (sep_line_slope * mid_x));
	
	sep_y = ((sep_line_slope * mid_x) + sep_line_b);//line equation for the seperating line which passes through midpoint.
	

	///////////////////////////////////////////////////////////////////////////////////


	//Input and output from user  and checking
	do 	//Loop to keep read and check until user enters an unusual input .
	{
		
		//printing style
		printf("line %d > ",j);

		//Read test point's cordinates from user and check if user enter 2  values or not  
		check = scanf("%lf %lf",&test_x,&test_y);

		if (check == 2)//condition to check whether did we get the correct inputs from the user or not.
		{
		
			test_slope = sep_line_slope;//slope of testing points and slope of the seperating line will be the same because the point that we are testing is in the same trajectory with the line seperating passess through midpoints.
		
			test_b = (test_y - (test_slope * test_x));//finding value of b from the equation(y = mx + b) for testing point.
			
			equa_of_test_point = ((test_slope * test_x) + (test_b));//equations of the test point (y = mx + b)			
			
			if (test_b > sep_line_b)//Condition to print class1.
			{

				printf("class1\n");
			}
			else if (test_b < sep_line_b)//Condition to print class2.
			{
				printf("class2\n");
			} 
		}

		j++;//And here dont forget to add 1 to counter j line counter
	}while(check == 2);




	
	return 0;
}



	// End of main function 
