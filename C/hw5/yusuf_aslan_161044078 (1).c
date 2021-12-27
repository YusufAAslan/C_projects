#include <stdio.h>
#include <string.h>
#define TEXT_LENGHT 250	//Define maximum text lenght as it said in pdf.
#define NODE_NAMES 10	//Define  maximum node name  lenght as it said in pdf.

void read_tree(FILE *inp,char text_arr[TEXT_LENGHT]);//this func will take inp pointer file and array ,so it will read and  fill the text array with input file's contenent
void ignore_left_spaces(char text_arr[TEXT_LENGHT],char copied_arr[TEXT_LENGHT]);//this func will take txt array and another array to ignore  white spaces on the left side till  it takes char
int ignore_right_spaces(char text_arr[TEXT_LENGHT],char copied_arr[TEXT_LENGHT],int lenght);//this func will ignore the white spaces at the end of any textfile in a line 
int pars_tree(FILE *out,char tree_arr[TEXT_LENGHT],char word_arr[NODE_NAMES],int parentes,int par,int spaces);//this func pars the newick tree representaion in the desired format in pdf  by useing recursion.
void print_sign(FILE *outp,int parentes);//this func prints - sign according to the number of it I used this func inside pars_tree func
void print_one_node(FILE *outp,char main_arr[TEXT_LENGHT],int *counter);//this func prints one node even if it is only one word,also used inside pars_tree function
void print_space(FILE *outp,int space);//this func prints spaces into output file according to the entry.


/////////////////////////////////////////////////////////////main func starts here  
int main(){

	FILE *inp,*outp;

	char node_arr[NODE_NAMES];//node array will hold only one word at a time
	char tree_arr[TEXT_LENGHT],cpy_arr[TEXT_LENGHT];//declare some helper arrays
	int arr_s = 0,par_count = 0,delete; //also helper variablers

	inp = fopen("input.txt","r");//open input file in read mode. 
	outp = fopen("output.txt","w");//also output file to print the results into it
	
	read_tree(inp,&tree_arr[0]);//function call,it returns the occurence number of'(' char in our array
	
	arr_s = strlen(tree_arr);//mesure the lenght of tree_arr and assign it 
	

	if(arr_s > 0){//if the file has input values.
	
		strcpy(cpy_arr,tree_arr);//make a copy of the tree_arr	
		ignore_left_spaces(&tree_arr[0],&cpy_arr[0]);//ignore left spaces  
		
		strcpy(cpy_arr,tree_arr);//make a copy of tree_arr	
		
		arr_s = strlen(tree_arr);//take lenght of new array.
		delete = ignore_right_spaces(&tree_arr[0],&cpy_arr[0],arr_s);//ifnore right spaces and take the new length
		
		tree_arr[delete] = '\0';//put null at the end ,while delete is  new size of the tree_arr after ignoring right and left side's spaces
	}
	
	pars_tree(outp,&tree_arr[0],&node_arr[0],par_count,0,0);// after ignoring spaces call pars tree function.

	fclose(inp);//close input file
	fclose(outp);//close output file
	
	return 0;
}
/////////////////////////////////////////////////////////////////end of main function.




///////////////////////read_tree func

void read_tree(FILE *inp,char text_arr[TEXT_LENGHT]){//read input file till the end of it and put the inputs in array of chars.

	int i = 0,status = 0;
	char ch;
	
	while(!feof(inp)){

		status = fscanf(inp,"%c",&ch); // check if we read correctly
		
		if(status == 1 && ch != '\n'){
		
			text_arr[i++] = ch;	
		}

	}
	text_arr[i]='\0';	// put null at the end of string
}
/////////////////////////////end of file reading 



//////////////////ignore left spaces func
void ignore_left_spaces(char text_arr[TEXT_LENGHT],char copied_arr[TEXT_LENGHT]){	//ignore the left side's spaces using recursion.

	if(copied_arr[0]!=' '){// base case go till u find char at the begining of the string.
		
		strcpy(text_arr,&copied_arr[0]);	
	}
	else{

		return ignore_left_spaces(text_arr,&copied_arr[1]);//call function itself with new index

	}
}



////////////////////////////////end of ignor left spaces func





///////////////////// ignore right spaces function
int ignore_right_spaces(char *text_arr,char *copied_arr,int lenght){ // like above

	
	if(copied_arr[lenght-1]!=' '){	// base case 
		
		return lenght;//when it be here rturn lenght of spaces u find at the end of teksen string 
	}
	else{
		
		lenght = ignore_right_spaces(text_arr,copied_arr,lenght-1);//call function recusrsivly and assign lenght the new value
		return lenght;
	}

}
///////////////////////////////end of ignore right funcition.




