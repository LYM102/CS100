#pragma once

/// \file
/// \brief This file contains the game lifecycle and logics.
/// There are 5 important functions:
/// `GameInit`, `GameInput`, `GameUpdate`, `GameTerminate`, and
/// the most important: `GameLifecycle`.
/// Please read the corresponding comments to understand their relationships.

//
//
//
//
//
#include "Config.h"
#include "Renderer.h"

#include <time.h>

typedef struct {
  char keyHit; // The keyboard key hit by the player at this frame.
} Game;

// The game singleton.
static Game game;
// The keyboard key "ESC".
static const char keyESC = '\033';

//
/// \brief Configure the scene (See `Scene.h`) with `config` (See `Config.h`), and
/// perform initializations including:
/// 1. Terminal setup.
/// 2. Memory allocations.
/// 3. Map and object generations.
/// 4. Rendering of the initialized scene.
///
/// \note This function should be called at the very beginning of `GameLifecycle`.
//
/// \brief Function1:Generate a random char from {'a','w','s','d'} to represent the direction of the tank.
char RandomAWSD(void) {
  int randomValue = rand() % 4;
  switch (randomValue) {
  case 0:
    return 'a'; // Left
  case 1:
    return 'w'; // Up
  case 2:
    return 's'; // Down
  case 3:
    return 'd'; // Right
  }
  return 'a'; // Default value.
}

/// \brief :Generate a random Dir from {eDirOP,eDirNO,eDirON,eDirPO} to represent the direction.
char RandomDirection(void) {
  int randomValue = rand() % 4;
  switch (randomValue) {
  case 0:
    return eDirOP; // Up
  case 1:
    return eDirNO; // Left
  case 2:
    return eDirON; // Down
  case 3:
    return eDirPO; // Right
  }
  return eDirInvalid; // Default value.
}

/// \brief Function3:check if it is the valid position for a 3*3 Object.
bool is_pos_valid(Vec pos, Tank *currentTank) {
  // Firstly check the Walls and Solids.
  for (int dy = -1; dy <= 1; dy++) {
    for (int dx = -1; dx <= 1; dx++) {
      Vec temp_pos = (Vec){pos.x + dx, pos.y + dy};
      if (temp_pos.x <= 0 || temp_pos.x >= map.size.x - 1 || temp_pos.y <= 0 || temp_pos.y >= map.size.y - 1)
        return false;
      if (map.flags[Idx(temp_pos)] == eFlagSolid || map.flags[Idx(temp_pos)] == eFlagWall)
        return false;
    }
  }
  // Then check other tanks.
  for (RegIterator it = RegBegin(regTank); it != RegEnd(regTank); it = RegNext(it)) {
    Tank *temp_tank = RegEntry(regTank, it);
    if (temp_tank == currentTank && currentTank != NULL) // temp_tenk,current_tank are the pointers.
      continue;
    if (abs(temp_tank->pos.x - pos.x) < 3 && abs(temp_tank->pos.y - pos.y) < 3)
      return false;
  }
  // If all checks passed, the position is valid.
  return true;
}

/// \brief generate ramdom position for tank
void Generate_Position(Tank *tank) {
  Vec validPositions[1000];
  int validCount = 0;
  // Serch all the map to find all of the valid positions.
  for (int y = 2; y < map.size.y - 3; y++)
    for (int x = 2; x < map.size.x - 3; x++)
      if (is_pos_valid((Vec){x, y}, tank))
        validPositions[validCount++] = ((Vec){x, y});
  // choose a random position from the valid positions.
  if (validCount > 0)
    tank->pos = validPositions[ramdom_generator(0, validCount - 1)];
}

