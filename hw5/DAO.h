#include <sstream>
#include <string>
#include <fstream>
#include <cstdlib>

#include "structs.h"

using namespace std;

class DAO{
	public:
		List *readAllLinesFloatData(char *fname, int items);
		List *readFirstLineParam(char *fname);
};