//////////////
/////////////
///////////////////////////////////////////////////start of pars tree function !!

int pars_tree(FILE *out,char *tree_arr,char word_arr[NODE_NAMES],int parentes,int par,int spaces){//This is the monster function//this function parses the array which hold the newick represented tree by takeing illestraded data as input and then it prints the resulte into output file,where it calls itself acording to the given input files content ,and we call inside this func other helper functions to do the desired mission also it checks for some known combinitions and manipulates the given array according to that

	int counter = 0;
	
	if (tree_arr[0]=='\0'){//if we reach  end of file then terminate the function and return
		
		return 0;
	}
	else{//else check the combinations till reach to the end of file.

		if(tree_arr[0] =='('){//if certain value is left faced comma then do this
			
			pars_tree(out,&tree_arr[1],word_arr,++parentes,1,0);
			word_arr[0] = '\0';
			
			return 0;
		}
		else if (tree_arr[0] == ')'){
			
			pars_tree(out,&tree_arr[1],word_arr,--parentes,1,0);//call itself after updating input values of it
			word_arr[0] = '\0';
			
			return 0;
		}
		else if (tree_arr[0] == ','){
			
			pars_tree(out,&tree_arr[1],word_arr,parentes,1,0);//call itself after updating input values of it
			word_arr[0] = '\0';
	
			return 0;
		}
		else if (tree_arr[0] == ' ' && (par == 1)){
			
			spaces++;//increment space 
			
			if(tree_arr[1]!= ' '){

				pars_tree(out,&tree_arr[1],word_arr,parentes,0,spaces);//call itself after updating input values of it

			}
			else{
				
				pars_tree(out,&tree_arr[1],word_arr,parentes,1,spaces);//call itself after updating input values of it

			}

		}	
		else{

			if (spaces!= 0){////// check if we have spaces after prantheses before reaching to any character.
			
				print_sign(out,parentes);//call funciton print_sign
				print_space(out,spaces);//also call function print spaces.

			}
			else{

				print_sign(out,parentes);//call funciton print_sign

			}

			print_one_node(out,&tree_arr[0],&counter);//call function printf_one_node
			
			if(tree_arr[1]!='\n')
			{
			 	fprintf(out,"\n");

			 }
			
			pars_tree(out,&tree_arr[counter],word_arr,parentes,0,0);//call itself after updating input values of it
			
			word_arr[0]='\0';
			return 0;///////////if we reach here then we did it so return 0.
		}	
	}
}

/////////////////////////////////////////end of pars tree function




///////////////////////////////////////////start of print this sign (-) function 

void print_sign(FILE *outp,int parentes){//funciton which takes output file as a pointer and takes number of (-) we find and print every sign recursivley as it neccessary

	//base case
	if (parentes == 0){

		return;
	}
	else{

		fprintf(outp,"-");//if u here then print (-) into output file.
		print_sign(outp,--parentes); // and call with new index
	}
	return;

}


//////////////////////////////////////end of print (-) sign function




/////////////////////////////////////////////////////// start of print one node function

void print_one_node(FILE *outp,char *main_arr,int *counter){//funciton which takes output file pointer and the main array where we  holde the actual newick tree and returns the lenght of a node so in the next iteration in callling can start from the desired index


	if(main_arr[0] == '\0' || main_arr[0] == '(' || main_arr[0] == ')' || main_arr[0] == ','){// base ecase iterate untill one of these characters as been found
		
		return ;
	}
	else{

		
		fprintf(outp, "%c",main_arr[0]);//if u are here then print into output file
		
		*counter  =*counter + 1;//also incerement the counter pointer  by 1 .
		print_one_node(outp,&main_arr[1],counter);//call function itself again with new indexes.
		
		return;
	}

}



//////////////////////////////////////////////////end of print one node function 





//////////////////////////////////////// start of print space function 


void print_space(FILE *outp,int space){//this function creats space according to given space index
	
	if (space == 0){	// base case to stop

		return;
	}
	else{

		fprintf(outp," ");//if u here then print into output file.
		print_space(outp,--space);// call function with new index by -1
	}
	return;

}
///////////////////////////////////end of print space function




/////////////////////////////////////////////////////////////////////END OF HW/////// VOILAAAAA !!