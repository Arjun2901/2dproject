#ifndef ENENMY2MSPRITE__H
#define ENEMY2MSPRITE__H
#include <string>
#include <vector>
#include "drawable.h"

class ExplodingSprite; 
class Enemy2Msprite : public Drawable {
public:
  Enemy2Msprite(const std::string&,const Vector2f&,const Vector2f&);
  Enemy2Msprite(const Enemy2Msprite&);
  virtual ~Enemy2Msprite() { } 

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
  Enemy2Msprite& operator=(const Enemy2Msprite& rhs);
};
#endif
