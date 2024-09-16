#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 #include <MPU6050_light.h>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>


// Bluetooth
SoftwareSerial hm10(6, 8);

// LCD
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET     4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Buttons
#define BUTTON_PIN_0 10
#define BUTTON_PIN_1 11
#define BUTTON_PIN_2 12

byte buttonState0 = 0;
byte buttonState1 = 0;
byte buttonState2 = 0;


// Finger sensors
#define sensorPin0 A0
#define sensorPin1 A1
#define sensorPin2 A2
#define sensorPin3 A3

int sensorValue0 = 0;
int sensorValue1 = 0;
int sensorValue2 = 0;
int sensorValue3 = 0;

int max_1 = 700;
int min_1 = 400;

int max_2 = 700;
int min_2 = 400;

int max_3 = 700;
int min_3 = 400;


// Rotary Encoder
#define CLK 2
#define DT 3

int counter = 0;
int currentStateCLK;
int lastStateCLK;
//String currentDir = "";


// Gyro
MPU6050 mpu(Wire);
//sensors_event_t a, g, temp;

// ----------------- SETUP -----------------
void setup() {
  Serial.begin(9600);
  hm10.begin(9600);
  Wire.begin();

  setUpGyro();
  setUpLCD();
  setUpRotaryEncoder();
  setUpButtons();
}

void setUpRotaryEncoder() {
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT);
  lastStateCLK = digitalRead(CLK);
  attachInterrupt(0, updateEncoder, CHANGE);
  attachInterrupt(1, updateEncoder, CHANGE);
}

void setUpGyro() {
  byte status = mpu.begin();
   Serial.print(F("MPU6050 status: "));
   Serial.println(status);
   while (status != 0) { } // stop everything if could not connect to MPU6050
  Serial.println(F("Calculating offsets, do not move MPU6050"));
   delay(1000);
   mpu.calcOffsets(); // gyro and accelero
   Serial.println("Done!\n");

}

void setUpLCD() {
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
}

void setUpButtons() {
  pinMode(BUTTON_PIN_0, INPUT_PULLUP);
  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);
}

// ----------------- LOOP -----------------

void loop() {
  updateSensors();
  updateCalibration();
  updateDisplay();
  sendSensorData();

  //  char buffer[10]; // Buffer to hold the ASCII representation of the int
  //
  //  // Convert int to char array and send it through SoftwareSerial
  //  itoa(sensorValue0, buffer, 10);
  //  hm10.write(buffer);

  //  int mappedValue = map(sensorValue0, min_2, max_2, 0, 255);
  //  String hexString = String(mappedValue, HEX);
  //  if (hexString.length() == 1) hexString = "0" + hexString;
  //
  //  int mappedValue1 = map(sensorValue1, min_1, max_1, 0, 255);
  //  String hexString1 = String(mappedValue1, HEX);
  //  if (hexString1.length() == 1) hexString1 = "0" + hexString1;


  //  hm10.print(hexString+hexString1);


  delay(100);
}

void updateSensors() {

  mpu.update();

  sensorValue0 = analogRead(sensorPin0);
  sensorValue1 = analogRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);
  sensorValue3 = analogRead(sensorPin3);

  buttonState0 = digitalRead(BUTTON_PIN_0);
  buttonState1 = digitalRead(BUTTON_PIN_1);
  buttonState2 = digitalRead(BUTTON_PIN_2);
}

void updateCalibration() {
  if (sensorValue1 > max_1) {
    max_1 = sensorValue1;
  }
  if (sensorValue1 < min_1 && sensorValue1 > 0) {
    min_1 = sensorValue1;
  }

  if (sensorValue0 > max_2) {
    max_2 = sensorValue0;
  }
  if (sensorValue0 < min_2 && sensorValue0 > 0) {
    min_2 = sensorValue0;
  }

  if (sensorValue2 > max_3) {
    max_3 = sensorValue2;
  }
  if (sensorValue2 < min_3 && sensorValue2 > 0) {
    min_3 = sensorValue2;
  }

}

void updateEncoder() {
  // Read the current state of CLK
  currentStateCLK = digitalRead(CLK);

  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1) {

    if (digitalRead(DT) != currentStateCLK) {
      counter --;
//      currentDir = "CCW";
    } else {
      // Encoder is rotating CW so increment
      counter ++;
//      currentDir = "CW";
    }

    Serial.print("Direction: ");
//    Serial.print(currentDir);
    Serial.print(" | Counter: ");
    Serial.println(counter);
  }

  // Remember last CLK state
  lastStateCLK = currentStateCLK;
}

