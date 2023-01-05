#pragma once
#include "LEDGrid.h"

class Renderer {
public:
  Renderer(LEDGrid& grid) : mGrid(grid) {}

  void update() {
    mFrames++;
    updateGrid();
  }
protected:
  virtual void updateGrid() = 0;
  LEDGrid& mGrid;

  unsigned long mFrames = 0;
};
