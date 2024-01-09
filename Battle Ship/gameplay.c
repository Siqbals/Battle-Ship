
#include <stdio.h>
#include <ctype.h>
#include <err.h>
#include "gameboard.h"
#include "gameplay.h"


/**
 * Reads a board position from the keyboard.
 *
 * @return A board position structure containing the row and column index of the position on the gameboard.
 *         E.g. Position A1 corresponds ton row and column indices [0,0].
 */
static BoardPosition read_board_position() {
    // A buffer into which to read the position as a string.
    const size_t buffer_size = 10;
    char buffer[buffer_size];

    printf("Enter a board position to attack (e.g. B12): ");
    if( fgets(buffer, buffer_size, stdin) == NULL) {
        errx(1, "Error reading board position in read_board_position().");
    }

    // Try to read a character followed by an integer from the string entered.
    BoardPosition p = {0, 0};
    if( sscanf(buffer, "%c%d", (char*)&p.row, &p.col) != 2) {
        errx(1, "Error: malformed board position entered in read_board_position().");
    }

    // Convert the character read to upper-case and subtract 'A' to get the row index.
    p.row = toupper(p.row) - 'A';

    // Subtract 1 from the integer read to get the column index.
    p.col = p.col - 1;

    return p;
}


int play_game(unsigned int board_width, unsigned int board_height) {

    // Initially, zero ships are sunk.
    unsigned int ships_sunk = 0;

    // Print welcome message.
    printf("Welcome to ShipBattle!\n");

    // Create the gameboard.
    Gameboard* board = create_gameboard(board_width, board_height);

    // Loop until the game ends.  The loop is broken by returning the number of shots taken when the game ends.
    while(1) {

        // Display the current game state.
        printf("Here's the current board. So far you've sunk %d of %d ships.\n\n", ships_sunk, board->num_ships);
        print_game_state(board);

        // Read a board position that the user wants to shoot at.
        BoardPosition pos = read_board_position();

        // Check whether the position shot at scored a hit, was a miss, or was already shot at.
        unsigned int result = check_for_hit(board, pos);
        if(result == RESULT_HIT) {
            // If the result was a hit, record the hit and increase number of ship sunk, and notifiy the player.
            record_hit(board, pos);
            ships_sunk += 1;
            printf("It's a hit!\n");
        }
        else if (result == RESULT_MISS) {
            // If the result was a miss, record it and notify the player.
            record_miss(board, pos);
            printf("It's a miss.  Sad.\n");
        }
        else {
            // Otherwise notify the player that they already attacked there (but it still counts a shot).
            printf("You already attacked there. Try again.\n");
        }

        // Check whether the win condition is met.
        if(is_victory(board)) {
            // If victory is achieved, return the number of shots taken.
            return board->num_shots;
        }

        // Prompt whether to continue or quit.
        printf("Press ENTER to continue or type the letter 'q' or 'Q' followed by enter to quit...");
        const size_t buffer_size = 10;
        char buffer[buffer_size];

        // Read the user's response.
        if( fgets(buffer, buffer_size, stdin) == NULL) {
            errx(1, "Error reading from keyboard in play_game().");
        }

        // If the first character of whatever is read is a 'Q' or a 'q', then quit the game by returning the number of shots taken.
        if(buffer[0] == 'Q' || buffer[0] == 'q') {
            return -board->num_shots;
        }
    }

}

