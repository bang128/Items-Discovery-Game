#include "Queue.h"

Queue::Queue()
{
	head = nullptr;
	tail = nullptr;
}


Queue::~Queue()   // destructor
{
	while (head) {  // while the queue has not ended
		Item* ptr = head->GetNext();  // delete from the head
		delete head;
		head = ptr;
	}
}


void Queue::Print()
{
	if (isempty()) cout << "Queue is empty" << endl;  
	else {  //if the queue is not empty
		Item* ptr = head;  // assign the current pointer with the queue's head
		while (ptr != NULL) {  // while the queue has not ended
			cout << ptr->GetItem();  // print out each element
			ptr = ptr->GetNext();
		}
	}
}

void Queue::Enqueue(Item* p)
{
	Item* ptr = new Item();   // create a new pointer of type Item
	ptr->SetItem(p->GetItem());  // assign the value of the new pointer to the pointer p's
	ptr->SetNext(NULL);  // because insert to the back of the queue so the next pointer must be NULL
	if (isempty()) {   // if the queue first has no element
		head = ptr;
		tail = ptr;
	}
	else {  // if the queue has elements
		tail->SetNext(ptr);  // add the new pointer to the next of tail
		tail = ptr;  // then the tail will be the new pointer
	}
}

Item* Queue::Dequeue()
{
	Item* ptr = head;   // assign a pointer as the head of queue
	if(isempty()) return NULL;
	else {
		head = head->GetNext();  // delete the head, so the new head will be the next of the old head
		if (head == NULL) tail = NULL;  // if the queue first just has 1 element, then the new head becomes NULL and so does the tail
		return ptr;  // return the old head which has been assigned to ptr
	}
}
Item* Queue::Remove(string key)
{
	Item* pre = NULL; // for the previous element
	Item* curr = head; // for the current element
	while (curr != NULL) {
		if (curr->item == key) {  // find the element to remove
			if (pre == NULL) { // remove if it is the first element
				head = head->next;
				if (head == NULL) tail = NULL;
			}
			else if (tail == curr) { // remove if it is the last element
				if (pre != NULL) pre->next = NULL;
				tail = pre;
			}
			else pre->next = curr->next; // remove if it is in the middle

			return curr;
		}
		else {  // if not, the pre comes to curr, and curr comes to next
			pre = curr;
			curr = curr->next;
		}
	}
	return nullptr; // return NULL if there is no such element in the list
}

bool Queue::isempty()
{
	if (head == NULL && tail == NULL) return true;
	return false;
}



