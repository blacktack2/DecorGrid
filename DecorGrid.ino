#include "LEDGrid.h"

#include "Renderer.h"
#include "CARenderer.h"
#include "RainbowRenderer.h"

LEDGrid grid(8, 24, 6);
Renderer* renderer = nullptr;

color_t matrixSetColour[3] = {0, 0, 0};

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("-------------------------------");
  Serial.println("-----------Resetting-----------");
  Serial.println("-------------------------------");

  grid.init();
  grid.setStride(1, 3);
  grid.clearPixels();
  grid.showPixels();

  renderer = new RainbowRenderer(grid);
  ((RainbowRenderer*)renderer)->initRings();

//  renderer = new CARenderer(grid);
  
  Serial.println("Setup finished...");
}

void loop() {
  renderer->update();
  grid.showPixels();

  delay(100);
}

void loopRunner() {
  static int i = 0;
  static color_t r = 100;
  static color_t g = 0;
  static color_t b = 0;
  grid.setRGB(i++, r, g, b);
  grid.showPixels();
  if (i >= grid.getWidth() * grid.getHeight()) {
    i = 0;
    if (r == 100) {
      r = 0;
      g = 100;
    } else if (g == 100) {
      g = 0;
      b = 100;
    } else {
      b = 0;
      r = 100;
    }
  }
}
