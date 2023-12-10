// Based on lab 20 and modified to fit to my idea

//FileName:		Videogame.cpp
//Programmer:	Dan Cliburn
//Date:			9/15/2015
//Purpose:		This file defines the methods for the Videogame class
//See:  http://www.sdltutorials.com/sdl-tutorial-basics/
//		http://www.sdltutorials.com/sdl-opengl-tutorial-basics/
//		http://www.sdltutorials.com/sdl-soundbank
//for many more details on how to write an OpenGL program using SDL.
//You might also want to go to these pages which will link you to other tutorials on how to do stuff with SDL.
//Be warned, however, that a lot of the tutorials describe SDL 1.2, but we will be using SDL 2 in this lab.

#include "videogame.h"
#include "texture.h"
#include <SDL.h>
#include <Windows.h>  //Must include this here to get it to compile
//#include <gl/gl.h>
//#include <gl/glu.h>
#include <glut.h>  //includes gl.h and glu.h
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

const int MONITORWIDTH = 1200;
const int MONITORHEIGHT = 800;

//Static class variables
string Videogame::message1 = "";
string Videogame::message2 = "";
string Videogame::message3 = "";
string Videogame::message4 = "";
string Videogame::message5 = "";

Videogame::Videogame()
{
	message1 = "";
	message2 = "";
	message3 = "";
	message4 = "";
	message5 = "";
}

