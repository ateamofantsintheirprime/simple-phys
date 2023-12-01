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
#include "agent_manager.h"
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
    AgentManager agent_manager;
    init_manager(&agent_manager);

    // Agent *agent_list = calloc(MAX_AGENT_COUNT, sizeof(Agent));
    // if (agent_list == NULL) {
    //   printf("WARNING CALLOC FAILED\n");
    // }

    // for (size_t i = 0; i < MAX_AGENT_COUNT; i++) {
    //     init_agent(&agent_list[i]);
    // }
    // int active_agents = 0;

    // pid_t pid = fork();
    //--------------------------------------------------------------------------------------

// Main game loop
while (!WindowShouldClose())
{
    printf("RAYLIB FPS: %d\n", GetFPS());
    printf("RAYLIB Frametime: %f\n", GetFrameTime());
    printf("AGENT COUNT %d\n", agent_manager.agent_count);
    // Update
    //----------------------------------------------------------------------------------
    update_agents(&agent_manager, GetFrameTime());
    if (IsMouseButtonDown(0) && agent_manager.agent_count < MAX_AGENT_COUNT) {
        new_agent(&agent_manager, GetMousePosition());
    }

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(BLANK);
        for (size_t i = 0; i < agent_manager.agent_count; i++) {
            draw_agent(agent_manager.agent_list[i]);
        }

    EndDrawing();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
CloseWindow();
uninit_manager(&agent_manager);

return 0;
}
