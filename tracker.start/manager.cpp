#include <iostream>
#include <string>
#include <iomanip>
#include "multisprite.h"
#include "twowayMsprite.h"
#include "Enemy2Msprite.h"
#include "sprite.h"
#include "gamedata.h"
#include "manager.h"
#include "aaline.h"
#include "Hud.h"
#include "health.h"
#include <cmath>
#include <algorithm>

int flag = 0;
int flag1 = 0;

class ScaledSpriteCompare {
public:
  bool operator()(const ScaledSprite* lhs, const ScaledSprite* rhs) {
    return lhs->getScale() < rhs->getScale();
  }
};

Manager::~Manager() { 
  // These deletions eliminate "definitely lost" and
  // "still reachable"s in Valgrind.
  SDL_FreeSurface(orbSurface);
  for (unsigned i = 0; i < sprites.size(); ++i) {
    delete sprites[i];
  }
  for (unsigned i = 0; i < orbs.size(); ++i) {
    delete orbs[i];
  }
}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ), 
  screen( io.getScreen() ),
  orbSurface( io.loadAndSet(Gamedata::getInstance().getXmlStr("redorb/file"), 
              Gamedata::getInstance().getXmlBool("redorb/transparency")) ),
  Sky("Sky", Gamedata::getInstance().getXmlInt("Sky/factor") ),
  Buildings("Buildings", Gamedata::getInstance().getXmlInt("Buildings/factor") ),
  Pyramid("Pyramid", Gamedata::getInstance().getXmlInt("Pyramid/factor") ),
  Land("Land", Gamedata::getInstance().getXmlInt("Land/factor") ),
  player("redstar"),
  viewport( Viewport::getInstance() ),
  flag2(false),
  hud1(),
  currentSprite(0),
  sprites(),
  orbs(),
  makeVideo( false ),
  frameCount( 0 ),
  username(  Gamedata::getInstance().getXmlStr("username") ),
  title( Gamedata::getInstance().getXmlStr("screenTitle") ),
  frameMax( Gamedata::getInstance().getXmlInt("frameMax") )
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  SDL_WM_SetCaption(title.c_str(), NULL);
  atexit(SDL_Quit);
  makeOrbs();
  printOrbs();
  
  sprites.push_back( new TwowayMSprite("Transformer") );
  sprites.push_back( new Sprite("genie") );
  //sprites.push_back( new MultiSprite("Enemy") );
  
  makeEnemy();
  sprites.push_back( new MultiSprite("sword") );
  viewport.setObjectToTrack(sprites[currentSprite]);
}

void Manager::makeEnemy(){
	std::string name = "Enemy";
	unsigned numberofEnemy = Gamedata::getInstance().getXmlInt("Enemy/numberofEnemy");
	std::cout << "------------------Enemy-" << numberofEnemy << std::endl;
	Enemy2Msprite *enemies = NULL;
	Vector2f vel(Gamedata::getInstance().getXmlFloat("Enemy/speedX"),Gamedata::getInstance().getXmlFloat("Enemy/speedY"));
	for(unsigned int i=0; i < numberofEnemy; i++)
	{
		Vector2f pos(Gamedata::getInstance().getRandFloat(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),Gamedata::getInstance().getXmlInt(name+"/endLoc/x")),
		Gamedata::getInstance().getRandFloat(Gamedata::getInstance().getXmlInt(name+"/endLoc/x"),Gamedata::getInstance().getXmlInt(name+"/endLoc/y")));
		
		enemies = new Enemy2Msprite(name,pos,vel);
		sprites.push_back(enemies);
	}
	
	
}
void Manager::makeOrbs() {
  unsigned numberOfOrbs = Gamedata::getInstance().getXmlInt("numberOfOrbs");
  orbs.reserve( numberOfOrbs );
  for (unsigned i = 0; i < numberOfOrbs; ++i) {
    orbs.push_back( new ScaledSprite("redorb", orbSurface) );
  }
  sort(orbs.begin(), orbs.end(), ScaledSpriteCompare());
}

void Manager::printOrbs() const {
  for (unsigned i = 0; i < orbs.size(); ++i) {
    //std::cout << orbs[i]->getScale() << std::endl;
  }
}

