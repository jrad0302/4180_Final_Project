# 4180_Final_Project
An arcade-style embedded electronics system based on the Mbed ecosystem
The "arcade" can support up to eight games using the Bluefruit connect app
Only two games are implemented as of right now: a snake game and a math game
When booted, user is prompted to use the bluetooth app to choose which game to play
Any time while the user is playing either game, he or she can use the bluetooth app to switch between games
Game specifications:
Snake Game: a player will start at a common point on the screen and must navigate a virtual snake through a four-walled room to eat “fruit” 
and grow a predetermined size. The game ends when a player reaches the maximum possible length or runs into the wall.
Math Game: a player will be asked a series of random math questions and must use the MPR121 capacitive touchpad to input and submit the correct answer. 
The game ends when the player correctly answers 10 questions consecutively, incorrectly answers a question, or the timer runs out. 
The user initially has 30 seconds to answer, but with every subsequent correct answer, the time is decreased by 3 seconds.

# Demo
https://youtu.be/-_NwCmx6EHU

# Photo of Circuitry
![IMG_2482](https://user-images.githubusercontent.com/96077867/146098311-afe2a833-7f93-4d71-95b2-a05a14a9faa4.jpg)

# Wiring
|    MPR 121    |      mbed     |
| ------------- | ------------- |
|      Vcc      |   Vout(3.3V)  |
|      SDA      |      p9       |
|      SCL      |      p10      |
|      IRQ      |      p26      |
|      Gnd      |      Gnd      |


|  Adafruit BLE |      mbed     |
| ------------- | ------------- |
| Vin (3.3-16V) |     Vu(5V)    |
|      RTS      |      nc       |
|      CTS      |      Gnd      |
|      TXO      |      p27      |
|      RXI      |      p28      |
|      Gnd      |      Gnd      |


|  uLCD Header  |   uLCD Cable  |      mbed     |
| ------------- | ------------- | ------------- |
|      +5V      |      +5V      |     Vu(5V)    |
|      RX       |      TX       |      p13      |
|      TX       |      RX       |      p14      |
|     Reset     |     Reset     |      p11      |
|      Gnd      |      Gnd      |      Gnd      |


|   Button #    |      mbed     |
| ------------- | ------------- |
|       1       |      p21      |
|       2       |      p22      |
|       3       |      p23      |
|       4       |      p24      |
|       5       |      p25      |
