#include <Servo.h>

Servo servo;
const int servoPin = 6;

const int in1 = 2;
const int in2 = 3;
const int in3 = 4;
const int in4 = 5;

int speed = 100; // 0 - 255
int response;

const int trigPin = 42;
const int echoPin = 44;

const int buzzerPin = 7;

int distance = 0;

void setup() 
{
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(servoPin, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(buzzerPin, OUTPUT);

  servo.attach(servoPin);
  servo.write(90);

  Serial.begin(9600);
}

void loop() 
{
  if (Serial.available() > 0)
  {
    stop();

    response = Serial.read();

    switch (response)
    {
      case 'F':
        forward();
      break;

      case 'B':
        back();
        analogWrite(buzzerPin, 100);
      break;

      case 'L':
        left();
      break;

      case 'R':
        right();
      break;

      case 'G':
        left();
        forward();
      break;

      case 'I':
        right();
        forward();
      break;

      case 'H':
        back();
        left();
      break;

      case 'J':
        back();
        right();
      break;
    }
  }
}

void stop()
{
  analogWrite(in1, 0);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
  analogWrite(in4, 0);
  servo.write(90);
  digitalWrite(buzzerPin, LOW);
}

void forward()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  distance = pulseIn(echoPin, HIGH) * 0.017;

  Serial.println(distance);

  if (distance > 0 && distance < 4) analogWrite(buzzerPin, 127);

  analogWrite(in2, speed);
  analogWrite(in4, speed);
}

void back()
{
  analogWrite(in1, speed);
  analogWrite(in3, speed);
}

void left()
{
  servo.write(110);
}

void right()
{
  servo.write(70);
}