void Manager::draw() const {
  
  Health bar;
  Sky.draw();
  for (unsigned j = 0; j < (orbs.size()/3); ++j) {
    orbs[j]->draw();
  }
  Land.draw(); 
  Buildings.draw();
  for (unsigned j = orbs.size()/3; j < orbs.size()/2; ++j) {
    orbs[j]->draw();
  }
  Pyramid.draw();
  player.draw();
  
  for (unsigned j = orbs.size()/2; j < (orbs.size()); ++j) {
    orbs[j]->draw();
  }

  for (unsigned i = 0; i < sprites.size(); ++i) {
    sprites[i]->draw();
  }
  
  if ( checkForCollisions() ) {
    io.printMessageAt("*** Oops ***, collision!", 320, 60);
    
    sprites[2]->explode();
  }
  else {
    io.printMessageAt("No Collision.", 320, 60);
  }
  
  if(flag2 || clock.getSeconds() < 4)
  {
	hud1.drawhud(clock.getSeconds(),clock.getfps());
  }
  io.printMessageAt(title, 10, 450);
  viewport.draw();
  bar.draw();
  
  SDL_Flip(screen);
}

void Manager::makeFrame() {
  std::stringstream strm;
  strm << "frames/" << username<< '.' 
       << std::setfill('0') << std::setw(4) 
       << frameCount++ << ".bmp";
  std::string filename( strm.str() );
  std::cout << "Making frame: " << filename << std::endl;
  SDL_SaveBMP(screen, filename.c_str());
}

void Manager::switchSprite() {
  currentSprite = (currentSprite+1) % sprites.size();
  viewport.setObjectToTrack(sprites[currentSprite]);
}

bool Manager::checkForCollisions() const {
  std::vector<Drawable*>::const_iterator sprite = sprites.begin();
  while ( sprite != sprites.end() ) {
    if ( player.collidedWith(*sprite) ) return true;
    ++sprite;
  }
  return false;
}

void Manager::update() {
  ++clock;
  Health bar;
  Uint32 ticks = clock.getElapsedTicks();

  static unsigned int lastSeconds = clock.getSeconds();
  if ( clock.getSeconds() - lastSeconds == 5 ) {
    lastSeconds = clock.getSeconds();
    //switchSprite();
  }

  for (unsigned int i = 0; i < sprites.size(); ++i) {
    sprites[i]->update(ticks);
  }
  for (unsigned j = 0; j < orbs.size(); ++j) {
    orbs[j]->update(ticks);
  }
  if ( makeVideo && frameCount < frameMax ) {
    makeFrame();
  }
  bar.update(ticks);
  
  player.update(ticks);
  player.stop();
  Sky.update();
  Buildings.update();
 // Pyramid.update();
  Land.update();
  viewport.update(); // always update viewport last
}

void Manager::play() {
  
  Health bar;
  SDL_Event event;
  bool done = false;
 // bool flag = false;
  
  while ( not done ) {
    while ( SDL_PollEvent(&event) ) {
      Uint8 *keystate = SDL_GetKeyState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
          done = true;
          break;
        }
        if ( keystate[SDLK_t] ) {
          switchSprite();
        }
       /* if ( keystate[SDLK_1] ) {
		  sprites[0]->explode();
        }*/
        if ( keystate[SDLK_i] ) {
          clock.toggleSloMo();
        }
        if ( keystate[SDLK_p] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if (keystate[SDLK_F4] && !makeVideo) {
          std::cout << "Making video frames" << std::endl;
          makeVideo = true;
        }
        
        if (keystate[SDLK_m]) 
        {
           bar.reset();
           break;
        }
        if(keystate[SDLK_F1]) {
			 if(!flag2)
			 { 
				flag2 = true;
			 }
			 else
			 {  
				flag2 = false;
		     }
		 }
		if(keystate[SDLK_d])
        {
			flag = 1;
		}
		if(keystate[SDLK_s])
		{
			flag1 = 1;
		}
		if(keystate[SDLK_a])
		{
			flag = -1;
		}
		if(keystate[SDLK_w])
		{
			flag1 = -1;
		}
		player.setCollisionStrategy(2);
      }
      if(event.type == SDL_KEYUP) 
      {
		 flag = 0; 
		 flag1 = 0; 
	  }
    }
    draw();	
    update();
  }
}
