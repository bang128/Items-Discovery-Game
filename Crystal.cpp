#include "Crystal.h"
#include "videoGame.h"

using namespace std;

Crystal::Crystal(char s) : Location (s) 
{   
    taken = false;
    list->Insert(crystal); // insert a crystal to the world board
}

void Crystal::SetTaken(bool t) {
    taken = t;
}

bool Crystal::IsTaken() {
    return taken;
}

void Crystal::draw()
{
    if ((visited && !taken) || drop) {
        cout << symbol;
    }
    else if (taken) {
        cout << " ";
    }
    else {
        cout << ".";
    }
}


int Crystal::visit(Player& p)
{
    if (taken == false)
    {
        string title = "You found a magic Crystal";
        string message = "What do you want to do?";
        //Three things must be specified for each button: an SDL flag (or the number 0), the ID number to be returned if the button is selected, and the text for the button
        const SDL_MessageBoxButtonData buttons[2] = {
                { 0, 1, "Leave crystal" }, //button with ID 1
                { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Take crystal" } //button with ID 0
        }; //NOTE that the buttons appear in the REVERSE order of how they are specified above
        const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION, NULL, title.c_str(), message.c_str(), SDL_arraysize(buttons), buttons, NULL };
        //NOTE that the first parameter can be: SDL_MESSAGEBOX_ERROR, SDL_MESSAGEBOX_WARNING, or SDL_MESSAGEBOX_INFORMATION
        int answer;
        SDL_ShowMessageBox(&messageboxdata, &answer); //answer will hold the ID of the pressed button 
        if (answer == 0) //The user must have pressed the "Take crystal" button
        {
            taken = true;
            Item* ptr = list->Remove("crystal"); // remove 1 crystal in the board if the player found it
            delete ptr;
            p.inventory->Insert(crystal); // insert the found crystal to the player's bag
        }
    }
    visited = true;
    return 1;
}

void Crystal::render()
{
    //Only render the picture for this location if we have been here (visited == true)
    //but we did not "Take crystal" (taken == false)
    // or when the player drop it
    if (visited == true && taken == false)
    {
        Videogame::renderBitMap((int)(symbol));
    }
}