void GameInit(void) {
  // Setup terminal.
  TermSetupGameEnvironment();
  TermClearScreen();

  // Configure scene.
  map.size = config.mapSize;
  int nEnemies = config.nEnemies;
  int nSolids = config.nSolids;
  int nWalls = config.nWalls;

  // Initialize scene.
  RegInit(regTank);
  RegInit(regBullet);
  // Initialize map.
  map.flags = (Flag *)malloc(sizeof(Flag) * map.size.x * map.size.y); // map.flags will be free in the GameTerminate()
  for (int y = 0; y < map.size.y; ++y)
    for (int x = 0; x < map.size.x; ++x) {
      Vec pos = {x, y};
      Flag flag = eFlagNone;
      if (x == 0 || y == 0 || x == map.size.x - 1 || y == map.size.y - 1)
        flag = eFlagSolid;

      map.flags[Idx(pos)] = flag;
    }
  // Initialize 3*3 # wall
  for (int i = 0; i < nWalls; i++) {
    Vec pos = RandPos();
    if (is_pos_valid(pos, NULL)) { // Send NULL in to comfirm not to neglect any tank
      for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
          Vec currentPos = {pos.x + x, pos.y + y};
          map.flags[Idx(currentPos)] = eFlagWall;
        }
      }
    }
  }
  // Initialize 3*3 % solid
  for (int i = 0; i < nSolids; i++) {
    Vec pos = RandPos();
    if (is_pos_valid(pos, NULL)) { // Send NULL in to comfirm not to neglect any tank
      for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
          Vec currentPos = {pos.x + x, pos.y + y};
          map.flags[Idx(currentPos)] = eFlagSolid;
        }
      }
    }
  }
  // Initialize player's tank and other's tank.
  {
    Tank *tank = RegNew(regTank);
    tank->dir = RandomDirection();
    tank->color = TK_GREEN;
    tank->isPlayer = true;
    Generate_Position(tank);
  }
  for (int i = 0; i < nEnemies - 1; i++) {
    {
      Tank *tank = RegNew(regTank);
      tank->dir = RandomDirection();
      tank->color = TK_RED;
      tank->isPlayer = false;
      Generate_Position(tank);
    }
  }

  // Initialize renderer.
  renderer.csPrev = (char *)malloc(sizeof(char) * map.size.x * map.size.y);
  renderer.colorsPrev = (Color *)malloc(sizeof(Color) * map.size.x * map.size.y);
  renderer.cs = (char *)malloc(sizeof(char) * map.size.x * map.size.y);
  renderer.colors = (Color *)malloc(sizeof(Color) * map.size.x * map.size.y);

  for (int i = 0; i < map.size.x * map.size.y; ++i) {
    renderer.csPrev[i] = renderer.cs[i] = ' ';
    renderer.colorsPrev[i] = renderer.colors[i] = TK_NORMAL;
  }

  // Render scene.
  for (int y = 0; y < map.size.y; ++y)
    for (int x = 0; x < map.size.x; ++x) {
      Vec pos = {x, y};
      RdrPutChar(pos, map.flags[Idx(pos)], TK_AUTO_COLOR);
    }
  RdrRender();
  RdrFlush();
}

//
//
//
/// \brief Read input from the player.
///
/// \note This function should be called in the loop of `GameLifecycle` before `GameUpdate`.
void GameInput(void) {
  game.keyHit = kbhit_t() ? (char)getch_t() : '\0';
}

void GameTerminate(void);

