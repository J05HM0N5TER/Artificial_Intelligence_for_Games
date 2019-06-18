#include "Application2D.h"
#include <crtdbg.h>
#include "heap.h"

int main()
{
	heap<int> h;

	h.add(91);
	h.add(56);
	h.add(95);
	h.add(95);
	h.add(76);
	h.add(58);
	h.add(48);
	h.add(32);

	int p = h.get_parent_index_of(10);

	auto [s_left, s_right] = h.get_children_index_of(10);

	int left, right;

	

	h.get_children_index_of(10, left, right);





	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// allocation
	auto app = new Application2D();

	// initialise and loop
	app->run("Artificial Intelligence for Games", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}