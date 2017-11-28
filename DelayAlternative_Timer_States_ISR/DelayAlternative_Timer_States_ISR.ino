#include <Servo.h>

Servo myServo;

//LED 
#define PIN_LED 11
int ledState = LOW;
long ledChangeTime = 0L;

//SERVO
#define STEP_FORWARD 10
#define STEP_BACK -10
int servoState = STEP_FORWARD;
int servoPos = 0;
long servoStepTime = 0L;

//BUTTON
#define PIN_BUTTON 2
volatile byte buttonState = LOW; //volatile moet ervoor als je met Interrupt Service Routine (ISR) werkt

//LED 2 (BUTTON LED)
#define PIN_LED2 12
int led2State = LOW;


void setup() {
  Serial.begin(9600);
  myServo.attach(9);

  pinMode(PIN_LED, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  pinMode(PIN_LED2, OUTPUT);

  /*CHANGE (verandering van een state) is 1 van de verschillende states, die je kunt detecteren met ISR.
   De andere zijn: RISING (van 0 naar 5v), FALLING (van 5v naar 0), en LOW (0). De state HIGH kan met ISR niet
  gedetecteerd worden op de Aruidno Uno.*/
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON), buttonISR, CHANGE); /*pin die gechecked moet worden (PIN_BUTTON, in dit geval pin 2),
  naam die je aan de functie geeft (buttonISR), state die je wil checken (CHANGE).*/
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(A0);
  Serial.print("value");
  Serial.println(value);

  long currentTimeMS = millis();
  if (currentTimeMS - ledChangeTime > 500) {
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(PIN_LED, ledState);
    ledChangeTime = currentTimeMS;
  }

  if (currentTimeMS - servoStepTime > 200) {
    myServo.write(servoPos);
    servoStepTime = STEP_FORWARD;
    if (servoState == STEP_FORWARD) {
      servoPos += 10;
    } else {
      servoPos -= 10;
    }
  }

  if (servoPos > 180) {
    servoPos = 180;
    servoState = STEP_BACK;
  } else if (servoPos < 0) {
    servoPos = 0;
    servoState = STEP_FORWARD;
  }

}

void buttonISR() {
  buttonState = !buttonState;
  if (buttonState == HIGH) {
    led2State = HIGH;
    } else {
      led2State = LOW;
      }
}
