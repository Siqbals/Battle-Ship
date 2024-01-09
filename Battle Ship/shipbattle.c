#include <stdio.h>
#include "gameplay.h"
#include "rand_num.h"


int main() {

    // Comment out the next line to use the same pseudorandom sequence for every run -- good for debugging!
    rand_init();

    int shots_taken = play_game(5, 5);

    if( shots_taken > 0) {
        printf("Congratulations!  You sunk all the ships using only %d shot(s)!", shots_taken);
    }
    else {
        printf("You walked away after only taking %d shot(s).  Sad.", -shots_taken);
    }

}
