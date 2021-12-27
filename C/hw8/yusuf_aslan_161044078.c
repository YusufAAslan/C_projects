#include <stdio.h>
#define MAX_SIZE 514 	// Cuz we have one extra int at the first also  I assume the border as water so I made my array's dimension 514 

void fill_terrains_array(char terrain[][MAX_SIZE],FILE *input);//this function fills the desired array in specific form  
int check_terrain_cells(char terrain[][MAX_SIZE]);//this function trace evry cell of array by it's indecators.
void search_for_island(char terrain[][MAX_SIZE],int row,int column);//this function to search and check for island
void print_into_outputfile(FILE *output,char terrain[][MAX_SIZE],int count);// this function prints the resulte into output file

int main(){
  
 	FILE *input,*output;					// declare pointer and variabels and 2D arr to use down
  	int count_of_islands = 0;		// at most it will be 100
  	char terrain[MAX_SIZE][MAX_SIZE];

   	input = fopen("input.txt","r");		// open file in read mode to read from
   	output = fopen("output.txt","w");	// open file in write mode to write into
  	
 	fill_terrains_array(terrain,input);//function calling
 	
	count_of_islands = check_terrain_cells(terrain);
 	fprintf(output,"%d",count_of_islands);//print islands into output file
 	
 	if (count_of_islands != 0){//take care for extra newline at the end of file
 		
 		fprintf(output,"\n");
 	}
 	print_into_outputfile(output,terrain,count_of_islands);

	fclose(input);
  	fclose(output);
 	
 	return 0;
}
////////////////////////////////////////////////////////////End of main


void fill_terrains_array(char terrain[][MAX_SIZE],FILE *input){//fill our array in  deisred form

	int i,j,temp,water_level;

	fscanf(input,"%d",&water_level);//read water level value

	for (i = 0; i < MAX_SIZE; ++i){
	   
	    for (j = 0; j < MAX_SIZE; ++j){
			
			// if statment to check for the borders of the array since we assumed that our array is surrended by the water 
		    if (i == 0|| (i == 0 && j != 0) || (i != 0 && j == 0) || (i == (MAX_SIZE-1) && j == 0) || (i == (MAX_SIZE-1) && j !=0)||(j == (MAX_SIZE-1))){//condition to avoid preceding the border of the array assuming that array is coverrd by water.
		    
		    //this means we are at  the very first cell or firts cell's all colums or last or first columns all rows or last colums all row or last rows columns the marked as water
	          	
	          	terrain[i][j] = 'w';// so set the desired cells as water .
		    }
	    	else{
	    		
	    		fscanf(input,"%d",&temp);
	     		
	     		if (temp > water_level){//above water
	      			
	      			terrain[i][j] = 'n';//not visited yet 

	     		}
	      		else if(water_level > temp || water_level == temp){//bellow water.

	          		terrain[i][j] = 'w';	//also marked as water if it is bellow water level

	      		}
	    	}
		}
	}
}
//////////////////////////////////////////////////////

int check_terrain_cells(char terrain[][MAX_SIZE]){//go throw whole array and  check and marke the visited valus and find the islands if there is inside it

	int i,j,counter = 0;

	for (i = 0; i < MAX_SIZE-1; ++i){
		
		for (j = 0; j < MAX_SIZE-1; ++j){
			
			if (terrain[i][j] != 'v' && terrain[i][j] != 'r' && terrain[i][j] != 'w'){//if the cell hasn't been visited yet or it is not water.
				
				search_for_island(terrain,i,j);//check all related cells 
				
				terrain[i][j] = 'v';//mark it as visited
				counter++;//also add one to island
			}
		}
	}
	return counter;//return  count of island.
}

//////////////////////////////////////////////////////////

void search_for_island(char terrain[][MAX_SIZE],int row,int column){//search and check for islands if there 

	if (terrain[row][column] == 'r' || terrain[row][column] == 'v'|| terrain[row][column] == 'w'){//base condition 
		
		return;
	}
	else{	// keep chceking 
		
		terrain[row][column] = 'r';//marked as visited
		
		search_for_island(terrain,row,column+1);//check for right side
		search_for_island(terrain,row,column-1);//check for left side
		search_for_island(terrain,row-1,column);//check on  up 
		search_for_island(terrain,row+1,column);//check on down 
		return;
	}
}
//////////////////////////////////////////////////////

void print_into_outputfile(FILE *output,char terrain[][MAX_SIZE],int count){//print the results into output file

	int i,j;
	
	for (i = 0; i < MAX_SIZE-1; ++i){
		
		for (j = 0; j < MAX_SIZE-1; ++j){
		
			if (terrain[i][j] == 'v'){//print the coordenates into file		
				

				fprintf(output,"%d %d",i,j);
				--count;
				if (count!=0){	// take care for extra new lines
					
					fprintf(output,"\n");
				}
			}
		}
	}	
}

/////////////////////////////////////////////////////////// VOILA!!!