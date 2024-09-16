const int sensorPin = A0;  // pin where your sensor is connected
int sensorValue = 0; 
int minValue = 1023;  // initialize to the maximum possible value
int maxValue = 0;     // initialize to the minimum possible value

void setup() {
  Serial.begin(9600);  // start serial communication at 9600 bps
  // pinMode(sensorPin, INPUT);
}

void loop() {
  sensorValue = analogRead(sensorPin);  // read the sensor value

  // Check if this reading is a new minimum
  if (sensorValue < minValue) {
    minValue = sensorValue;
  }

  // Check if this reading is a new maximum
  if (sensorValue > maxValue) {
    maxValue = sensorValue;
  }

  Serial.print("Current reading: "); 
  Serial.print(sensorValue);
  Serial.print("\t Min reading: ");
  Serial.print(minValue);
  Serial.print("\t Max reading: ");
  Serial.println(maxValue);

  delay(500);  // wait half a second before the next reading
}
