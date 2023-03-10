#include "LEDGrid.h"

LEDGrid::LEDGrid(pixel_t width, pixel_t height, pin_t ledPin) :
mPixels(width * height, ledPin, NEO_BRG | NEO_KHZ800), mWidth(width), mHeight(height), mStrideX(1), mStrideY(1) {
  mPixels.setBrightness(50);
}

void LEDGrid::init() {
  Serial.println("Initialising Grid.");
  mPixels.begin();
}

void LEDGrid::setRGB(pixel_t index, color_channel_t r, color_channel_t g, color_channel_t b) {
  mPixels.setPixelColor(index, Adafruit_NeoPixel::Color(r, g, b));
}

void LEDGrid::setHSV(pixel_t index, hue_channel_t h, color_channel_t s, color_channel_t v) {
  mPixels.setPixelColor(index, Adafruit_NeoPixel::ColorHSV(h, s, v));
}

void LEDGrid::setRGB(pixel_t pixelX, pixel_t pixelY, color_channel_t r, color_channel_t g, color_channel_t b) {
  for (pixel_t i = 0; i < mStrideX; i++) {
    for (pixel_t j = 0; j < mStrideY; j++) {
      mPixels.setPixelColor(flatten(pixelX * mStrideX + i, pixelY * mStrideY + j), Adafruit_NeoPixel::Color(r, g, b));
    }
  }
}

void LEDGrid::setHSV(pixel_t pixelX, pixel_t pixelY, hue_channel_t h, color_channel_t s, color_channel_t v) {
  for (pixel_t i = 0; i < mStrideX; i++) {
    for (pixel_t j = 0; j < mStrideY; j++) {
      mPixels.setPixelColor(flatten(pixelX * mStrideX + i, pixelY * mStrideY + j), Adafruit_NeoPixel::ColorHSV(h, s, v));
    }
  }
}

void LEDGrid::setRGBAll(color_channel_t r, color_channel_t g, color_channel_t b) {
  color_t c = Adafruit_NeoPixel::Color(r, g, b);
  for (pixel_t i = 0; i < mWidth * mHeight; i++) {
    mPixels.setPixelColor(i, c);
  }
}

void LEDGrid::setHSVAll(hue_channel_t h, color_channel_t s, color_channel_t v) {
  color_t c = Adafruit_NeoPixel::ColorHSV(h, s, v);
  for (pixel_t i = 0; i < mWidth * mHeight; i++) {
    mPixels.setPixelColor(i, c);
  }
}

void LEDGrid::clearPixels() {
  mPixels.clear();
}

void LEDGrid::showPixels() {
  mPixels.show();
}
