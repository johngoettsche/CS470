/*
 * John Goettsche
 * CS 470
 * Assignment 2
 * A* search for 8 puzzle
 */

#include "eights.h"

/*
 * function reads standard input.
 */
char *readData(){
	char *input;
	char *nums;
	input = (char *)calloc(SIZE * SIZE * 2 + 1, sizeof(char));
	input = fgets(input, SIZE * SIZE * 2 + 1, stdin);
	nums = (char *)calloc(SIZE * SIZE, sizeof(char));
	int i;
	// converts raw data to a string of characters negating the spaces.
	for(i = 0; i < SIZE * SIZE * 2; i += 2) nums[i / 2] = input[i];
	return nums;
}

Board *makeBoardOnMove(Board *current, Move thisMove, int f){
	Board *newBoard;
	int x = thisMove.x;
	int y = thisMove.y;
	int currentX = current->openX;
	int currentY = current->openY;
	int mov;
	if(current->tile[currentX + x][currentY + y] > 0){
		if((newBoard = (Board *)calloc(1, sizeof(Board))) == NULL) exit(1);
		insertTiles(newBoard, current->numbers);
		newBoard->tile[currentX + x][currentY + y] = current->tile[currentX][currentY];
		newBoard->tile[currentX][currentY] = current->tile[currentX + x][currentY + y];
		mov = newBoard->tile[currentX][currentY];
		completeBoard(current, newBoard, mov, f);
		return newBoard;
	}
	return NULL;
}

int main(){
	//set up moves
	Move moves[4] ={{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
	
	//set up hash table
	HashTable *hashTable;
	HashTable *heapTable;
	int tableSize = pow(SIZE, 9) - SIZE + 1;

	int nos[SIZE * SIZE];
	int g[SIZE * SIZE];
	char *nums = (char *)calloc(SIZE * SIZE, sizeof(char));
	//char nums[9] = {'7', '2', '4', '5', '6', '0', '8', '3', '1'};
	nums = readData();
	char *gl = (char *)calloc(SIZE * SIZE, sizeof(char));
	//char gl[9] =  {'2', '4', '1', '7', '8', '6', '5', '0', '3'};
	gl = readData();
	int i;
	//converts char* to int*
	for(i = 0; i < SIZE * SIZE; i++) nos[i] = (int)nums[i] - '0';
	for(i = 0; i < SIZE * SIZE; i++) g[i] = (int)gl[i] - '0';
	goal = (Board *)calloc(1, sizeof(Board));
	insertTiles(goal, g);
	setNumbers(goal);
	start = (Board *)calloc(1, sizeof(Board));
	insertTiles(start, nos);
	setNumbers(start);
	start->depth = 0;
	printf("\nSTART:\n");
	printBoard(start);
	printf("\nGOAL:\n");
	printBoard(goal);
	heapsize = 0;
	
	Board *newBoard;
	int f;
	for (f = 0; f < 5; f++){
		success = 0;
		//printf("\na");
		hashTable = (HashTable *)createHashTable(tableSize);
		heapTable = (HashTable *)createHashTable(tableSize);
		//printf("b");
		solution = (Board *)calloc(1, sizeof(Board));
		Board *board = (Board *)calloc(1, sizeof(Board));
		//printf("c");
		board = start;
		switch(f){
			case 0:
				board->f = getH(board);
				break;
			case 1:
				board->f = getHout(board);
				break;
			case 2:
				board->f = getHmanhattan(board);
				break;
			case 3:
				board->f = getHgreat2(board);
				break;
			case 4:
				board->f = getHgreat3(board);
				break;
			default:
				printf("error\n");
		}
		int error;
		//printf("d");
		createHeap();
		//printf("inserting into heap\n");
		insertHeap(board);
		//printf("e");
		Board *current;
		int m;
		int fVal;
		int tries = 0;
		//iterate through queue until done
		//printf("f");
		//printf("%d\n", heapsize);
		while(!success){	
			//printf("popping from heap\n");
			current = (Board *)popHeap();
			//printBoard(current);
			//printf("\n*a");
			if((fVal = lookupBoard(hashTable, current)) == -1) {
				if((error = addBoard(hashTable, current)) == 1) {
					printf("failed to add board to hashtable\n");
					exit(1);
				}
				//moves
				//printf("b");
				for(m = 0; m < 4; m++){
					if(!success) {
						if((newBoard = makeBoardOnMove(current, moves[m], f)) != NULL){
						//printf("\n**a");
							if(newBoard->value == goal->value){
								success = 1;
								solution = newBoard;
							}
						//printf("b");
							if((fVal = lookupBoard(heapTable, newBoard)) == -1){
								//printf("-A");
								tries++;
								//printf("inserting into heap\n");
								insertHeap(newBoard);
								if((error = addBoard(heapTable, newBoard)) == 1) {
									printf("failed to add new Board to queuetable\n");
									exit(1);
								}
							} else if(newBoard->f < fVal) {
								//printf("-B");
								tries++;
								//printf("inserting into heap\n");
								insertHeap(newBoard);
								error = addBoard(heapTable, newBoard);
							} else {
								//printf("-C");
								free(newBoard);
							}
							//printf("x");
						}
					}
				}
			}
		}
		//print out results
		//printf("\nA");
		printf("\nTRIES:  %d\n", tries);
		printf("COST: %d\n", solution->depth);
		printf("EST. DIST. START TO GOAL: %d\n", start->f);
		printf("\nSOLUTION:  ");
		printPath(solution);
		printf("QUEUE LEN:  %d\n\n", heapsize);
		free(hashTable);
		free(heapTable);
		hashTable = NULL;
		heapTable = NULL;
	}
	return 1;
}
