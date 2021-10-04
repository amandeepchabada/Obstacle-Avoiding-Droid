const int trigPin = 11;
const int echoPin = 10;
const int in1 = 9;
const int in2 = 8;
const int in3 = 4;
const int in4 = 3;
//const int pwm1 = 5;
const int pwm2 = 6;
int state;
int flag=0;        //makes sure that the serial only prints once the state
int stateStop=0;
 
void setup()
{
//  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode (in1, OUTPUT);
  pinMode (in2, OUTPUT);
  pinMode (in3, OUTPUT);
  pinMode (in4, OUTPUT);
  Serial.begin(38400);
}
long duration, distance;
void loop()
{
    if(Serial.available() > 0){     
      state = Serial.read();   
      flag=0;
    } 
 if(state=='A'){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration/58.2;
    if(distance<25 && distance>10)
      {
  //      analogWrite(pwm1,180);
        analogWrite(pwm2,180);
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
      }
    else if(distance<10)
      {
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        digitalWrite(in3, LOW);
        digitalWrite(in4, LOW);
      }
    else
      {
    //    analogWrite(pwm1,180);
        analogWrite(pwm2,180);
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
      }
      if(flag == 0){
        Serial.println("Go Auto!");
        flag=1;
      }
  delay(50);
  }//outer if close
  if (state == 'F') {
  //analogWrite(pwm1,180);
  analogWrite(pwm2,180);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
      if(flag == 0){
        Serial.println("Go Forward!");
        flag=1;
      }
  }
 
  // if the state is 'B' the motor will go back
  else if (state == 'B') {
  //analogWrite(pwm1,180);
  analogWrite(pwm2,180);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
      if(flag == 0){
        Serial.println("Reverse");
        flag=1;
      }
  }
  // if the state is 'S' the motor will Stop
  else if (state == 'S' || stateStop == 1) {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      if(flag == 0){
        Serial.println("STOP!");
        flag=1;
      }
      stateStop=0;
  }
  // if the state is 'L' the motor will turn Left
  else if (state == 'L') {
      //analogWrite(pwm1,180);
      analogWrite(pwm2,180);
      digitalWrite(in1,HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      if(flag == 0){
        Serial.println("Turn Left");
        flag=1;
      }
      delay(750);
      state=3;
      stateStop=1;
  }
  // if the state is 'R' the motor will Right
  else if (state == 'R') {
      //analogWrite(pwm1,180);
      analogWrite(pwm2,180);
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      if(flag == 0){
        Serial.println("Right!");
        flag=1;
      }
      delay(750);
      state=3;
      stateStop=1;
  }
}