//
//
//
/// \brief Perform all tasks required for a frame update, including:
/// 1. Game logics of `Tank`s, `Bullet`s, etc.
/// 2. Rerendering all objects in the scene.
///
/// \note This function should be called in the loop of `GameLifecycle` after `GameInput`.
void GameUpdate(void) {
  RdrClear();
  if (game.keyHit == keyESC)
    GameTerminate();
  static int enemyMoveCounter = 0, enemyshootcount = 0, bullet_move = 0, playershoot = 0;
  enemyMoveCounter++;
  enemyshootcount++;
  bullet_move++;
  playershoot++;
  bool shouldMoveEnemies = (enemyMoveCounter >= 15); // Control the frequency of the enemy's moves
  bool shouldshoot = (enemyshootcount >= 20);        // Control the frequency of the enemy's shoots
  bool should_bullet_move = (bullet_move >= 20);     // Control the speed of the bullet
  bool can_player_shoot = (playershoot >= 5);        // Player can only shoot every 5 frames.
  if (shouldMoveEnemies)
    enemyMoveCounter = 0;
  if (shouldshoot)
    enemyshootcount = 0;
  for (RegIterator it = RegBegin(regTank); it != RegEnd(regTank); it = RegNext(it)) {
    Tank *tank = RegEntry(regTank, it);
    char temp;
    if (tank->isPlayer) {
      temp = game.keyHit;
    } else {
      if (shouldMoveEnemies) {
        temp = RandomAWSD();
      } else {
        continue;
      }
    }
    Vec targetPos = tank->pos;
    switch (temp) {
    case 'w': // Up
      if (tank->dir == eDirOP)
        targetPos.y += 1;
      else
        tank->dir = eDirOP;
      break;
    case 's': // Down
      if (tank->dir == eDirON)
        targetPos.y -= 1;
      else
        tank->dir = eDirON;
      break;
    case 'a': // Left
      if (tank->dir == eDirNO)
        targetPos.x -= 1;
      else
        tank->dir = eDirNO;
      break;
    case 'd': // Right
      if (tank->dir == eDirPO)
        targetPos.x += 1;
      else
        tank->dir = eDirPO;
      break;
    default:
      break;
    }
    if (is_pos_valid(targetPos, tank))
      tank->pos = targetPos;
  }

  // Initialize Bullets
  for (RegIterator it = RegBegin(regTank); it != RegEnd(regTank); it = RegNext(it)) {
    Tank *tank = RegEntry(regTank, it);
    Vec pos;
    if (tank->isPlayer && game.keyHit == 'k' && can_player_shoot) {
      playershoot = 0;
      // Initialize the bullet according to the direction of the player's tank.
      switch (tank->dir) {
      case eDirON:
        pos = (Vec){tank->pos.x, tank->pos.y - 1};
        break;
      case eDirNO:
        pos = (Vec){tank->pos.x - 1, tank->pos.y};
        break;
      case eDirPO:
        pos = (Vec){tank->pos.x + 1, tank->pos.y};
        break;
      case eDirOP:
        pos = (Vec){tank->pos.x, tank->pos.y + 1};
        break;
      default:
        break;
      }
      // Initialize the bullet.
      Bullet *bullet = RegNew(regBullet);
      bullet->pos = pos;
      bullet->dir = tank->dir;
      bullet->isPlayer = true;
      bullet->color = TK_GREEN;
    }
    if (!tank->isPlayer && shouldshoot) {
      // Initialize the bullet according to the direction of the enemy's tank.
      switch (tank->dir) {
      case eDirON:
        pos = (Vec){tank->pos.x, tank->pos.y - 1};
        break;
      case eDirNO:
        pos = (Vec){tank->pos.x - 1, tank->pos.y};
        break;
      case eDirPO:
        pos = (Vec){tank->pos.x + 1, tank->pos.y};
        break;
      case eDirOP:
        pos = (Vec){tank->pos.x, tank->pos.y + 1};
        break;
      default:
        break;
      }
      // Initialize the bullet.
      Bullet *bullet = RegNew(regBullet);
      bullet->pos = pos;
      bullet->dir = tank->dir;
      bullet->isPlayer = false;
      bullet->color = TK_RED;
    }
  }

  // check the move of the bullet
  if (should_bullet_move) {
    for (RegIterator it = RegBegin(regBullet); it != RegEnd(regBullet);) {
      Bullet *bullet = RegEntry(regBullet, it);
      Vec nextPos = bullet->pos;
      // Update of the pos of the bullet with their dir.
      switch (bullet->dir) {
      case eDirON:
        nextPos.y -= 1;
        break;
      case eDirNO:
        nextPos.x -= 1;
        break;
      case eDirPO:
        nextPos.x += 1;
        break;
      case eDirOP:
        nextPos.y += 1;
        break;
      default:
        break;
      }
      // check the boundary of the map
      if (nextPos.x < 0 || nextPos.x >= map.size.x || nextPos.y < 0 || nextPos.y >= map.size.y) {
        RegIterator nextIt = RegNext(it);
        RegDelete(bullet);
        it = nextIt;
        continue;
      }
      // check the walls
      if (map.flags[Idx(nextPos)] == eFlagWall) {
        map.flags[Idx(nextPos)] = eFlagNone;
        RegIterator nextIt = RegNext(it);
        RegDelete(bullet);
        it = nextIt;
        continue;
      }
      // check the solid.
      if (map.flags[Idx(nextPos)] == eFlagSolid) {
        RegIterator nextIt = RegNext(it);
        RegDelete(bullet);
        it = nextIt;
        continue;
      }
      // check the range of the tank.
      bool hitTank = false;
      for (RegIterator tankIt = RegBegin(regTank); tankIt != RegEnd(regTank); tankIt = RegNext(tankIt)) {
        Tank *tank = RegEntry(regTank, tankIt);
        if (((tank->pos.x - 1) <= nextPos.x) && ((tank->pos.x + 1) >= nextPos.x) && ((tank->pos.y - 1) <= nextPos.y) &&
            ((tank->pos.y + 1) >= nextPos.y)) {
          hitTank = true;
          if (bullet->isPlayer && !tank->isPlayer) {
            RegDelete(tank);
            if (RegSize(regTank) == 1) {
              TermClearScreen();
              printf("You win!!!");
              getchar();
              GameTerminate();
            }
          } else if (!bullet->isPlayer && tank->isPlayer) {
            TermClearScreen();
            printf("You Failed");
            getchar();
            GameTerminate();
          }
        }
      }
      if (hitTank) {
        RegIterator nextIt = RegNext(it);
        RegDelete(bullet);
        it = nextIt;
        continue;
      }
      // If the bullet is not hit anything, update the pos of the bullet.
      bullet->pos = nextPos;
      it = RegNext(it);
    }
    RdrRender();
    RdrFlush();
  }
}

//
//
//
/// \brief Terminate the game and free all the resources.
///
/// \note This function should be called at the very end of `GameLifecycle`.
void GameTerminate(void) {
  while (RegSize(regTank) > 0)
    RegDelete(RegEntry(regTank, RegBegin(regTank)));

  while (RegSize(regBullet) > 0)
    RegDelete(RegEntry(regBullet, RegBegin(regBullet)));

  free(map.flags);

  free(renderer.csPrev);
  free(renderer.colorsPrev);
  free(renderer.cs);
  free(renderer.colors);

  TermClearScreen();
}

//
//
//
/// \brief Lifecycle of the game, defined by calling the 4 important functions:
/// `GameInit`, `GameInput`, `GameUpdate`, and `GameTerminate`.
///
/// \note This function should be called by `main`.
void GameLifecycle(void) {
  GameInit();

  double frameTime = (double)1000 / (double)config.fps;
  clock_t frameBegin = clock();

  while (true) {
    GameInput();
    if (game.keyHit == keyESC)
      break;

    GameUpdate();

    while (((double)(clock() - frameBegin) / CLOCKS_PER_SEC) * 1000.0 < frameTime - 0.5)
      Daze();
    frameBegin = clock();
  }

  GameTerminate();
}
