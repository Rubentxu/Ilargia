#include <Engine.h>
#include <Game.h>

using namespace Ilargia;

int main(int argc, char *argv[]) {

    Game game {Engine {}};
    game.init(argc, argv);

    return 0;

}
