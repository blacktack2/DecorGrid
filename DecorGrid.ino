#include "arduino_secrets.h"

#include "LEDGrid.h"

#include "OTAHandler.h"

#include "Renderer.h"
#include "CARenderer.h"
#include "RainbowRenderer.h"

const String webpageHtml = R"(
<!DOCTYPE HTML>
<head><title>LED Grid</title></head>
<body style="font-size: 1.1em;">
  <h3>Arduino ESP OTA Home Page</h3>

  <div>
    Project: LED Grid
  </div>

  <fieldset style="margin: 20px 5px 20px 5px; border: 1px solid darkgray; border-radius: 5px; background-color: white;">
    <legend style="font-size: 0.8em;">Project description:</legend>
    <div style="font-size: 0.8em; background-color: #EEEEEE; padding: 5px; border-radius: 10px;">
      Description goes here...
    </div>
  </fieldset>

  <p>
    To update your device from the Arduino IDE choose:
    <ul>
      <li><b>Sketch->Export compiled Binary</b></li>
      <li>then find the sketch folder by choosing</li>
      <li><b>Sketch->Show Sketch Folder</b> and then</li>
      <li>use the 'update' link below to navigate to your '.bin' file to upload</li>
    </ul>
  </p>

  <p>
    To update your code type this into your address bar:<br>
    <a href="http://)" + OTAHandler::getCurrentURL() + R"(/update" target="_blank">http://)" + OTAHandler::getCurrentURL() + R"(/update</a><br>
    or just click this link.
  </p>

  <button id="hello-button" onclick="helloThere();">Hello</button>

  <script>
    function helloThere() {
      const xhttp = new XMLHttpRequest();
      xhttp.onload = function() {
        document.getElementById("hello-button").innerHTML = this.responseText;
      }
      xhttp.open("GET", "/print_debug", true);
      xhttp.send();
    }
  </script>
</body>
</html>
)";

const char* SSID = SECRET_SSID;
const char* PASS = SECRET_PASS;

OTAHandler otaHandler(SSID, PASS);

LEDGrid grid(24, 24, 4);
//RainbowRenderer renderer = RainbowRenderer(grid);
RainbowRenderer renderer = RainbowRenderer(grid);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("-------------------------------");
  Serial.println("-----------Resetting-----------");
  Serial.println("-------------------------------");

  otaHandler.init(webpageHtml);

  grid.init();
  grid.clearPixels();
  grid.showPixels();
  
  Serial.println("Setup finished...");
}

void loop() {
  grid.clearPixels();
  grid.showPixels();
//  renderer.updateGrid();
  grid.setRGBAll(100, 0, 0);
  grid.showPixels();

  delay(100);
}
