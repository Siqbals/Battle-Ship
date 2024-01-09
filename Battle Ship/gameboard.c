#include <stdio.h>
#include <err.h>
#include <stdlib.h>
#include "gameboard.h"
#include "rand_num.h"

//macro varibles
#define RESULT_MISS 0
#define RESULT_HIT 1 
#define RESULT_REPEAT 2

int shot_loc_increment = 0;   //global varibale to increment the array index of shot location array

/*
create_gameboard function
purpose - create a gameboard
pre-conditions
	int height - the height of the board (length)
	int width - the width of the board
post conditions
	temp_arr - temporary array used to create unique random values
	int i - loop control variable
	dup_count - duplicate control variable
return - a pointer to the first index of a gameboard struct
*/
Gameboard* create_gameboard(int height, int width) {

	//check if height and width are valid
	if ( !(height>=5 && height<=26) || !(width>=5 && width<=26)) {
		errx(1 , "invalid board dimensions");
	}

	rand_init();
	int num_ships = rand_num(5) + 5;   //generate a random number of ships between 5 and 10

	BoardPosition* temp_arr = (BoardPosition*) malloc(sizeof(BoardPosition*) * num_ships);   //temporary array to store randomly generated numbers

	//initialize all indexes of temp array to integer 30
	for (int n = 0; n < num_ships ; n++) {
		temp_arr[n].row = 30;
		temp_arr[n].col = 30;
	}

	//main array used for generating ship coordinates
	BoardPosition* crd_arr = (BoardPosition*) malloc(sizeof(BoardPosition*) * num_ships);  

	int i = 0;   //loop control variable

	
	//while loop used to create unique random values 
	while (i < num_ships) {
		int dup_count = 0;
		crd_arr[i].row = rand_num(width);
		crd_arr[i].col = rand_num(height);

		//iterate thru temporary array
		//if generated value isnt in the array, "append" to array
		//if it is, then generate a new value, check again
		for (int j = 0; j < num_ships; j++) {
			if ((temp_arr[j].row == crd_arr[i].row) && (temp_arr[j].col == crd_arr[i].col)) {
				dup_count++;
			}
		
		}
		if (dup_count == 0) {
			temp_arr[i].row = crd_arr[i].row;
			temp_arr[i].col = crd_arr[i].col;
			i++;
		}
	}



	hit_or_miss* shot_loc_grid = (hit_or_miss*) malloc(sizeof(hit_or_miss) * (width * height));   //shot location array

	//initialize values of shot location array to int 30
	for (int n = 0; n < width * height ; n++) {
		shot_loc_grid[n].coords.col = 30;
		shot_loc_grid[n].coords.row = 30;
		shot_loc_grid[n].hit_or_miss = 30;
	}

	

	
	

	Gameboard* ret = (Gameboard*)malloc(sizeof(Gameboard));   //dynamically allocate the gameboard struct 

	//assign values to struct members 
	ret->gbheight = height;
	ret->gbwidth = width;
	ret->num_ships = num_ships;
	ret->num_shots = 0;
	ret->pos = crd_arr;   
	ret->shot_loc = shot_loc_grid;   

	return ret;
	
}

/*
check_for_hit function
purpose - to check if a grid position is a hit, miss, or repeat
preconditions
	brd - pointer to a gameboard struct 
	passthru - a boardposition struct
postconditions
	arrLen - length of the array
return 
	the macros, defined above (which are int values)
*/
int check_for_hit(Gameboard* brd , BoardPosition passthru) {
	brd->num_shots += 1;   //increase the shot count since if we call this function, we have taken a shot
	int arrLen = brd->gbheight * brd->gbwidth;

	//first check the shot location array to see if passthru was already shot at
  for (int i = 0; i < arrLen; i++) {
    if ((brd->shot_loc[i].coords.row == passthru.row) && (brd->shot_loc[i].coords.col == passthru.col) ) {
			return RESULT_REPEAT;
		}
	}

	//then check thru the ship coordinate array to see if it matches, if it does then its a hit
	for (int k = 0 ; k < brd->num_ships ; k++) {
		if ((brd->pos[k].row == passthru.row) && (brd->pos[k].col == passthru.col)) {
			return RESULT_HIT;
		}
	}
	return RESULT_MISS;   //otherwise its a miss
	
}

