#include "Special.h"
#include "videoGame.h"

Special::Special(Player& p, char s) : Location(s)
{
    srand(time(NULL));
    int r = rand() % 2;  // there are 2 kind of Special items: chocolate and candy, so use rand() to randomly set special item
    if (r == 0) {
        special = new Item("chocolate");
        symbol = '1';
        p.SpecialItems.at("chocolate")++; // add the chocolate to the player's map
    }
    else {
        special = new Item("candy");
        symbol = '2';
        p.SpecialItems.at("candy")++;  // add the candy to the player's map
    }
    q->Enqueue(special);  // enqueue that special item to the queue
}

void Special::SetTaken(bool t) {
    taken = t;
}

bool Special::IsTaken() {
    return taken;
}

void Special::draw()
{
    if (visited && !taken) {
        cout << symbol;
    }
    else if (taken) {
        cout << " ";
    }
    else {
        cout << ".";
    }
}

int Special::visit(Player& p)
{
    if (taken == false) {
        Location::SetVisited(true);
        string title = "You found a Special " + special->GetItem();
        string message = "What do you want to do?";
        const SDL_MessageBoxButtonData buttons[2] = {
            { 0, 1, "Leave item" }, //button with ID 1
            { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Take item" } //button with ID 0
        }; //NOTE that the buttons appear in the REVERSE order of how they are specified above
        const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION, NULL, title.c_str(), message.c_str(), SDL_arraysize(buttons), buttons, NULL };
        //NOTE that the first parameter can be: SDL_MESSAGEBOX_ERROR, SDL_MESSAGEBOX_WARNING, or SDL_MESSAGEBOX_INFORMATION
        int answer;
        SDL_ShowMessageBox(&messageboxdata, &answer); //answer will hold the ID of the pressed button 
        if (answer == 0) //The user must have pressed the "Take crystal" button
        {
            taken = true;
            Item* ptr = q->Remove(special->GetItem()); // whenever the player finds out the special item, the program will remove that item from the queue
            delete ptr;                                // because there are 2 kinds of special items, so we need to use Remove(key)
            p.SpecialItems.at(special->GetItem())--;    // then the player's map at this map will decrease 1 element.
                                                        // because the map is to show how many items left to find, not the number of items that the player has found
        }
           
    }
    return 1;
}


void Special::render()
{
    //Only render the picture for this location if we have been here (visited == true)
    //but we did not "Take special item" (taken == false)
    if (visited == true && taken == false)
    {
        Videogame::renderBitMap((int)(symbol));
    }
}

