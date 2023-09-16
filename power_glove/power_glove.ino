#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int sensorPin0 = A0;
const int sensorPin1 = A1;
const int sensorPin2 = A2;
const int sensorPin3 = A3;

int sensorValue0 = 0;
int sensorValue1 = 0;
int sensorValue2 = 0;
int sensorValue3 = 0;

int max_1 = 700;
int min_1 = 400;

int max_2 = 700;
int min_2 = 400;

void setup() {
  Serial.begin(9600);
  setUpLCD();
}

void loop() {
  updateSensors();
  
  if (sensorValue1 > max_1) {
    max_1 = sensorValue1;
  }
  if (sensorValue1 < min_1 && sensorValue1 > 0) {
    min_1 = sensorValue1;
  }

  if (sensorValue0 > max_2) {
    max_2 = sensorValue0;
  }
  if (sensorValue2 < min_2 && sensorValue0 > 0) {
    min_2 = sensorValue0;
  }
  
  updateDisplay();
}

void setUpLCD() {
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
}

void updateSensors() {
  sensorValue0 = analogRead(sensorPin0);
  sensorValue1 = analogRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);
  sensorValue3 = analogRead(sensorPin3);
}

void updateDisplay() {
  display.clearDisplay();




  display.drawRect(0, 0, display.width() / 2, display.height() / 2, SSD1306_WHITE);
  display.drawRect(0, display.height() / 2, display.width() / 2, display.height() / 2, SSD1306_WHITE);

  display.fillRect(0, 0, (display.width() / 2) * (sensorValue1 - min_1)/(max_1 - min_1), display.height() / 2, SSD1306_WHITE);
  display.fillRect(0, display.height() / 2, (display.width() / 2) * (sensorValue0 - min_2)/(max_2 - min_2), display.height() / 2, SSD1306_WHITE);

  display.drawCircle(display.width() / 2 + 12, 10, 10, SSD1306_WHITE);
  display.drawCircle(display.width() / 2 + 32, 10, 10, SSD1306_WHITE);
  display.fillCircle(display.width() / 2 + 52, 10, 10, SSD1306_WHITE);

  // Draw button text
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  
  display.setCursor(72, 4);
  display.println(F("A"));
  display.setCursor(92, 4);
  display.println(F("B"));
  display.setTextColor(SSD1306_BLACK);
  display.setCursor(112, 4);
  display.println(F("C"));

  display.setCursor(0, 0);
  //  display.println((sensorValue-minValue)*100/(maxValue-minValue));

  //  display.println(sensorValue2);
  //  display.println(sensorValue3);

  display.setTextSize(1);
  //  display.setTextColor(SSD1306_WHITE);
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  display.setCursor(0, 0);
  display.println(F("THUMB"));
  //  display.println(sensorValue1);


  display.setCursor(0, 16);
  display.println(F("INDEX"));
  //  display.println(sensorValue0);



  //  display.invertDisplay(true);
  // Draw a single pixel in white
  //  display.drawPixel(10, 10, SSD1306_WHITE);
  //  display.fillRect(i, i, display.width()-i*2, display.height()-i*2, SSD1306_INVERSE);
  //  for(int16_t i=0; i<display.height()/2; i+=2) {
  //    display.drawRect(0, 0, display.width()*(sensorValue-minValue)/(maxValue-minValue), display.height()-2, SSD1306_WHITE);
  //  display.drawRoundRect(i, i, display.width()-2*i, display.height()-2*i,
  //      display.height()/4, SSD1306_WHITE);
  //    display.fillRoundRect(i, i, display.width()-2*i, display.height()-2*i,
  //      display.height()/4, SSD1306_INVERSE);
  //display.fillTriangle(
  //      display.width()/2  , display.height()/2-i,
  //      display.width()/2-i, display.height()/2+i,
  //      display.width()/2+i, display.height()/2+i, SSD1306_INVERSE);
  //  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  //  display.drawBitmap(
  //    (display.width()  - LOGO_WIDTH ) / 2,
  //    (display.height() - LOGO_HEIGHT) / 2,
  //    logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  //  display.drawLine(0, 0, display.width() - 1, i, SSD1306_WHITE);
  display.display();
  //  display.drawCircle(display.width() / 2, display.height() / 2, i, SSD1306_WHITE);
  //  display.startscrollright(0x00, 0x0F);
  //  delay(2000);
  //  display.stopscroll();
  //  delay(1000);
  //  display.startscrollleft(0x00, 0x0F);
  //  delay(2000);
  //  display.stopscroll();
  //  delay(1000);
  //  display.startscrolldiagright(0x00, 0x07);
  //  delay(2000);
  //  display.startscrolldiagleft(0x00, 0x07);
  //  delay(2000);
  //  display.stopscroll();
}
