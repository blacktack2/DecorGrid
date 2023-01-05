#include "RainbowRenderer.h"

RainbowRenderer::RainbowRenderer(LEDGrid& grid) : Renderer(grid) {
  mUpdateCallback = &RainbowRenderer::updateFlat;

  grid.setStride(1, 3);
}

void RainbowRenderer::updateGrid() {
  (this->*mUpdateCallback)();
}

void RainbowRenderer::updateFlat() {
  mHue = (mHue + 100) % 65535;
  mGrid.setHSVAll(mHue, 255, 255);
}

void RainbowRenderer::updateRings() {
  
}
