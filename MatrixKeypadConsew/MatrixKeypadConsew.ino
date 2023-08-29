/**
 * Matrix Keypad
 * 
 * This example shows how to use the library to perform a blocking read of a generic keypad.
 *  
 * @version 1.1.0
 * @author Victor Henrique Salvi
 */

#include <Arduino.h>
#include "MatrixKeypad.h"
#include <stdint.h>
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

const uint8_t rown = 5;
const uint8_t coln = 8;
uint8_t rowPins[rown] = {11,10,9,3,2}; //frist row is connect to pin 10, second to 9...
uint8_t colPins[coln] = {15,14,13,12,7,6,5,4}; //frist column is connect to pin 6, second to 5...
char keymap[rown][coln] = {
  {'7','5','3','1','6','4','2','0'},
  {'X','D','S','P','R','C','M','Y'},
  {' ',' ',' ',' ','<','v','>','^'},
  {'F','~','+','9','A','C','O','8'},
  {'E','{','?','*','H','}','!','I'}  
};
MatrixKeypad_t *keypad; //keypad is the variable that you will need to pass to the other functions

LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display

char key;

int charsPrinted = 0;

void setup() {
  int error;

	//Serial.begin(9600);
	pinMode(LED_BUILTIN, OUTPUT);

	keypad = MatrixKeypad_create((char*)keymap /* don't forget to do this cast */, rowPins, colPins, rown, coln); //creates the keypad object

  Wire.setSDA(16);
  Wire.setSCL(17);

  // See http://playground.arduino.cc/Main/I2cScanner how to test for a I2C device.
  Wire.begin();
  Wire.beginTransmission(0x27);

  error = Wire.endTransmission();
  //Serial.print("Error: ");
  //Serial.print(error);

  if (error == 0) {
    //Serial.println(": LCD found.");
    lcd.begin(16, 2);  // initialize the lcd

    lcd.setBacklight(255);
    lcd.home();
    lcd.clear();
    lcd.print("Ready");
    delay(1000);
    lcd.clear();

  } else {
    //Serial.println(": LCD not found.");
  }  // if
}

void loop() {

	key = MatrixKeypad_waitForKey(keypad); //blocks the program until the user presses a key
	//Serial.print(key); //prints the pressed key to the serial output

  if(charsPrinted > 15) {
    lcd.clear();
    lcd.home();
    charsPrinted = 0;
  }
  lcd.print(key);
  charsPrinted++;

	blink (); //blinks a led everytime that's called to show that the keypad scanning is blocking the program
	
	delay(20); //do something
}

/* inverts the led state */
void blink () {
	static int led_state = LOW;
	if(led_state == HIGH){
		led_state = LOW;
	}
	else {
		led_state = HIGH;
	}
	digitalWrite(LED_BUILTIN, led_state);
}