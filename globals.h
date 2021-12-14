// ============================================
// The header file for general project settings
//
// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================
#ifndef GLOBAL_H
#define GLOBAL_H

// Include all the hardware libraries
#include "mbed.h"
#include "wave_player.h"
#include "MMA8452.h"
#include "uLCD_4DGL.h"
#include "SDFileSystem.h"
#include "mpr121.h"

// Declare the hardware interface objects
extern uLCD_4DGL uLCD;      // LCD Screen
extern SDFileSystem sd;     // SD Card
extern Serial pc;           // USB Console output
extern DigitalIn button1;   // Pushbuttons
extern DigitalIn button2;
extern DigitalIn button3;
extern DigitalIn button4;
extern DigitalIn button5;
extern AnalogOut DACout;    // Speaker
extern PwmOut speaker;
extern wave_player waver;
extern Serial Blue;
extern DigitalOut myled1;
extern DigitalOut myled2;
extern InterruptIn interrupt;
extern I2C i2c;
extern Mpr121 numpad;


// Global settings
#define BACKGROUND_COLOR 0x000000 //black
#define LANDSCAPE_HEIGHT 4        // number of pixel on the screen
#define MAX_BUILDING_HEIGHT 10    // number of pixel on the screen


// === [define the macro of error heandle function] ===
// when the condition (c) is not true, assert the program and show error code
#define ASSERT_P(c,e) do { \
    if(!(c)){ \
        pc.printf("\nERROR:%d\n",e); \
        while(1); \
    } \
} while (0)

// === [error code] ===
#define ERROR_NONE 0 // All good in the hood
#define ERROR_MEH -1 // This is how errors are done

#endif //GLOBAL_H