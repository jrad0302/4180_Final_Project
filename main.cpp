//=================================================================
// The main program file.
//
// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================

// Project includes
#include "globals.h"
#include "hardware.h"
#include "map.h"
#include "graphics.h"
#include "snake.h"

#include <math.h>
#include<stdio.h>

#define CITY_HIT_MARGIN 1
#define CITY_UPPER_BOUND (SIZE_Y-(LANDSCAPE_HEIGHT+MAX_BUILDING_HEIGHT))

// Helper function declarations
void playSound(char* wav);

/**
 * The main game state. Must include snake locations and previous locations for
 * drawing to work properly. Other items can be added as needed.
 */

/**
 * Given the game inputs, determine what kind of update needs to happen.
 * Possbile return values are defined below.
 */
Snake snake;

//global variables for main and interrupt routine
volatile bool button_ready = 0;
volatile int  bnum = 0;
volatile int  bhit  ;
int operand1;
int operand2;
int op;
int answer;
int ans = 0;
int score = 0;
int seconds = 30;
float seed;

//state used to remember previous characters read in a button message
enum statetype {start = 0, got_exclm, got_B, got_num, got_hit};
statetype state = start;

//Interrupt routine to parse message with one new character per serial RX interrupt
void parse_message()
{
    switch (state) {
        case start:
            if (Blue.getc()=='!') state = got_exclm;
            else state = start;
            break;
        case got_exclm:
            if (Blue.getc() == 'B') state = got_B;
            else state = start;
            break;
        case got_B:
            bnum = Blue.getc();
            state = got_num;
            break;
        case got_num:
            bhit = Blue.getc();
            state = got_hit;
            break;
        case got_hit:
            if (Blue.getc() == char(~('!' + ' B' + bnum + bhit))) button_ready = 1;
            state = start;
            break;
        default:
            Blue.getc();
            state = start;
    }
}

void generateProblem()
{
    //generates random numbers between 1 and 10 as operands
    operand1 = rand() % 10 + 1;
    operand2 = rand() % 10 + 1;
    op = rand() % 3;
    
    //genearte random operator and appropriate answer
    if (op == 0)
    {
        uLCD.locate(0,0);
        uLCD.printf("%d + %d\n",operand1, operand2);
        answer = operand1 + operand2;
    }
    else if (op == 1)
    {
        uLCD.locate(0,0);
        uLCD.printf("%d - %d\n",operand1, operand2);
        answer = operand1 - operand2;
    }
    else if (op == 2)
    {
        uLCD.locate(0,0);
        uLCD.printf("%d * %d\n",operand1, operand2);
        answer = operand1 * operand2;        
    }
}

void fallInterrupt() 
{
    int num = numpad.read(0x00);
     num +=numpad.read(0x01)<<8;
     int i=0;
     i = 0;
     for (i=0; i<12; i++) {
        if (num & (1<<i))
        break;
     }
     if(i == 12)
     {
         return;
    }
     else if(i == 0) {
        ans = i;
        uLCD.locate(1,2);
        uLCD.printf("%d", i);
     }
     else if (i == 1) {
        ans = i;
        uLCD.locate(1,2);
        uLCD.printf("%d", i);
     }
     else if (i == 2) {
        ans = i;
        uLCD.locate(1,2);
        uLCD.printf("%d", i);
         }
     else if (i == 3) {
        ans = i;
        uLCD.locate(1,2);
        uLCD.printf("%d", i);
         }
     else if (i == 4) {
        ans = i;
        uLCD.locate(1,2);
        uLCD.printf("%d", i);
         }
     else if (i == 5) {
        ans = i;
        uLCD.locate(1,2);
        uLCD.printf("%d", i);
         }
     else if (i == 6) {
        ans = i;
        uLCD.locate(1,2);
        uLCD.printf("%d", i);
         }
     else if (i == 7) {
        ans = i;
        uLCD.locate(1,2);
        uLCD.printf("%d", i);
         }
     else if (i == 8) {
        ans = i;
        uLCD.locate(1,2);
        uLCD.printf("%d", i);
         }
     else if (i == 9) {
        ans = i;
        uLCD.locate(1,2);
        uLCD.printf("%d", i);
         }
     else if (i == 10) {
        ans = i;
        uLCD.locate(1,2);
        uLCD.printf("%d", i);
         }
     else if (i == 11) {
        ans = i;
        uLCD.locate(1,2);
        uLCD.printf("%d", i);
         }
        pc.printf("%d", i);
}

