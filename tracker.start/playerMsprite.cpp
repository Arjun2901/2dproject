#include "playerMsprite.h"
#include "gamedata.h"
#include "frameFactory.h"
#include <iostream>
#include <string>
#include <iomanip>
#include "sprite.h"
#include "explodingSprite.h"

extern int flag;
extern int flag1;
void playerMsprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	unsigned int mid = numberOfFrames/2;
	if (timeSinceLastFrame > frameInterval) 
	{
        if(velocityX() > 0)
        {
			if(flag == 0)
            {
				mid = 1;
			}
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
            if(flag == 0)
            {
				currentFrame = 5;
			}
        }
        timeSinceLastFrame = 0;
	}
}

playerMsprite::playerMsprite( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
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

playerMsprite::playerMsprite( const std::string& name, const Vector2f &pos, const Vector2f &vel) :
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

playerMsprite::playerMsprite(const playerMsprite& s) :
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


void playerMsprite::explode(){
	if(explosion) return;
	explosion = new ExplodingSprite(Sprite(getName(), getPosition(), getVelocity(), frames[currentFrame]));
}	
void playerMsprite::draw() const { 
	if (explosion){
		explosion->draw();
		return;
	}
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frames[currentFrame]->draw(x, y);
}

void playerMsprite::update(Uint32 ticks) { 
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
 // setPosition(getPosition() + incr);
  float x = incr[0] ;
  float y = incr[1];
  if(flag == 1)
  {
	  if(X() < 1510)
	  {
		float t = X() + x;
		X(t);
	  }
  }
  if(flag == -1)
  {
	  if(X() > 0)
	  {
		float t = X() + x;
		X(t);
	  }
  }
  
  if(flag1 == 1)
  {
	  if(Y() < 695)
	  {
		float s = Y() + y;
		Y(s);
	  }
  }
  if(flag1 == -1)
  {
	  if(Y() > 620)
	  {
	 float s = Y() - y;
	 Y(s);
 }
  }
  if (flag1 == 1) {
    velocityY( abs( velocityY() ) );
  }
  if ( flag1 == -1) {
    velocityY( abs( velocityY() ) );
  }

  if (flag == 1)
  {
    velocityX( abs( velocityX() ) );
  }
 else if ( flag == -1) {
      velocityX( -abs( velocityX() ) );
  }    
}