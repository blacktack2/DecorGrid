#pragma once
#include "Renderer.h"

class CARenderer : public Renderer {
public:
  CARenderer(LEDGrid& grid);
  ~CARenderer();
private:
  virtual void updateGrid();
  
  typedef uint8_t cell;
  typedef uint16_t ruleset;

  cell* mCells;
  ruleset mBirthRules;
  ruleset mDeathRules;
  cell mNumGenerations;
};
