#ifndef AGENT_H
#define AGENT_H

#include "include/raylib.h"
#include "include/raymath.h"
#include "basic.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct Agent {
  Vector2 pos;
  Vector2 last_pos;
  Vector2 accel;
  Color colour;
  float radius;
  float bounciness;
}Agent;


void move(Agent *a, float delta_time);
float collide(Agent *a, Agent *b); // Returns the amount of overlap

void set_pos(Agent* a, Vector2 new_pos);
void shift_pos(Agent *a, Vector2 shift);
void bounds(Agent *a);
void init_agent(Agent *a);

#endif
