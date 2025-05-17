#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

const int STOP = 375;
const int FORWARD = 650;
const int REVERSE = 175;

const int servoChannel0 = 0; // base
const int servoChannel1 = 1; // Link 1
const int servoChannel2 = 2; // Link 2
const int servoChannel3 = 3; // End of Arm (grabber)

// Try increasing this until your servo makes 1 full rotation
const int ROTATE_360_TIME = 1200; // milliseconds — adjust this

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50);

  Serial.println("Press keys to rotate servos 360°:");
  Serial.println("  q = Servo 0 forward");
  Serial.println("  a = Servo 0 reverse");
  Serial.println("  w = Servo 1 forward");
  Serial.println("  s = Servo 1 reverse");
}

void loop() {
  // Check for a response byte
  
  if (Serial.available()) {
    char receivedByte = Serial.read();
    
    if (receivedByte == 'B') {
      Serial.println("Handshake received!");
      Serial.print('A');  // Send acknowledgment
      return;
    }
  }

      char key = Serial.read();
      switch (key) {
        case 'q':
          spinOnce(servoChannel0, FORWARD);
          Serial.println("Servo 0 → max");
          break;

        case 'a':
          spinOnce(servoChannel0, REVERSE);
          Serial.println("Servo 0 → min");
          break;

        case 'w':
          spinOnce(servoChannel1, 600);
          Serial.println("Servo 1 → Max");
          break;

        case 's':
          spinOnce(servoChannel1, 150);
          Serial.println("Servo 1 → Min");
          break;

        case 'e':
          spinOnce(servoChannel1, 485);
          Serial.println("Servo 1 → Starting Point (Neutral)");
          break;

        case 'f':
          spinOnce(servoChannel0, 412.5);
          Serial.println("Servo 0 -> Starting Pooint (Neutral facing forward)");
          break;
        
        case 'g':
          spinOnce(servoChannel2, 650);
          Serial.println("Servo 2 → Max down");
          break;

        case 'h':
          spinOnce(servoChannel2, 150);
          Serial.println("Servo 2 → Max up");
          break;
        
        case 'j':
          spinOnce(servoChannel2, 535);
          Serial.println("Servo 2 → Starting (Neuatral, straight up)");
          break;
        
        case 'r':
          spinOnce(servoChannel3, 615);
          Serial.println("Servo 3 → grabber pickup");
          break;
        
        case 't':
          spinOnce(servoChannel3, 140);
          Serial.println("Servo 3 → grabber hold (neutral position for surveying)");
          break;
        
        case 'y':
          spinOnce(servoChannel3, 377.5);
          Serial.println("Servo 3 → straight up");
          break;

        default:
          Serial.println("Unknown key.");
          break;
      }
    }
  }
}

void spinOnce(int channel, int directionPWM) {
  pwm.setPWM(channel, 0, directionPWM);
  delay(ROTATE_360_TIME);         // Spin duration (calibrate this!)
  //pwm.setPWM(channel, 0, STOP);   // Stop motor
}
