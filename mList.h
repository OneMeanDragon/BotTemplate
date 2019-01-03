#ifndef _MLIST_H
#define _MLIST_H

namespace Common {

	class mList {
	private:
		typedef struct node {
			uint32_t index;
			// internal guts //
			node* next;
		} *nodePtr;

		uint32_t item_counter;
		nodePtr head;
		nodePtr curr;
		nodePtr temp;

	public:
		mList();
		~mList();

		void AddNode(int addData);
		void DeleteNode(int mIndex);
		void PrintList();
		uint32_t Length();

	};

}


#endif
