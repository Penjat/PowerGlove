#define BUTTON_PIN_0 10
#define BUTTON_PIN_1 11
#define BUTTON_PIN_2 12

void setup()
{
  Serial.begin(9600);
  pinMode(BUTTON_PIN_0, INPUT_PULLUP);
  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);
}
void loop()
{
  byte buttonState0 = digitalRead(BUTTON_PIN_0);
  byte buttonState1 = digitalRead(BUTTON_PIN_1);
  byte buttonState2 = digitalRead(BUTTON_PIN_2);
  
  if (buttonState0 == LOW) {
      Serial.println("Button 0 is pressed");
  }
  else {
      
  }

  if (buttonState1 == LOW) {
      Serial.println("Button 1 is pressed");
  }
  else {
      
  }

  if (buttonState2 == LOW) {
      Serial.println("Button 2 is pressed");
  }
  else {
      
  }
  delay(100);
}
