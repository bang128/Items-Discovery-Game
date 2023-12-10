// Based on lab 20 and modified to fit to my idea

//FileName:		videoGame.h
//Programmer:	Dan Cliburn
//Date:			9/15/2015
//Purpose:		This file defines the header for the Videogame class
//We will use OpenGL (www.opengl.org) and SDL (www.libsdl.org) for the game


#ifndef VIDEOGAME_H
#define VIDEOGAME_H

#include "Game.h"
#include <SDL.h>
#include <Windows.h> //Must include this here to get it to compile
#include <GL/GLU.h>

class Videogame : public Game
{
	private:
		//SDL and other Graphics variables
		SDL_Window *display;
		SDL_GLContext oglcontext;
		GLuint playerTexID;

		//Variables to handle player movement
		double Eye[3], Aim[3], Up[3];

		//Variables to manage the Heads Up Display (HUD) display
		static string message1;  // to show player's name "use the arrow key to move"
		static string message2; // to show which normal items the player has got
		static string message3; // to show how many special items left that they player needs to find
		static string message4;  // to show "Press button D to drop your item"
		static string message5;  // to show "Invalid move" or "Invalid button"

	public:
		Videogame();

		static void setMessage1(string s) {message1 = s;}
		static void setMessage2(string s) {message2 = s;}
		static void setMessage3(string s) {message3 = s;}
		static void setMessage4(string s) {message4 = s;}
		static void setMessage5(string s) { message5 = s; }
		static string getMessage1() {return message1;}
		static string getMessage2() {return message2;}
		static string getMessage3() {return message3;}
		static string getMessage4() {return message4;}
		static string getMessage5() { return message5; }

		bool init();  //sets up both SDL and OpenGL
		
		void playGame();
		void drawGame();
		void instructions();

		static void renderBitMap(int texID);
		bool handleEvent(SDL_Event *theEvent);
		void drawHUD();
		void endGame();
};

#endif