#ifndef HEALTH__H
#define HEALTH__H

#include "vector2f.h"
#include "ioManager.h"
#include "aaline.h"
#include "playerMsprite.h"

class Health {
public:
  Health();
  Health(int sx, int sy, int tl, int cl, 
         float t, float inc, Uint32 c, float sp);
  void draw() const;
  void update();
  void reset() { currentLength = totalLength; }
private:
  SDL_Surface* screen;
  Vector2f start;
  int totalLength;
  int currentLength;
  int thick;
  float increments;
  float interval;
  int deltaTime;
  const Uint32 RED;
  const Uint32 GRAY;
  const Uint32 BLACK;
  const Uint32 color;
  void drawBox() const;
  Health(const Health&);
  Health& operator=(const Health&);
};
#endif
