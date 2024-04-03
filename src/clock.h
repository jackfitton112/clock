/**
 * @file clock.h
 * @author Jack Fitton (jf1595@york.ac.uk)
 * @brief Header file for the clock class
 * @version 0.1
 * @date 28-03-2024
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef CLOCK_H
#define CLOCK_H

#include <DigitLed72xx.h>
#include <TinyGPSPlus.h>

#define PRINT_DIGIT_NEG 1
#define LOAD_PIN 15 //LOAD / CS PIN
#define NCHIP 2 //Number of chips

#define DP 0x80
#define A 0x40
#define B 0x20
#define C 0x10
#define D 0x08
#define E 0x04
#define F 0x02
#define G 0x01



// Numerical digits
#define ZERO  (A | B | C | D | E | F)
#define ONE   (B | C)
#define TWO   (A | B | G | E | D)
#define THREE (A | B | G | C | D)
#define FOUR  (F | G | B | C)
#define FIVE  (A | F | G | C | D)
#define SIX   (A | F | E | D | C | G)
#define SEVEN (A | B | C)
#define EIGHT (A | B | C | D | E | F | G)
#define NINE  (A | B | C | D | F | G)

// Alphabetic characters
#define LETTER_A (A | B | C | E | F | G)
#define LETTER_B (F | E | D | C | G)
#define LETTER_C (A | F | E | D)
#define LETTER_D (B | C | D | E | G)
#define LETTER_E (A | F | E | D | G)
#define LETTER_F (A | F | E | G)
#define LETTER_G (A | F | E | D | C)
#define LETTER_H (F | E | B | C | G)
#define LETTER_I (B | C)
#define LETTER_J (B | C | D | E)
#define LETTER_K (F | E | G)
#define LETTER_L (F | E | D)
#define LETTER_M (A | E | F)
#define LETTER_N (E | F | A | B | C)
#define LETTER_O (A | B | C | D | E | F)
#define LETTER_P (A | B | E | F | G)
#define LETTER_Q (A | B | C | F | G)
#define LETTER_R (E | G)
#define LETTER_S (A | F | G | C | D)
#define LETTER_T (A | F | E)
#define LETTER_U (B | C | D | E | F)
#define LETTER_V (C | D | E)
#define LETTER_W (D | E | B)
#define LETTER_X (B | C | E | F | G)
#define LETTER_Y (B | C | D | F | G)
#define LETTER_Z (A | B | D | E)

#define DECIMAL_POINT 0x80
#define DATE_SEPARATOR (D | DP)

class Clock
{
    public:
        Clock();
        void begin();
        void displayOn();
        void displayOff();
        void write(int number);
        void updateTime(int hour, int minute, int second);
        void updateDate(int day, int month, int year);
        void EnableDST();
        void type(char* text);

    private:
        char displayBuffer[8];
        DigitLed72xx display;
        TinyGPSPlus gps;
        unsigned long lastUpdate;
        unsigned long lastDisplay;
        bool displayState;
        byte getDigitCode(int digit);
        void clearDisplay();
        int DST = 0;
        byte getCharCode(char character);


};


#endif // CLOCK_H

