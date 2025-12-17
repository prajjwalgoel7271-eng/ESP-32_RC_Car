#include "BluetoothSerial.h"

// Check if Bluetooth is properly enabled
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

// --- Pin Definitions ---
// Main L298N Motor Driver (Controls the 4 wheels - Left Side & Right Side)
// Assumes 2 Left motors parallel on Channel A, 2 Right motors parallel on Channel B
const int IN1 = 26; // Left Motor Forward
const int IN2 = 27; // Left Motor Backward
const int IN3 = 14; // Right Motor Forward
const int IN4 = 12; // Right Motor Backward
const int ENA = 25; // Left Motor Speed (PWM) - Optional, can be jumpered to 5V
const int ENB = 13; // Right Motor Speed (PWM) - Optional, can be jumpered to 5V

// Secondary Motor Driver (Mirrors the signals of the main driver)
// Connect these pins to the IN/EN pins of the second driver
const int SEC_IN1 = 16;
const int SEC_IN2 = 17;
const int SEC_IN3 = 5;
const int SEC_IN4 = 18;
const int SEC_ENA = 19;
const int SEC_ENB = 21;

// Motor Speed (0-255)
const int MOTOR_SPEED = 255; // Max speed

void setup() {
  Serial.begin(115200);
  
  // Initialize Bluetooth
  SerialBT.begin("ESP32_RC_Car"); // Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  // Initialize Main Motor Pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Initialize Secondary Motor Pins
  pinMode(SEC_IN1, OUTPUT);
  pinMode(SEC_IN2, OUTPUT);
  pinMode(SEC_IN3, OUTPUT);
  pinMode(SEC_IN4, OUTPUT);
  pinMode(SEC_ENA, OUTPUT);
  pinMode(SEC_ENB, OUTPUT);

  // Stop all motors initially
  stopMotors();
}

void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read();
    Serial.print("Received: ");
    Serial.println(command);
    processCommand(command);
  }
}

void processCommand(char command) {
  // Convert to uppercase to handle 'f' and 'F'
  command = toupper(command);

  switch (command) {
    case 'F':
      moveForward();
      break;
    case 'B':
      moveBackward();
      break;
    case 'L':
      turnLeft();
      break;
    case 'R':
      turnRight();
      break;
    case 'S':
      stopMotors();
      break;
    default:
      // Ignore unknown commands or handle extra logic
      break;
  }
}

// --- Motor Control Functions ---

// Helper to set pins for both drivers simultaneously
void setMotors(int in1, int in2, int in3, int in4) {
  // Main Driver
  digitalWrite(IN1, in1);
  digitalWrite(IN2, in2);
  digitalWrite(IN3, in3);
  digitalWrite(IN4, in4);
  
  // Enable pins (Always ON for now, or use analogWrite for speed control)
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);

  // Secondary Driver (Mirroring)
  digitalWrite(SEC_IN1, in1);
  digitalWrite(SEC_IN2, in2);
  digitalWrite(SEC_IN3, in3);
  digitalWrite(SEC_IN4, in4);
  
  // Secondary Enable pins
  analogWrite(SEC_ENA, MOTOR_SPEED);
  analogWrite(SEC_ENB, MOTOR_SPEED);
}

void moveForward() {
  Serial.println("Moving Forward");
  // Left Forward, Right Forward
  setMotors(HIGH, LOW, HIGH, LOW);
}

void moveBackward() {
  Serial.println("Moving Backward");
  // Left Backward, Right Backward
  setMotors(LOW, HIGH, LOW, HIGH);
}

void turnLeft() {
  Serial.println("Turning Left");
  // Left Backward, Right Forward (Spin Turn)
  setMotors(LOW, HIGH, HIGH, LOW);
}

void turnRight() {
  Serial.println("Turning Right");
  // Left Forward, Right Backward (Spin Turn)
  setMotors(HIGH, LOW, LOW, HIGH);
}

void stopMotors() {
  Serial.println("Stopping");
  // All Low
  setMotors(LOW, LOW, LOW, LOW);
  
  // Turn off Enable pins to ensure full stop
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  digitalWrite(SEC_ENA, LOW);
  digitalWrite(SEC_ENB, LOW);
}
