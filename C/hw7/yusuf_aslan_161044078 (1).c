#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WORD_SIZE 10//Each identifier is unique. Max length of each identifier is 10 chars
#define MAX_SIZE_OF_LINE 100 //Assume that the max length of input lines will be 100 to avoid any overflow and segmentation fault including spaces and input chars  	


struct node{
	
	char gate_type[WORD_SIZE];
	char input_name1[WORD_SIZE];
	char input_name2[WORD_SIZE];
	char output_name[WORD_SIZE];
	
	int input1;
	int input2;
	int output;
	int previous_output;

	struct node *input1p;
	struct node *input2p;
};



void put_inputs_into_arr(FILE *inputf,int arr[],int size);//This function will take input file and gives filled array with it's each line from input file  ,so that will be used in each iteration 
void link_between_structs(struct node **p_to_structs,int inp_limit,int limit);//this function will link the array of structs with it's desired data
void fill_structp(char testarr[][MAX_SIZE_OF_LINE],int my_array[],int size,struct node **arrp,int line_size,int inp_elemnts_count);//function fill the pointer to structure array by certain inputs 
int lines_counter(FILE *inp,int *size);//This function reads input file and returns count of lines in circuet.txt file
void find_partial_length(char *arr,int *lenght);//finds the lenght untill encounters white spaces.
int calculate_given_circuit(struct node *gates_p,int *keep_prev_outp);//this function will calculate the given circiut and retrun the resulte to print  




/////////////////////////////////////////////main start here
int  main(){
	
	FILE *circiut_p,*inp_p,*out_p;
	
	int i = 0,j = 0,count = 0,input_lenght = 0,prev_prev = 0;	
	int make_alloc = 0,result;
	
	circiut_p = fopen("circuit.txt","r");
	inp_p = fopen("input.txt","r");
	out_p = fopen("output.txt","w");

	input_lenght = lines_counter(circiut_p,&count);//get the count of the lines in circiut file.

	make_alloc = input_lenght + count;//alocation limit 	
	int inputarray[input_lenght];//input array used down
	int inputarray_keep[input_lenght];
	
	inputarray_keep[input_lenght] = '\0';
	inputarray[input_lenght] = '\0';

	struct node **gates_p = (struct node**)malloc(sizeof(struct node) * make_alloc);//allocate spaces for certain structure type pointers in  the heap.
	gates_p[make_alloc] = NULL;
	
	circiut_p = fopen("circuit.txt","r");//reopen the file again to be used .
	
	char *pointer = (char*)malloc(sizeof(char));
	char keep_arr[count][MAX_SIZE_OF_LINE];
	
	while(!feof(circiut_p)){//fill the array from the datas of circiut.txt so that we can avoid reopening it again and again.
		
		fscanf(circiut_p,"%[^\n]\n",&keep_arr[i][0]);
		i++;
	}
	i = 0;
	while(!feof(inp_p)){//loop iterates till EOF which is input.txt in this case.

		j = 0;
		strcpy(pointer,keep_arr[count]);//copying the last line of array so that avoid any garbage values and bad effect of result .
		
		put_inputs_into_arr(inp_p,inputarray,input_lenght);//get the each line of input file in each iteration 
		for (int man = 0; man < input_lenght; ++man){
			inputarray_keep[man] = inputarray[man];
		}

		strcpy(keep_arr[count],pointer);
		
		fill_structp(keep_arr,inputarray,input_lenght,gates_p,count,input_lenght);//fill the structs from the circiut.txt with appropriate gates' details

		while(j < input_lenght){//set the world INPUT to all of the input entities.
		
			strcpy(gates_p[j]->gate_type,"INPUT");
			j++;
		
		}
		j = 0;
		while(j < make_alloc){
			
			if (0 == strcmp(gates_p[j]->gate_type,"FLIPFLOP"))
			{
			
				gates_p[j]->previous_output = prev_prev;
				break;
			}
			j++;
		}

		link_between_structs(gates_p,input_lenght,make_alloc);
		result = calculate_given_circuit(gates_p[make_alloc-1],&prev_prev);
		
		fprintf(out_p,"%d",result);
		
		if (!feof(inp_p)){//to ignore ,do not print newline (extra newline a the end of the file while writing..
			fprintf(out_p,"\n");
		}
	}

	fclose(inp_p);
	fclose(circiut_p);
	fclose(out_p);
	free(gates_p);	
	
	return 0;
}
////////////////////////////////////////////////////////////End of main!!!!

