/**
 * @file clock.cpp
 * @author Jack Fitton (jf1595@york.ac.uk)
 * @brief Implementation file for the clock class
 * @version 0.1
 * @date 28-03-2024
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "clock.h"

// Constructor
Clock::Clock(): display(LOAD_PIN, NCHIP){

}

void Clock::begin(){
    Serial2.begin(9600, SERIAL_8N1, 16, 17);
}

void Clock::EnableDST(){
    DST = 1;
}

void Clock::displayOn(){
    display.on(NCHIP);
}

void Clock::displayOff(){
    display.off(NCHIP);
}

void Clock::write(int number){
    // Crop number to 8 digits max
    if (number > 99999999){
        number = 99999999;
    }

    // Split number into digits
    int digits[8];
    for (int i = 0; i < 8; i++){
        digits[7 - i] = number % 10; // Fill from the right (least significant digit)
        number /= 10;
    }

    // Write digits to display, skipping leading zeros
    bool leadingZerosSkipped = false;
    for (int i = 0; i < 8; i++){
        if (digits[i] != 0) {
            leadingZerosSkipped = true;
        }
        if (leadingZerosSkipped) {
            display.write(8 - i, getDigitCode(digits[i])); // Write digit with correct indexing
        } else {
            // Optionally, you can clear the leading zero positions or leave them as is.
            // display.write(8 - i, 0x00); // To clear the digit
        }
    }
}

void Clock::type(char* text){
    clearDisplay();
    // Write text to display
    for (int i = 0; i < 8; i++){
        if (text[i] == '\0'){
            break;
        }
        display.write(8 - i, getCharCode(text[i])); // Write character with correct indexing
    }
}


byte Clock::getCharCode(char character){
    switch(character) {
        case 'A': return LETTER_A;
        case 'B': return LETTER_B;
        case 'C': return LETTER_C;
        case 'D': return LETTER_D;
        case 'E': return LETTER_E;
        case 'F': return LETTER_F;
        case 'G': return LETTER_G;
        case 'H': return LETTER_H;
        case 'I': return LETTER_I;
        case 'J': return LETTER_J;
        case 'K': return LETTER_K;
        case 'L': return LETTER_L;
        case 'M': return LETTER_M;
        case 'N': return LETTER_N;
        case 'O': return LETTER_O;
        case 'P': return LETTER_P;
        case 'Q': return LETTER_Q;
        case 'R': return LETTER_R;
        case 'S': return LETTER_S;
        case 'T': return LETTER_T;
        case 'U': return LETTER_U;
        case 'V': return LETTER_V;
        case 'W': return LETTER_W;
        case 'X': return LETTER_X;
        case 'Y': return LETTER_Y;
        case 'Z': return LETTER_Z;
        case '.': return DECIMAL_POINT;
        case '/': return DATE_SEPARATOR;
        default: return 0;
    }
}

byte Clock::getDigitCode(int digit){
    switch(digit) {
        case 0: return ZERO;
        case 1: return ONE;
        case 2: return TWO;
        case 3: return THREE;
        case 4: return FOUR;
        case 5: return FIVE;
        case 6: return SIX;
        case 7: return SEVEN;
        case 8: return EIGHT;
        case 9: return NINE;
        default: return 0;
  }
}

void Clock::updateTime(int hour, int minute, int second){
  // Assuming your display is laid out like this:
  // [hh tens][hh ones]:[mm tens][mm ones]:[ss tens][ss ones]
  // And that the addresses are 1 to 6 for each position
  clearDisplay();

    hour = (hour + DST) % 24;


  byte hhTens = getDigitCode(hour / 10);
  byte hhOnes = getDigitCode(hour % 10);
  byte mmTens = getDigitCode(minute / 10);
  byte mmOnes = getDigitCode(minute % 10);
  
  byte ssTens = getDigitCode(second / 10);
  byte ssOnes = getDigitCode(second % 10);
  
  // Write to the 7-segment display at the correct address
  // The address and order depend on how your hardware is set up. Here's an example:
  display.write(8, hhTens);
  display.write(7, hhOnes);
  display.write(5, mmTens);
  display.write(4, mmOnes);
  display.write(2, ssTens);
  display.write(1, ssOnes);
}

void Clock::clearDisplay(){
    for (int i = 1; i <= 8; i++){
        display.write(i, 0x00);
    }
}

void Clock::updateDate(int day, int month, int year) {
    // If the year is four digits, reduce it to the last two digits
    clearDisplay();
    year = year % 100;

    byte ddTens = getDigitCode(day / 10);
    byte ddOnes = getDigitCode(day % 10); // Add decimal point to day ones place
    byte mmTens = getDigitCode(month / 10);
    byte mmOnes = getDigitCode(month % 10); // Add decimal point to month ones place
    byte yyTens = getDigitCode(year / 10);
    byte yyOnes = getDigitCode(year % 10); // Add decimal point to year ones place

    // Write to the 7-segment display at the correct address
    display.write(8, ddTens);
    display.write(7, ddOnes);
    display.write(6, DATE_SEPARATOR);
    display.write(5, mmTens);
    display.write(4, mmOnes);
    display.write(3, DATE_SEPARATOR);
    display.write(2, yyTens);
    display.write(1, yyOnes);
}


