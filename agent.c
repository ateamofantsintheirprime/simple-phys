#include "agent.h"

void move(Agent *a, float delta_time) {
    // Move the lad around
    a->accel.y = 200; // Gravity
    Vector2 last_update_move = Vector2Subtract(a->pos, a->last_pos);
    Vector2 v1 = Vector2Add(a->pos, last_update_move);
    Vector2 v2 = Vector2Subtract(a->accel, Vector2Scale(last_update_move, 40)); // why 40?
    v2 = Vector2Scale(v2, delta_time*delta_time);
    Vector2 new_pos = Vector2Add(v1,v2);
    a->last_pos = a->pos;
    a->pos = new_pos;

    // printf("vel: {%f,%f}\n", a->last_pos.x-a->pos.x, a->last_pos.y-a->pos.y);

    // Keep the little bloke within bounds
    bounds(a);
   
}

void bounds(Agent *a) {
     Vector2 clamped_pos = Vector2Clamp(a->pos, (Vector2){a->radius,a->radius}, 
                            (Vector2){WINDOW_WIDTH-a->radius,WINDOW_HEIGHT-a->radius});
    Vector2 clamp_move = Vector2Subtract(clamped_pos, a->pos);
    a->last_pos = Vector2Add(a->last_pos, clamp_move);
    a->pos = clamped_pos;
    if (clamp_move.x != 0) {
        // collision on x wall, reflect!
        Vector2 reflected_last_pos = Vector2Subtract(a->last_pos, a->pos);
        reflected_last_pos.x *= -1;
        reflected_last_pos = Vector2Add(reflected_last_pos, a->pos);
        a->last_pos = reflected_last_pos;
    }
    if (clamp_move.y != 0) {
        // collision on y wall, reflect!
        Vector2 reflected_last_pos = Vector2Subtract(a->last_pos, a->pos);
        reflected_last_pos.y *= -1;
        reflected_last_pos = Vector2Add(reflected_last_pos, a->pos);
        a->last_pos = reflected_last_pos;
    }

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
        // a->pos = Vector2Clamp(a->pos, (Vector2){a->radius,a->radius}, 
        //     (Vector2){WINDOW_WIDTH-a->radius,WINDOW_HEIGHT-a->radius});
        // b->pos = Vector2Clamp(b->pos, (Vector2){b->radius,b->radius}, 
        //     (Vector2){WINDOW_WIDTH-b->radius,WINDOW_HEIGHT-b->radius});
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
    a->radius = AGENT_RADIUS;
    a->bounciness = .5;
}
