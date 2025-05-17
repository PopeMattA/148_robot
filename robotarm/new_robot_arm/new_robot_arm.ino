#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

const int STOP = 375;
const int FORWARD = 650;
const int REVERSE = 175;
const int ROTATE_360_TIME = 1200;  // Adjust this for your servos

const int servoChannel0 = 0;
const int servoChannel1 = 1;
const int servoChannel2 = 2;
const int servoChannel3 = 3;

// Function prototype
void spinOnce(int channel, int directionPWM, const char* message);

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50);

  Serial.println("Press keys to control servos:");
  Serial.println("  q = Servo 0 forward");
  Serial.println("  a = Servo 0 reverse");
  Serial.println("  w = Servo 1 forward");
  Serial.println("  s = Servo 1 reverse");
}

void loop() {
  // Check for a handshake
  if (Serial.available()) {
    char receivedByte = Serial.read();
    
    if (receivedByte == 'B') {
      Serial.println("Handshake received!");
      Serial.print('A');  // Send acknowledgment
      return;
    }
    
    // Process commands
    switch (receivedByte) {
      case 'q': spinOnce(servoChannel0, FORWARD, "Servo 0 → FORWARD 360°"); break;
      case 'a': spinOnce(servoChannel0, REVERSE, "Servo 0 → REVERSE 360°"); break;
      case 'w': spinOnce(servoChannel1, 600, "Servo 1 → FORWARD 360°"); break;
      case 's': spinOnce(servoChannel1, 150, "Servo 1 → REVERSE 360°"); break;
      case 'e': spinOnce(servoChannel1, 485, "Servo 1 → Up"); break;
      case 'f': spinOnce(servoChannel0, 412, "Servo 0 → Forward"); break;
      case 'g': spinOnce(servoChannel2, 650, "Servo 2 → Down"); break;
      case 'h': spinOnce(servoChannel2, 150, "Servo 2 → Up"); break;
      case 'j': spinOnce(servoChannel2, 535, "Servo 2 → Straight Up"); break;
      case 'r': spinOnce(servoChannel3, 615, "Servo 3 → Grabber Pickup"); break;
      case 't': spinOnce(servoChannel3, 140, "Servo 3 → Grabber Hold"); break;
      case 'y': spinOnce(servoChannel3, 378, "Servo 3 → Straight Up"); break;
      default: Serial.println("Unknown key."); break;
    }
  }
}

void spinOnce(int channel, int directionPWM, const char* message) {
  Serial.println(message);
  pwm.setPWM(channel, 0, directionPWM);
  delay(ROTATE_360_TIME);
  // Uncomment the line below to stop the motor after each command
  // pwm.setPWM(channel, 0, STOP);
}
