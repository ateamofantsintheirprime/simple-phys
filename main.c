/*******************************************************************************************
*
*   raylib [core] example - Keyboard input
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "include/raylib.h"
#include "agent.h"
#include "basic.h"
#include "draw.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct timespec start, stop;


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Game Window");
    // SetTargetFPS(MAX_FPS);
    //Agent agent_list[AGENT_COUNT];

    Agent *agent_list = calloc(MAX_AGENT_COUNT, sizeof(Agent));
    if (agent_list == NULL) {
      printf("WARNING CALLOC FAILED\n");
    }

    for (size_t i = 0; i < MAX_AGENT_COUNT; i++) {
        init_agent(&agent_list[i]);
    }

    printf("WINDOW DIMENSIONS: {%d, %d}\n", WINDOW_WIDTH, WINDOW_HEIGHT);
    int active_agents = 0;
    // struct timespec start, stop;

    // pid_t pid = fork();
    //--------------------------------------------------------------------------------------

// Main game loop
while (!WindowShouldClose())
{
    // Get Framerate
    double framerate = get_fps(start, stop);
    clock_gettime( CLOCK_REALTIME, &start);

    printf("RAYLIB FPS: %d\n", GetFPS());
    printf("RAYLIB Frametime: %f\n", GetFrameTime());
    printf("MY FPS:     %f\n", framerate);
    printf("TIME:     %f\n", GetTime());
    // Update
    //----------------------------------------------------------------------------------
    for (size_t repeats = 0; repeats < 8; repeats ++) {
        float max_overlap = 0;
        for (size_t i = 0; i < active_agents; i++) {
            for (size_t j = 0; j < active_agents; j++) {
                if (i != j) {
                    // Can't be colliding with ourselves, lads
                    float overlap = collide(&agent_list[i], &agent_list[j]);
                    if (overlap > max_overlap) {
                        max_overlap = overlap;
                    }
                }
            }
        }
        printf("Max overlap: %f\n", max_overlap);
    }
    for (size_t i = 0; i < active_agents; i++) {
        move(&agent_list[i], GetFrameTime());
    }
    if (IsMouseButtonDown(0) && active_agents < MAX_AGENT_COUNT) {
        set_pos(&agent_list[active_agents], GetMousePosition());
        active_agents += 1;
    }

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(BLANK);
        for (size_t i = 0; i < active_agents; i++) {
            draw_agent(agent_list[i]);
        }

    EndDrawing();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
CloseWindow();

return 0;
}
