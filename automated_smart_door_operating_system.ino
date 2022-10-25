// Coding and schematics: Md Faiyaz Siddiquee

#include <Servo.h> // importing the Servo library
Servo servo;

#define echoPin 6
#define trigPin 7
#define servoPin 2
#define buzzerPin 8
#define ledPin 12

long duration; 
long distance;

void setup() {
  Serial.begin(9600); // setup for the serial monitor
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
  pinMode(echoPin, INPUT); // echo pin will receive the input
  pinMode(trigPin, OUTPUT); // trig pin will trigger/send the output

  servo.attach(servoPin);
  servo.write(90);
  delay(2000);
}

void loop() {
  digitalWrite(ledPin, HIGH); // red LED is initailly on
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH); // sends the high pulse
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH); // measures the time taken for the pulse (high) to reach the object and come back (in µs)
  duration = duration/2; // one-way duration is half, as the pulse covered the distance two times 
  distance = 0.033*duration; // speed of sound in dry air is 0.033 cm/µs
  Serial.println(distance); // in cm
  delay(50);

  if(distance < 15) {
    digitalWrite(ledPin, LOW); // red LED turns off
    servo.write(0); // gate opens
    delay(1000);
    digitalWrite(buzzerPin, HIGH); // buzzer rings
    delay(1500);
    digitalWrite(buzzerPin, LOW);
    delay(1000);
    servo.write(90); // gate closes
  }
}
