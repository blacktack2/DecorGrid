#include "LEDGrid.h"

#include "Renderer.h"
#include "CARenderer.h"
#include "RainbowRenderer.h"

LEDGrid grid(8, 24, 6);
Renderer* renderer = nullptr;
//RainbowRenderer renderer = RainbowRenderer(grid);

typedef void (*onloop_callback_t)(void);

void loopBlankInit();
void loopBlank();
void loopSetMatrix();
void loopRunner();

onloop_callback_t onloop = &loopBlank;

color_t matrixSetColour[3] = {0, 0, 0};

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("-------------------------------");
  Serial.println("-----------Resetting-----------");
  Serial.println("-------------------------------");

  grid.init();
  grid.clearPixels();
  grid.showPixels();

  Serial.println("Setting mainloop");
  onloop = loopRunner;
  
  Serial.println("Setup finished...");
}

void loop() {
  onloop();

  delay(100);
}

void loopBlankInit() {
  grid.clearPixels();
  grid.showPixels();
  onloop = &loopBlank;
}

void loopBlank() {
  
}

void loopSetMatrix() {
  grid.setRGBAll(matrixSetColour[0], matrixSetColour[1], matrixSetColour[2]);
  grid.showPixels();
//  onloop = &loopBlank;
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
