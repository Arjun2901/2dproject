#ifndef HUD__H
#define HUD__H
#include <vector>
#include <SDL.h>



class Hud {
public:
Hud();
~Hud();
void drawhud(float,float, int, int) const;

private:
SDL_Surface* screen;
const Uint32 RED;
bool flag2;
Hud(const Hud&);
Hud& operator=(const Hud&);
};
#endif
