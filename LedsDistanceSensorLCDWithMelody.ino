#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "pitches.h"
//=================================================================
LiquidCrystal_I2C lcd(0x27,16 , 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
//=================================================================
// PARIMETER
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
// LEDS
const int analogOutPin = 9; // Analog output pin that the LED is attached to
const int analogOutPin8 = 8; // Analog output pin that the LED is attached to
const int analogOutPin7 = 7; // Analog output pin that the LED is attached to
const int analogOutPin6 = 6; // Analog output pin that the LED is attached to
const int analogOutPin5 = 5; // Analog output pin that the LED is attached to
const int analogOutPin4 = 4; // Analog output pin that the LED is attached to

int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

int timer = 125;           // The higher the number, the slower the timing.

int ledPins[] = {9, 8, 7, 6, 5, 4};

int pinCount = 6;           // the number of pins (i.e. the length of the array)
//=================================================================
// DISTANCE ECHO SENSOR
//create veriables
int trig = 2;
int echo = 3;
long duretion, distance;

// BUZZER
const int buzzer = 10;
//=================================================================
//=================================================================
void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();

  lcd.setCursor(2,0);
  lcd.print("Distance");

  lcd.setCursor(1,1);
  lcd.print("MEASURE");
  delay(1000);
  
  lcd.clear();
 //=================================================================
 // PIN MODE DISTANCE SENSOR
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
 //=================================================================
 // PIN MODE BUZZER
  pinMode(buzzer, OUTPUT);
 //=================================================================
  // initialize serial communications at 9600 bps:

  Serial.begin(9600);
  
  // LED PINS MODE
  // the array elements are numbered from 0 to (pinCount - 1).
  // use a for loop to initialize each pin as an output:
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    pinMode(ledPins[thisPin], OUTPUT);
  }
}
//=================================================================
// MELODY
// notes in the melody:
int melody[] = {

  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {

  4, 8, 8, 4, 4, 4, 4, 4
};
//=================================================================
//=================================================================
void loop() {
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  delayMicroseconds(10);
  digitalWrite(trig,HIGH);

  duretion = pulseIn(echo,HIGH);
  distance = ((duretion/2)*0.0346);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Distance:");

  if(distance > 1000)
  {
    lcd.setCursor(0,1);
    lcd.print("greater > 10m");

    noTone(buzzer);
  }
  else if (distance < 10)
  {
    lcd.setCursor(0,1);
    lcd.print("smaller < 10cm");
    // Activate buzzer
    //tone(buzzer, 1000);
    //delay(100);
    //noTone(buzzer);     // Stop sound...
    //delay(10);  
      // iterate over the notes of the melody:

    for (int thisNote = 0; thisNote < 8; thisNote++) 
    {

    // to calculate the note duration, take one second divided by the note type.

    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

    int noteDuration = 1000 / noteDurations[thisNote];

    tone(buzzer, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.

    // the note's duration + 30% seems to work well:

    int pauseBetweenNotes = noteDuration * 1.30;

    delay(pauseBetweenNotes);

    // stop the tone playing:

    noTone(buzzer);
    }
    
  }
  else
  {
    lcd.setCursor(0,1);
    lcd.print(distance);
    lcd.setCursor(5,1);
    lcd.print("cm");

    noTone(buzzer);
  }
    // Wait 0.2s
  //delay(100);
  // read the analog in value:

  sensorValue = analogRead(analogInPin);

  // map it to the range of the analog out:

  outputValue = map(sensorValue, 0, 1023, 0, 255);

  // change the analog out value:
  // loop from the lowest pin to the highest:
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    // turn the pin on:
    //digitalWrite(ledPins[thisPin], HIGH);
    digitalWrite(ledPins[thisPin], LOW);
    //digitalWrite(ledPins[pinCount - 1], HIGH);
    //analogWrite(analogOutPin, outputValue);
    //analogWrite(analogOutPin8, outputValue);
    //analogWrite(analogOutPin7, outputValue);
    //analogWrite(analogOutPin6 , outputValue);
    //analogWrite(analogOutPin5 , outputValue);
    //analogWrite(analogOutPin4 , outputValue);
    //delay(timer * 10);
    //digitalWrite(ledPins[pinCount - 1], LOW);
    delay(timer);
    analogWrite(analogOutPin, outputValue);
    analogWrite(analogOutPin8, outputValue);
    analogWrite(analogOutPin7, outputValue);
    analogWrite(analogOutPin6 , outputValue);
    analogWrite(analogOutPin5 , outputValue);
    analogWrite(analogOutPin4 , outputValue);
    //digitalWrite(ledPins[pinCount - 1], LOW);
  //=================================================================
 
  }


  // print the results to the Serial Monitor:

  Serial.print("sensor = ");

  Serial.print(sensorValue);

  Serial.print("\t output = ");

  Serial.println(outputValue);

  // wait 2 milliseconds before the next loop for the analog-to-digital

  // converter to settle after the last reading:

  delay(2);
}
