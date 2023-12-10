#include "Storage.h"
#include "Videogame.h"

Storage::Storage(char s) : Location(s)
{
	storage = true;
	store = new Item();
}

void Storage::draw()
{
	if (visited && drop) {
		cout << symbol;
	}
	else if (!drop) {
		cout << ' ';
	}
	else {
		cout << '.';
	}
}

int Storage::visit(Player& p)
{
	// Based on which item the player chooses to drop (Crystal, Key or Clover), then set its symbol in videoGame.cpp, then dynamically allocate it here to Item object
	if (symbol == 'K') {
		store = new Item("key");
	}
	else if (symbol == 'c') {
		store = new Item("clover");
	}
	else if (symbol == 'C') {
		store = new Item("crystal");
	}

	if (drop == false && stored == true) {
		drop = true;
		back = false;  // because the player visit this location for the first time to drop item, so back is false (back means "come back")
		string title = "Storage";
		string message = "You've stored a " + store->GetItem() + ". You can retrieve it later.";
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title.c_str(), message.c_str(), NULL);
		Item* ptr = p.inventory->Remove(store->GetItem()); // remove the item in his/her bag
		delete ptr;
	}
	else if (back == false) back = true;  // to avoid asking the player to retrieve the item immediately after he/she dropped it.
									      // when the player come back the Storage location where he/she dropped item, back becomes true
	else if (drop == true && stored == true && back == true) {  // because back is true, so the program asks the player if he/she would like to retrieve the item
		string title = "Storage";
		string message = "You've stored a " + store->GetItem() + ". Do you want to retrieve it now?";
		const SDL_MessageBoxButtonData buttons[2] = {
				{ 0, 1, "No" }, //button with ID 1
				{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Yes" } //button with ID 0
		};
		const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION, NULL, title.c_str(), message.c_str(), SDL_arraysize(buttons), buttons, NULL };  // the box to ask the player if he/she would like to retrieve item
		int answer;
		SDL_ShowMessageBox(&messageboxdata, &answer); //answer will hold the ID of the pressed button 
		if (answer == 0) 
		{
			drop = false; 
			stored = false;
			back = false;
			// because the player chooses to retrieve item, everything gets back to their original state (false)
			p.inventory->Insert(store); // insert the item back to the player's bag
		}
	}
	visited = true;
	return 1;
}


void Storage::render()
{
	//Only render the picture for this location if we have been here (visited == true)

	if (drop == true && stored == true)
	{
		Videogame::renderBitMap((int)(symbol));
	}
}