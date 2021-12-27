/*In this code I  read all the contents of input2.txt and put them in 2d array called 
temp[][]Then I read all the contents from input1.txt word by word and every word I read 
I assign it to array called word_arr character by character after that I take 
this word array and compare it with the contents of temp[][] and search if the 
word is exist at first horizontally if not then search vertically and when I find it
horizontally or vertically I save the position into two variabels one called row
and the other called column and then I print every found word with it's position 
to output.txt file */


#include <stdio.h>
#include <string.h>
					// Here is the macros we can change them as we want 	
#define COLUMN_INDEX 250	//Maximum length of each row is 250
#define ROW_INDEX 100	//Maximum number of rows is 100
#define WORD_LENGTH 10 //Maximum word length is 10 characters.

int check_horizontally(char word_arr[WORD_LENGTH],char temp[ROW_INDEX][COLUMN_INDEX],int row_size,FILE *outp);//This function like I said up it takes array for the word we need to find ,and 2D array which contain the contents we will search insid it,and variabel called row_size to know how many line we have in input2 ,and if we find the word  then print it to output file which I have it's pointer 
int check_vertically(char word_arr[WORD_LENGTH],char temp[ROW_INDEX][COLUMN_INDEX],int row_size,FILE *outp);//This function works similar to the previous one but it will look vertically



//////////////////////////////////////////////main function  starts here
int main(){

	
	FILE *inp1,*inp2,*outp;			//File pointers to open files

	inp1 = fopen("input1.txt","r");//open input1 file in read mode
	inp2 = fopen("input2.txt","r");//open input2 file in read mode 
	outp = fopen("output.txt","w");//open output file in write mode
	
	char word_arr[WORD_LENGTH];		// this array to save the wanted word
	char temp[ROW_INDEX][COLUMN_INDEX];//and this array to save the contents of input2 file as 2D array 
	char ch; // this variabel to read charachter

	int i = 0,j = 0;
	int cursor = 0 ,row_size =  0;	// helper variabels  //cursor to trace and if we find the wanted number it will be 1
	
	while(!feof(inp2)){	// this while to read and save the contents of input2.txt into our 2D array 
		
		fscanf(inp2,"%c",&ch);//char by char 
		
		while (ch!='\n')//go untill you find a new line
		{

			temp[i][j] = ch;
			fscanf(inp2,"%c",&ch);
			
			j++;	// add one to the current column
		}	//end of inner loop
		
		i++;	// add one to the current row
		j = 0;	// reset column position
		row_size++;// increment row_size by one
	
	}//edn of outer loop
	
	i = 0;	// after finishing work in the previous two loops  reset i 
		
	while(!feof(inp1))//this while to read input1.txt untill the end of file
	{
		
		fscanf(inp1,"%c",&ch);	// also char by char
		
		while (ch!='\n'){//while the given char is not new line take it and save it in word_arr[]

			word_arr[i] = ch;
			
			fscanf(inp1,"%c",&ch);		
			
			i++;	// after saving the char increment i to save new char
		}
		word_arr[i] = '\0';//after reading all wanted word from input file put null at the end to tell us the end of string.
				
		cursor = check_horizontally(word_arr,temp,row_size-1,outp);// here we call check horizontally to search for the wanted word horizontally if it return 1 then the wanted word was found and make var cursor = 1 so no need to look vertically
		
		if (cursor!= 1)	// here check if cursor still zero then you have to look vertically to find the wanted word 
		{
			check_vertically(word_arr,temp,row_size,outp);

		}

		i = 0;// at the end of every iteration dont forget to reset i because it will be used in the next iteration as the first element of the word_arr[].
	}

	fclose(inp1);//close input1 file.
	fclose(inp2);//close input2 file.
	fclose(outp);//close output file.

	return 0;
}
//////////////////////////////////////////////////////////////end of main function