//Initializes SDL and OpenGL
bool Videogame::init()
{
	display = NULL;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}

	if ((display = SDL_CreateWindow("Project 8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, MONITORWIDTH, MONITORHEIGHT, SDL_WINDOW_OPENGL)) == NULL)
	{
		return false;
	}
	oglcontext = SDL_GL_CreateContext(display);

	glClearColor(0.3, 0.3, 0.3, 1.0);  //Will be the color of the background
	
	//Set parameters for how we want to view the scene
	glViewport(0,0, MONITORWIDTH, MONITORHEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Create a view frustum whose aspect ratio matches that of the window 
	double aspectRatio = ((double)(MONITORWIDTH)) / ((double)(MONITORHEIGHT));
	glFrustum(-0.1, 0.1, -0.1/aspectRatio, 0.1/aspectRatio, 0.1, 100);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Do OpenGL init stuff
	glEnable(GL_DEPTH_TEST);
	glLineWidth(1.0); //Controls the thickness of lines

	//Now, initialize our other variables for drawing the game
	Eye[0] = Aim[0] = cols/2.0;
	Eye[2] = 1.28*rows;
	Aim[2] = rows/2.0;
	Eye[1] = rows/2.0;
	Aim[1] = 0.0;
	Up[0] = 0.0;
	Up[1] = 1.0;
	Up[2] = 0.0;

	Texture loader;
	loader.loadTexBMP("images//crystal.bmp", (int)('C'), addAlpha);  //Image for crystal
	loader.loadTexBMP("images//bomb.bmp", (int)('B'), addAlpha);     // Image for bomb
	loader.loadTexBMP("images//riddle.bmp", (int)('R'), addAlpha);   // Image for riddle
	loader.loadTexBMP("images//clover.bmp", (int)('c'), addAlpha);   // Image for clover
	loader.loadTexBMP("images//key.bmp", (int)('K'), addAlpha);      // Image for key
	loader.loadTexBMP("images//chocolate.bmp", (int)('1'), addAlpha);// Image for chocolate
	loader.loadTexBMP("images//candy.bmp", (int)('2'), addAlpha);    // Image for candy
	loader.loadTexBMP("images//monster.bmp", (int)('M'), addAlpha);  // Image for monster

	glGenTextures(1, &playerTexID); 
	loader.loadTexBMP("images//doraemon.bmp", playerTexID, addAlpha);  //Image for the player	

	return true;  //Everything got initialized
}


//Method to draw an image associated with texID
void Videogame::renderBitMap(int texID)
{
	// make sure the transparent part of the texture isn't drawn
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0);

	// select the texture
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, texID);
	glBegin(GL_QUADS);
		// bottom left corner
		glTexCoord2f(0.0, 0.0); 
		glVertex3f(0.0, 0.0, 0.0);
					
		// bottom right corner
		glTexCoord2f(1.0, 0.0);
		glVertex3f(1.0, 0.0, 0.0);

		// top right corner
		glTexCoord2f(1.0, 1.0);
		glVertex3f(1.0, 1.0, 0.0);
					
		// top left corner
		glTexCoord2f(0.0, 1.0);
		glVertex3f(0.0, 1.0, 0.0);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
}

//Draws the Heads Up Display (HUD) that shows players' info
void Videogame::drawHUD()
{
	unsigned int i;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Create a view frustum whose aspect ratio matches that of the window 
	double aspectRatio = ((double)(MONITORWIDTH)) / ((double)(MONITORHEIGHT));
	int width = 260;  //TODO:  Make this bigger if you need more space for your messages
	int height = width/aspectRatio;
	glOrtho(0, width, 0, height, -10, 10);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1.0, 1.0, 1.0);  //COLOR OF THE TEXT MESSAGES
	glPushMatrix();
		glTranslatef(0.0, .95*height, 0.0);
		glScalef(0.05, 0.05, 0.05);
		for (i = 0; i < message1.length(); i++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, message1[i]);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0.0, .90*height, 0.0);
		glScalef(0.05, 0.05, 0.05);
		for (i = 0; i < message2.length(); i++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, message2[i]);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, .85*height, 0.0);
		glScalef(0.05, 0.05, 0.05);
		for (i = 0; i < message3.length(); i++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, message3[i]);
	glPopMatrix();
	
	// make up 2 more messages
	glPushMatrix();
	glTranslatef(0.0, .80 * height, 0.0);
	glScalef(0.05, 0.05, 0.05);
	for (i = 0; i < message4.length(); i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, message4[i]);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, .75 * height, 0.0);
	glScalef(0.05, 0.05, 0.05);
	for (i = 0; i < message5.length(); i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, message5[i]);
	glPopMatrix();


	//Put the program back in the proper projection for drawing the rest of the game
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-0.1, 0.1, -0.1/aspectRatio, 0.1/aspectRatio, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//This method draws the map of the world that the user sees
void Videogame::drawGame()
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//Establish the eye and aim positions, and the up vector 
	//The analogy is that of holding a digital camera and pointing it at what you want to take a picture of:
	//Eye is where the camera is at
	//Aim is what the camera is pointed at
	//Up is a vector that defines the up direction
	//NOTE: you do not need to change these parameters for Project 8
	gluLookAt(Eye[0],Eye[1],Eye[2], Aim[0],Aim[1],Aim[2], Up[0],Up[1],Up[2]);
 
	//Go through each location and render what the user should see
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			if (playerRow == r && playerCol == c) //Is this the square the player is at?
			{
				glColor3f(0.1, 0.8, 0.1);  //If so, then draw this square a different color
			}
			else
			{
				glColor3f(0.1, 0.4, 0.1); //color for ground locations the player has visited
			}
			if (world[r][c]->IsVisited() == true || (playerRow == r && playerCol == c) )
			{	
				//Player has been to or is currently at this spot
				//Draw the green square that makes up the ground at a visited location
				glBegin(GL_QUADS);
					glVertex3f(c, 0.0, r);
					glVertex3f(c, 0.0, r+1.0);
					glVertex3f(c+1.0, 0.0, r+1.0);
					glVertex3f(c+1.0, 0.0, r);
				glEnd();
				
				//Now render what the player should see at this location
				glPushMatrix(); //Save the current transformation state
					glTranslatef(c, 0, r+0.7);
					world[r][c]->render(); //Go render the appropriate image (if any) for this location
				glPopMatrix();
			}
		}
	}

	//Now render the Player's Bitmap Image
	glPushMatrix(); //Save the current transformation state
		glTranslatef(playerCol, 0, playerRow+0.3);
		renderBitMap(playerTexID);
	glPopMatrix();

	//Draw the text messages. HUD stands for Heads Up Display
	drawHUD();
	
	SDL_GL_SwapWindow(display);
}

