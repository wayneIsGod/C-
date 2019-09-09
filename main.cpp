#include "game.h"
#include "memory_leak.h"

int main()
{
	set_initial_leak_test();
	game sq;
	sq.object();
    system("pause");
}