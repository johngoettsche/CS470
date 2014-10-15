#include "c4board.h"

Board::Board(string nameArg)
{
    name = nameArg;

    for (int r=0; r<height; r++) {
        for (int c=0; c<width; c++) {
            board[r][c] = '.';
        }
    }
    check();
}


char Board::isWinner()
{
    if (isWinner('X')) return 'X';
    if (isWinner('O')) return 'O';
    return '\0';  // zero or false
}


bool Board::isWinner(char piece)
{
    Bit64 bits, tmp;
    
    bits = toBitstring(piece);

    // horizontal win
    tmp = (bits & (bits>>1));
    tmp = (tmp>>2) & tmp;
    if (tmp) return true;
//    tmp = tmp | (tmp<<2)   // for marking the win if you want
//    tmp = tmp | (tmp<<1)

    // vertial win
    tmp = (bits & (bits>>(width+1)));
    tmp = (tmp>>(2*(width+1))) & tmp;
    if (tmp) return true;

    // down diagonal win
    tmp = (bits & (bits>>(width+2)));
    tmp = (tmp>>(2*(width+2))) & tmp;
    if (tmp) return true;

    // up diagonal win
    tmp = (bits & (bits>>(width)));
    tmp = (tmp>>(2*(width))) & tmp;
    if (tmp) return true;

    return false;
}




Bit64 Board::toBitstring(char piece)
{
    Bit64 bits;

    if (height * (width+1)>64) {
        cout << "ERROR(toBitstring): board too large to be bit encoded.  height * (width+1) <= 64." << endl;
    }

    bits = 0ULL;
    for (int r=0; r<height; r++) {
        for (int c=0; c<width; c++) {
            bits = (bits<<1) | ((board[r][c]==piece) ? 1 : 0);
        }
        bits = (bits<<1);
    }

    return bits;
}


char Board::cleanChar(char c)
{
    char uc;

    uc = toupper((int)c);
    switch (uc) {
    case 'X' :
        uc = 'X';
        break;
    case 'O' :
        uc = 'O';
        break;
    case '.' :
        uc = '.';
        break;
    default:
        cout << "ERROR(read): invalid character '" <<  c << "' treated as a period." << endl;
        uc = '.';
    }

    return uc;
}

// return true if valid board.
// return false on invalid board and indicates time for termination
bool Board::read()
{
    string line[width+1];

    // get board
    int numlines;

    numlines = 0;
    for (; numlines<height; numlines++) {
        cin >> line[numlines];
        if (line[numlines]=="--" || cin.eof()) {
            return false;   // immediate termination signal
            break;
        }
        if (line[numlines]=="-") {
            break;
        }
        if (line[numlines].length()<width) {
            cout << "ERROR(read): input line '" << line[numlines] << "' is too short." << endl;
            return false;
        }
    }
    numlines--;

    for (int r=0; r<height; r++) {
        for (int c=0; c<width; c++) {
            if (numlines>=0) {
                board[r][c] = cleanChar((unsigned char)line[numlines][c]);
            }
            else {
                board[r][c] = '.';
            }
        }
        numlines--;
    }

    return check();
}

// print out board
void Board::print(char *spacing)
{
    for (int r=height-1; r>=0; r--) {
        for (int c=0; c<width; c++) {
            cout << board[r][c] << spacing;
        }
        cout << endl;
    }
}
    

// check board to see that it is legal
// and set whose move it is
bool Board::check()
{
    bool ok = true;

    x = o = 0;
    for (int r=0; r<height; r++) {
        for (int c=0; c<width; c++) {
            if (board[r][c]=='X') x++;
            else if (board[r][c]=='O') o++;
        }
    }
    if (x>o+1) {
        cout << "ERROR(board): there are too many X's on the board" << endl;
        ok = false;
    }
    else if (x<o) {
        cout << "ERROR(board): there are too many O's on the board" << endl;
        ok = false;
    }
    else if (x==o) {
        moveChar = 'X';
    }
    else {
        moveChar = 'O';
    }

    for (int c=0; c<width; c++) {
        int firstPeriod;

        firstPeriod = height;
        for (int r=0; r<height; r++) {
            if (board[r][c]=='.') {
                if (firstPeriod==height) firstPeriod=r;
            }
            else {
                if (firstPeriod<height) {
                    cout << "ERROR(board): board has a gap in column " << c+1 << endl;
                    ok = false;
                }
            }
        }
        top[c] = firstPeriod;
    }

    return ok;
}


// check if move OK.
// if c==-1 then there is no legal move and move is not OK
bool Board::moveOK(int c)
{
    return (c>=0 && top[c]<height && board[top[c]][c] == '.');
}


// is board full?
bool Board::isBoardFull()
{
    for (int i=0; i<width; i++) 
        if (top[i]<height) return false;
    return true;
}


// pick a random place to move
int Board::pickRandomMove()
{
    int c;

    if (isBoardFull()) {
        cout << "ERROR(pickRandomMove): Can't move.  The board is full" << endl;
        return -1;
    }

    c = randMod(width);
    while (! moveOK(c)) {
        c = randMod(width);
    }
    return c;
}

// pick and place a random move
void Board::playRandomMove()
{
    int c;

    c = pickRandomMove();
    placeMove(c);
//    cout << moveChar << ": Player " << name << " plays in column " << c+1 << endl;
}


// put the piece on the board in column c
void Board::placeMove(int c)
{
    if (moveOK(c)) {
        board[top[c]][c] = moveChar;
        top[c]++;
    }
}