int check_horizontally(char word_arr[WORD_LENGTH],char temp[ROW_INDEX][COLUMN_INDEX],int row_size,FILE *outp){	// check_horizontally  function implimentaion


	int row = 0,col = 0,i = 0,j = 0;
	int counter = 0,flag = 1;	// helper variabels
	char temp_ar[WORD_LENGTH];
	char column = 0;




	while (row_size!= 0){	//while loop to search for the wanted word line by line horizontally in our 2D array
		
		row_size--;	// decrement row count to look in the next line till 0

	 	while(temp[row][col]!='\0'){	//this loop goes till the end of every line or  it return 1 the word was found 
			
			if (word_arr[counter] == temp[row][col]){	// this condition to check if the current char is same in every strings if yes then look to next char 
				
				temp_ar[counter] = word_arr[counter];//store the char to temp array.
				counter++;	//and go to the next char in array word_arr[].
				col++;//also go to te next char in the 2D arr which we look inside it temp[][].
				flag = 1;//successfully stored a char to the array temp_ar.

				while (flag == 1){//loop which iterates till the flag is 1 and that mean that we found the wanted word
			
					if(word_arr[counter] == temp[row][col] && ((strlen(&word_arr[counter]))!= 0)){	//this if check if all chars  are same and word_arr not zero yet
					
						temp_ar[counter] = word_arr[counter];//store the current char into temp_ar

						counter++;
						col++;
						flag  = 1;	// that mean still same chars
					}
					else{	//else then  go to the loop and iterat again to look in other place 

						flag = 0;
					}

				}//end of inner loop

				if (flag == 0 && (strlen(&word_arr[counter]))== 0){//if we have succefully found  the word and we know where it starts then  print the word and it's position to output file and return 1
					
					row++;// becuase we start indexes from one in this homework  I incremented the coordinates of  row and column by one
					column++;
					temp_ar[counter] = '\0';// and dont forget to put null to the end of the chars so that can be stored correctly in anywhere.
										
					fprintf(outp,"%s (%d,%d) Horizontal",temp_ar,row,column);//printing the word and it's position to output file.
					fprintf(outp,"\n"); // print new line 
					
					return 1;
				}
				
			}//end of outer if statement.
			else//if you didnt find the word then reset counters and  increment the column and go look again to privious conditions
			{
				counter = 0;
				column++;
				col = column;
			}

		}//end of the first inner loop
	
		counter = 0;
		row++;//look to next row
		column = 0;// and start from the start of the new line
		col = column;//assign it to the first colunm of the current row
	
	}//end of the outer loop
	return 0;
}


////////////////////////////////////////////////////////end of check horizontally






int check_vertically(char word_arr[WORD_LENGTH],char temp[ROW_INDEX][COLUMN_INDEX],int row_size,FILE *outp){	// check vertically function's body and implimentation


	int row = 0,col = 0,i = 0,j = 0;
	int counter = 0,flag = 1;
	int row_length,count = 0,current_row = 0;
	char temp_ar[WORD_LENGTH];
		
	while(row_size!=0 && row_size >= (strlen(word_arr)))//while loop iterates untill the end of rows.
	{
		
		row_size--;//increment row size to go to the next line to look inside it
		
		row_length = strlen(&temp[count][0]);//I take in every iteratiin the current line's lenght so it searchs vertically untill that lenght end  		
		
		while (row_length!= 0)//this while loop will iterate untill the end of the current row char char  .
		{
			

		 	while(temp[row][col]!= '\0')	// check if it's null
			{
				
				if (word_arr[counter] == temp[row][col])	//look if  the current char in both of the arrays is same then enter to the if statement
				{
					
					temp_ar[counter] = word_arr[counter];	//if we find same char then you have to  store it to temp array.
					
					row++;
					counter++;
					flag = 1;//that mean we found the char and saved it to array
					
					while (flag == 1)
					{
				
						if(word_arr[counter] == temp[row][col] && ((strlen(&word_arr[counter]))!= 0)) 
						{
						
							temp_ar[counter] = word_arr[counter];

							counter++;
							flag  = 1;	// that mean still chars are same of both arrays
							row++;
						
						}
						else 
						{
							flag = 0;
						}

					}
					if (flag == 0 && (strlen(&word_arr[counter]))== 0)//if we find the wanted word in the our 2D array  then  print it to output file and  return 1
					{
						
						temp_ar[counter] = '\0';
						current_row++;
						col++;
										
						fprintf(outp,"%s (%d,%d) Vertical",temp_ar,current_row,col);// print the word and it's position to output file
						fprintf(outp,"\n");
						
						return 1;	// The word has been found!

					}
				
				}
				else//if  the current chars is not same then go to the next char in the current row
				{
				
					counter = 0;
					current_row++;
					row = current_row;
					
				}

			}//end of inner loop
		
			counter = 0;
			col++;
			current_row = 0;
			row = current_row;
			row_length--;
		
		}//end of fisrt inner loop
		
		count++;
	}//end of outer loop
	return 0;
}
/////////////////////////////////////////////////////////end of check_vetically function.



////////////////////done!!!!