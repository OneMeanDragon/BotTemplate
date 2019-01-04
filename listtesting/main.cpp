#include <Windows.h>
#include <cstdlib>
#include <iostream>

#include "mlist.h"

int main(int argc, char** argv) {


	Common::mList myList;

	for (int i = 0; i < 10; i++)
	{
		myList.AddNode(i);
	}
	myList.PrintList(); //1-9

	myList.DeleteNode(99);
	myList.PrintList();

	myList.DeleteNode(5);
	myList.PrintList();

	myList.DeleteNode(0);
	myList.PrintList();

	///////////////////////////
	Common::IndexedList myList2;
	for (int i = 0; i < 5; i++)
	{
		myList2.AddItem(); //self indexing
	}
	myList2.PrintAll();
	myList2.Length();

	myList2.DeleteItem(99);
	myList2.PrintAll();
	myList2.Length();

	myList2.DeleteItem(2);
	myList2.PrintAll();
	myList2.Length();

	myList2.AddItem();
	myList2.PrintAll();
	myList2.Length();

	myList2.AddItem();
	myList2.PrintAll();
	myList2.Length();

	myList2.DeleteItem(2);
	myList2.PrintAll();
	myList2.Length();

	myList2.AddItem();
	myList2.PrintAll();
	myList2.Length();

	std::cout << "Press Enter to Continue";
	std::cin.ignore();

	return 0;
}
