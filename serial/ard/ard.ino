/*
* Copyright (C) 2022 by Roberto Calvo-Palomino
*
*
*  This programa is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with RTL-Spec.  If not, see <http://www.gnu.org/licenses/>.
*
*   Authors: Roberto Calvo-Palomino <roberto.calvo [at] urjc [dot] es>
*/

// Subject: Sistemas Empotrados y de Tiempo Real
// Universidad Rey Juan Carlos, Spain

#include "FastLED.h"
#define PIN_RBGLED 4
#define NUM_LEDS 1
CRGB leds[NUM_LEDS];

uint32_t Color(uint8_t r, uint8_t g, uint8_t b)
{
  return (((uint32_t)r << 16) | ((uint32_t)g << 8) | b);
}

void setup() {

  Serial.begin(9600);
  delay(1000);

  FastLED.addLeds<NEOPIXEL, PIN_RBGLED>(leds, NUM_LEDS);
  FastLED.setBrightness(20);

  // Set Red Color to LED
  FastLED.showColor(Color(255, 0, 0));
  delay(1000);

  String sendBuff;

  // To make this code works, remember that the switch S1 should be set to "CAM"
  while(1) {

    if (Serial.available()) {

      char c = Serial.read();
      sendBuff += c;
      
      if (c == '}')  {            
        Serial.print("Received data in serial port from ESP32: ");
        Serial.println(sendBuff);

        // Set Red Green to LED
        FastLED.showColor(Color(0, 0, 255));
        sendBuff = "";
        break;
      } 

    }
  }

}

void loop () {  

  Serial.println("{ 'test': " + String(millis()) + " }");
  delay(500);

}