//This method handles user key presses on the keyboard
bool Videogame::handleEvent(SDL_Event *theEvent) 
{ 
	string title = "Error";
	string message = "Invalid move";
	switch(theEvent->type)
	{
		case SDL_QUIT:  //User clicks on the 'X' in the Window
		{
			endGame();
			exit(0);
		}
		case SDL_KEYDOWN:
		{
			if (theEvent->key.keysym.sym == SDLK_DOWN) //Code that allows the player to move down
			{
				playerRow++;
				if (playerRow >= rows) {  // if the player moves out of the board
					playerRow--;  // his/her current location is set back to the previous location
					message5 = "Invalid move";  // then the program shows that the player made an invalid move
					drawGame();
					Sleep(1000); //Show the error message for one second
				}
			}
			//TODO: Add code so that the user can move left, right, and up
			else if (theEvent->key.keysym.sym == SDLK_UP) {  // similar to the above
				playerRow--;
				if (playerRow < 0) {
					playerRow++;
					message5 = "Invalid move";
					drawGame();
					Sleep(1000); //Show the error message for one second
				}
			}
			else if (theEvent->key.keysym.sym == SDLK_LEFT) { //similar to the above
				playerCol--;
				if (playerCol < 0) {
					playerCol++;
					message5 = "Invalid move";
					drawGame();
					Sleep(1000); //Show the error message for one second
				}
			}
			else if (theEvent->key.keysym.sym == SDLK_RIGHT) {  // similar to the above
				playerCol++;
				if (playerCol >= cols) {
					playerCol--;
					message5 = "Invalid move";
					drawGame();
					Sleep(1000); //Show the error message for one second
				}
			}
			
			//TODO: ADD CODE TO SUPPORT OTHER TYPES OF KEY PRESSES
			else if (theEvent->key.keysym.sym == SDLK_d)  // when the player chooses to drop item, he/she can chooses to drop item at any location in the board
			{
				title = "Drop your item";
				message = "You pressed the d key to drop your item. What do you want to drop?\nNote: If this is a Storage location, you can retrieve your item later and vice versa.";
				const SDL_MessageBoxButtonData buttons[4] = {
					{0, 3, "Cancel"},
					{0, 2, "Key"}, // button with ID 2
					{ 0, 1, "Clover" }, //button with ID 1
					{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Crystal" } //button with ID 0
				}; //NOTE that the buttons appear in the REVERSE order of how they are specified above
				const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION, NULL, title.c_str(), message.c_str(), SDL_arraysize(buttons), buttons, NULL };
				// show the box to ask the player which item he/she would like to drop and warn him/her of losing item if this is not a Storage location, the player also can choose to cancel the drop
				int answer;
				SDL_ShowMessageBox(&messageboxdata, &answer); //answer will hold the ID of the pressed button
				string item;
				char i;
				if (answer == 0) {   				//set item's name and symbol
					item = "crystal";
					i = 'C';
				}
				else if (answer == 1) {
					item = "clover";
					i = 'c';
				}
				else if (answer == 2) {
					item = "key";
					i = 'K';
				}
				else return true;  // if the player chooses to cancel, the function returns true, then nothing happens
				
				if (p.inventory->Find(item)) {
					if (world[playerRow][playerCol]->GetStorage()) { 
						world[playerRow][playerCol]->SetSymbol(i);  // set symbol based on character i above
						world[playerRow][playerCol]->SetStored(true); // the player chooses to store the item, and fortunately this is a Storage location so set stored to true
						world[playerRow][playerCol]->visit(p); 
					}
					else {  // because this is not a Storage location, nothing happens and the player loses his/her item
						title = "Non-storage location";
						message = "This is not a Storage location, so your " + item + " got lost.";
						SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title.c_str(), message.c_str(), NULL);
						Item* ptr = p.inventory->Remove(item);
						delete ptr;
					}
				}
				else { // when the player would like to drop a item that he/she does not have in bag
					title = "Error";
					message = "You don't have any " + item + " in your bag.";
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title.c_str(), message.c_str(), NULL);
				}
				
			}
			else
			{  // when the player presses an incorrect button
				message5 = "Invalid button";
				drawGame();
				Sleep(1000); //Show the error message for one second
			}
			return true;
		}
	} 
	return false; //was not a KEYDOWN event
}

