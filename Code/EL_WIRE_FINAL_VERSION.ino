/********************************/
/* EL WIRE FINAL VERSION        */
/* Interactive Costumes         */
/* Diver Costume                */
/* Group HEMASU                 */
/* Version 1.0 July 14th, 2014  */
/* Author: Marco Schmandt       */
/********************************/

// initialize all pins
const int collar     = 13;
const int whiteLeft  = 12;
const int whiteRight = 11;
const int blueLeft   = 10;
const int blueRight  =  9;
const int button     =  8;

// counts the times the button has been pressed
int buttonCounter = 0;
// saves the current state of the button
int buttonState   = 0;
// saves the last state of the button
int lastBState    = 0;


void setup() {
  //Serial.begin(9600); // only for debugging
  pinMode(collar, OUTPUT);
  pinMode(whiteLeft, OUTPUT);
  pinMode(whiteRight, OUTPUT);
  pinMode(blueLeft, OUTPUT);
  pinMode(blueRight, OUTPUT);
}

void loop() {

  // read the actual state of the button
  buttonState = digitalRead(button);
  //Serial.println(digitalRead(button)); // only for debugging

  // since white is the standard illumination, set white HIGH
  // and the rest LOW
  digitalWrite(collar, 0);
  digitalWrite(whiteLeft, 1);
  digitalWrite(whiteRight, 1);
  digitalWrite(blueLeft, 0);
  digitalWrite(blueRight, 0);

  // if buttonState is unequal to lastBstate
  // something must have changed
  if(buttonState != lastBState) {
    // if button has been pressed increase counter by 1
    if(buttonState == HIGH) {
      buttonCounter++;
    }
  }
  // current buttonState gets assigned to lastBState
  lastBState = buttonState;

  // everytime the counter modulo 2 == 0
  // white light becomes active
  if(buttonCounter % 2 == 0) {
    digitalWrite(collar, 0);
    digitalWrite(whiteLeft, 1);
    digitalWrite(whiteRight, 1);
    digitalWrite(blueLeft, 0);
    digitalWrite(blueRight, 0);
  }
  // everytime the counter modulo 2 == 1
  // blue light becomes active
  else if(buttonCounter % 2 == 1) {
    digitalWrite(collar, 1);
    digitalWrite(whiteLeft, 0);
    digitalWrite(whiteRight, 0);
    digitalWrite(blueLeft, 1);
    digitalWrite(blueRight, 1);
  }
}
