#include <Engine.h>
#include <Game.h>

int main(int argc, char *argv[]) {

    Ilargia::Game game {Ilargia::Engine {}};
    game.init(argc, argv);

    return 0;

}
