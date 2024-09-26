int ENA1 = 6;
int IN1 = 7;
int IN2 = 8;
int HIGH1 = 1;
int LOW1 = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ENA1, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
}

void loop() {
  int count = 0;
//  for(count = 0; count < 5; count++) {
    forwardMotors(220);
    delay(4000);
  //  reverseMotors(220);
    delay(4000);
 // }
}

void forwardMotors(int speed) {
  if(speed > 255) {
    speed = 255;
  }
  if(speed < 0) {
    speed = 0;
  }
  digitalWrite(IN1, HIGH1);
  digitalWrite(IN2, LOW1);
  analogWrite(ENA1, speed);
}

void reverseMotors(int speed) {
  if(speed > 255) {
    speed = 255;
  }
  if(speed < 0) {
    speed = 0;
  }
  digitalWrite(IN1, LOW1);
  digitalWrite(IN2, HIGH1);
  analogWrite(ENA1, speed); 
}

void initBreaking() {
  analogWrite(ENA1, 150);
  digitalWrite(IN1, LOW1);
  digitalWrite(IN2, LOW1);
}