// Function prototypes

/**
 * Given the game inputs, determine what kind of update needs to happen.
 * Possible return values are defined below.
 */
#define NO_RESULT 0
#define NO_ACTION 0
#define ACTION_BUTTON 1
#define MENU_BUTTON 2
#define GO_LEFT 3
#define GO_RIGHT 4
#define GO_UP 5
#define GO_DOWN 6
#define GAME_OVER 7
#define FULL_DRAW 8
// Get Actions from User (push buttons & accelerometer)
// Based on push button and accelerometer inputs, determine which action
// needs to be performed (may be no action).
int get_action(GameInputs inputs)
{
    if(inputs.b1 == 0)
    {
        return GO_RIGHT;
    }
    else if(inputs.b2 == 0) 
    {
        return GO_LEFT;
    }
    else if(inputs.b3 == 0) {
        return GO_UP;
    }
    else if(inputs.b4 == 0) {
        return GO_DOWN;
    }
    else {
        return NO_ACTION;
    }
}
/**
 * Update the game state based on the user action. For example, if the user
 * requests GO_UP, then this function should determine if that is possible by
 * consulting the map, and update the snake position accordingly.
 *
 * Return values are defined below. FULL_DRAW indicates that for this frame,
 * draw_game should not optimize drawing and should draw every tile, even if
 * the snake has not moved.
 */
