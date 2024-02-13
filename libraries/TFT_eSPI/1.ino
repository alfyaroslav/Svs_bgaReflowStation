// Pause in milliseconds between screens, change to 0 to time font rendering
#define WAIT 1000
#include <TFT_eSPI.h> // Graphics and font library for ILI9341 driver chip
#include <SPI.h>
TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

//----------------------------------------
void setup(void) {
	
  tft.init();
  tft.setRotation(3);
  Serial.begin(115200);
  
}

//----------------------------------------
void loop() {


	tft.fillScreen(TFT_BLACK);

	tft.setTextSize(1);
	tft.setTextColor(TFT_GREEN, TFT_BLACK);
	tft.drawString("шрифт 1, размер 1", 0, 0, 1);
	tft.drawString("1234567890-=\QWERTYUIOP{}", 0, 20, 1);
	tft.drawString("!№;%:?*()_+/qwertyuiop[]", 0, 40, 1);
	tft.drawString("ЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭ", 0, 60, 1);
	tft.drawString("йцукенгшщзхъфывапролджэ", 0, 80, 1);
	tft.drawString("ЯЧСМИТЬБЮячсмитьбю.", 0, 100, 1);
	delay(5000);
  
	tft.fillScreen(TFT_BLACK);
  
	tft.setTextSize(2);
	tft.setTextColor(TFT_GREEN, TFT_BLACK);
	tft.drawString("шрифт 1, размер 2", 0, 0, 1);
	tft.drawString("1234567890-=\QWERTYUIOP{}", 0, 20, 1);
	tft.drawString("!№;%:?*()_+/qwertyuiop[]", 0, 40, 1);
	tft.drawString("ЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭ", 0, 60, 1);
	tft.drawString("йцукенгшщзхъфывапролджэ", 0, 80, 1);
	tft.drawString("ЯЧСМИТЬБЮячсмитьбю.", 0, 100, 1);
	delay(5000);
	
	tft.fillScreen(TFT_BLACK);
  
	tft.setTextSize(3);
	tft.setTextColor(TFT_GREEN, TFT_BLACK);
	tft.drawString("шрифт 1, размер 3", 0, 0, 1);
	tft.drawString("12345QWERTY", 0, 30, 1);
	tft.drawString("!№;%:?qwertyu", 0, 60, 1);
	tft.drawString("ЙЦУКЕНГШЩЗХЪ", 0, 90, 1);
	tft.drawString("йцукенгшщзхъ", 0, 120, 1);
	tft.drawString("ЯЧСМИТЬБЮ", 0, 150, 1);
	delay(5000);
  
  
  
  
  
	tft.fillScreen(TFT_BLACK);

	tft.setTextSize(1);
	tft.setTextColor(TFT_GREEN, TFT_BLACK);
	tft.drawString("шрифт 2, размер 1", 0, 0, 2);
	tft.drawString("1234567890-=\QWERTYUIOP{}", 0, 20, 2);
	tft.drawString("!№;%:?*()_+/qwertyuiop[]", 0, 40, 2);
	tft.drawString("ЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭ", 0, 60, 2);
	tft.drawString("йцукенгшщзхъфывапролджэ", 0, 80, 2);
	tft.drawString("ЯЧСМИТЬБЮячсмитьбю.", 0, 100, 2);
	delay(5000);
  
	tft.fillScreen(TFT_BLACK);
  
	tft.setTextSize(2);
	tft.setTextColor(TFT_GREEN, TFT_BLACK);
	tft.drawString("шрифт 2, размер 2", 0, 0, 2);
	tft.drawString("1234567890-=\QWERTYUIOP{}", 0, 30, 2);
	tft.drawString("!№;%:?*()_+/qwertyuiop[]", 0, 60, 2);
	tft.drawString("ЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭ", 0, 90, 2);
	tft.drawString("йцукенгшщзхъфывапролджэ", 0, 120, 2);
	tft.drawString("ЯЧСМИТЬБЮячсмитьбю.", 0, 150, 2);
	delay(5000);
	
  
  
  
  
  
  
  
  
  
  
  
  
  //return;




	tft.fillScreen(TFT_BLACK);

  tft.setTextSize(1);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  tft.drawString("Привет", 110, 0, 2);
  delay(WAIT);

  tft.setTextSize(1);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.drawString("кусок мяса", 90, 20, 2);
  delay(WAIT);
  
    tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("я китайский экран", 40, 40, 2);
  delay(WAIT);
  
    tft.setTextSize(1);
  tft.drawString("2.4' 240x320", 80, 80, 2);
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  delay(WAIT);

  tft.setTextSize(1);
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.drawString("библиотека TFT_eSPi", 25, 100, 2);
  delay(WAIT);
  
    tft.setTextSize(1);
  tft.setTextColor(TFT_ORANGE, TFT_BLACK);
  tft.drawString("я умею писать русскими", 8, 140, 2);
  tft.drawString("буквами", 100, 160, 2);
  delay(WAIT);
  
  
  delay(WAIT);
  delay(WAIT);
  
  
  
  
  
  
  
  	tft.fillScreen(TFT_BLACK);
	
	tft.setTextSize(1);
	tft.setTextColor(TFT_CYAN, TFT_BLACK);	  
	tft.drawString("font 1. 123.,ABCabc ЙЦЫФйцыф", 0, 0, 1);
  	delay(WAIT);
  
    tft.setTextSize(1);
	tft.drawString("font 2. 123.,ABCabc ЙЦЫФйцыф", 0, 20, 2);
	delay(WAIT);
  
    tft.setTextSize(1);
	tft.drawString("font 4. 123.,ABCabc ЙЦЫФйцыф", 0, 50, 4);
	delay(WAIT);
  
    tft.setTextSize(1);
	tft.drawString("font 6. цифры", 0, 80, 2);	
	tft.drawString("12345.:-apm", 0, 100, 6);
	delay(WAIT);
  
    tft.setTextSize(1);
	tft.drawString("font 7. цифры", 0, 150, 2);	
	tft.drawString("12345.:-", 0, 180, 7);
	delay(WAIT);
  

  delay(WAIT);
  delay(WAIT);
  delay(WAIT);
  delay(WAIT);
  delay(WAIT);
  delay(WAIT);
  delay(WAIT);
  delay(WAIT);
  delay(WAIT);

  
  

   

}