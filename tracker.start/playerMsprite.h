#ifndef PLAYERMSPRITE__H
#define PLAYERMSPRITE__H
#include <string>
#include <vector>
#include "drawable.h"

class ExplodingSprite; 
class playerMsprite : public Drawable {
public:
  playerMsprite(const std::string&,const Vector2f&,const Vector2f&);
  playerMsprite(const std::string&);
  playerMsprite(const playerMsprite&);
  virtual ~playerMsprite() { } 

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }
  void explode();
protected:
  ExplodingSprite* explosion;
  const std::vector<Frame *> frames;
  int worldWidth;
  int worldHeight;

  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int frameWidth;
  int frameHeight;

  void advanceFrame(Uint32 ticks);
  void flipImage(Uint32 ticks);
  playerMsprite& operator=(const playerMsprite& rhs);
};
#endif
