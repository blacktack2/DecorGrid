#pragma once
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

typedef int16_t pin_t;
typedef uint16_t pixel_t;
typedef uint8_t color_channel_t;
typedef uint16_t hue_channel_t;
typedef uint32_t color_t;

class LEDGrid {
public:
  LEDGrid(pixel_t width, pixel_t height, pin_t ledPin);

  void init();

  void setRGB(pixel_t pixelX, pixel_t pixelY, color_channel_t r, color_channel_t g, color_channel_t b);
  void setHSV(pixel_t pixelX, pixel_t pixelY, hue_channel_t h, color_channel_t s, color_channel_t v);

  void setRGBAll(color_channel_t r, color_channel_t g, color_channel_t b);
  void setHSVAll(hue_channel_t h, color_channel_t s, color_channel_t v);

  void clearPixels();
  void showPixels();

  inline pixel_t getWidth() {
    return mWidth;
  }

  inline pixel_t getHeight() {
    return mHeight;
  }
private:
  inline pixel_t flatten(pixel_t x, pixel_t y) {
    return y & 1 ? (mWidth - x) + (y * mWidth) : x + (y * mWidth);
  }
  inline void unflatten(pixel_t& x, pixel_t& y, pixel_t xy) {
    y = xy / mHeight;
    x = y & 1 ? (mWidth - (xy % mWidth)) : (xy % mWidth);
  }

  pixel_t mWidth, mHeight;
  Adafruit_NeoPixel mPixels;
};
