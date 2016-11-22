#include <iostream>
#include <cmath>
#include "multibullet.h"
#include "gamedata.h"
#include "collisionStrategy.h"

multibullet::multibullet(const std::string& name, const Vector2f& pos, const Vector2f& vel):
  TwowayMSprite(name, pos, vel),
  maxDistance(400),
  tooFar(false),
  strategy(new MidPointCollisionStrategy())
{ }

multibullet::multibullet(const multibullet& mb):
  TwowayMSprite(mb),
  maxDistance(mb.maxDistance),
  tooFar(mb.tooFar),
  strategy(new MidPointCollisionStrategy())
{ }

multibullet::~multibullet(){
  if(strategy){
    delete strategy;
    strategy = NULL;
  }
}

void multibullet::setStrategy(CollisionStrategy* aStrategy){
    strategy = aStrategy;
}

void multibullet::update(Uint32 ticks, const Vector2f& pPos) {
  
  Vector2f position = getPosition();
  //std::cout << "bullet position" << position[0] << std::endl;
  //std::cout << "player position" << pPos[0] << std::endl;
  if(Y()+frameHeight < 0 || Y() > worldHeight || X() < 0 || X() > worldWidth || position[0] > pPos[0] + maxDistance)
    tooFar = true;

  TwowayMSprite::update(ticks);
}

bool multibullet::collidedWith(const Drawable* d) {
  bool bRet = false;
  if(strategy){
    bRet = strategy->execute(*this, *d);
  }
  return bRet;
}

