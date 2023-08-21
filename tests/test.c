#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../tests/deque/deque_t.h"
#include "../tests/colours/colours_t.h"

int main(int argc, const char *argv[])
{
	// Enable all feature
    bool all = (argc == 2) && (!strcmp(argv[argc - 1], "--all")) ? true : false;

	test_init();

	deque_t();
	stack_t();
	queue_t();
	get_t();

	if (all)
	{
		colours_t();
	}
	
	return 0;
}