//////////////////
void put_inputs_into_arr(FILE *inputf,int arr[],int size){//take the input values and assign them  into array.

	int i = 0;
	
	while(i < size){

		fscanf(inputf,"%d",&arr[i]);
		i++; 
	}
}//End of function

/////////////////
void link_between_structs(struct node **p_to_structs,int inp_limit,int limit){//this function takes the pointer to structure type in which each pointer cell point to a corresponding struct and also limit size to be evaluated and links each structure with it's corresponding one

	int i = 0;
	
	while(inp_limit < limit){//iterate till the end of array of pointer to structurs.
			
		if(0 == strcmp(p_to_structs[inp_limit]->gate_type,"OR")){//if it is and or or gate then do this >> 

			i = 0;			
			while(i < inp_limit){//find or inputs

				if (0 == strcmp(p_to_structs[inp_limit]->input_name1,p_to_structs[i]->output_name)){

					p_to_structs[inp_limit]->input1p = p_to_structs[i];
					break;
				}
				i++;
			} 	
			i = 0;
			while(i < inp_limit){
				
				if (0 == strcmp(p_to_structs[inp_limit]->input_name2,p_to_structs[i]->output_name)){

					p_to_structs[inp_limit]->input2p = p_to_structs[i];
					break;
				}
				i++;
			}
		}
		else if( 0 == strcmp(p_to_structs[inp_limit]->gate_type,"AND")){
			i = 0;			
			while(i < inp_limit){//find AND inputs

				if (0 == strcmp(p_to_structs[inp_limit]->input_name1,p_to_structs[i]->output_name)){

					p_to_structs[inp_limit]->input1p = p_to_structs[i];
					break;
				}
				i++;
			} 	
			i = 0;
			while(i < inp_limit){
				
				if (0 == strcmp(p_to_structs[inp_limit]->input_name2,p_to_structs[i]->output_name)){

					p_to_structs[inp_limit]->input2p = p_to_structs[i];
					break;
				}
				i++;
			}
		}
		else if (0 == strcmp(p_to_structs[inp_limit]->gate_type,"NOT") ||0 == strcmp(p_to_structs[inp_limit]->gate_type,"FLIPFLOP")){//if it is flipflop or not gate then do this >>
			i = 0;

			while(i < inp_limit){//find the flipflop's and not's inputs

				if (0 == strcmp(p_to_structs[inp_limit]->input_name1,p_to_structs[i]->output_name)){
				
					p_to_structs[inp_limit]->input1p = p_to_structs[i];
				}
				i++;
			}//end of while
		}//end of else

		inp_limit = inp_limit+1;
		i = 0;

	}//end of outer loop

}//End of function


