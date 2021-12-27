/*  In this homework  I wrote 3 functions :
1)count_the_inputs: which read the file untill the end and return the 
count of the inputs as a integer number to use it for array's size later.

2) Then in  function main I did reading and conditions checking works

3)print_to_file: in this function I print the resultes to output file 		 */




#include <stdio.h>
#define p1 0.5
#define p2 20


// This function to count  the inputs from file to know what size should be my arrays
int count_the_inputs(int inputs_count);	

// I made the reading and checking work in main 


// This function to print the results to output file
void print_to_file(int inputs,double chunks[inputs][inputs],int tmp_arr[],int size,FILE *output,double chunks_average[inputs]);



int main(){
	


	FILE *input; //Input pointer file
	FILE *output;//output pointer file
	



	// First find count of inputs to make array in that size



	int input_size = 0;
	int inputs_count = 0;

	input_size = count_the_inputs(inputs_count) * 10;	



	int i = 0,j = 0,counter = 0,counter_for_array = 0,nth_num = 1;
	int number = 1,old_index[input_size],flag = 0,status = 0;
	int size_i = 0; // this counter to count the inputs

	double n,a = 0.0,b = 0.0,temp_sum = 0.0;   // for the equation condition
	double chunks_array[input_size][input_size];//Array to store chunks's elments
	double chunks_average[input_size];//This helper  array  to store the chunks's averages

	input = fopen("input.txt","r");//open file  in read mode to read from it 
	output = fopen("output.txt","w");//open file in write mode to write into it



	/////////////////////////////////////////////Reading the file and check the conditions /////////////////////////
	while(!feof(input))//loop to read input file until the end of file
	{	
	
		if (flag == 0){
		
			fscanf(input,"%lf",&n);

			size_i++;

		}		
			
		a = n/nth_num++;//at the start we assign to a the first number of the chunks 
		
		chunks_array[i][j++] = n;//and then assign it to the array  

		fscanf(input,"%lf",&n);//get another number from the file
		size_i++;
			
		b = (a + n)/nth_num++;//and calculate the average b here
			
		temp_sum = a + n;//to calculate  the sum of the numbers in the chunks	
		
		while(!(b > (a*(1 + p1))|| b < (a*(1 - p1)) || a > (n*p2)|| a < (n/p2)) && (!feof(input)))// condition to check end of file and condition from pdf to decide if I have to add number to  chunk or not
		{
	
			chunks_array[i][j++] = n;
			
			a = b;//assign last value of b to a.
			
			status = fscanf(input,"%lf",&n);
						// printf("n: %lf\n",n );

			size_i++;

			
			if (status==1)
			{

				// chunks_array[i][j++] = n;

				
				status = 0;
	
				temp_sum = temp_sum + n;// sum of numbers
				
				b =((double)(temp_sum)/(double)nth_num++);// put b is the new average 				
			
				if (!(b > (a*(1 + p1))|| b < (a*(1 - p1)) || a > (n*p2)|| a < (n/p2))){	//  This condition to look and  check   the next scanf whether it should be taken  or not
						
					flag = 0;

				}
				else{	//otherwise I put a flag to check and decide to take the first or the  second scanf in the next iteration.
					
					flag = 1;
				}		

			}

			if (size_i == input_size / 10)	// to take the last value also and add it to avg
			{
				a=b;
			}


			
		}
		
		chunks_average[counter_for_array] = a;//this array which is integer array collects the all average of the chunck in corresponding cells 

		a = 0;
		b = 0;
		j = 0;
		
		nth_num = 1;//this variable to count the count of numbers in each iteration.
		counter_for_array++;
		i++;
		
	}

	// printf("%d\n",size_i );
	for (i = 0; i < input_size;++i)//filling array from 0 to input size contiguously.
	{
		
		old_index[i]= i;

	}

	//////////////////////////////////////////////////////////////////End reading file and checking works ////////////






	print_to_file(input_size, chunks_array,old_index,counter_for_array,output,chunks_average);	// print the results to output file 

	fclose(input);	// Ofcours dont forget closing files.
	fclose(output);	//closing files.

	return 0;
}



int count_the_inputs(int inputs_count){
	FILE *input; //Input pointer file

	inputs_count = 0;
	double anything = 0.0;

	// firstly read hall file to count how many inputs we have and calculate the size of arrays we will need
	input = fopen("input.txt","r");//open file  in read mode to read from it 
	while(!feof(input)){
		fscanf(input,"%lf",&anything);
		inputs_count++;

	}
	fclose(input);	// Ofcours dont forget closing files.

	// printf("%d\n",inputs_count);
	return inputs_count;


}



void print_to_file(int inputs ,double chunks[inputs][inputs],int tmp_arr[],int size,FILE *output,double chunks_average[inputs]){

	int i,j;
	int counter = 0;//Helper counter to find the index of the number which we should store in the output file 
	
	while(counter!=size)//This loop iterates untill we completly store the all desired values of the required array's data.
	{
		
		for ( i = 0; i < inputs; ++i)//this loop iterates for each cell of the old_index array to find which  values of it mathces with the i.
		{
					
			if (i == tmp_arr[counter])
			{

				for ( j = 0; j <=size; ++j)
				{
					if (chunks[i][j] !=0)
					{
						if (chunks[i][j] * chunks [i][j] > 0) // this condition to prevent other unwanted things
						{
							fprintf(output, "%.4lf ",chunks[i][j]);//print the result to the output file.
						}
					}
				
				}
				
				fprintf(output,"average:%.4f \n",chunks_average[i]);
			}
		}
	
		counter++;	
	}

}




///////////