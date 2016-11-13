	#ifndef TWOWAYMPRITE__H
#define TWOWAYMSPRITE__H
#include <string>
#include <vector>
#include "drawable.h"

class ExplodingSprite; 
class TwowayMSprite : public Drawable {
public:
  TwowayMSprite(const std::string&);
  TwowayMSprite(const TwowayMSprite&);
  virtual ~TwowayMSprite() { } 

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
  TwowayMSprite& operator=(const TwowayMSprite& rhs);
};
#endif