void sendSensorData() {

  byte data[12]; 

  // Start Marker
  data[0] = 0x02;
  
  data[1] = map(sensorValue0, min_2, max_2, 0, 255);
  data[2] = map(sensorValue1, min_1, max_1, 0, 255);
  data[3] = map(sensorValue2, min_3, max_3, 0, 255);
  data[4] = (buttonState0 << 2) | (buttonState1 << 1) | buttonState2;

  data[5] = map(mpu.getAngleX(), -180, 180, 0, 255);
  data[6] = map(mpu.getAngleY(), -180, 180, 0, 255);
  data[7] = map(mpu.getAngleZ(), -180, 180, 0, 255);
  data[8] = mpu.getAccX();
  data[9] = mpu.getAccY();
  data[10] = mpu.getAccZ();

  // End marker
  data[11] = 0x03;

  hm10.write(data, 12);
}


void updateDisplay() {
  if (counter % 2 == 0) {
    buttonsDisplay();
  } else {
    gyroDisplay();
  }
}
 

// ----------------- DISPLAYS -----------------


void buttonsDisplay() {
  display.clearDisplay();
  display.drawRect(0, 0, display.width() / 2, display.height() / 3, SSD1306_WHITE);
  display.drawRect(0, display.height() / 3, display.width() / 2, display.height() / 3, SSD1306_WHITE);
  display.drawRect(0, (display.height() / 3) * 2 , display.width() / 2, display.height() / 3, SSD1306_WHITE);

  display.fillRect(0, 0, (display.width() / 2) * (sensorValue1 - min_1) / (max_1 - min_1), display.height() / 3, SSD1306_WHITE);
  display.fillRect(0, display.height() / 3, (display.width() / 2) * (sensorValue0 - min_2) / (max_2 - min_2), display.height() / 3, SSD1306_WHITE);
  display.fillRect(0, (display.height() / 3) * 2, (display.width() / 2) * (sensorValue2 - min_2) / (max_2 - min_2), display.height() / 3, SSD1306_WHITE);



  // Draw button text
  display.setTextSize(2);


  // A
  if (buttonState1 == LOW) {
    display.setTextColor(SSD1306_BLACK);
    display.fillCircle(display.width() / 2 + 12, 10, 10, SSD1306_WHITE);
  }
  else {
    display.setTextColor(SSD1306_WHITE);
    display.drawCircle(display.width() / 2 + 12, 10, 10, SSD1306_WHITE);

  }
  display.setCursor(72, 4);
  display.println(F("A"));

  // B
  if (buttonState2 == LOW) {
    display.setTextColor(SSD1306_BLACK);
    display.fillCircle(display.width() / 2 + 32, 10, 10, SSD1306_WHITE);
  }
  else {
    display.setTextColor(SSD1306_WHITE);
    display.drawCircle(display.width() / 2 + 32, 10, 10, SSD1306_WHITE);

  }
  display.setCursor(92, 4);
  display.println(F("B"));

  // C
  if (buttonState0 == LOW) {
    display.setTextColor(SSD1306_BLACK);
    display.fillCircle(display.width() / 2 + 52, 10, 10, SSD1306_WHITE);
  }
  else {
    display.setTextColor(SSD1306_WHITE);
    display.drawCircle(display.width() / 2 + 52, 10, 10, SSD1306_WHITE);

  }
  display.setCursor(112, 4);
  display.println(F("C"));


  display.setCursor(0, 0);


  display.setTextSize(1);

  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  //  display.setCursor(0, 0);
  //  display.println(F("THUMB"));
  //  //  display.println(sensorValue1);
  //
  //
  //  display.setCursor(0, 16);
  //  display.println(F("INDEX"));
  //  display.println(sensorValue0);

  display.setTextColor(SSD1306_WHITE);
  display.setCursor(80, 24);
  display.println(counter);
  display.display();
}

void gyroDisplay() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
//  display.println(g.gyro.x);
//
//  display.setCursor(45, 0);
//  display.println(g.gyro.y);
//
//  display.setCursor(90, 0);
//  display.println(g.gyro.z);
//
//  display.setCursor(0, 20);
//  display.println(g.acceleration.x);
//  display.setCursor(45, 20);
//  display.println(g.acceleration.y);
//  display.setCursor(90, 20);
//  display.println(g.acceleration.z);


  display.display();

}
