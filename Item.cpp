#include "Item.h"

Item::Item() {
	item = "NoItem";
}
Item::Item(string n) {
	item = n;
}
void Item::SetItem(string n) {
	item = n;
}
string Item::GetItem() {
	return item;
}

void Item::SetNext(Item* p)
{
	next = p;
}

Item* Item::GetNext() {
	return next;
}
