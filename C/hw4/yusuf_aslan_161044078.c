/* In this code I read values.txt and polynomial.txt files in main function  and then assign them into char arrays and then we use our func polynomial_calc
by giving the needed arguments and calculates the polynomial in each iteration, also our function checks for some combinations (in this hw they are five combinations 
there are 5 possibilities in  each monom and according to that ckecks  possible monom formats and calculates the monom and also calc the hole polynom and writes it into evaluation.txt file). */



#include <stdio.h>  
#include <math.h>   

#define VAL_SIZE 100	// value's inputs size
#define POL_SIZE 1000	// polynomial's inputs size 



void polynomial_calc(FILE *outp,double val_arr[POL_SIZE],char pol_arr[VAL_SIZE],char testarr[VAL_SIZE],int counter);



int main(){
	
	FILE *val,*pol,*outp;	//file pointers for files
	int status = 0,i = 0,each_time = 0,values_inputs;	//Helper variabels
	double val_arr[VAL_SIZE],num;	//Helper variabels
	char poll[POL_SIZE],test_arr[POL_SIZE],ch;	//Helper variabels

	val = fopen("values.txt","r");//open values file  in read mode 	
	pol = fopen("polynomial.txt","r");// open polynomial file in read mode also
	outp = fopen("evaluations.txt","w");//  open evaluations file in write mode to print tthe resualts into it

	while(!feof(val)){	//reading from the file values until the end of it 

		status = fscanf(val,"%lf",&num);
		
		if (status == 1){	// if there any error skip it dont take it
			
			val_arr[i++] = num;

		}
		
	}	//end of while loop which read values file



	values_inputs = i;// assign i  to values inputs 

	i = 0;	//reset i
	
	while(!feof(pol)){	// read file polynomial.txt until the end and store what u find in poll[] array
		
		status = fscanf(pol,"%c",&ch);	// to check if there are any error
		
		if (status == 1 && ch!= ' '){	// this condition to check to errors and to skip white spaces 
			
			test_arr[i] = ch;	//test_arr is array that store same like poll[] I used  it as a temp array to do operations in it
			poll[i] = ch;
			i++;			
		}

	}	//end of while loop which reads polynomial inputs
	
	poll[i] = '\0';	//set the end of poll array to null to avooid any errors and to know the end of string
	test_arr[i] = '\0';	//also set the end of test_arr array to null to avooid any errors and to know the end of string
	

	//in this while do the manipulation work to all values's inputs one by one till thhe end
	while(each_time < values_inputs){
		
	 	polynomial_calc(outp,val_arr,poll,test_arr,each_time);

	 	each_time++;
	
	}

	fclose(val);	//close values file
	fclose(pol);	//close polynomial file
	fclose(outp);	//close evaliuation file
	
	return 0;

}//////////////////////////////////////////end of main



// The down function takes output file as a pointer to print the resualtes to it 
//and also  it takes values arr to use it's numbers, and  polymonial array 
//which holds the polymonial form, and do the work for every value then print the resualte one by one

