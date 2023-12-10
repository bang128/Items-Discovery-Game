#include "Monster.h"
#include "videoGame.h"

Monster::Monster(char s) : Location(s)
{
    list->Insert(monster);
}

void Monster::draw()
{
    if (visited) {
        cout << symbol;
    }
    else {
        cout << ".";
    }
}

int Monster::visit(Player& p)
{
    if (visited == false)
    {
        Item* ptr = list->Remove("monster");
        delete ptr;
        string title = "Be careful! You are facing an angry Monster.";
        string message = "The Monster extremely loves Crystal, so the only way to calm it is to give it your Crystals; or yield and then you will lose.\nAlso, the Monster is mean to protect Clover which is a magical curative leaf. If you give the Monster your Crystal, it will give its Clover back to you.";
        const SDL_MessageBoxButtonData buttons[2] = {
                { 0, 1, "Yield" }, //button with ID 1
                { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Give out Crystal" } //button with ID 0
        };
        const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION, NULL, title.c_str(), message.c_str(), SDL_arraysize(buttons), buttons, NULL };
        int answer;
        SDL_ShowMessageBox(&messageboxdata, &answer); //answer will hold the ID of the pressed button 

        if (answer == 0) {
            if (p.inventory->Find("crystal") == NULL) { // if the player doesn't have any crystal in his/ her bag
                title = "GAME OVER";
                message = "Sorry. You don't have any crystals in your bag.\nThe Monster is super angry and beats you. You lose.";
                // then he/she loses
                exit(0);
            }
            else { // if he/she has
                title = "GREAT!!!";
                message = "The Monster calms down and let you go with its Clover.";
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title.c_str(), message.c_str(), NULL);
                Item* ptr = p.inventory->Remove("crystal"); // remove 1 crystal in his/her bag
                delete ptr;
                p.inventory->Insert(clover); // but he/she can get 1 clover to his/her bag
            }
        }
        else {
            title = "GAME OVER";
            message = "You lose.";
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title.c_str(), message.c_str(), NULL);
            exit(0);
        }
    }
    visited = true;
    return 1;
}

void Monster::render()
{
    //Only render the picture for this location if we have been here (visited == true)
    if (visited == true)
    {
        Videogame::renderBitMap((int)(symbol));
    }
}