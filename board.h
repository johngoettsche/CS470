#define SIZE 3

typedef struct Board Board;
struct Board{
		int openX;
		int openY;
		int value;
		int depth;
		int *path;
		int numbers[(SIZE * SIZE)];
		int tile[SIZE + 2][SIZE + 2];
};