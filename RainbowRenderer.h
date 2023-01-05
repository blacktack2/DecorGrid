#pragma once
#include "Renderer.h"

class RainbowRenderer : public Renderer {
public:
  RainbowRenderer(LEDGrid& grid);

  void initFlat();
  void initRings();
private:
  virtual void updateGrid();
  
  void updateFlat();
  void updateRings();

  typedef void (RainbowRenderer::*update_callback)(void);
  update_callback mUpdateCallback;

  hue_channel_t mHue = 0;
  pixel_t mSpeed = 1000;
};