////////////////////
void fill_structp(char testarr[][MAX_SIZE_OF_LINE],int my_array[],int size,struct node **arrp,int line_size,int inp_elemnts_count){

	char first_line_name[WORD_SIZE];
	char one_word[WORD_SIZE];
	int one_value,i = 0,j = 1,input_vals = 0;
	
	int portion = 0,keep_portion = 0;//these two used to keep track of indexs in each line.

	sscanf(testarr[0],"%s",first_line_name);//holds the word 'INPUT'	
	find_partial_length(testarr[i],&portion);//finds the lenght untill encounters white spaces.
	keep_portion += portion;

	while(i < inp_elemnts_count){//this fills the struct with inout line desired vals.

		struct node *one_struct = (struct node*)malloc(sizeof(struct node));

		(one_struct+i)->input1p = NULL;//nodes of the input line which must be null in this case...
		(one_struct+i)->input2p = NULL;//nodes of the input line which must be null in this case...

		strcpy((one_struct+i)->gate_type,"INPUT");//input gate name.
				
		sscanf(&testarr[0][keep_portion],"%s",one_word);//input strigns names.		
		find_partial_length(&testarr[0][keep_portion],&portion);//finds the lenght untill encounters white spaces.
		keep_portion += portion;

		strcpy((one_struct+i)->output_name,one_word);
		(one_struct+i)->output = my_array[i];
		my_array[size] = '\0';
	
		*(arrp+i) = (one_struct+i);//copy the structure to main one .>> 
		i++;	
	}
	while(j <= line_size){//fills the strcts with varous gates types >>> 
		
		keep_portion = 0,portion = 0;
		struct node *one_struct = (struct node*)malloc(sizeof(struct node));		
		
		sscanf(testarr[j],"%s",first_line_name);
		find_partial_length(testarr[j],&portion);
		keep_portion += portion;
				
		if (0 == strcmp(first_line_name,"AND")){//end gate to be filled
			
			(one_struct+i)->input1p = NULL;
			(one_struct+i)->input2p = NULL;

			strcpy((one_struct+i)->gate_type,first_line_name);//input gate name.
			
			sscanf(&testarr[j][keep_portion],"%s",one_word);
			strcpy((one_struct+i)->output_name,one_word);
			
			find_partial_length(&testarr[j][keep_portion],&portion);
			keep_portion += portion;
			sscanf(&testarr[j][keep_portion],"%s",(one_struct+i)->input_name1);
			

			find_partial_length(&testarr[j][keep_portion],&portion);
			keep_portion += portion;
			sscanf(&testarr[j][keep_portion],"%s",(one_struct+i)->input_name2);

			*(arrp+i) = (one_struct+i);//copy the structure to main one .>> 

		}
		else if (0 == strcmp(first_line_name,"OR")){//condition ot or gate to be filled
			
			keep_portion = 0,portion = 0;
			(one_struct+i)->input1p = NULL;
			(one_struct+i)->input2p = NULL;

			strcpy((one_struct+i)->gate_type,"OR");//input gate name.
			
			find_partial_length(&testarr[j][keep_portion],&portion);
			keep_portion += portion;
		
			sscanf(&testarr[j][keep_portion],"%s",(one_struct+i)->output_name);
			find_partial_length(&testarr[j][keep_portion],&portion);
			keep_portion += portion;

			sscanf(&testarr[j][keep_portion],"%s",(one_struct+i)->input_name1);
			find_partial_length(&testarr[j][keep_portion],&portion);
			keep_portion += portion;


			sscanf(&testarr[j][keep_portion],"%s",(one_struct+i)->input_name2);

			*(arrp+i) = (one_struct+i);//copy the structure to main one .>> 

		}
		else if (0 == strcmp(first_line_name,"NOT")){//not gate to be filled
			
			keep_portion = 0,portion = 0;
			
			(one_struct+i)->input1p = NULL;
			(one_struct+i)->input2p = NULL;

			strcpy((one_struct+i)->gate_type,first_line_name);//input gate name.
			
			find_partial_length(&testarr[j][keep_portion],&portion);
			keep_portion += portion;
			
			sscanf(&testarr[j][keep_portion],"%s",(one_struct+i)->output_name);
			find_partial_length(&testarr[j][keep_portion],&portion);
			keep_portion += portion;
			sscanf(&testarr[j][keep_portion],"%s",(one_struct+i)->input_name1);
		
			*(arrp+i) = (one_struct+i);//copy the structure to main one .>> 

		}
		else if (0 == strcmp(first_line_name,"FLIPFLOP")){//flipflop gated to be filled.
				
			keep_portion = 0,portion = 0;
			
			(one_struct+i)->input1p = NULL;
			(one_struct+i)->input2p = NULL;

			strcpy((one_struct+i)->gate_type,first_line_name);//input gate name.
			
			find_partial_length(&testarr[j][keep_portion],&portion);
			keep_portion += portion;
			
			sscanf(&testarr[j][keep_portion],"%s",(one_struct+i)->output_name);
			find_partial_length(&testarr[j][keep_portion],&portion);
			keep_portion += portion;
			
			sscanf(&testarr[j][keep_portion],"%s",(one_struct+i)->input_name1);

			*(arrp+i) = (one_struct+i);//copy the structure to main one .>>

		}
		i++;
		j++;
		free(one_struct);

	}//end of whil loop

}//End of fuunction.

