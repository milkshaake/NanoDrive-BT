#include <SoftwareSerial.h>

// Bluetooth setup
#define rxPin 2 // RX pin for Bluetooth communication
#define txPin 3 // TX pin for Bluetooth communication
//Create software serial object to communicate with HC-05
SoftwareSerial mySerial(3, 2); //HC-05 Tx & Rx is connected to Arduino #3 & #2

// Motor control pins
int enA = 9;  // PWM pin for speed control of right motors
int in1 = A0; // Direction pin for right motor 1
int in2 = A1; // Direction pin for right motor 2
int enB = 10; // PWM pin for speed control of left motors
int in3 = A2; // Direction pin for left motor 1
int in4 = A3; // Direction pin for left motor 2

void setup() {
  // Set motor control pins as outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Set Bluetooth serial communication baud rate
  mySerial.begin(9600);
  Serial.begin(9600);
  
  Serial.println("Initializing...");
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if (mySerial.available()) {
    char command = mySerial.read();
    Serial.println(command); // For debugging purposes
    executeCommand(command);
  }
}

void executeCommand(char command) {
  switch (command) {
    case 'F': // Forward
      moveForward();
      break;
    case 'B': // Backward
      moveBackward();
      break;
    case 'L': // Turn left
      turnLeft();
      break;
    case 'R': // Turn right
      turnRight();
      break;
    case 'S': // Stop
      stopMotors();
      break;
  }
}

void moveForward() {
  // Right motors forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // Left motors forward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 255); // Speed control
  analogWrite(enB, 255); // Speed control
  Serial.println("moveForward called");
}

void moveBackward() {
  // Right motors backward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // Left motors backward
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, 255); // Speed control
  analogWrite(enB, 255); // Speed control
}

void turnLeft() {
  // Right motors forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // Left motors backward
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, 255); // Speed control
  analogWrite(enB, 255); // Speed control
}

void turnRight() {
  // Right motors backward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // Left motors forward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 255); // Speed control
  analogWrite(enB, 255); // Speed control
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0); // Stop
  analogWrite(enB, 0); // Stop
}
