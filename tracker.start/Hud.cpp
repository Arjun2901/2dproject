#include <iostream>
#include <string>
#include <iomanip>
#include "Hud.h"
#include "aaline.h"
#include "ioManager.h"


Hud::Hud():
	screen(IOManager::getInstance().getScreen()),
	RED(SDL_MapRGB(screen->format, 0xff, 0, 0)),
	flag2(false){}
Hud::~Hud(){}
void Hud::drawhud(float secs, float fpss) const {
	IOManager& io = IOManager::getInstance();
    io.printMessageValueAt("Seconds: ", secs, Gamedata::getInstance().getXmlInt("Hud/xval"), Gamedata::getInstance().getXmlInt("Hud/yval"));
    io.printMessageValueAt("Frames per sec(fps) = ",fpss, Gamedata::getInstance().getXmlInt("Hud/xval"), 
    Gamedata::getInstance().getXmlInt("Hud/yval")+15);
    io.printMessageAt("Tracking Transformer", Gamedata::getInstance().getXmlInt("Hud/xval"), 
    Gamedata::getInstance().getXmlInt("Hud/yval")+30);
    io.printMessageAt("Gameplay : ", Gamedata::getInstance().getXmlInt("Hud/xval"), Gamedata::getInstance().getXmlInt("Hud/yval")+50);
    io.printMessageAt("W : Move Up", Gamedata::getInstance().getXmlInt("Hud/xval")+90, Gamedata::getInstance().getXmlInt("Hud/yval")+90);
    io.printMessageAt("A : Move left      D: Move right ", Gamedata::getInstance().getXmlInt("Hud/xval")+10, 
    Gamedata::getInstance().getXmlInt("Hud/yval")+130);
    io.printMessageAt("S : Move Down", Gamedata::getInstance().getXmlInt("Hud/xval")+90, Gamedata::getInstance().getXmlInt("Hud/yval")+170);
     Sint16 y1 = 20;
     y1 += 40;
     Sint16 x1 = 50, x2 = 350;
     
     Draw_AALine(screen, x1,y1, x2,y1, 2.0f,RED);
	 y1= 260;
     Draw_AALine(screen, x1,y1, x2,y1, 2.0f,RED);
     Sint16 y2;
     x1 = 50, y1 = 260, y2 = y1-200;
     Draw_AALine(screen, x1,y1, x1,y2, 2.0f, RED);
     x1 = 350, y1 = 260, y2 = y1-200;
     Draw_AALine(screen, x1,y1, x1,y2, 2.0f, RED);
     Draw_AALine(screen, 202, 62, 202, 262, 298, 128, 128, 128, 0xff/2);  
     SDL_Flip(screen);
}

