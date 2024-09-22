#define BUTTON_PIN_0 4
#define BUTTON_PIN_1 5
#define BUTTON_PIN_2 6
#define BUTTON_PIN_3 7

void setup()
{
  Serial.begin(9600);
  pinMode(BUTTON_PIN_0, INPUT_PULLUP);
  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);
  pinMode(BUTTON_PIN_3, INPUT_PULLUP);
}
void loop()
{
  byte buttonState0 = digitalRead(BUTTON_PIN_0);
  byte buttonState1 = digitalRead(BUTTON_PIN_1);
  byte buttonState2 = digitalRead(BUTTON_PIN_2);
  byte buttonState3 = digitalRead(BUTTON_PIN_3);
  
  if (buttonState0 == HIGH) {
      Serial.println("Button 0 is pressed");
  }
  else {
      
  }

  if (buttonState1 == HIGH) {
      Serial.println("Button 1 is pressed");
  }
  else {
      
  }

  if (buttonState2 == HIGH) {
      Serial.println("Button 2 is pressed");
  }
  else {
      
  }

  if (buttonState3 == HIGH) {
      Serial.println("Button 3 is pressed");
  }
  delay(100);
}
