#include <Servo.h>

const int leftSensorPin = A0;
const int rightSensorPin = A1;
const int graspSensorPin = 2;
const int S2 = 7;
const int S3 = 8;
const int sensorOut = 12;
const int sonarTrigPin = 10;
const int sonarEchoPin = 11;
const int leftMotorPin1 = 3;
const int leftMotorPin2 = 4;
const int rightMotorPin1 = 5;
const int rightMotorPin2 = 6;
const int servoPin = 9;

Servo grasper;

void setup() {
  pinMode(leftSensorPin, INPUT);
  pinMode(rightSensorPin, INPUT);
  pinMode(graspSensorPin, INPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  pinMode(sonarTrigPin, OUTPUT);
  pinMode(sonarEchoPin, INPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  grasper.attach(servoPin);
  grasper.write(0);
  Serial.begin(9600);
}

void loop() {
  int leftBorder = analogRead(leftSensorPin);
  int rightBorder = analogRead(rightSensorPin);
  int graspSensor = digitalRead(graspSensorPin);
  long distance = getDistance();
  String color = readColor();

  if (leftBorder > 500) {
    turnRightShort();
  } else if (rightBorder > 500) {
    turnLeftShort();
  } else {
    moveShortForward();
  }

  if (distance > 0 && distance < 10) {
    if (color == "RED") {
      moveForward();
    } else if (color == "BLUE") {
      turnRightShort();
    } else if (color == "GREEN") {
      turnLeftShort();
    } else {
      grasp();
    }
  }
}

String readColor() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  int red = pulseIn(sensorOut, LOW);
  delay(50);

  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  int blue = pulseIn(sensorOut, LOW);
  delay(50);

  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  int green = pulseIn(sensorOut, LOW);
  delay(50);

  if (red < blue && red < green) {
    return "RED";
  } else if (blue < red && blue < green) {
    return "BLUE";
  } else if (green < red && green < blue) {
    return "GREEN";
  } else {
    return "UNKNOWN";
  }
}