#include <cstdlib>
#include <iostream>

#include "mList.h"

namespace Common {

	mList::mList() {
		head = NULL;
		curr = NULL;
		temp = NULL;
		item_counter = 0;
	}

	mList::~mList() {

	}

	void mList::AddNode(int addData)
	{
		nodePtr n = new node;
		n->next = NULL;
		n->index = addData;

		if (head != NULL)
		{
			curr = head;
			while (curr->next != NULL)
			{
				curr = curr->next;
			}
			curr->next = n;
		} else {
			head = n;
		}
		item_counter++;
	}

	void mList::DeleteNode(int mIndex)
	{
		nodePtr delPtr = NULL;
		temp = head;
		curr = head;

		while (curr != NULL && curr->index != mIndex)
		{
			temp = curr;
			curr = curr->next;
		}
		if (curr == NULL)
		{
			std::cout << mIndex << " was not found \r\n";
			delete delPtr;
		} else {
			delPtr = curr;
			curr = curr->next;
			temp->next = curr;
			if (delPtr == head)
			{
				head = head->next;
				temp = NULL;
			}
			delete delPtr;
			std::cout << "Node at index " << mIndex << " has been deleted\r\n";

			item_counter--;
		}
	}

	void mList::PrintList()
	{
		curr = head;
		while (curr != NULL)
		{
			std::cout << curr->index << std::endl;
			curr = curr->next;
		}
	}

	uint32_t mList::Length()
	{
		return item_counter;
	}

}
