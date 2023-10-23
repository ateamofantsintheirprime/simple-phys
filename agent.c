#include "agent.h"

void move(Agent *a, float delta_time) {
    // Move the lad around
    a->accel.y = 100; // Gravity
    Vector2 vel = Vector2Subtract(a->pos, a->last_pos);
    vel = Vector2Add(vel, a->accel);
    vel = Vector2Scale(vel, delta_time);

    a->last_pos = a->pos;
    a->pos = Vector2Add(a->pos, vel);

    // Keep the little bloke within bounds
    a->pos = Vector2Clamp(a->pos, (Vector2){a->radius,a->radius}, 
                            (Vector2){WINDOW_WIDTH-a->radius,WINDOW_HEIGHT-a->radius});
}

float collide(Agent *a, Agent *b) {
    // Make this parallelisable
    Vector2 distance = Vector2Subtract(b->pos, a->pos);
    float overlap = (a->radius + b->radius) - Vector2Distance(b->pos, a->pos);
    float buffer = 0.0;
    if (overlap > buffer) {
        // Collision!
        Vector2 b_move = Vector2Scale(Vector2Normalize(distance), overlap/2.0);
        Vector2 a_move = Vector2Scale(Vector2Normalize(distance), -overlap/2.0);
        // printf("Collision:\n");
        // printf("\tOverlap: %f\n", overlap);
        // printf("\ta_pos: {%f,%f}\n\tb_pos(%f,%f)\n",
        //                     a->pos.x,a->pos.y,
        //                     b->pos.x,b->pos.y);
        // printf("\ta_move: {%f,%f}\n\tb_move: {%f,%f}\n",
        //                     a_move.x,a_move.y,
        //                     b_move.x,b_move.y);
        a->pos = Vector2Add(a->pos, a_move);
        b->pos = Vector2Add(b->pos, b_move);
        a->pos = Vector2Clamp(a->pos, (Vector2){a->radius,a->radius}, 
            (Vector2){WINDOW_WIDTH-a->radius,WINDOW_HEIGHT-a->radius});
        b->pos = Vector2Clamp(b->pos, (Vector2){b->radius,b->radius}, 
            (Vector2){WINDOW_WIDTH-b->radius,WINDOW_HEIGHT-b->radius});
    }
    return overlap;
}

void set_pos(Agent* a, Vector2 new_pos) {
    // Stick him somewhere new
    Vector2 retain_vel =  Vector2Subtract(a->last_pos, a->pos);
    a->pos = new_pos;
    a->last_pos = Vector2Add(a->pos, retain_vel);
}
void shift_pos(Agent* a, Vector2 shift) {
    // Budge the lad around a little
    Vector2 retain_vel =  Vector2Subtract(a->last_pos, a->pos);
    a->pos = Vector2Add(a->pos, shift);
    a->last_pos = Vector2Add(a->pos, retain_vel);
}

void init_agent(Agent *a) {
    // G'day mate
    a->pos = Vector2Zero();
    a->last_pos = Vector2Zero();
    a->accel = Vector2Zero();
    a->colour = ColorFromHSV(GetRandomValue(0,360), 1, 1);
    a->radius = 15;
    a->bounciness = .5;
}
