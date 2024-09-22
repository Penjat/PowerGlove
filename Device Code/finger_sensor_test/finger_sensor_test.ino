const int sensorPin0 = A0;  // pin where your sensor is connected
const int sensorPin1 = A1;  // pin where your sensor is connected
const int sensorPin2 = A2;  // pin where your sensor is connected
const int sensorPin3 = A3;  // pin where your sensor is connected

int sensorValue0 = 0; 
int sensorValue1 = 0; 
int sensorValue2 = 0; 
int sensorValue3 = 0; 

int minValue = 1023;  // initialize to the maximum possible value
int maxValue = 0;     // initialize to the minimum possible value

void setup() {
  Serial.begin(9600);  // start serial communication at 9600 bps
  pinMode(sensorPin0, INPUT);
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  pinMode(sensorPin3, INPUT);
}

void loop() {
  sensorValue0 = analogRead(sensorPin0);  // read the sensor value
  sensorValue1 = analogRead(sensorPin1);  // read the sensor value
  sensorValue2 = analogRead(sensorPin2);  // read the sensor value
  sensorValue3 = analogRead(sensorPin3);  // read the sensor value
  
  Serial.print("0: "); 
  Serial.print(sensorValue0);
  Serial.print("1: "); 
  Serial.print(sensorValue1);
  Serial.print("2: "); 
  Serial.print(sensorValue2);
  Serial.print("3: "); 
  Serial.println(sensorValue3);
 

  delay(500); 
}
