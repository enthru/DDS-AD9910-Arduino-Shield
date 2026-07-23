/*                                        *******************************************
 *                                        *             GRA-AFCH.COM                *
 *                                        *******************************************                                      
 */

#include <Arduino.h>
#include "main.h"

#define BLACK   0
#define WHITE   1
#define INVERSE 2

Adafruit_CH1116 display = Adafruit_CH1116(128, 64, &Wire);
ClickButton modeButton(MODE_PIN, LOW, CLICKBTN_PULLUP);
ClickButton RFOutButton(RFOUT_PIN, LOW, CLICKBTN_PULLUP);

// Защёлка событий клика, заполняется в таймерном прерывании (ServiceButtons)
static volatile int8_t modeClicksLatched  = 0;
static volatile int8_t RFOutClicksLatched = 0;

// Вызывается из ISR(TIMER5_A) каждую ~1 мс: опрашивает кнопки и сохраняет
// ненулевой результат клика до тех пор, пока его не заберёт главный цикл.
void ServiceButtons()
{
  modeButton.Update();
  if (modeButton.clicks != 0) modeClicksLatched = modeButton.clicks;

  RFOutButton.Update();
  if (RFOutButton.clicks != 0) RFOutClicksLatched = RFOutButton.clicks;
}

// Атомарно прочитать и сбросить защёлку (вызывается из главного цикла).
int8_t TakeModeClicks()
{
  uint8_t sreg = SREG;
  cli();
  int8_t c = modeClicksLatched;
  modeClicksLatched = 0;
  SREG = sreg;
  return c;
}

int8_t TakeRFOutClicks()
{
  uint8_t sreg = SREG;
  cli();
  int8_t c = RFOutClicksLatched;
  RFOutClicksLatched = 0;
  SREG = sreg;
  return c;
}

void DisplaySaved(void)
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(40, 0);
  //display.setCursor(0, 0);
  display.cp437(true);
  display.println("SETUP");
  display.setCursor(40, 32);
  display.print("SAVED");
  display.display();
}
