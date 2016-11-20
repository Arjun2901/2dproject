#include "Enemy2Msprite.h"
#include "gamedata.h"
#include "frameFactory.h"
#include <iostream>
#include <string>
#include <iomanip>
#include "sprite.h"
#include "explodingSprite.h"

void Enemy2Msprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	unsigned int mid = numberOfFrames/2;
	if (timeSinceLastFrame > frameInterval) 
	{
        if(velocityX() > 0)
        {
            currentFrame = (currentFrame+1) % mid;
        }
        else 
        {
            if(currentFrame > mid)
            {
                currentFrame =  (currentFrame+1) % numberOfFrames;
            }
            if(currentFrame < mid)
            {
                currentFrame = (currentFrame + mid + 1) % numberOfFrames;
            }
        }
        timeSinceLastFrame = 0;
	}
}


Enemy2Msprite::Enemy2Msprite( const std::string& name, const Vector2f &pos, const Vector2f &vel) :
  Drawable(name, pos, vel),
  explosion(NULL),
  frames( FrameFactory::getInstance().getFrames(name) ),
  worldWidth(Gamedata::getInstance().getXmlInt("Sky/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("Sky/height")),

  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight())
{ }

Enemy2Msprite::Enemy2Msprite(const Enemy2Msprite& s) :
  Drawable(s), 
  explosion(NULL),
  frames(s.frames),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  frameWidth( s.frameWidth ),
  frameHeight( s.frameHeight )
  { }


void Enemy2Msprite::explode(){
	if(explosion) return;
	explosion = new ExplodingSprite(Sprite(getName(), getPosition(), getVelocity(), frames[currentFrame]));
}	
void Enemy2Msprite::draw() const { 
	if (explosion){
		explosion->draw();
		return;
	}
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frames[currentFrame]->draw(x, y);
}

void Enemy2Msprite::update(Uint32 ticks) { 
  advanceFrame(ticks);
if (explosion){
		explosion->update(ticks);
		if(explosion->chunkCount() == 0){
			delete explosion;
			explosion = NULL;
		}
		return;
  }
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( Y() < 0) {
    velocityY( abs( velocityY() ) );
  }
  if ( Y() > worldHeight-frameHeight) {
    velocityY( -abs( velocityY() ) );
  }

  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -abs( velocityX() ) );
 
  }  

}
