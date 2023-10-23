#include "draw.h"

void draw_agent(Agent a) {
    DrawCircleV(a.pos, a.radius, a.colour);
}