int update_game(int action)
{
    MapItem* item;
    if(action == GO_RIGHT) {
        item = get_east(snake.head_x, snake.head_y);  // item to the right of  head
        pc.printf("%d\n", item -> type);
        pc.printf("%d\n", item -> walkable);
        // if the item to the right isn't walkable...
        if(item -> walkable == 0) {
            // if this nonwalkable item is the snake body position right behind the head, do nothing
            if(snake.head_x + 1 == snake.head_px) {
                return NO_RESULT;
            }
            return GAME_OVER;
        }
        else {
            if(item -> type == GOODIE) {
                snake.score++;
                snake.head_px = snake.head_x;
                snake.head_py = snake.head_y;
                // incrementing head
                snake.head_x++;
                uLCD.cls();
                uLCD.printf("Pos:%d,%d Score:%d", snake.head_x, snake.head_y, snake.score);
                for(int i = 0; i < snake.length; ++i) {
                    map_erase(snake.locations[i].x, snake.locations[i].y);
                }
                snake.length++;
                add_plant(snake.locations[snake.length - 1].x, snake.locations[snake.length - 1].y);
                for(int j = snake.length - 1; j >= 0; --j) {
                    snake.locations[j].x = snake.locations[j  - 1].x;
                    snake.locations[j].y = snake.locations[j  - 1].y;
                }
                snake.locations[0].x = snake.head_x;
                snake.locations[0].y = snake.head_y;
                // draw snake
                add_snake_head_right(snake.head_x, snake.head_y);
                add_snake_tail(snake.locations[snake.length - 1].x, snake.locations[snake.length - 1].y);
                for(int k = 1; k <= snake.length - 2; ++k) {
                    add_snake_body(snake.locations[k].x, snake.locations[k].y);
                }
                return NO_ACTION;
            }   
            
            // replacing the head with previous head
            snake.head_px = snake.head_x;
            snake.head_py = snake.head_y;
            // incrementing head
            snake.head_x++;
            uLCD.cls();
            uLCD.printf("Pos:%d,%d Score:%d", snake.head_x, snake.head_y, snake.score);
            // erase previous snake
            for(int i = 0; i < snake.length; ++i) {
                map_erase(snake.locations[i].x, snake.locations[i].y);
            }
            add_plant(snake.locations[snake.length - 1].x, snake.locations[snake.length - 1].y);
            // update locations array
            for(int j = snake.length - 1; j > 0; --j) {
                snake.locations[j].x = snake.locations[j  - 1].x;
                snake.locations[j].y = snake.locations[j  - 1].y;
            }
            snake.locations[0].x = snake.head_x;
            snake.locations[0].y = snake.head_y;
            // draw snake
            add_snake_head_right(snake.head_x, snake.head_y);
            add_snake_tail(snake.locations[snake.length - 1].x, snake.locations[snake.length - 1].y);
            for(int k = 1; k <= snake.length - 2; ++k) {
                add_snake_body(snake.locations[k].x, snake.locations[k].y);
            }
            return NO_RESULT;
        }
    }
    
    if(action == GO_LEFT) {
        item = get_west(snake.head_x, snake.head_y);
        pc.printf("%d\n", item -> type);
        pc.printf("%d\n", item -> walkable);
        if(item -> walkable == 0) {
            if(snake.head_x - 1 == snake.head_px) {
                return NO_ACTION;
            }
            return GAME_OVER;
        }
        else {
            if(item -> type == GOODIE) {
                snake.score++;
                snake.head_px = snake.head_x;
                snake.head_py = snake.head_y;
                // incrementing head
                snake.head_x--;
                uLCD.cls();
                uLCD.printf("Pos:%d,%d Score:%d", snake.head_x, snake.head_y, snake.score);
                for(int i = 0; i < snake.length; ++i) {
                    map_erase(snake.locations[i].x, snake.locations[i].y);
                }
                snake.length++;
                add_plant(snake.locations[snake.length - 1].x, snake.locations[snake.length - 1].y);
                for(int j = snake.length - 1; j >= 0; --j) {
                    snake.locations[j].x = snake.locations[j  - 1].x;
                    snake.locations[j].y = snake.locations[j  - 1].y;
                }
                snake.locations[0].x = snake.head_x;
                snake.locations[0].y = snake.head_y;
                
                // draw snake
                add_snake_head_left(snake.head_x, snake.head_y);
                add_snake_tail(snake.locations[snake.length - 1].x, snake.locations[snake.length - 1].y);
                for(int k = 1; k <= snake.length - 2; ++k) {
                    add_snake_body(snake.locations[k].x, snake.locations[k].y);
                }
                return NO_ACTION;
            }   
            snake.head_px = snake.head_x;
            snake.head_py = snake.head_y;
            // incrementing head
            snake.head_x--;
            uLCD.cls();
            uLCD.printf("Pos:%d,%d Score:%d", snake.head_x, snake.head_y, snake.score);
            // erase previous snake
            for(int i = 0; i < snake.length; ++i) {
                map_erase(snake.locations[i].x, snake.locations[i].y);
            }
            add_plant(snake.locations[snake.length - 1].x, snake.locations[snake.length - 1].y);
            // update locations array
            for(int j = snake.length - 1; j > 0; --j) {
                snake.locations[j].x = snake.locations[j  - 1].x;
                snake.locations[j].y = snake.locations[j  - 1].y;
            }
            snake.locations[0].x = snake.head_x;
            snake.locations[0].y = snake.head_y;
            // draw snake
            add_snake_head_left(snake.head_x, snake.head_y);
            add_snake_tail(snake.locations[snake.length - 1].x, snake.locations[snake.length - 1].y);
            for(int k = 1; k <= snake.length - 2; ++k) {
                add_snake_body(snake.locations[k].x, snake.locations[k].y);
            }
            return NO_ACTION;
        }
    }
    
    if(action == GO_UP) {
        item = get_north(snake.head_x, snake.head_y);
        pc.printf("%d\n", item -> type);
        pc.printf("%d\n", item -> walkable);
        if(item -> walkable == 0) {
            if(snake.head_y + 1 == snake.head_py) {
                return NO_ACTION;
            }
            return GAME_OVER;
        }
        else {
            if(item -> type == GOODIE) {
                snake.score++;
                snake.head_px = snake.head_x;
                snake.head_py = snake.head_y;
                // incrementing head
                snake.head_y++;
                uLCD.cls();
                uLCD.printf("Pos:%d,%d Score:%d", snake.head_x, snake.head_y, snake.score);
                for(int i = 0; i < snake.length; ++i) {
                    map_erase(snake.locations[i].x, snake.locations[i].y);
                }
                snake.length++;
                add_plant(snake.locations[snake.length - 1].x, snake.locations[snake.length - 1].y);
                for(int j = snake.length - 1; j >= 0; --j) {
                    snake.locations[j].x = snake.locations[j  - 1].x;
                    snake.locations[j].y = snake.locations[j  - 1].y;
                }
                snake.locations[0].x = snake.head_x;
                snake.locations[0].y = snake.head_y;
                // draw snake
                add_snake_head_up(snake.head_x, snake.head_y);
                add_snake_tail(snake.locations[snake.length - 1].x, snake.locations[snake.length - 1].y);
                for(int k = 1; k <= snake.length - 2; ++k) {
                    add_snake_body(snake.locations[k].x, snake.locations[k].y);
                }
                return NO_ACTION;
            }   
            
            snake.head_px = snake.head_x;
            snake.head_py = snake.head_y;
            // incrementing head
            snake.head_y++;
            uLCD.cls();
            uLCD.printf("Pos:%d,%d Score:%d", snake.head_x, snake.head_y, snake.score);
            // erase previous snake
            for(int i = 0; i < snake.length; ++i) {
                map_erase(snake.locations[i].x, snake.locations[i].y);
            }
            add_plant(snake.locations[snake.length - 1].x, snake.locations[snake.length - 1].y);
            // update locations array
            for(int j = snake.length - 1; j > 0; --j) {
                snake.locations[j].x = snake.locations[j  - 1].x;
                snake.locations[j].y = snake.locations[j  - 1].y;
            }
            snake.locations[0].x = snake.head_x;
            snake.locations[0].y = snake.head_y;
            // draw snake
            add_snake_head_up(snake.head_x, snake.head_y);
            add_snake_tail(snake.locations[snake.length - 1].x, snake.locations[snake.length - 1].y);
            for(int k = 1; k <= snake.length - 2; ++k) {
                add_snake_body(snake.locations[k].x, snake.locations[k].y);
            }
            return NO_ACTION;
        }
    }
    
    if(action == GO_DOWN) {
        item = get_south(snake.head_x, snake.head_y);
        pc.printf("%d\n", item -> type);
        pc.printf("%d\n", item -> walkable);
        if(item -> walkable == 0) {
            if(snake.head_y - 1 == snake.head_py) {
                return NO_ACTION;
            }
            return GAME_OVER;
        }
        else {
            if(item -> type == GOODIE) {
                snake.score++;
                snake.head_px = snake.head_x;
                snake.head_py = snake.head_y;
                // incrementing head
                snake.head_y--;
                uLCD.cls();
                uLCD.printf("Pos:%d,%d Score:%d", snake.head_x, snake.head_y, snake.score);
                for(int i = 0; i < snake.length; ++i) {
                    map_erase(snake.locations[i].x, snake.locations[i].y);
                }
                snake.length++;
                add_plant(snake.locations[snake.length - 1].x, snake.locations[snake.length - 1].y);
                for(int j = snake.length - 1; j >= 0; --j) {
                    snake.locations[j].x = snake.locations[j  - 1].x;
                    snake.locations[j].y = snake.locations[j  - 1].y;
                }
                snake.locations[0].x = snake.head_x;
                snake.locations[0].y = snake.head_y;
                // draw snake
                add_snake_head_down(snake.head_x, snake.head_y);
                add_snake_tail(snake.locations[snake.length - 1].x, snake.locations[snake.length - 1].y);
                for(int k = 1; k <= snake.length - 2; ++k) {
                    add_snake_body(snake.locations[k].x, snake.locations[k].y);
                }
                return NO_ACTION;
            }   
            
            snake.head_px = snake.head_x;
            snake.head_py = snake.head_y;
            // incrementing head
            snake.head_y--;
            uLCD.cls();
            uLCD.printf("Pos:%d,%d Score:%d", snake.head_x, snake.head_y, snake.score);
            // erase previous snake
            for(int i = 0; i < snake.length; ++i) {
                map_erase(snake.locations[i].x, snake.locations[i].y);
            }
            add_plant(snake.locations[snake.length - 1].x, snake.locations[snake.length - 1].y);
            // update locations array
            for(int j = snake.length - 1; j > 0; --j) {
                snake.locations[j].x = snake.locations[j  - 1].x;
                snake.locations[j].y = snake.locations[j  - 1].y;
            }
            snake.locations[0].x = snake.head_x;
            snake.locations[0].y = snake.head_y;
            // draw snake
            add_snake_head_down(snake.head_x, snake.head_y);
            add_snake_tail(snake.locations[snake.length - 1].x, snake.locations[snake.length - 1].y);
            for(int k = 1; k <= snake.length - 2; ++k) {
                add_snake_body(snake.locations[k].x, snake.locations[k].y);
            }
            return NO_ACTION;
        }
    }
    return NO_ACTION;
}


