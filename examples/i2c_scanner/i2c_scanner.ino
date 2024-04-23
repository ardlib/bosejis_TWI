/**
 * I2C Scanner Example
 *
 * बोसजी की अंतर-एकीकृत परिपथ लाइब्रेरी
 * ===============================
 * आधुनिकतम अंतर-एकीकृत परिपथ का सरल कार्यान्वयन।
 *
 * एक रचनात्मक भारतीय उत्पाद।
 *
 * Boseji's TWI Library
 * TWI operations Library.
 *
 * Sources
 * -------
 * https://github.com/ardlib/bosejis_TWI
 *
 * License
 * --------
 * SPDX: GPL-3.0-or-later
 *
 *  bosejis_TWI - TWI operations Library
 *  Copyright (C) 2024 by Abhijit Bose (aka. Boseji)
 *
 *  This program is free software: you can redistribute it and/or modify
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
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include <bosejis_TWI.h>

uint8_t count = 0;
void setup() {
  Serial.begin(115200);
  Serial.println();
  delay(1000);
  Wire.begin();
}

void loop() {
  Serial.println();
  Serial.println("I2C scanner. Scanning …");
  count = 0;

  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.print(address, HEX);
      Serial.println("  !");
      ++count;
    }
  }
  if (count == 0) {
    Serial.println("No I2C devices found");
  } else {
    Serial.println("done");
  }
  delay(5000); // Wait 5 seconds for next scan
}
