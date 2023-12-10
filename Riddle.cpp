#include "Riddle.h"
#include "videoGame.h"

Riddle::Riddle(char s) : Location(s)
{
    list->Insert(riddle);
}


void Riddle::draw()
{
    if (visited) {
        cout << symbol;
    }
    else {
        cout << ".";
    }
}

int Riddle::visit(Player& p) {
    if (!IsVisited()) {
        visited = true;
        Item* ptr = list->Remove("riddle");  // remove the riddle from the list
        delete ptr;
        srand(time(NULL));
        int num = rand() % 10;
        string title = "Welcome to FUNNY RIDDLE";
        string message = "To pass this riddle, you need to find out the answer based on the following clues.";
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title.c_str(), message.c_str(), NULL);
        bool b;
        if (num == 0) {
            b = play("A famous mouse character of Disney", "Mickey", "Donald");
        }
        else if (num == 1) {
            b = play("King of the Gods on Olympus Mount in ancient Greek religion", "Zeus", "Hades");
        }
        else if (num == 2) {
            b = play("A country which is famous for Pyramids", "Egypt", "Korean");
        }
        else if (num == 3) {
            b = play("A famous studio which has made superhero movies such as Spider-man, Captain America, Iron-man, etc", "Marvel", "Disney");
        }
        else if (num == 4) {
            b = play("The largest planet in the Solar System", "Jupiter", "Mars");
        }
        else if (num == 5) {
            b = play("A famous Disney movie which is about the Snow Queen named Elsa", "Frozen", "Maleficent");
        }
        else if (num == 6) {
            b = play("A technology corporation that has the same name with a kind of fruit", "Apple", "Microsoft");
        }
        else if (num == 7) {
            b = play("A famous video sharing site", "Youtube", "Yahoo");
        }
        else if (num == 8) {
            b = play("A kind of fruit that has the same name with a color", "Orange", "Banana");
        }
        else if (num == 9) {
            b = play("A kind of bird that mainly live in the Antarctic", "Penguin", "Parrot");
        }

        if (b) {
            title = "Wonderful!!!";
            message = "You've found the correct answer. You got a Key into your bag.";
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title.c_str(), message.c_str(), NULL);
            p.inventory->Insert(key); // insert 1 riddle to the player's bag
        }
        else {
            title = "Oops!!!";
            message = "You've found the incorrect answer. You cannot get any Key into your bag.";
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title.c_str(), message.c_str(), NULL);
        }
    }
    return 1;
}


bool Riddle::play(string question, const char a[], const char b[]) {
    string title = "Riddle";
    string message = question;
    srand(time(NULL));
    int r = rand() % 2;
    int answer;
    if (r == 0) {
        const SDL_MessageBoxButtonData buttons[2] = {
                { 0, 1, b }, //button with ID 1
                { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, a } //button with ID 0
        };
        const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION, NULL, title.c_str(), message.c_str(), SDL_arraysize(buttons), buttons, NULL };
        SDL_ShowMessageBox(&messageboxdata, &answer);
    }
    else if (r == 1) {
        const SDL_MessageBoxButtonData buttons[2] = {
                { 0, 1, a }, //button with ID 1
                { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, b } //button with ID 0
        };
        const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION, NULL, title.c_str(), message.c_str(), SDL_arraysize(buttons), buttons, NULL };
        SDL_ShowMessageBox(&messageboxdata, &answer);
    }
    if (answer == r) return true;
    return false;
}

void Riddle::render()
{
    //Only render the picture for this location if we have been here (visited == true)

    if (visited == true)
    {
        Videogame::renderBitMap((int)(symbol));
    }
}