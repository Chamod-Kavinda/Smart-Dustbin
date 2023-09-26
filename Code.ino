#include <Servo.h>

// constants won't change
const int TRIG_PIN1  = 7;  // Arduino pin connected to Ultrasonic Sensor's TRIG pin
const int ECHO_PIN1  = 8;  // Arduino pin connected to Ultrasonic Sensor's ECHO pin
const int TRIG_PIN2  = 5;  // Arduino pin connected to Ultrasonic Sensor's TRIG pin
const int ECHO_PIN2  = 6;  // Arduino pin connected to Ultrasonic Sensor's ECHO pin
const int SERVO_PIN = 3; // Arduino pin connected to Servo Motor's pin
const int DISTANCE_THRESHOLD = 20; // centimeters

Servo servo; // create servo object to control a servo

// variables will change:
float duration_1, distance_1;
float duration_2, distance_2;
int red_LED = 10;
int green_LED = 11;
int blue_LED = 9;

void setup() {
  Serial.begin (9600);       // initialize serial port
  pinMode(TRIG_PIN1, OUTPUT); // set arduino pin to output mode
  pinMode(ECHO_PIN1, INPUT);  // set arduino pin to input mode
  pinMode(TRIG_PIN2, OUTPUT); // set arduino pin to output mode
  pinMode(ECHO_PIN2, INPUT);  // set arduino pin to input mode
  pinMode(red_LED, OUTPUT);
  pinMode(green_LED, OUTPUT);
  pinMode(blue_LED, OUTPUT);
  servo.attach(SERVO_PIN);   // attaches the servo on pin 9 to the servo object
  servo.write(0);
  analogWrite(red_LED, 0);
  analogWrite(green_LED, 255);
  analogWrite(blue_LED, 0);
}

void loop() {
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN1, LOW);

  duration_1 = pulseIn(ECHO_PIN1, HIGH);
  // calculate the distance
  distance_1 = 0.017 * duration_1;

  digitalWrite(TRIG_PIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN2, LOW);

  duration_2 = pulseIn(ECHO_PIN2, HIGH);
  // calculate the distance
  distance_2 = 0.017 * duration_2;

  if(distance_1 < DISTANCE_THRESHOLD) {
    servo.write(90); // rotate servo motor to 90 degree
    analogWrite(red_LED, 0);
    analogWrite(green_LED, 0);
    analogWrite(blue_LED, 255);
    delay(3000);
  }
  else {
    servo.write(0);  // rotate servo motor to 0 degree
    if (distance_2 < 10) {
      analogWrite(red_LED, 255);
      analogWrite(green_LED, 0);
      analogWrite(blue_LED, 0);
    }
    else if (distance_2 < 20) {
      analogWrite(red_LED, 255);
      analogWrite(green_LED, 200);
      analogWrite(blue_LED, 0);
    }
    else {
      analogWrite(green_LED, 255);
      analogWrite(red_LED, 0);
      analogWrite(blue_LED, 0);
    }
  }

  // print the value to Serial Monitor

  delay(300);
}
