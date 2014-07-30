/***********************************************/
/* OXYGEN TANK/DISPLAY AND ?GUN? FINAL VERSION */
/* Interactive Costumes                        */
/* Diver Costume                               */
/* Group HEMASU                                */
/* Version 1.0 July 14th, 2014                 */
/* Author: Marco Schmandt                      */
/***********************************************/

// Pin connected to DS of 74HC595
const int clockPin      = 13; //12
//Pin connected to DS of 74HC595
const int dataPin       = 12; //11
//Pin connected to ST_CP of 74HC595
const int latchPin      = 11; //8

// initialize led pins
int redR          = A0;
int greenR        = A1;
int blueR         = A2;
int redL          = A3;
int greenL        = A4;
int blueL         = A5;

// variables for the color values
int redRVal   = 0;
int greenRVal = 0;
int blueRVal  = 0;
int redLVal   = 0;
int greenLVal = 0;
int blueLVal  = 0;

int displayButton =  10;

// counts the times the button has been pressed
int buttonCounter = 0;
// saves the current state of the button
int buttonState   = 0;
// saves the last state of the button
int lastBState    = 0;

// holds the current value of the button
int val = 0;

// array for the shift patterns
int input[16];

void setup() {

  Serial.begin(9600); // only for debugging

  //set pins to OUTPUT so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(redR, OUTPUT);
  pinMode(greenR, OUTPUT);
  pinMode(blueR, OUTPUT);
  pinMode(redL, OUTPUT);
  pinMode(greenL, OUTPUT);
  pinMode(blueL, OUTPUT);
  pinMode(displayButton, INPUT);
  input[0]  = B11111111;
  input[1]  = B01111111;
  input[2]  = B00111111;
  input[3]  = B00011111;
  input[4]  = B00001111;
  input[5]  = B00000111;
  input[6]  = B00000011; // display shows empty state
  input[7]  = B00000001; // red led blinks
  input[8]  = B00000000; // to indicate out of oxygen
  input[9]  = B00000011; // display starts to refill after button press
  input[10] = B00000111;
  input[11] = B00001111;
  input[12] = B00011111;
  input[13] = B00111111;
  input[14] = B01111111;
  input[15] = B11111111;
}

void loop() {
  // read the actual state of the button
  buttonState = digitalRead(displayButton);
  val = buttonState;
  //Serial.println(val); // only for debugging
  oxyLoss();
  // if buttonState is unequal to lastBstate
  // something must have changed
  if(buttonState != lastBState) {
    // if button has been pressed increase counter by 1
    if(buttonState == HIGH) {
      //buttonCounter++;
      oxyGain();
      delay(10);
    }
    
  }
  buttonCounter++;
  
  // current buttonState gets assigned to lastBState
  lastBState = buttonState;
  Serial.println(buttonCounter);

  // depending on the button state functions are called
  if(buttonCounter % 2 == 0) {
    rightActiveBlueGreen();
    rightActiveGreenBlue();
    leftRegenerate();
    buttonState = 0;
  }
  else if(buttonCounter % 2 == 1) {
    leftActiveBlueGreen();
    leftActiveGreenBlue();
    rightRegenerate();
    buttonState = 1;
  }

}

//Functions

// function for decresing oxygen
void oxyLoss() {
  for (int i = 0; i < 8; i++) {
      // take the latchPin low so
      // the LEDs don't change while you're sending in bits:
      digitalWrite(latchPin, LOW);
      // shift out the bits:
      shiftOut(dataPin, clockPin, LSBFIRST, input[i]);

      //take the latch pin high so the LEDs will light up:
      digitalWrite(latchPin, HIGH);
      // pause before next value:
      delay(1000);
      // only red led is on and button is not pressed
      // red led blinks until button gets pressed
      while(i == 7 && val == 1) {
        for(int i = 7; i < 9; i++) {
          digitalWrite(latchPin, LOW);
          shiftOut(dataPin, clockPin, LSBFIRST, input[i]);
          digitalWrite(latchPin, HIGH);
          val = digitalRead(displayButton);
          delay(500);
        }
      }
    }
}

// display gets refilled on button press
void oxyGain() {
  for (int i = 10; i < 16; i++) {
    // pull the latchPin low so
    // LEDs won't change while sending in new bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, LSBFIRST, input[i]);

    //pull latch pin high so LEDs light up:
    digitalWrite(latchPin, HIGH);
    // pause before next value:
    delay(300);
  }
}

// right chamber fades from blue to green
void rightActiveBlueGreen() {
  redRVal    = 0;
  blueRVal   = 0;
  greenRVal  = 180;

  for(int i = 0; i < 180; i++) {
    blueRVal  += 1;
    greenRVal -= 1;
    analogWrite(blueR, 180 - blueRVal);
    analogWrite(greenR, 180 - greenRVal);
    delay(8);
  }
}

// left chamber fades from blue to green
void leftActiveBlueGreen() {
  redLVal    = 0;
  blueLVal   = 0;
  greenLVal  = 180;

  for(int i = 0; i < 180; i++) {
    blueLVal  += 1;
    greenLVal -= 1;
    analogWrite(blueL, 180 - blueLVal);
    analogWrite(greenL, 180 - greenLVal);
    delay(8);
  }
}

// right chamber fades from green to blue
void rightActiveGreenBlue() {
  redRVal   = 0;
  blueRVal  = 180;
  greenRVal = 0;

  for(int i = 0; i < 180; i++) {
    blueRVal  -= 1;
    greenRVal += 1;
    analogWrite(blueR, 180 - blueRVal);
    analogWrite(greenR, 180 - greenRVal);
    delay(8);
  }
}

// left chamber fades from green to blue
void leftActiveGreenBlue() {
  redLVal   = 0;
  blueLVal  = 180;
  greenLVal = 0;

  for(int i = 0; i < 180; i++) {
    blueLVal  -= 1;
    greenLVal += 1;
    analogWrite(blueL, 180 - blueLVal);
    analogWrite(greenL, 180 - greenLVal);
    delay(8);
  }
}

void rightRegenerate() {
  

}

void leftRegenerate() {

}

void testing() {
  redRVal    = 0;
  blueRVal   = 0;
  greenRVal  = 180;

  for(int i = 0; i < 180; i++) {
    blueRVal  += 1;
    greenRVal -= 1;
    analogWrite(blueR, 180 - blueRVal);
    analogWrite(greenR, 180 - greenRVal);
    delay(8);
  }
  
  redRVal   = 0;
  blueRVal  = 180;
  greenRVal = 0;

  for(int i = 0; i < 180; i++) {
    blueRVal  -= 1;
    greenRVal += 1;
    analogWrite(blueR, 180 - blueRVal);
    analogWrite(greenR, 180 - greenRVal);
    delay(8);
  }
  
}
