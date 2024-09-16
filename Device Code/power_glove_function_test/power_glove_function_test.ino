
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MPU6050_light.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32


int angleX = 0;
int angleY = 0;
int angleZ = 0;

MPU6050 mpu(Wire);
unsigned long timer = 0;

#define OLED_RESET 4  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int button1Pin = 2;
const int button2Pin = 3;
const int button3Pin = 4;
const int button4Pin = 5;

int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;

const int ledPin = 13;

// ----------------- SETUP -----------------

void setup() {
  Serial.begin(9600);
  Serial.println(F("starting up..."));

  Wire.begin();
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while (status != 0) {}  // stop everything if could not connect to MPU6050
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets();  // gyro and accelero
  Serial.println("Done!\n");

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }



  Serial.println(F("found lcd"));

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  display.clearDisplay();

  pinMode(ledPin, OUTPUT);

  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  pinMode(button4Pin, INPUT);

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);  // Draw white text
  display.setCursor(0, 0);              // Start at top-left corner
  display.println(F("Hello, assmass!"));
  display.display();
}

// ----------------- LOOP -----------------

void loop() {
  processInputs();

  mpu.update();
  if ((millis() - timer) > 60) {  // print data every 10ms
    angleX = mpu.getAngleX();
    angleY = mpu.getAngleY();
    angleZ = mpu.getAngleZ();
    timer = millis();
  }


  buttonsDisplay();
}

void processInputs() {
  buttonState1 = digitalRead(button1Pin);
  buttonState2 = digitalRead(button2Pin);
  buttonState3 = digitalRead(button3Pin);
  buttonState4 = digitalRead(button4Pin);
}

// ----------------- DISPLAYS -----------------

void buttonsDisplay() {
  display.clearDisplay();

  // Draw button text
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(angleX);
  display.setCursor(0, 10);
  display.println(angleY);
  display.setCursor(0, 20);
  display.println(angleZ);
  display.display();
  return;
  // A
  if (buttonState1 == LOW) {
    display.setTextColor(SSD1306_BLACK);
    display.fillCircle(10, 10, 10, SSD1306_WHITE);
  } else {
    display.setTextColor(SSD1306_WHITE);
    display.drawCircle(10, 10, 10, SSD1306_WHITE);
  }
  display.setCursor(5, 4);
  display.println(F("A"));

  // B
  if (buttonState2 == LOW) {
    display.setTextColor(SSD1306_BLACK);
    display.fillCircle(30, 10, 10, SSD1306_WHITE);
  } else {
    display.setTextColor(SSD1306_WHITE);
    display.drawCircle(30, 10, 10, SSD1306_WHITE);
  }
  display.setCursor(25, 4);
  display.println(F("B"));

  // C
  if (buttonState3 == LOW) {
    display.setTextColor(SSD1306_BLACK);
    display.fillCircle(50, 10, 10, SSD1306_WHITE);
  } else {
    display.setTextColor(SSD1306_WHITE);
    display.drawCircle(50, 10, 10, SSD1306_WHITE);
  }
  display.setCursor(45, 4);
  display.println(F("C"));

  // D
  if (buttonState4 == LOW) {
    display.setTextColor(SSD1306_BLACK);
    display.fillCircle(70, 10, 10, SSD1306_WHITE);
  } else {
    display.setTextColor(SSD1306_WHITE);
    display.drawCircle(70, 10, 10, SSD1306_WHITE);
  }
  display.setCursor(65, 4);
  display.println(F("D"));


  display.setCursor(0, 0);


  display.display();
}