#include "Common.h"
#include <DbgHelp.h>

using namespace InjecteeFuncs;
int main() {
	int process_id = MyInjecteeFuncs::getNextProcessID(0);

  	printf("Starting injections with process: %d\n", process_id);
  	MyInjecteeFuncs::inject(process_id);

	return 0;
}