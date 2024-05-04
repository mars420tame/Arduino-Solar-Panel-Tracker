#include <Servo.h>

// Define pin numbers for the LDRs
#define LDR_LEFT_TOP A2
#define LDR_RIGHT_TOP A0
#define LDR_LEFT_BOTTOM A1
#define LDR_RIGHT_BOTTOM A3

// Define pin numbers for the servos
#define HORIZONTAL_SERVO_PIN 11
#define VERTICAL_SERVO_PIN 10

// Tolerance to determine how close the readings need to be
#define TOLERANCE 10

// Initial position of the servos
#define INITIAL_HORIZONTAL_POSITION 90
#define INITIAL_VERTICAL_POSITION 90

// Servo objects
Servo horizontalServo;
Servo verticalServo;

void setup() {
  // Attach the servos
  horizontalServo.attach(HORIZONTAL_SERVO_PIN);
  verticalServo.attach(VERTICAL_SERVO_PIN);
  
  // Move the servos to the initial positions
  horizontalServo.write(INITIAL_HORIZONTAL_POSITION);
  verticalServo.write(INITIAL_VERTICAL_POSITION);
  
  // Wait a bit for the servos to reach the positions
  delay(1000);
}

void loop() {
  // Read values from all four LDRs
  int ldrLeftTopValue = analogRead(LDR_LEFT_TOP);
  int ldrRightTopValue = analogRead(LDR_RIGHT_TOP);
  int ldrLeftBottomValue = analogRead(LDR_LEFT_BOTTOM);
  int ldrRightBottomValue = analogRead(LDR_RIGHT_BOTTOM);

  // Calculate the differences between the top and bottom LDR pairs
  int horizontalDifference = (ldrLeftTopValue - ldrRightTopValue) + (ldrLeftBottomValue - ldrRightBottomValue);
  int verticalDifference = (ldrLeftTopValue + ldrRightTopValue) - (ldrLeftBottomValue + ldrRightBottomValue);

  // Retrieve the current positions of the servos
  int currentHorizontalPosition = horizontalServo.read();
  int currentVerticalPosition = verticalServo.read();

  // Check if the differences are outside the tolerance
  if (abs(horizontalDifference) > TOLERANCE) {
    // Adjust horizontal servo position
    currentHorizontalPosition += horizontalDifference > 0 ? -1 : 1;
    currentHorizontalPosition = constrain(currentHorizontalPosition, 0, 180);
    horizontalServo.write(currentHorizontalPosition);
  }

  if (abs(verticalDifference) > TOLERANCE) {
    // Adjust vertical servo position
    currentVerticalPosition += verticalDifference > 0 ? -1 : 1;
    currentVerticalPosition = constrain(currentVerticalPosition, 0, 180);
    verticalServo.write(currentVerticalPosition);
  }

  // Short delay before the next loop iteration
  delay(80);
}
