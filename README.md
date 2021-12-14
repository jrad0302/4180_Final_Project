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
