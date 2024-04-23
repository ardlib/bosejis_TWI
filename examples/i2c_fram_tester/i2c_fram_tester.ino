/**
 * I2C FRAM Tester Example
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

// I2C Address - A2,A1,A0 by default Zero and WP pulled low
#define FRAM 0x50
// Note: If this is being performed on I2C EEPROM this would
// consume quite the lifetime of the chip.

// FRAM Functions
uint8_t WriteFRAM(uint16_t addr, uint8_t data);
uint8_t ReadFRAM(uint16_t addr);
uint8_t PageWriteFRAM(uint16_t addr, uint8_t *data, size_t len);
size_t PageReadFRAM(uint16_t addr, uint8_t *data, size_t len);

void setup() {
  Serial.begin(115200);
  Serial.println();
  delay(1000);
  Wire.begin();
}

// Data for Storage Test
byte warr[5] = {0xF1, 0xF2, 0xA2, 0xB3, 0xC1};
byte rarr[5];
byte fillarr[5] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

void loop() {
  int i;
  Serial.println();

  WriteFRAM(0x35, 0xA5);
  if (ReadFRAM(0x35) == 0xA5)
    Serial.println("OK Byte Read/Write");
  WriteFRAM(0x35, 0xFF);

  PageWriteFRAM(0x11, warr, 5);
  memset(rarr, 0, 5);
  PageReadFRAM(0x11, rarr, 5);
  PageWriteFRAM(0x11, fillarr, 5);
  for (i = 0; i < 5; i++) {
    if (rarr[i] != warr[i]) {
      Serial.println("ERROR in Page Write/Read");
      break;
    }
  }
  if (i == 5) {
    Serial.println("OK Page Read/Write");
  }
  Serial.println();
  // Cycle Delay
  delay(5000);
}

uint8_t WriteFRAM(uint16_t addr, uint8_t data) {
  Wire.beginTransmission(FRAM);
  Wire.write((byte)((addr >> 8) & 0xFF));
  Wire.write((byte)((addr >> 0) & 0xFF));
  Wire.write(data);
  return Wire.endTransmission();
}

uint8_t ReadFRAM(uint16_t addr) {
  uint8_t ret = 0;
  Wire.beginTransmission(FRAM);
  Wire.write((byte)((addr >> 8) & 0xFF));
  Wire.write((byte)((addr >> 0) & 0xFF));
  Wire.endTransmission();
  Wire.requestFrom(FRAM, 1);
  if (Wire.available())
    ret = Wire.read();
  return ret;
}

uint8_t PageWriteFRAM(uint16_t addr, uint8_t *data, size_t len) {
  Wire.beginTransmission(FRAM);
  Wire.write((byte)((addr >> 8) & 0xFF));
  Wire.write((byte)((addr >> 0) & 0xFF));
  for (size_t i = 0; i < len; i++) {
    Wire.write(data[i]);
  }
  return Wire.endTransmission();
}

size_t PageReadFRAM(uint16_t addr, uint8_t *data, size_t len) {
  size_t i = 0;
  Wire.beginTransmission(FRAM);
  Wire.write((byte)((addr >> 8) & 0xFF));
  Wire.write((byte)((addr >> 0) & 0xFF));
  Wire.endTransmission();
  Wire.requestFrom(FRAM, len);

  while (Wire.available() && i < len)
    data[i++] = Wire.read();

  return i;
}