//This method controls the game
void Videogame::playGame()
{

	instructions(); //Tell the player how to play the game
	SetupGame();  //call setUpGame() from the Game class

	if (!init()) //This function (defined above) sets up OpenGL and SDL
	{
		cout << "Not everything was initialized" << endl;
		return;
	}

	SDL_Event events;  //Makes an SDL_Events object that we can use to handle events
	SDL_PollEvent(&events); //This initializes the events object
	while (!CheckWin()) //the game continues as long as the player has not got at least 1 Crystal, 1 Clover, 1 Key and all Special items
	{					// CheckWin() is called from Game class
		//Build message strings for the HUD (Head's Up Display)
		message1 = p.GetName() + ", use the arrow keys to move.";
		stringstream out2;
		out2 << p.normalPrint();
		message2 = out2.str();
		stringstream out3;
		out3 << p.specialPrint();
		message3 = out3.str();
		message4 = "Press button D to drop your item";
		drawGame(); //draw the current state of the game

		do
		{
			SDL_WaitEvent(&events); //wait here until there is an event to handle
		} while (handleEvent(&events) == false); //keep looping if event was something other than a KEYDOWN 
		drawGame(); //update the user's position on the gameboard

		//reset message strings and resolve actions involved with the move
		message1 = message2 = message3 = message4 = message5 ="";
		world[playerRow][playerCol]->visit(p);
		CheckWin();
	}
	string title = "CONGRATULATE!!!";
	string message = "You've found all neccessary items. You win!!!~~~~";
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title.c_str(), message.c_str(), NULL); // display a box to show the player has won the game
	endGame();
	system("pause");
}

void Videogame::instructions()
{
	//In this example we use the SDL_ShowSimpleMessageBox function to display instructions to the user. 
	//See: https://wiki.libsdl.org/SDL_ShowSimpleMessageBox
	string message = "LET'S PLAY ITEMS DISCOVER GAME.\nIn this game you use the arrow keys to navigate around on the game board to gain at least one item of Crystal, Clover and Key, and all Special items.\n";
	message += "In this version of the game, there are also obstacles like Bomb and Monster which can take your items out of your bag!\nYou can dress button D to drop your item at any locations. If it is a Storage location, you can retrieve it later and vice versa.\nHave fun!";
	string title = "Items Discover Game";
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title.c_str(), message.c_str(), NULL);
	 //NOTE that the first parameter can be: SDL_MESSAGEBOX_ERROR, SDL_MESSAGEBOX_WARNING, or SDL_MESSAGEBOX_INFORMATION

	//Check to see if the user wants to play. Here we will use the SDL_ShowMessageBox function which allows the programmer to
	//specify his/her own buttons. See: https://wiki.libsdl.org/SDL_ShowMessageBox
	title = "Question?";
	message = "Are you ready to play?";
	//Three things must be specifed for each button: an SDL flag (or the number 0), the ID number to be returned if the button is selected, and the text for the button
	const SDL_MessageBoxButtonData buttons[3] = { 
			{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "CANCEL" }, //button with ID 2
			{0, 1, "NO"}, //button with ID 1
			{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "YES" } //button with ID 0
	}; //NOTE that the buttons appear in the REVERSE order of how they are specified above
	const SDL_MessageBoxData messageboxdata = { SDL_MESSAGEBOX_INFORMATION, NULL, title.c_str(), message.c_str(), SDL_arraysize(buttons), buttons, NULL };
										//NOTE that the first parameter can be: SDL_MESSAGEBOX_ERROR, SDL_MESSAGEBOX_WARNING, or SDL_MESSAGEBOX_INFORMATION
	int answer;
	do
	{
		SDL_ShowMessageBox(&messageboxdata, &answer); //answer will hold the ID of the pressed button
		if (answer == 1) //The user must have pressed the "NO" button
		{
			endGame();
			exit(0);
		}
		else if (answer == 2 || answer == -1) //The user must have pressed the "CANCEL" button or closed the Window
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Uh oh!", "You have to select YES or NO", NULL);
		}
	} while (answer != 0); //Loop until the user selects to play since the ID for "YES" is 0

	//We can still use the console to get input from the user until our graphics window is created (which happens as soon as this method ends).
	string name;
	cout << "To start the game, please let us know something about you!" << endl;
	cout << "What's your name? ";
	cin >> name;
	cout << "How old are you? ";
	int age;
	cin >> age;
	p.SetName(name);
	p.SetAge(age);
}

void Videogame::endGame()
{
	SDL_GL_DeleteContext(oglcontext);
	SDL_DestroyWindow(display);
	SDL_Quit();
}