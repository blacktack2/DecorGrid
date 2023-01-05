#include "RainbowRenderer.h"

RainbowRenderer::RainbowRenderer(LEDGrid& grid) : Renderer(grid) {
  initFlat();
}

void RainbowRenderer::initFlat() {
  mUpdateCallback = &RainbowRenderer::updateFlat;
  mSpeed = 1000;
}

void RainbowRenderer::initRings() {
  mUpdateCallback = &RainbowRenderer::updateRings;
  mSpeed = 5000;
}

void RainbowRenderer::updateGrid() {
  (this->*mUpdateCallback)();
}

void RainbowRenderer::updateFlat() {
  mHue = (mHue + mSpeed) % 65535;
  mGrid.setHSVAll(mHue, 255, 255);
}

void RainbowRenderer::updateRings() {
  mSpeed = 5000 + (pixel_t)(4000 * sin(mFrames * 0.05f));
  mHue = (mHue + mSpeed) & 65535;
  for (pixel_t x = 0; x < mGrid.getWidth(); x++) {
    for (pixel_t y = 0; y < mGrid.getHeight(); y++) {
      float rx = x - mGrid.getWidth() * 0.5f + 0.5f;
      float ry = y - mGrid.getHeight() * 0.5f + 0.5f;
      hue_channel_t hue = (mHue + (pixel_t)(5000.0f * sqrt(rx * rx + ry * ry))) & 65535;
      mGrid.setHSV(x, y, hue, 255, 255);
    }
  }
}