//////////////////////
int  lines_counter(FILE *inp,int *size){//this fun will find count of lines in given file,also pars the first line in out  line and find  number of entities and return the lenght.

	char *line1 = (char*)malloc(sizeof(char));
	char *line = (char*)malloc(sizeof(char));
	
	int i = 0,lenght,j = 0;
	
	fscanf(inp,"%s",line1);
	fscanf(inp,"%[^\n]\n",line1);

	lenght = strlen(line1);

	char temp[lenght];
	temp[lenght] = '\0';
	strcpy(temp,line1);

	while(temp[i]!='\0'){//pars first line.

		if (temp[i] == ' '){
			j++;
		}
		i++;
	}	
	
	while(!feof(inp))//pars circiut.txt file.
	{

		fscanf(inp,"%[^\n]\n",line1);
		line = strtok(line1,"\n");
		*size = *size+1;
	
	}
	free(line1);
	free(line);

	return j;//return  count of elements number in first line 'INPUT' line


}//// End of function

/////////////////////
void find_partial_length(char *arr,int *lenght){//find the lenght untill it find  white spaces.

	int i = 1;
	
	while(arr[i]!=' ' && arr[i]!='\n'){
		
		i++;
	}
	
	*lenght = i;
}
///////End of function 

int calculate_given_circuit(struct node *gates_p,int *keep_prev_outp){


	int inp1,inp2;
	if (gates_p->input1p == NULL && gates_p->input2p == NULL){// base case
		return (gates_p->output);
	}
	else{//else we have check several conditions...

		if (0 == strcmp(gates_p->gate_type,"AND")){
			
			inp1 = calculate_given_circuit(gates_p->input1p,keep_prev_outp);
			inp2 = calculate_given_circuit(gates_p->input2p,keep_prev_outp);
		}
		else if (0 == strcmp(gates_p->gate_type,"OR")){
			
			inp1 = calculate_given_circuit(gates_p->input1p,keep_prev_outp);
			inp2 = calculate_given_circuit(gates_p->input2p,keep_prev_outp);
		}
	 	else if (0 == strcmp(gates_p->gate_type,"NOT")){
			
			inp1 = calculate_given_circuit(gates_p->input1p,keep_prev_outp);
		}
		else if ( 0 == strcmp(gates_p->gate_type,"FLIPFLOP")){

			inp1 = calculate_given_circuit(gates_p->input1p,keep_prev_outp);
		}
	}
	/*conditions to be manipulated and returned.*/	
	if (0 == strcmp(gates_p->gate_type,"AND")){

		return(inp1 && inp2);

	}
	else if (0 == strcmp(gates_p->gate_type,"OR")){
	
		return ( inp1 || inp2);
	}
	else if (0 == strcmp(gates_p->gate_type,"NOT")){
		
		if (inp1 == 1){
			return 0;
		}
		else if (inp1 == 0){
			return 1;
		}
	}
	else if (0 == strcmp(gates_p->gate_type,"FLIPFLOP")){
		
		if (inp1 == 0 && *keep_prev_outp == 0 || inp1 == 1 && *keep_prev_outp == 1){

			*keep_prev_outp = 0;
			gates_p->previous_output = 0;		
			return 0;
		}
		else if (inp1 == 0 && *keep_prev_outp == 1 || inp1 == 1 && *keep_prev_outp == 0){

			*keep_prev_outp = 1; 
			gates_p->previous_output = 1;
			return 1;
		}
	}
}

/////////////End of function 





////////////////////////////////////////Voila!!! (I hope)