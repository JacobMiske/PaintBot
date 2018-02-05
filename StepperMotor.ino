#include <Stepper.h>

const int ledPin = 8;
Stepper upStepper1(360, 0, 1, 2, 3);
Stepper upStepper2(360, 0, 1, 2, 3);
Stepper horizontalStepper(360, 0, 1, 2, 3);

Stepper motionStepperLeft(360, 0, 1, 2, 3);
Stepper motionStepperRight(360, 0, 1, 2, 3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  
  upStepper1.setSpeed(60);
  upStepper2.setSpeed(60);
  horizontalStepper.setSpeed(60);
  motionStepperLeft.setSpeed(60);
  motionStepperRight.setSpeed(60);
}

char buffer[255];

void rotate() {
  stepper.step(200);
  delay(5000);
  stepper.step(0);
}

void blink() {
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);
}

// Helper This is for the 90 degree turned gears
void driveStep90(x, y, SteppMotor, Speed){
  // Diameter is 25mm
  Radius
}

// Helper This is for the straight on gears
void driveStepStraight(x, y, SteppMotor, Speed){
  // Diameter is 40mm
  Radius = 20
}

int i = 0;
void loop() {
    if(Serial.available() > 0) {
        char c = Serial.read();
        if(c == '\n') {
          buffer[i] = '\0';

          String message(buffer);

          if(message == "BLINK") {
              blink();
          } else if(message == "MOVE_FORWARD") {
              move_forward();
          } else if(message == "MOVE_BACKWARD") {
              move_backward();
          } else if(message == "MOVE_BAC") {
              move_backward();
          } 
          i = 0;
        } else {
          buffer[i] = c;
          i++;
        }
      }

      int buttonState = digitalRead(buttonPin);
      if(buttonState !=  lastButtonState) {
        if(buttonState == LOW) {
          Serial.println("Message1");
        }
        lastButtonState = buttonState;
      }
}