/*
record_hit function
purpose - to record a hit
pre conditions
	gph - a pointer to a gameboard struct
	crds - a boardposition struct
post_conditions
	none
return
	void type
*/
void record_hit (Gameboard *gbh , BoardPosition crds) {
	gbh->shot_loc[shot_loc_increment].coords = crds;   //add the shot coordinates to the shot location array
	gbh->shot_loc[shot_loc_increment].hit_or_miss = 1;  //change hit or miss struct member to 1
	shot_loc_increment += 1;   //increase the shot location increment so that next shot location can be indexed
}

/*
record_miss function
purpose - to record a misa
pre conditions
	gph - a pointer to a gameboard struct
	crds - a boardposition struct
post_conditions
	none
return
	void type
*/
void record_miss (Gameboard *gbh , BoardPosition crds) {
	gbh->shot_loc[shot_loc_increment].coords = crds;   //add the shot coordinates to the shot location array
	gbh->shot_loc[shot_loc_increment].hit_or_miss = 0;   //change hit or miss struct member to 0
	shot_loc_increment += 1;   //increase the shot location increment so that next shot location can be indexed
}





/*
print game state function
purpose - to print the current game state
pre-conditions
	gb - a pointer to a gameboard
postconditions
	pprint - varibale to check if a "." should be printed 
	temp - temporary boardposition struct
return 
	void type
*/
void print_game_state(Gameboard* gb) {
	printf("shots taken %d \n" ,gb->num_shots);   //print the current shots taken

	int pprint = 0;

	char alphabet_arr[28] = "ABCDEFJHIJKLMNOPQRSTUVWXYZ";  

	//print the column indexes
	for (int i = 1 ; i < gb->gbwidth + 1 ; i++) {
		printf("%3d" , i);
	}

	printf("\n");

	//for loop iterates thru each row
	for (int k = 0 ; k < gb->gbwidth; k++ ) {
		printf("%c" , alphabet_arr[k]);   //print the row indexes
		//for loop iterates thru each column
		for (int l = 0 ; l < gb->gbheight; l++) {
			//for given location, iterate thry shot_loc array to decide what to print
			for (int m = 0; m < gb->gbwidth * gb->gbheight; m++) {
				BoardPosition temp;
				temp.row = k;
				temp.col = l;
				//if current cords are in the shot loc array, then a shot has been taken there
				if ((gb->shot_loc[m].coords.row == temp.row) && (gb->shot_loc[m].coords.col == temp.col)) {
					//print x if shot was a hit 
					if (gb->shot_loc[m].hit_or_miss == 1) {
						printf("%3s" , "X");
						pprint = 1;
					//otherwise print o
					}
					else {
						printf("%3s" , "o");
						pprint = 1;
					}
				}
			}

			//if the shot was never taken, pprint never increments
			//this variable allows the program to somewhat print an x or o in place of the .
			//makes sure that excess . do not get printed
			if (pprint == 0) {
				printf("%3s" , ".");
			}
			pprint = 0;
		}
	printf("\n");
	}
}
		
/*
is victory function
purpose - to check if game is won
pre conditions - a pointer to a game board
post-conditions
	hit-count - variable to keep track of shots that were hit
return 
	int 1 or 0 based on outcome
*/
int is_victory(Gameboard* gbs) {
	int hit_count;

	//count the number of hits that were taken on a board
	for (int i = 0 ; i < gbs->gbheight * gbs->gbwidth ; i++) {
		if (gbs->shot_loc[i].hit_or_miss == 1) {
			hit_count += 1;
		} 
	}

	//if the number of hits equals the number of ships, then all ships have been sunk otherwise not
	if (hit_count == gbs->num_ships) {
	return 1;
	}
	else {
		return 0;	
	}
}
