#pragma once

/// \file
/// \brief This file introduces a renderer which
/// helps us visualize objects in the scene.

//
//
//
//
//
#include "Scene.h"
#include <string.h>

/// \brief Let the renderer automatically deduce the color.
#define TK_AUTO_COLOR ((const char *)(NULL))

/// \brief The error message for undefined behaviors.
#define TK_INVALID_COLOR "Invalid Color"

/// \example Consequently call these functions to render a frame.
/// ```c
/// RdrClear();
/// // Update objects in the scene here.
/// RdrRender();
/// RdrFlush();
/// ```
///
/// \details The renderer is implemented by
/// imitating the double buffering technique.
/// See https://en.wikipedia.org/wiki/Multiple_buffering for more details.
typedef struct {
  char *csPrev;      // Characters of the previous frame.
  Color *colorsPrev; // Character colors of the previous frame.
  char *cs;          // Characters of the current frame.
  Color *colors;     // Character colors of the current frame.
} Renderer;

// The renderer singleton.
static Renderer renderer;

//
//
//
/// \brief Render character `c` at position `pos` with color `color`.
///
/// \example ```c
/// // Explicitly specify the color.
/// RdrPutChar(pos, 'o', TK_RED);
/// // Let the renderer automatically deduce the color.
/// RdrPutChar(pos, eFlagWall, TK_AUTO_COLOR);
/// ```
void RdrPutChar(Vec pos, char c, Color color) {
  renderer.cs[Idx(pos)] = c;

  if (color == TK_AUTO_COLOR) {
    Flag flag = (Flag)c;
    color = flag == eFlagNone    ? TK_NORMAL
            : flag == eFlagSolid ? TK_BLUE
            : flag == eFlagWall  ? TK_WHITE

            : flag == eFlagTank ? TK_INVALID_COLOR
                                : TK_INVALID_COLOR;
  }
  renderer.colors[Idx(pos)] = color;
}

//
//
//
/// \brief Clear all the objects in the scene from the frame.
void RdrClear(void) {
  // Clear tanks.
  for (RegIterator it = RegBegin(regTank); it != RegEnd(regTank); it = RegNext(it)) {
    Tank *tank = RegEntry(regTank, it);
    Vec pos = tank->pos;

    for (int y = -1; y <= 1; ++y)
      for (int x = -1; x <= 1; ++x)
        RdrPutChar(Add(pos, (Vec){x, y}), map.flags[Idx(pos)], TK_AUTO_COLOR);
  }

  // Clear bullets.
  for (RegIterator it = RegBegin(regBullet); it != RegEnd(regBullet); it = RegNext(it)) {
    Bullet *bullet = RegEntry(regBullet, it);
    Vec pos = bullet->pos;

    RdrPutChar(pos, map.flags[Idx(pos)], TK_AUTO_COLOR);
  }
}

/// \brief Render all the objects in the scene to the frame.
void RdrRender(void) {
  // Render All
  for (int y = 0; y < map.size.y; ++y)
    for (int x = 0; x < map.size.x; ++x) {
      Vec pos = {x, y};
      int i = Idx(pos);
      RdrPutChar(pos, map.flags[Idx(pos)], TK_AUTO_COLOR);
    }
  // Render tanks.
  for (RegIterator it = RegBegin(regTank); it != RegEnd(regTank); it = RegNext(it)) {
    Tank *tank = RegEntry(regTank, it);
    Vec pos = tank->pos;
    Color color = tank->color;
    char tankShape[3][3];
    switch (tank->dir) {
    case eDirNO:
      memcpy(tankShape, (char[3][3]){{'O', '+', 'O'}, {'O', '-', 'O'}, {'@', '@', '@'}}, sizeof(tankShape));
      break;
    case eDirPO:
      memcpy(tankShape, (char[3][3]){{'@', '@', '@'}, {'O', '-', 'O'}, {'O', '+', 'O'}}, sizeof(tankShape));
      break;
    case eDirON:
      memcpy(tankShape, (char[3][3]){{'O', 'O', '@'}, {'+', '|', '@'}, {'O', 'O', '@'}}, sizeof(tankShape));
      break;
    case eDirOP:
      memcpy(tankShape, (char[3][3]){{'@', 'O', 'O'}, {'@', '|', '+'}, {'@', 'O', 'O'}}, sizeof(tankShape));
      break;
    case eDirInvalid:
      break;
    default:
      break;
    }
    // draw the tank shape
    for (int x = 0; x < 3; ++x) {
      for (int y = 0; y < 3; ++y) {
        Vec offset = {x - 1, y - 1};
        RdrPutChar(Add(pos, offset), tankShape[x][y], color);
      }
    }
  }

  // Render bullets.
  for (RegIterator it = RegBegin(regBullet); it != RegEnd(regBullet); it = RegNext(it)) {
    Bullet *bullet = RegEntry(regBullet, it);
    Vec pos = bullet->pos;
    Color color = bullet->color;
    RdrPutChar(pos, 'o', color);
  }
}

/// \brief Flush the previously rendered frame to screen to
/// make it truly visible.
void RdrFlush(void) {
  // 获取上一帧的字符和颜色数据
  char *csPrev = renderer.csPrev;
  Color *colorsPrev = renderer.colorsPrev;
  // 获取当前帧的字符和颜色数据
  const char *cs = renderer.cs;
  const Color *colors = renderer.colors;

  // 遍历地图的每一个位置
  for (int y = 0; y < map.size.y; ++y)
    for (int x = 0; x < map.size.x; ++x) {
      // 计算当前位置的坐标
      Vec pos = {x, y};
      // 计算当前位置在一维数组中的索引
      int i = Idx(pos);

      // 检查当前帧和上一帧的字符或颜色是否不同
      if (cs[i] != csPrev[i] || colors[i] != colorsPrev[i]) {
        // 如果不同，移动光标到该位置
        MoveCursor(pos);
        // 输出带有颜色的字符
        printf(TK_TEXT("%c", TK_RUNTIME_COLOR), colors[i], cs[i]);

        // 更新上一帧的数据为当前帧的数据
        csPrev[i] = cs[i];
        colorsPrev[i] = colors[i];
      }
    }
}
