#include <iostream>
#include "rand.h"

typedef unsigned long long int Bit64;

using namespace std;

// input/output:
// .......
// .......
// .......
// .......
// .......
// .......
//
// ...O...
// ..XX...
// -
// --  is the end of game signal
//
class Board {
private:
    static const int height = 6;
    static const int width = 7;
	 static const int depth = 3;

private:
    string name;                // name of player
    char board[height][width];  // full board
    int top[width];             // location of first empty cell in column
    char moveChar;              // character for next play
    int x, o;                   // number of x's and number of o's
	 int child[width];

public:
	bool eval;

// methods
private:
    char cleanChar(char c);

public:
    Board(string nameArg);
    bool read();
    bool check();
    void print(char *spacing="");
    bool moveOK(int c);
    bool isBoardFull();
    int pickRandomMove();
    void placeMove(int c);
    void playRandomMove();
    char isWinner();
    bool isWinner(char c);
    Bit64 toBitstring(char piece);
	 bool evaluate();
};
