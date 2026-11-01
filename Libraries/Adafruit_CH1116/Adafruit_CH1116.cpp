#include "Adafruit_CH1116.h"

Adafruit_CH1116::Adafruit_CH1116(uint8_t w, uint8_t h, TwoWire *twi,
                                 int8_t rst_pin, uint32_t clkDuring,
                                 uint32_t clkAfter)
    : Adafruit_SSD1306(w, h, twi, rst_pin, clkDuring, clkAfter), _wire(twi),
      _addr(0x3C), _clkDuring(clkDuring), _clkAfter(clkAfter) {}

boolean Adafruit_CH1116::begin(uint8_t switchvcc, uint8_t i2caddr,
                               boolean reset, boolean periphBegin) {
  _addr = i2caddr ? i2caddr : ((HEIGHT == 32) ? 0x3C : 0x3D);
  if (!Adafruit_SSD1306::begin(switchvcc, i2caddr, reset, periphBegin))
    return false;
  // SSD1306 init leaves the cursor somewhere in horizontal mode; resync.
  display();
  return true;
}

void Adafruit_CH1116::display(void) {
  uint8_t *buf = getBuffer();
  const uint8_t pages = (HEIGHT + 7) / 8;
  const uint8_t chunk = 16;  // AVR Wire buffer is 32 bytes incl. control byte

#if ARDUINO >= 157
  _wire->setClock(_clkDuring);
#endif
  for (uint8_t p = 0; p < pages; p++) {
    _wire->beginTransmission(_addr);
    _wire->write((uint8_t)0x00);  // command stream
    _wire->write((uint8_t)(0xB0 | p));
    _wire->write((uint8_t)(0x00 | (CH1116_COL_OFFSET & 0x0F)));
    _wire->write((uint8_t)(0x10 | (CH1116_COL_OFFSET >> 4)));
    _wire->endTransmission();

    for (uint8_t x = 0; x < WIDTH; x += chunk) {
      _wire->beginTransmission(_addr);
      _wire->write((uint8_t)0x40);  // data stream
      _wire->write(buf + (uint16_t)p * WIDTH + x, chunk);
      _wire->endTransmission();
    }
  }
#if ARDUINO >= 157
  _wire->setClock(_clkAfter);
#endif
}
