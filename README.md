# DDS-AD9910-Arduino-Shield
DDS (Direct Digital Synthesis) Analog Devices AD9910 Arduino Shield by GRA &amp; AFCH

[HARDWARE Version 2.x:](https://github.com/afch/DDS-AD9910-Arduino-Shield/blob/master/README_HW2.md)  
[HARDWARE Version 3.x:](https://github.com/afch/DDS-AD9910-Arduino-Shield/blob/master/README_HW3.md)  
# Fork changes (enthru, HW3.x + attenuator)
This fork is based on upstream firmware v.3.22 for HW3.x and adds:

* **External step attenuator 0–70 dB** in 10 dB steps (latching relays on pins A8–A13: 10/20/40 dB sections). The output level is split between the AD9910 amplitude and the attenuator, which extends the lower limit of the output level.
* **CH1116 OLED display** instead of SSD1306. The driver is in `Libraries/Adafruit_CH1116`.
* **Buttons are polled in a Timer5 interrupt (1 ms)**. Clicks are latched and no longer get lost during blocking operations such as I2C display redraws or SPI transfers to the DDS. Timer1 is still used for S-Curve modulation.
* **The RF output is OFF after power-up** (v.3.23). The first press of ON/OFF enables generation.

Build: Arduino Mega 2560, with the libraries from the `Libraries` folder (`arduino-cli compile -b arduino:avr:mega --libraries Libraries "Firmware Source (.INO File)/HW3.x/DDS-AD9910-Arduino-Shield_HW3.x"`).
