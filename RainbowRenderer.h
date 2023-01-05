#pragma once
#include "Renderer.h"

class RainbowRenderer : public Renderer {
public:
  RainbowRenderer(LEDGrid& grid);

  virtual void updateGrid();
private:
  void updateFlat();
  void updateRings();

  typedef void (RainbowRenderer::*update_callback)(void);
  update_callback mUpdateCallback;

  hue_channel_t mHue = 0;
};
