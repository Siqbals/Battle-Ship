#ifndef __GAMEPLAY_H__
#define __GAMEPLAY_H__

/**
 * Initiate gameplay for a gameboard with a certain width and height.
 *
 * @param board_width   Width of the gameboard (must be between 5 and 26)
 * @param board_height  Height of the gameboard (must be between 5 and 26)
 * @return              The number of shots taken by the player when the game ends.
 */
int play_game(unsigned int board_width, unsigned int board_height);

#endif
