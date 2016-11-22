#include <iostream>
#include <string>
#include <iomanip>
#include "Hud.h"
#include "aaline.h"
#include "ioManager.h"
#include "multibullets.h"

Hud::Hud():
	screen(IOManager::getInstance().getScreen()),
	RED(SDL_MapRGB(screen->format, 0xff, 0xff, 0)),
	flag2(false){}
Hud::~Hud(){}
void Hud::drawhud(float secs, float fpss, int bulletlistsize, int freelistsize) const {
	IOManager& io = IOManager::getInstance();
    io.printMessageValueAt("Seconds: ", secs, Gamedata::getInstance().getXmlInt("Hud/xval"), Gamedata::getInstance().getXmlInt("Hud/yval"));
    io.printMessageValueAt("Frames per sec(fps) = ",fpss, Gamedata::getInstance().getXmlInt("Hud/xval"), 
    Gamedata::getInstance().getXmlInt("Hud/yval")+15);
    io.printMessageAt("Let's save Daisie", Gamedata::getInstance().getXmlInt("Hud/xval"), 
    Gamedata::getInstance().getXmlInt("Hud/yval")+30);
    io.printMessageAt("Gameplay : ", Gamedata::getInstance().getXmlInt("Hud/xval"), Gamedata::getInstance().getXmlInt("Hud/yval")+50);
    io.printMessageAt("W : Move Up", Gamedata::getInstance().getXmlInt("Hud/xval")+90, Gamedata::getInstance().getXmlInt("Hud/yval")+70);
    io.printMessageAt("A : Move left      D: Move right ", Gamedata::getInstance().getXmlInt("Hud/xval")+5, 
    Gamedata::getInstance().getXmlInt("Hud/yval")+105);
    io.printMessageAt("S : Move Down", Gamedata::getInstance().getXmlInt("Hud/xval")+90, Gamedata::getInstance().getXmlInt("Hud/yval")+140);
    io.printMessageAt("Spacebar : Shoot", Gamedata::getInstance().getXmlInt("Hud/xval")+5, Gamedata::getInstance().getXmlInt("Hud/yval")+160);
    io.printMessageValueAt("bulletlist = ", bulletlistsize, Gamedata::getInstance().getXmlInt("Hud/xval")+5, Gamedata::getInstance().getXmlInt("Hud/yval")+175);
    io.printMessageValueAt("freelist = ", freelistsize, Gamedata::getInstance().getXmlInt("Hud/xval")+5, Gamedata::getInstance().getXmlInt("Hud/yval")+190);
    io.printMessageAt("Press n to Reset Health bar : ", Gamedata::getInstance().getXmlInt("Hud/xval")+5, Gamedata::getInstance().getXmlInt("Hud/yval")+205);
    io.printMessageAt("Press R to Restart Game : ", Gamedata::getInstance().getXmlInt("Hud/xval")+5, Gamedata::getInstance().getXmlInt("Hud/yval")+220);
    
     Sint16 y1 = 20;
     y1 += 0;
     Sint16 x1 = 10, x2 = 310;
     
     Draw_AALine(screen, x1,y1, x2,y1, 2.0f,RED);
	 y1= 260;
     Draw_AALine(screen, x1,y1, x2,y1, 2.0f,RED);
     Sint16 y2;
     x1 = 10, y1 = 260, y2 = y1-240;
     Draw_AALine(screen, x1,y1, x1,y2, 2.0f, RED);
     x1 = 310, y1 = 260, y2 = y1-240;
     Draw_AALine(screen, x1,y1, x1,y2, 2.0f, RED);
     Draw_AALine(screen, 162, 22, 162, 262, 298, 128, 128, 128, 0xf0/2);  
     SDL_Flip(screen);
}

