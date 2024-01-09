#ifndef __GAMEPBOARD_H__
#define __GAMEBOARD_H__

#define RESULT_MISS 0
#define RESULT_HIT 1 


typedef struct board_position {
	unsigned int row;   //coordinates of row
	unsigned int col;   //coorindates of column
} BoardPosition;

typedef struct hitormiss {
	BoardPosition coords;
	int hit_or_miss;   //int of 1 or 0 depending on hit or miss 
} hit_or_miss;

typedef struct gameboard {
	unsigned int gbheight;	//height of board
	unsigned int gbwidth;   //width of board
	unsigned int num_ships;   //number of ships
	unsigned int num_shots;   //number of shots
	BoardPosition* pos;   //positions of ships
	hit_or_miss* shot_loc;   //array of shot locations
} Gameboard;


Gameboard* create_gameboard(int height, int width);

int check_for_hit(Gameboard* brd , BoardPosition passthru);

void record_hit(Gameboard *gbh , BoardPosition crds);

void record_miss(Gameboard *gbh , BoardPosition crds);

void print_game_state(Gameboard* gb);

int is_victory(Gameboard* gbs);

#endif