/**
 * Draw the upper status bar.
 */
void draw_upper_status()
{
    uLCD.line(0, 9, 127, 9, GREEN);
}

/**
 * Draw the lower status bar.
 */
void draw_lower_status()
{
    uLCD.line(0, 118, 127, 118, GREEN);
}

/**
 * Draw the border for the map.
 */
void draw_border()
{
    uLCD.filled_rectangle(0,     9, 127,  14, WHITE); // Top
    uLCD.filled_rectangle(0,    13,   2, 114, WHITE); // Left
    uLCD.filled_rectangle(0,   114, 127, 117, WHITE); // Bottom
    uLCD.filled_rectangle(124,  14, 127, 117, WHITE); // Right
}

/**
 * Entry point for frame drawing. This should be called once per iteration of
 * the game loop. This draws all tiles on the screen, followed by the status
 * bars. Unless init is nonzero, this function will optimize drawing by only
 * drawing tiles that have changed from the previous frame.
 */
void draw_game(int draw_option)
{
    // Draw game border first
    if(draw_option == FULL_DRAW) 
    {
        draw_border();
        int u = 58;
        int v = 56;
        draw_snake_head_right(u, v);
        draw_snake_body(u-11, v);
        draw_snake_tail(u-22, v);
        return;
    }
    // Iterate over all visible map tiles
    for (int i = -5; i <= 5; i++) { // Iterate over columns of tiles
        for (int j = -4; j <= 4; j++) { // Iterate over one column of tiles
            // Here, we have a given (i,j)

            // Compute the current map (x,y) of this tile
            int x = i + snake.head_x;
            int y = j + snake.head_y;

            // Compute the previous map (px, py) of this tile
            int px = i + snake.head_px;
            int py = j + snake.head_py;

            // Compute u,v coordinates for drawing
            int u = (i+5)*11 + 3;
            int v = (j+4)*11 + 15;

            // Figure out what to draw
            DrawFunc draw = NULL;
            if (x >= 0 && y >= 0 && x < map_width() && y < map_height()) { // Current (i,j) in the map
                MapItem* curr_item = get_here(x, y);
                MapItem* prev_item = get_here(px, py);
                if (draw_option || curr_item != prev_item) { // Only draw if they're different
                    if (curr_item) { // There's something here! Draw it
                        draw = curr_item->draw;
                    } else { // There used to be something, but now there isn't
                        draw = draw_nothing;
                    }
                } else if (curr_item && curr_item->type == CLEAR) {
                    // This is a special case for erasing things like doors.
                    draw = curr_item->draw; // i.e. draw_nothing
                }
            } else if (draw_option) { // If doing a full draw, but we're out of bounds, draw the walls.
                draw = draw_wall;
            }

            // Actually draw the tile
            if (draw) draw(u, v);
        }
    }

    // Draw status bars
    draw_upper_status();
    draw_lower_status();
}

