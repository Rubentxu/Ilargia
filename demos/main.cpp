#include "SDLEngine.h"
#include <Game.h>
#include <StateInit.h>
#include<SDL.h>

using namespace Ilargia;


int main(int argc, char **argv) {

    Game game {Engine {}};
    game.init(argc, argv);
    game.pushState(StateInit{});
    game.runGame();

    return 0;

}
