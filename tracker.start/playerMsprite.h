#ifndef PLAYERMSPRITE__H
#define PLAYERMSPRITE__H
#include <string>
#include <vector>
#include "drawable.h"
#include "gamedata.h"
#include "collisionStrategy.h"
#include "playerMsprite.h"
#include "multibullets.h"

class ExplodingSprite; 

class playerMsprite : public Drawable {
public:
  playerMsprite(const std::string&,const Vector2f&,const Vector2f&);
  playerMsprite(const std::string&);
  playerMsprite(const playerMsprite&);
  virtual ~playerMsprite(); 
  virtual void draw() const; 
  void shoot();
  void reset();
  multibullets getbullet() const { return bullet; }

  virtual void update(Uint32 ticks);
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }
  bool collidedWith(const Drawable* d) const
  {
	  return strategy->execute(*this, *d);
  }
  void setCollisionStrategy(int index) {
    strategy = strategies[index];
  }
  void explode();
protected:
  ExplodingSprite* explosion;
  std::string name1;
  multibullets bullet;
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
 // float playerWidth;
 // float playerHeight;
 // Vector2f velocity;
  std::vector<CollisionStrategy*> strategies;
  CollisionStrategy * strategy;
  
  
};
#endif
