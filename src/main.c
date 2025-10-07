#include "game.h"

int main(int argc, char* argv[]){
    Game game = {0}; // Initialize all fields to 0/NULL

    if (game_init(&game) < 0) {
        printf("Failed to initialize game!\n");
        game_cleanup(&game);
        return 1;
    }

    game_run(&game);

    game_cleanup(&game);

    return 0;
}