#include "RainbowRenderer.h"

RainbowRenderer::RainbowRenderer(LEDGrid& grid) : Renderer(grid) {
  mUpdateCallback = &RainbowRenderer::updateFlat;
}

void RainbowRenderer::updateGrid() {
  (this->*mUpdateCallback)();
}

void RainbowRenderer::updateFlat() {
  mHue = (mHue + 100) % 65535;
  mGrid.setHSVAll(mHue, 255, 5);
}

void RainbowRenderer::updateRings() {
  
}
