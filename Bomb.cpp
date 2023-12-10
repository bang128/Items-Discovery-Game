#include "Bomb.h"
#include "videoGame.h"

Bomb::Bomb(char s): Location(s)
{
    list->Insert(bomb);  // insert a bomb to the world's board
}


void Bomb::draw()
{
    if (visited) {
        cout << symbol;
    }
    else {
        cout << ".";
    }
}

int Bomb::visit(Player& p) {
    if (visited == false)
    {
 
        string title = "Oops.You are facing a BOMB.";
        string message = "Choose the number that you believe as the bomb's password: ";
        const SDL_MessageBoxButtonData buttons[2] = {
                { 0, 1, "0" }, //button with ID 1
                { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "1" } //button with ID 0
        }; 
        const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION, NULL, title.c_str(), message.c_str(), SDL_arraysize(buttons), buttons, NULL };
        
        int answer, pass;
        srand(time(NULL));
        pass = rand() % 2;
        SDL_ShowMessageBox(&messageboxdata, &answer); //answer will hold the ID of the pressed button 
        if (answer == pass) {
            visited = true;
        }
        else {
            string message = "The bomb exploded. However, you can use your Clover to cure yourself. Let's check your bag...\n";
            string title = "BOOMMMMMMM!";
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title.c_str(), message.c_str(), NULL);
            if (p.inventory->Find("clover") == NULL) { //if the player has no Clover in bag
                message = "Oops! You don't have any Clovers in bag.";
                title = "GAME OVER";
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title.c_str(), message.c_str(), NULL); // then he/she loses
                exit(0);
            }
            else {
                title = "Yeah! You have Clovers in bag.";
                message = "Do you want to use it?";
                const SDL_MessageBoxButtonData buttons[2] = {
                        { 0, 1, "No" }, //button with ID 1
                        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "YES" } //button with ID 0
                }; 
                const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION, NULL, title.c_str(), message.c_str(), SDL_arraysize(buttons), buttons, NULL };
                
                int choice;
                SDL_ShowMessageBox(&messageboxdata, &choice); //choice will hold the ID of the pressed button
                if (choice == 0) {
                    Item* ptr = p.inventory->Remove("clover"); // remove 1 clover in the player's bag
                    delete ptr;
                }
                else {
                    title = "GAME OVER";
                    message = "You lose.";
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title.c_str(), message.c_str(), NULL);
                    exit(0);
                }
            }
        }
    }
    visited = true;
    return 1;
}

void Bomb::render()
{
    //Only render the picture for this location if we have been here (visited == true)
    if (visited == true)
    {
        Videogame::renderBitMap((int)(symbol));
    }
}