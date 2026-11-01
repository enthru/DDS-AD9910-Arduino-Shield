#ifndef _ADAFRUIT_CH1116_H_
#define _ADAFRUIT_CH1116_H_

#include <Adafruit_SSD1306.h>

// Column offset of visible area in controller RAM.
// CH1116 modules usually need 0; SH1106 (132-column RAM) modules need 2.
#ifndef CH1116_COL_OFFSET
#define CH1116_COL_OFFSET 0
#endif

// CH1116 has no horizontal addressing mode (SSD1306 0x20/0x21/0x22),
// so the framebuffer is sent page by page with explicit page/column set.
class Adafruit_CH1116 : public Adafruit_SSD1306 {
 public:
  Adafruit_CH1116(uint8_t w, uint8_t h, TwoWire *twi = &Wire,
                  int8_t rst_pin = -1, uint32_t clkDuring = 400000UL,
                  uint32_t clkAfter = 100000UL);

  boolean begin(uint8_t switchvcc = SSD1306_SWITCHCAPVCC, uint8_t i2caddr = 0,
                boolean reset = true, boolean periphBegin = true);
  void display(void);

 private:
  TwoWire *_wire;
  uint8_t _addr;
  uint32_t _clkDuring, _clkAfter;
};

#endif
