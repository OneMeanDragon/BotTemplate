#include <cstdlib>
#include <iostream>

#include "mList.h"

namespace Common {

#pragma region "mList"

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
		}
		else {
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
		}
		else {
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

	unsigned int mList::Length()
	{
		return item_counter;
	}

#pragma endregion

#pragma region "Indexed List"
	IndexedList::IndexedList()
	{
		item_counter = 0;

		mHead = NULL;
		mCurrent = NULL;
		mTemp = NULL;
	}
	IndexedList::~IndexedList()
	{
		//
	}

	void IndexedList::AddItem()
	{
		iNodePtr n = new iNode;
		n->next = NULL;
		n->index = item_counter;

		if (mHead != NULL)
		{
			mCurrent = mHead;
			while (mCurrent->next != NULL)
			{
				mCurrent = mCurrent->next;
			}
			mCurrent->next = n;
		}
		else {
			mHead = n;
		}
		item_counter++;
	}
	void IndexedList::DeleteItem(unsigned int mIndex)
	{
		iNodePtr delPtr = NULL;
		mTemp = mHead;
		mCurrent = mHead;

		while (mCurrent != NULL && mCurrent->index != mIndex)
		{
			mTemp = mCurrent;
			mCurrent = mCurrent->next;
		}
		if (mCurrent == NULL)
		{
			std::cout << mIndex << " was not found \r\n";
			delete delPtr;
		}
		else {
			delPtr = mCurrent;
			mCurrent = mCurrent->next;
			mTemp->next = mCurrent;
			if (delPtr == mHead)
			{
				mHead = mHead->next;
			}
			delete delPtr;
			std::cout << "Node at index " << mIndex << " has been deleted\r\n";

			item_counter--;
			//update the index values
			UpdateListIndex(mCurrent);
		}
	}
	void IndexedList::UpdateListIndex(iNodePtr nTemp)
	{
		while (nTemp != NULL)
		{
			nTemp->index--;
			nTemp = nTemp->next;
		}
	}
	void IndexedList::PrintAll()
	{
		mCurrent = mHead;
		while (mCurrent != NULL)
		{
			std::cout << mCurrent->index << std::endl;
			mCurrent = mCurrent->next;
		}
	}
	unsigned int IndexedList::Length()
	{
		std::cout << "List length is currently: " << item_counter << std::endl;
		return item_counter;
	}

#pragma endregion
}