/**
 * Initialize the main world map. Add walls around the edges, interior chambers,
 * and plants in the background so you can see motion.
 */
void init_main_map()
{
    // "Random" plants
    Map* map = set_active_map(0);
    for(int i = map_width() + 3; i < map_area(); i += 39) {
        add_goodie(i % map_width(), i / map_width());
    }
    
    pc.printf("plants\r\n");

    pc.printf("Adding walls!\r\n");
    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());
    pc.printf("Walls done!\r\n");
    
    add_snake_head_right(snake.locations[0].x, snake.locations[0].y);
    add_snake_body(snake.locations[1].x, snake.locations[1].y);
    add_snake_tail(snake.locations[2].x, snake.locations[2].y);
    
    pc.printf("Add extra chamber\r\n");
    add_wall(30, 0, VERTICAL, 10);
    add_wall(30, 10, HORIZONTAL, 10);
    add_wall(39, 0, VERTICAL, 10);
    pc.printf("Added!\r\n");

    print_map();
}

/*
 * Main function
 */
int main()
{
    Blue.attach(&parse_message,Serial::RxIrq);
    uLCD.locate(0,0);
    uLCD.printf("Touch 1 to play snake game");
    uLCD.locate(0,2);
    uLCD.printf("Touch 2 to play math game");
    bool run_once_snake = true;
    bool run_once_math = true;
    bool keep_going = true;
    // Timer to measure game update speed
    Timer t;
    Timer t1;
    // Main game loop
    while(1) 
    {
        // plays the snake game
        if((bnum=='1')) { // button 1 changed
            myled1 = bhit - '0'; //turn led1 on/off
            if(run_once_snake)
            {
                // First things first: initialize hardware
                uLCD.cls();
                ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");
            
                snake_init(&snake);
                // 0. Initialize the maps -- implement this function:
                maps_init();
                init_main_map();
            
                // Initialize game state
                set_active_map(0);
                //snake.head_x = snake.head_y = 5;
                // Initial drawing
                draw_game(FULL_DRAW);
                uLCD.printf("Pos:%d,%d Score:%d", snake.head_x, snake.head_y, snake.score);
                run_once_snake = !run_once_snake;
            }
            t.start();
    
            // 1. Read inputs
            GameInputs inputs = read_inputs();
            
            // 2. Determine action
            int action = get_action(inputs);
            
            // 3. Update game
            int result = update_game(action);
            
            // 3b. Check for game over based on result
            if(result == GAME_OVER) {
                uLCD.cls();
                uLCD.printf("GAME OVER");
                run_once_snake = true;
                wait(5);
            }
            
            if(snake.length >= SNAKE_MAX_LENGTH) {
                uLCD.cls();
                uLCD.printf("YOU WIN");
                run_once_snake = true;
                wait(5);
            }
                    
            // 4. Draw screen
            draw_game(result);
            
            // Compute update time
            t.stop();
            int dt = t.read_ms();
    
            // Display and wait
            // NOTE: Text is 8 pixels tall
            if (dt < 100) wait_ms(250 - dt);
            button_ready = 0; //reset flag after reading button message
        }

        // plays the math game
        else if((bnum=='2')) { // button 2 changed
            myled2 = bhit - '0'; //turn led2 on/off
            run_once_math = true;
            // this portion should only run once
            if(run_once_math)
            {
                uLCD.cls();
                bool randomGen = true;
                t1.start();
                while(randomGen)
                { 
                    //push any button to start game
                    uLCD.locate(0,0);
                    uLCD.printf("Push any button to start the game");
                    if(button1==0 || button2==0 || button3==0 || button4==0 || button5==0)
                    {
                        seed = t1.read_us();
                    randomGen= false;
                    t1.reset();
                    uLCD.cls();
                    }
                } 
                srand((int)seed);
                run_once_math = !run_once_math;
                keep_going = true;
            }
            interrupt.fall(&fallInterrupt);
            interrupt.mode(PullUp);
            while(keep_going)
            {
            // keep generating problem until answer between 0 and 9 (for simplicity)
            while(1)
            {
                uLCD.cls();
                generateProblem();
                if(answer >= 0 && answer < 10)
                {
                    break;
                }
            }
            uLCD.locate(1,14);
            uLCD.printf("Score: %d",score);//display score
            //t1.start();
            while(t1.read() <= seconds){
                /*if(seconds - (int)t1.read() < 10){ //display time limit
                    uLCD.locate(13,1);
                    uLCD.printf("%d",(seconds -(int)t1.read()));
                } 
                else
                {
                    uLCD.locate(12,1);
                    uLCD.printf("%d",(seconds -(int)t1.read()));
                }*/
                // button to exit game
                if(button4 == 0)
                {
                    keep_going = false;
                }
                // enter button
                else if(button5 == 0) 
                {
                    break;
                }
            }
              
            //if correct answer then add score and decrease time limit
            if( ans == answer)
            {
            score += 1;
             seconds -=3;
            }
            else
            {
               if(score == 10)
                {
                    uLCD.cls();
                    uLCD.printf("You win!");
                    wait(5);
                    score = 0;
                    seconds = 30;
                }
                else
                {
                uLCD.cls();
                uLCD.printf("You lose!\n Your score is %d",score);
                pc.printf("ans: %d\n", ans);
                pc.printf("answer: %d\n", answer);
                wait(5);
                score = 0;
                seconds = 30;
                }
            }
            t1.reset();
                
            ans = 0;
              
            uLCD.cls();
            button_ready = 0; //reset flag after reading button message
            }
        }
    }
}


// Plays a wavfile
void playSound(char* wav)
{
    
}