// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.

#include "snake.h"

void snake_init (Snake* s)
{
    //s = (Snake*)malloc(sizeof(Snake));
    s -> head_x = s -> head_y = s -> head_py = 5;
    s -> head_px = 4;
    s -> length = 3;
    s -> locations[0].x = 5;
    s -> locations[0].y = 5;
    s -> locations[1].x = 4;
    s -> locations[1].y = 5;
    s -> locations[2].x = 3;
    s -> locations[2].y = 5;
    s -> score = 0;
    //add_snake_head(s -> head_x, s -> head_y);
    //add_snake_tail(s -> locations[s -> length - 1].x, s -> locations[s -> length - 1].y);
}
