// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.

#include "graphics.h"

#include "globals.h"

void draw_nothing(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, BLACK);
}

void draw_img(int u, int v, const char* img)
{
    int colors[11*11];
    for (int i = 0; i < 11*11; i++)
    {
        if (img[i] == 'R') colors[i] = RED;
        else if (img[i] == 'Y') colors[i] = 0xFFFF00; // Yellow
        else if (img[i] == 'G') colors[i] = GREEN;
        else if (img[i] == 'D') colors[i] = 0xD2691E; // "Dirt"
        else if (img[i] == '5') colors[i] = LGREY; // 50% grey
        else if (img[i] == '3') colors[i] = DGREY;
        else if (img[i] == 'W') colors[i] = 0xFFFFFF; // white
        else if (img[i] == '1') colors[i] = 0x0000FF; // blue
        else colors[i] = BLACK;
    }
    uLCD.BLIT(u, v, 11, 11, colors);
    wait_us(250); // Recovery time!
}

void draw_wall(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, LGREY);
}

void draw_plant(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
}

void draw_goodie(int u, int v)
{
    const char *goodie;
    goodie = "BBBBBBBGBBBBBBBBBGBBBBBBRRBGBRRBBBRRRRRRRRRBRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRBRRRRRRRRRBBBRRRRRRRBBBBBRRRRRBBBBBBBRBRBBBB";
    draw_img(u, v, goodie);
}

void draw_snake_body(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
}

void draw_snake_head_right(int u, int v)
{
     //May need to design a snake head sprite
     //Tile still need to be designed on paper
    const char *head;
    head = "GGGGBBBBBBBGGGGGBBBBBBGGGWWGBBBBRGGGWBBGBBRBGGGWWWGRRBBGGGGGGGRRBBGGGWWWGRRBBGGGWBBGBBRBGGGWWGBBBBRGGGGGBBBBBBGGGGBBBBBBB";
    draw_img(u, v, head);
}
void draw_snake_head_left(int u, int v)
{
     //May need to design a snake head sprite
     //Tile still need to be designed on paper
    const char *head;
    head = "BBBBBBBGGGGBBBBBBGGGGGRBBBBGWWGGGBRBBGBBWGGGBBRRGWWWGGGBBRRGGGGGGGBBRRGWWWGGGBRBBGBBWGGGRBBBBGWWGGGBBBBBBGGGGGBBBBBBBGGGG";
    draw_img(u, v, head);
}
void draw_snake_head_up(int u, int v)
{
     //May need to design a snake head sprite
     //Tile still need to be designed on paper
    const char *head;
    head = "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGWWWGWWWGGBGWBWGWBWGBBBGBWGWBGBBBBBGGGGGBBBBBBBRRRBBBBBBBBRRRBBBBBBBRBBBRBBBBBRBBBBBRBB";
    draw_img(u, v, head);
}
void draw_snake_head_down(int u, int v)
{
     //May need to design a snake head sprite
     //Tile still need to be designed on paper
    const char *head;
    head = "BBRBBBBBRBBBBBRBBBRBBBBBBBRRRBBBBBBBBRRRBBBBBBBGGGGGBBBBBGBWGWBGBBBGWBWGWBWGBGGWWWGWWWGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG";
    draw_img(u, v, head);
}

void draw_snake_tail(int u, int v)
{
     //May need to design a snake tail sprite
     //Tile still need to be designed on paper
    const char *tail;
    tail = "GGGGGGGGGGGDDDDDDDDDDDGGGGGGGGGGGDDDDDDDDDDDGGGGGGGGGGGDDDDDDDDDDDGGGGGGGGGGGDDDDDDDDDDDGGGGGGGGGGGDDDDDDDDDDDGGGGGGGGGGG";
    draw_img(u, v, tail);
}

void draw_plus_five(int u, int v)
{
    const char *tail;
    tail = "111111111111111WWW11111111WWW111111111111111111111111111111WWW11111111WWW11111111WWW11111111WWW11111111WWW111111111111111";
    draw_img(u, v, tail);
}

