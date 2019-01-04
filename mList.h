#ifndef _MLIST_H
#define _MLIST_H

namespace Common {

	typedef struct iNode {
		unsigned int index;
		iNode* next;
	} *iNodePtr;

	class mList {
	private:
		typedef struct node {
			unsigned int index;
			// internal guts //
			node* next;
		} *nodePtr;

		unsigned int item_counter;
		nodePtr head;
		nodePtr curr;
		nodePtr temp;

	public:
		mList();
		~mList();

		void AddNode(int addData);
		void DeleteNode(int mIndex);
		void PrintList();
		unsigned int Length();

	};

	class IndexedList {
	private:
		unsigned int item_counter;
		iNodePtr mHead;
		iNodePtr mCurrent;
		iNodePtr mTemp;

		void UpdateListIndex(iNodePtr nTemp);

	public:
		IndexedList();
		~IndexedList();

		void AddItem(); //temp add
		void DeleteItem(unsigned int mIndex);
		void PrintAll();
		unsigned int Length();

	};

}


#endif
