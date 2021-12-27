#include <stdio.h>//
#include <string.h>//
#include <stdlib.h>//libraries used down
#define MAX_LENGHT 101// define the maximum length of object name that will be used for array size down


void part_lent(char *ident_arr_p,int *lenght);//function takes a string and send the lenght of one word or one node of it untill it finds eigther null or a space,it is used to pars the entry in the pars_the_object function
void entities_count(char *string,int *counter);//function takes a string of inputs and send the number of entities inside that string according to the white spaces between them to pointer coutner
void ignore_spaces(char *original_arr,char *new_arr);//function takes two arrays and ignores  white spaces between each entity from the orginal string  and minimize spaces to only one space and assigns it to second array new array
double pars_the_object(char main_ob[MAX_LENGHT],char node_p[MAX_LENGHT],char test[MAX_LENGHT],int *node_count);// the basic function takes  helper arrays and orginal array  and counter as a pointer  and parses  the entry recursivly till it finds the final result


//////////////Start of main function
int main(){

	double total;//helper var to print final resulte
	int i,j,node_count = 0,first_lenght = 0;//used in function call as indicator of the number encountered in pars_the_object function 

	char object[MAX_LENGHT];	//this array will hold name of  first object the basic object
	
	char node_p[MAX_LENGHT];
	node_p[0] ='\0';//declare node array  and initialize the first element of it to null to be used in function calls down
	
	char test[MAX_LENGHT];
	test[0] = '\0';//also declare helper array, test array  and initialize the first element of it to null to be used in function calls down
	
	char *first_name = malloc(sizeof(char*));// make allocating spaces for char pointer by using malloc to creat new cell in every new call
	

	
	printf("> Name the object:\n> ");
	
	fgets(object,MAX_LENGHT,stdin);
	strcpy(first_name,object);  	

   	total = pars_the_object(object,node_p,test,&node_count);
    first_lenght  = strlen(first_name);
    first_name[first_lenght-1] = '\0';

   	printf("> Total Cost of %s is %.2lf\n",first_name,total);
	free(first_name);


	return 0;
}


/////End of main function

////////////////////////////////////////////////////////////////////////////////////

void part_lent(char *ident_arr_p,int *lenght){//this function finds the lenght by increment i while there is no white space or null 

	int i = 1;
	
	while(ident_arr_p[i]!=' ' &&ident_arr_p[i]!='\0'){
		
		i++;
	}
	
	*lenght = i;	// after finish upper while assign the result to length
}

/////////////////////////////////////////////////////////////////////////////////////

void entities_count(char *string,int *counter){//this function counts number of entities in string by checking white spaces between

	int i = 0;

	while(string[i]!='\0'){

		if (string[i]==' '){
			
			*counter = *counter+1;
		}
	i++;
	}
	*counter = *counter+1;
}



/////////////////////////////////////////////////////////////////////////

void ignore_spaces(char *original_arr,char new_arr[MAX_LENGHT]){ //function takes two arrays and ignores  white spaces between each entity from the orginal string  and minimize spaces to only one space and assigns it to second array new array

	int i = 0,j = 0;
	int counter = 0;
	
	while(original_arr[i]!='\0'){

		if (original_arr[i]!=' ' || counter == 0){
			
			new_arr[j] = original_arr[i];

			if(original_arr[i]==' ' && original_arr[i+1]==' ' && counter == 0){
				
				counter = 1;
			}
			else{
				
				counter = 0;
			}
		j++;
		
		}
	i++;
	
	}
	
	new_arr[j] = '\0';
}

///////////////////////////////////////////////////////////

double pars_the_object(char main_ob[MAX_LENGHT],char node_p[MAX_LENGHT],char test[MAX_LENGHT],int *node_count){
	char ignored_spaces_node[MAX_LENGHT];
	ignored_spaces_node[0] = '\0';//this arr used to store the new  array after minimze spaces to only one 
	double total = 0.00,sum = 0.00;// helper var for last reslut
	int counter = 0,i = 0,j = 0,lenght = 0,temp_counter =1,lent= 0,main_lenght = 0;//hleper variables to use later 
	
	if (node_p[0] == '\0'){//this condition to print object's name at first call
		
		main_lenght = strlen(main_ob);
		main_ob[main_lenght-1] = '\0';

		printf("> Define %s?:\n> ",main_ob);
	}
	else if (*node_count == 0){//here if node_count = 0  that means we found number in prevoius call of func itself so it should print this message down
	
		main_lenght = strlen(test);
		test[main_lenght] = '\0';// here we put null for minus one because ,fgets takes string and it also includes newline char so to avoid that in printing we use this
		main_lenght = 0;

		printf("> Define %s in %s?:\n> ",main_ob,test );
	}
	else if (*node_count == 1){// that mean we didnt found number we found another strings so print the message down
		
		main_lenght = strlen(node_p);	
		node_p[main_lenght] = '\0';
		
		printf("> Define %s in %s?:\n> ",main_ob,node_p);
	}

	fgets(node_p,MAX_LENGHT,stdin);

	entities_count(node_p,&counter);// call this function to find count of entities in the given string 

	if (counter !=1){//in this condition if we found count is not 1 that mean we need to get into the status when we have more than one entity at least a pair entered or more 
		
		counter = 0;

		ignore_spaces(node_p,ignored_spaces_node);//ignore spaces in between by function call
		
		lent = strlen(ignored_spaces_node);//find lenght of ignored spaces array.
		ignored_spaces_node[lent] = '\0';//put null to the end of array.
		
		entities_count(ignored_spaces_node,&counter);//here call count of entities function to check number of enitites inside so we will perform according to that count 
		strcpy(node_p,ignored_spaces_node);//copy the  string.
	}
	if(counter == 1){//if we have only a number entered 

		
		sscanf(node_p,"%lf",&total);
		
		*node_count = 0;//set it to zero to endicate that I have found only a num so it will be used in the next iteration of recursive call.
		return total;//return resulte.
	}
	else{

		double num_arr[counter/2];//this array to hold the number
		int k = 0;
		char *nodes[MAX_LENGHT];//will hold each word parsed in it's each cell.
		
		while(k < counter/2){

			nodes[k] = (char*)malloc(sizeof(char*));

			k++;
		}
		*node_count = 1;

		while(temp_counter <= counter)//make parsing 
		{

			if (temp_counter % 2 == 1){//pars the numbers
				
				sscanf(node_p,"%lf",&num_arr[i]);				
				part_lent(node_p,&lenght);
								
				node_p =(node_p+lenght+1);
				temp_counter++;i++;

			}
			else if(temp_counter % 2 !=1){//pars the written part words part or object's components

				lenght--;
				
				sscanf((node_p+lenght-1),"%s",nodes[j]);
				part_lent(node_p+lenght,&lenght);
				
				node_p = node_p+lenght+1;
				temp_counter++;j++;
			}
		}

		i = 0;
		char test[MAX_LENGHT];//this one to print correctly and use correct components in the next call of recursive.
		strcpy(test,main_ob);
		
		while(i < counter/2){//call function again and again till we find the final resulte and return it  
		
			total = pars_the_object(nodes[i],main_ob,test,node_count) * num_arr[i];

			sum = sum + total;
			i++;
		}
		return sum; //return the final result
	}

}



/////////////////////////////////////////////////////////////VOILA!!