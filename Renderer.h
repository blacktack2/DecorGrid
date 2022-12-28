#pragma once
#include "LEDGrid.h"

class Renderer {
public:
  Renderer(LEDGrid& grid) : mGrid(grid) {}

  virtual void updateGrid() = 0;
protected:
  LEDGrid& mGrid;
};
