#include "LinkedList.h"



LinkedList::LinkedList()
{
    head = nullptr;
    tail = nullptr;
}

LinkedList::~LinkedList()
{
    while (head) {  // delete from the beginning
        Item* next = head->next;
        delete head;
        head = next;
    }
}

Item* LinkedList::GetFirstElement()
{   
    return head;
}

void LinkedList::Insert(Item* p)
{   
    p = new Item(p->item); // dynamically assign p
    p->next = NULL; // p will be insert at the end of the list so p->next must be NULL
    if (head == NULL) {  // for an empty list
        head = p;
        tail = p;
    }
    else {  // for a non-empty list
        tail = head;  // the tail is first assign as head
        while (tail->next != NULL) {
            tail = tail->next;  // then tail is go through the list until the last element
        }
        tail->next = p; // insert p after the last element (tail)
    }
}

Item* LinkedList::Find(string key)
{
    Item* curr = head; // assign curr as head to go through the list from the first element
    while (curr != NULL) {   // while the list has not get ended
        if (curr->item == key) {  // find the element that has the key as its name
            return curr;
        }
        else curr = curr->next; // if not, curr comes to the next element
    }
    return nullptr;  // return NULL if there is no such element in the list

}

Item* LinkedList::Remove(string key)
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

int LinkedList::count(string key)
{   
    int count = 0;
    if(head == NULL && tail == NULL) return 0;  // return 0 if empty list
    else { 
        Item* curr = head; // as curr as head to go through the list
        while (curr != NULL) {
            if (curr->item == key) count++; // whenever finding out an element that has the key as its name then the count increases 1
            curr = curr->next; // then go to the next element
        }
    }
    return count; // return the number of item
}