void polynomial_calc(FILE *outp,double val_arr[POL_SIZE],char pol_arr[VAL_SIZE],char testarr[VAL_SIZE],int counter)
{  
	//declalring helper variables to be used down
	int i = 0,status = 0,my_test = 0,k = 0,expo,lent;
	int founded1 = 0,founded2 = 0,founded3 = 0,founded4 = 0,sign_marked = 0;
	double result = 0,coo,total = 0;	
	char x,star,ch,tem_ch,first_char;


  
	while(pol_arr[i]!= '\0')	//this loop iterates untill the null charachter in our polynomial string                        
	{	
		

		if (i == 0){	//if statement execute only one and every fist time in each call of function to check if there is  any other sign at beggening of the polynomial ,if there is any sign then works according to that and mark as it found a differnt sign in the beggining of the corresponding polynomial and for that make down one execution about it.
			
			sscanf(&pol_arr[0],"%c",&first_char);//take first charracter of the polynomial.
			
			if (first_char == '-'){
			
				i++;
				k++;
				sign_marked = (-1);		
			}
			
			else if(first_char == '+'){
			
				i++;
				k++;		
				sign_marked = (1);
			}
		
		}		


		while((pol_arr[i]!='+' && pol_arr[i] != '-') && pol_arr[i]!='\0')//this loop iterates untill it encounters plus or minus sign or end of file.
		{
			status = sscanf(&pol_arr[i],"%lf%c%c%d",&coo,&x,&star,&expo);//takes a monom in the format of (ax^n) 


			if((status == 4) && (star == '^' && x == 'x' && pol_arr[i]!='\0')){	//first condition to check if we take the correct format then execute the inner part 
				
				while(testarr[k]!='+' && testarr[k] !='-'&&testarr[k]!='\0'){	//this loop which has been used in the last four conditions also play the importand rule of the program :it goes untill a + of - occured and finds its lent and store is in k and se used down as next starting poini of or val_arr[].

					k++;//length of each monum.
				}
			
				result = coo * pow(val_arr[counter],expo);	//result of each momon between any possible + and - sigh in  given polynomial
				
				if (pol_arr[k]!='\0'){	//takes one operator from pol_arr
			
					sscanf(&pol_arr[k],"%c",&ch); 
				}
			
				founded1 = 1;//	if we succssed to get desired format then mark as 1 so that we need not to check other combinitions in the certain iteration ;	
			}	//end of first condtion


			status = sscanf(&pol_arr[i],"%c%c%d",&x,&star,&expo);//2TH taking input from pol_arr[i] in the format (x^n);
			
			if(status == 3 && founded1 == 0 && x == 'x' && star == '^' && pol_arr[i]!='\0'){//if we are successd in takig input in the desired foramt so implement if
			
				if(status == 3 && pol_arr[i]!='\0'){
					
					while(testarr[k]!='+' && testarr[k] !='-' && testarr[k]!='\0'){//this loop's work has been described in the FIRST condition

						k++;//length of each monum.
					}
				}

				result = pow(val_arr[counter],expo);//result of each momon between any possible + and - sigh in  given polynomial
				
				if(pol_arr[k]!='\0'){
				
					sscanf(&pol_arr[k],"%c",&ch);//takes one operator from pol_arr
				}

				founded2 = 1;//if we succssed to get desired format then mark as 1 so that we need not to checkk other cobinitions in the certain iteration ;	
			}//end of second condition



			status = sscanf(&pol_arr[i],"%lf%c",&coo,&x);//takes a monom in the format of  (ax).
		
			if (status == 2 &&founded1 == 0 && x == 'x'&& star!='^'){//3TH condition to check if have success to take the monom in desired format.
				
				if(status == 2 && star!='^'&& x == 'x' && pol_arr[i]!='\0'){//also chechs the end of file
				
					while(testarr[k]!='+' && testarr[k] !='-'&&testarr[k]!='\0'){//has been described prevously.

						k++;//length of each monum.
					}
			
					result = (val_arr[counter] * coo);//result of each momon between any possible + and - sigh in  given polynomial
					if(pol_arr[k]!='\0'){
			
						sscanf(&pol_arr[k],"%c",&ch);//takes one operator from pol_arr
					}

				}
					
				founded3 = 1;//if we succssed to get desired format then mark as 1 so that we need not to checkk other cobinitions in the certain iteration ;				
			}//end of third condition.



			status = sscanf(&pol_arr[i],"%c",&x);//takes  a monom in the format of (x).
			
			if(status == 1 && founded2 == 0 && founded1 == 0 && x == 'x'&& pol_arr[i+1]!='^' && pol_arr[i]!='\0'){//4TH condition to check if have success to take the monom in desired format.			

				if(status == 1 &&founded1 == 0&&founded2 == 0&& x == 'x'&& pol_arr[i+1]!='^'&& pol_arr[i]!='\0'){//check also.

					while(testarr[k]!='+' && testarr[k] !='-' && testarr[k]!='\0'){

						k++;//length of each monum.
					}
				
					result = val_arr[counter];//result of each momon between any possible + and - sigh in  given polynomial

					if(pol_arr[k]!='\0'){
				
						sscanf(&pol_arr[k],"%c",&ch);//takes one operator from pol_arr
					}
									
				}
				founded4 = 1;//if we succssed to get desired format then mark as 1 so that we need not to checkk other cobinitions in the certain iteration ;	
			}//end of fourth condition.
					


			status = sscanf(&pol_arr[i],"%lf",&coo);//takes in the format of (a).

			if(status == 1 && founded1 == 0 && founded3 == 0 && founded2 == 0 && pol_arr[i]!='\0'){//5TH condition to check if we got the desired format from the array.

				if (status == 1 && pol_arr[i]!='\0'){	
				
					while(testarr[k]!='+' && testarr[k] !='-' && testarr[k]!='\0'){

						k++;//length of each monum.
					}
				
				}
		
				result = coo;//result of each momon between any possible + and - sigh in  given polynomial

				if(pol_arr[k]!='\0'){//takes the operator
				
					sscanf(&pol_arr[k],"%c",&ch);
				}
			}	//end of fifth condition




			if (my_test == 0){	//store the operator of the fist time to be used in the next itratiin  to add or subtract of tow next numbers whith the fist number. 
				
				if (sign_marked == 1){
				
					total  = result;		//monom's result to be used in the next iteration
					
				}
				else if (sign_marked == -1){
					
					total  = (-1) * result;		//monom's result to be used in the next iteration
					
				}
				else if (sign_marked == 0){

					total  = result;		//monom's result to be used in the next iteration
					
				}

				tem_ch = ch;					

			}
			else //this else will be operated or true the rest of monom till the end of polynomial in the certain itration
			{	
				if (tem_ch == '+'){//add two num if the sign is plus
					
					total = total+result;
					result = 0;
				
				}
				else if (tem_ch=='-'){//subtract two if the sign is minus.
					
					total = total - result;
					result = 0;
				
				}

				tem_ch = ch;
			}	// end of else 

			i = ++k;//points to the next monom's position in the pol_arr  array.
			
			my_test = 1;

			founded1 = 0;founded2 = 0;founded3 = 0;founded4 = 0;//setting them as zero so that to be used again in the next iterations.
		
		}

		fprintf(outp,"%.2lf\n",total);//assigning to the output file the final result.
		
		sign_marked = 0;	
		founded1 = 0;founded2 = 0;founded3 = 0;founded4 = 0;//setting them as zero so that to be used again in the next iterations.
			
	}	//end of first while loop	

}
///////////////////////////////////////////////end of function