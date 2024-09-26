#include <Servo.h>

Servo fServo, bServo;
int plotMap[50][50];
long startTime;


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  servoTest(2);

}

/*
 * This function will use the Sonar Sensor 
 * Using the Sensor it  calculate the distance if the closest object
 */
int calculateDistance() {
 int distance = 0;

  return distance;
}

void servoTest(int Pin) {
  fServo.attach(Pin);
  for(int i = 0; i <= 180; i++) {
    fServo.write(i);
    delay(15);
  }
  for(int j = 180; j >= 0; j--) {
    fServo.write(j);
    delay(15);
  }
  
}
/*
 * This function sets up PINs for the front and back Servo Motors
 */
void setUpServos(int frontPin, int backPin) { 
  fServo.attach(frontPin);
  bServo.attach(backPin);

  fServo.write(90);
  bServo.write(90);
}

/*
 * Will turn the axle so that way the vehicle goes left
 */
void turnLeft() {

}

/*
 * Will turn the axle so that way the vehicle goes right
 */
void turnRight() {

}

/*
 * This function resets the servo Motors back to the origin position
 */
void resetPosition() {
  fServo.write(90);
  bServo.write(90);
}


/*
 * Need to use PWM to calculate time so we can find out speed. Then we will use the total time that the program has been running inorder to 
 * figure out where the vehicle is and then plot it so we can show where it has traveled.
 * IMPORTANT::: FOR X take the cos(servoAngle)*Distance travled FOR Y take the sin(servoAngle)* Distance
 * Distance = (Rate of Motor * Diameter of wheels) * Time passed (PWM - millis() )
 */
void plotPoint(long time) {
  
}
