#ifndef _SSD1339_H_
#define _SSD1339_H_

#include <cstdint>
#include <cstddef>

extern void digitalWrite(int pin, int val);
extern void pinMode(int pin, int mode);
extern void delay(int ms);
extern void delayMicroseconds(int us);

class SSD1339 {
private:
  uint8_t RST_PIN;
  uint8_t CS_PIN;
  uint8_t DC_PIN;
  uint8_t DIN_PIN;
  uint8_t CLK_PIN;
  uint8_t HVEN_PIN;

  void OLED_RES_1() { digitalWrite(RST_PIN, 1); }
  void OLED_RES_0() { digitalWrite(RST_PIN, 0); }
  void OLED_CS_1()  { digitalWrite(CS_PIN, 1); }
  void OLED_CS_0()  { digitalWrite(CS_PIN, 0); }
  void OLED_DC_1()  { digitalWrite(DC_PIN, 1); }
  void OLED_DC_0()  { digitalWrite(DC_PIN, 0); }
  void OLED_DIN_1() { digitalWrite(DIN_PIN, 1); }
  void OLED_DIN_0() { digitalWrite(DIN_PIN, 0); }
  void OLED_CLK_1() { digitalWrite(CLK_PIN, 1); }
  void OLED_CLK_0() { digitalWrite(CLK_PIN, 0); }
  void OLED_HVEN_1() { digitalWrite(HVEN_PIN, 1); }
  void OLED_HVEN_0() { digitalWrite(HVEN_PIN, 0); }

  void uDelay(int l) { delayMicroseconds(10 * l); }
  void Write_Command(uint8_t Data);
  void Write_Data(uint8_t Data);
  void Set_Gray_Scale_Table();
  void OLED_InitIOs();

public:
  SSD1339(uint8_t rst_pin, uint8_t cs_pin, uint8_t dc_pin, 
          uint8_t din_pin, uint8_t clk_pin, uint8_t hven_pin);
  void begin();
  static uint16_t MAKECOLOR64k(uint8_t r, uint8_t g, uint8_t b);
  void EnableFill(bool d);
  void Draw_Line64k(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint16_t col);
  void Draw_Rectangle64k(uint8_t xLeft, uint8_t yTop, uint8_t xRight, uint8_t yBottom, 
                        uint16_t colOutline, uint16_t colFill);
  void Draw_Circle64k(uint8_t x, uint8_t y, uint8_t r, uint16_t colOutline, uint16_t colFill);
  void Fill_Block64k(uint8_t xLeft, uint8_t yTop, uint8_t xRight, uint8_t yBottom, uint16_t col);
  void clear(uint16_t color = 0x0000);
  void Rainbow();
  void Set_Column_Address(uint8_t start, uint8_t end);
  void Set_Row_Address(uint8_t start, uint8_t end);
  void Set_Write_RAM();
  void Show_64k_Pattern(uint8_t* data, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
};

#endif 