#include <vector>
#include <SDL.h>
#include "ioManager.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "player.h"
#include "Hud.h"
#include "scaledSprite.h"

class Manager {
public:
  Manager ();
  ~Manager ();
  void play();
  void switchSprite();

private:
  const bool env;
  const IOManager& io;
  Clock clock;

  SDL_Surface * const screen;
  SDL_Surface * const orbSurface;
  World Sky;
  World Buildings;
  World Pyramid;
  World Land;
  Player player;
  Viewport& viewport;
  int flag2;
  Hud hud1;
  int currentSprite;
  std::vector<Drawable*> sprites;
  std::vector<ScaledSprite*> orbs;
  bool makeVideo;
  int frameCount;
  const std::string username;
  const std::string title;
  const int frameMax;

  void draw() const;
  bool checkForCollisions() const;
  void update();
  void makeEnemy();
  void makeOrbs();
  void printOrbs() const;

  Manager(const Manager&);
  Manager& operator=(const Manager&);
  void makeFrame();
};
