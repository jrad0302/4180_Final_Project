// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.

#include "map.h"

#include "globals.h"
#include "graphics.h"

/**
 * The Map structure. This holds a HashTable for all the MapItems, along with
 * values for the width and height of the Map.
 */
struct Map {
    HashTable* items;
    int w, h;
};

#define NUM_MAPS 1
static Map maps[NUM_MAPS];
static int active_map;

static const MapItem CLEAR_SENTINEL = {
    .type = CLEAR,
    .draw = draw_nothing
};

/**
 * The first step in HashTable access for the map is turning the two-dimensional
 * key information (x, y) into a one-dimensional unsigned integer.
 * This function should uniquely map (x,y) onto the space of unsigned integers.
 */
static unsigned XY_KEY(int X, int Y) {
     // TODO: Fix me!
     // known as Cantor pairing funtion
     unsigned key = 0.5 * (X + Y) * (X + Y + 1) + Y;
     return key;
}

/**
 * This is the hash function actually passed into createHashTable. It takes an
 * unsigned key (the output of XY_KEY) and turns it into a hash value (some
 * small non-negative integer).
 */
unsigned map_hash(unsigned key)
{
    // TODO: Fix me!
    unsigned new_key = key % 8;
    return new_key;
}

void maps_init()
{
    // TODO: Implement!    
    // Initialize hash table
    // Set width & height
    Map* map = (Map*)malloc(sizeof(Map));
    map -> items = createHashTable(map_hash, 8);
    map -> w = 50;
    map -> h = 50;
    get_active_map() -> items = map -> items;
    get_active_map() -> w = map -> w;
    get_active_map() -> h = map -> h;
}

Map* get_active_map()
{
    return &maps[active_map];
}

Map* set_active_map(int m)
{
    active_map = m;
    return &maps[active_map];
}

void print_map()
{
    char lookup[] = {'W', 'D', 'P', 'A', 'K', 'C', 'N',' ','S'};
    Map* map = get_active_map();
    for(int j = 0; j < map->h; j++)
    {
        for (int i = 0; i < map->w; i++)
        {
            MapItem* item = (MapItem*)getItem(map->items, XY_KEY(i, j));
            if (item) pc.printf("%c", lookup[item->type]);
            else pc.printf(" ");
        }
        pc.printf("\r\n");
    }
}

int map_width()
{
    Map* map = get_active_map();
    return map -> w;
}

int map_height()
{
    Map* map = get_active_map();
    return map -> h;
}

int map_area()
{
    Map* map = get_active_map();
    return map -> w * map -> h;
}
MapItem* get_current(int x, int y)
{
    unsigned key = XY_KEY(x, y);
    //key = map_hash(key);
    MapItem* item = (MapItem*)getItem(get_active_map() -> items, key);
    return item;
}
MapItem* get_north(int x, int y)
{
    unsigned key = XY_KEY(x, y + 1);
    //key = map_hash(key);
    MapItem* item = (MapItem*)getItem(get_active_map() -> items, key);
    return item;
}
MapItem* get_south(int x, int y)
{
    unsigned key = XY_KEY(x, y - 1);
    //key = map_hash(key);
    MapItem* item = (MapItem*)getItem(get_active_map() -> items, key);
    return item;
}

MapItem* get_east(int x, int y)
{
    unsigned key = XY_KEY(x + 1, y);
    //key = map_hash(key);
    MapItem* item = (MapItem*)getItem(get_active_map() -> items, key);
    return item;
}

MapItem* get_west(int x, int y)
{
    unsigned key = XY_KEY(x - 1, y);
    //key = map_hash(key);
    MapItem* item = (MapItem*)getItem(get_active_map() -> items, key);
    return item;
}

MapItem* get_here(int x, int y)
{
    unsigned key = XY_KEY(x, y);
    //key = map_hash(key);
    MapItem* item = (MapItem*)getItem(get_active_map() -> items, key);
    return item;
}

void map_erase(int x, int y)
{
    unsigned key = XY_KEY(x, y);
    deleteItem(get_active_map() -> items, key);
}

void add_wall(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1->type = WALL;
        w1->draw = draw_wall;
        w1->walkable = false;
        w1->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, w1);
        if (val) free(val); // If something is already there, free it
    }
}

void add_plant(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = PLANT;
    w1->draw = draw_nothing;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_goodie(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = GOODIE;
    w1->draw = draw_goodie;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void remove_goodie(int x, int y) // I'm lazy so overwrite it with a plant
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = PLANT;
    w1->draw = draw_plant;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_snake_body(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = SNAKE_BODY;
    w1->draw = draw_snake_body;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_snake_head_right(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = SNAKE_BODY;
    w1->draw = draw_snake_head_right;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
void add_snake_head_left(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = SNAKE_BODY;
    w1->draw = draw_snake_head_left;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
void add_snake_head_up(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = SNAKE_BODY;
    w1->draw = draw_snake_head_up;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
void add_snake_head_down(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = SNAKE_BODY;
    w1->draw = draw_snake_head_down;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_snake_tail(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = SNAKE_BODY;
    w1->draw = draw_snake_tail;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
void add_plus_five(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = BUFF_PLUS5;
    w1->draw = draw_plus_five;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}
