#include "c4board.h"
// a simple player
int main()
{
    Board b("Simplton");

    initRand();

    while (b.read() && ! b.isBoardFull()) {
        b.playRandomMove();
        b.print();
    }

    return 0;
}
