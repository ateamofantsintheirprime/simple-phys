#include "agent_manager.h"

void init_manager(AgentManager *am) {
    am->agent_count = 0;
    am->agent_list = calloc(MAX_AGENT_COUNT, sizeof(Agent));
    if (am->agent_list == NULL) {
      printf("WARNING CALLOC FAILED\n");
    }
    for (size_t i = 0; i < MAX_AGENT_COUNT; i++) {
        init_agent(&am->agent_list[i]);
    }

    int grid_dimensions[2] = {(int) ceil(WINDOW_WIDTH / (float)AGENT_RADIUS), 
                              (int) ceil(WINDOW_HEIGHT / (float)AGENT_RADIUS)};
    printf("grid dimensions: {%d,%d}\n", grid_dimensions[0], grid_dimensions[1]);
    am->grid_cells = calloc(grid_dimensions[0], sizeof(GridCell*));
    if (am->grid_cells == NULL) {
        printf("WARNING CALLOC FAILED\n");
    }

    for (size_t i = 0; i < grid_dimensions[0]; i++) {
        am->grid_cells[i] = calloc(grid_dimensions[1], sizeof(GridCell));
        for (size_t j = 0; j < grid_dimensions[1]; j++) {
            am->grid_cells[i][j].capacity = 1; // This is only accurate for now
            am->grid_cells[i][j].occupant_count= 0;
            am->grid_cells[i][j].occupants = calloc(am->grid_cells[i][j].capacity, sizeof(Agent));
        }
    }
}

void allocate_agents_cells(AgentManager *am) {
    int grid_dimensions[2] = {(int) ceil(WINDOW_WIDTH / (float)AGENT_RADIUS), 
                            (int) ceil(WINDOW_HEIGHT / (float)AGENT_RADIUS)};
    printf("grid dimensions: {%d,%d}\n", grid_dimensions[0], grid_dimensions[1]);
    for (size_t i = 0; i < grid_dimensions[0]; i++) {
        for (size_t j = 0; j < grid_dimensions[1]; j++) {
            am->grid_cells[i][j].occupant_count= 0;
        }
    }

    for (size_t i = 0; i < am->agent_count; i++) {
        int grid_pos[2] = {(int) floor( am->agent_list[i].pos.x / (float)AGENT_RADIUS), 
                           (int) floor( am->agent_list[i].pos.y / (float)AGENT_RADIUS)};

        printf("grid pos: {%d,%d}\n", grid_pos[0], grid_pos[1]);
        int occupant_count = am->grid_cells[grid_pos[0]][grid_pos[1]].occupant_count;
        am->grid_cells[grid_pos[0]][grid_pos[1]].occupants[occupant_count] = am->agent_list[i];
        am->grid_cells[grid_pos[0]][grid_pos[1]].occupant_count += 1;
    }
}

void new_agent(AgentManager *am, Vector2 mouse_pos) {
    set_pos(&am->agent_list[am->agent_count], mouse_pos);
    am->agent_count += 1;
}

void update_agents(AgentManager *am, float delta_time) {
    // allocate_agents_cells(am);
    collide_agents(am);
    move_agents(am, delta_time);
}
void move_agents(AgentManager *am, float delta_time) {
    for (size_t i = 0; i < am->agent_count; i++) {
        move(&am->agent_list[i], GetFrameTime());
    }
}


void collide_agents(AgentManager *am) {
    for (size_t repeats = 0; repeats < 15; repeats ++) {
        float max_overlap = 0;

        // int grid_dimensions[2] = {(int) ceil(WINDOW_WIDTH / (float)AGENT_RADIUS), 
        //                           (int) ceil(WINDOW_HEIGHT / (float)AGENT_RADIUS)};

        // for (size_t i = 0; i < grid_dimensions[0]; i++) {
        //     for (size_t j = 0; j < grid_dimensions[1]; j++) {
        //         am->grid_cells[i][j].occupant_count= 0;            
        //     }
        // }




        for (size_t i = 0; i < am->agent_count; i++) {
            for (size_t j = i; j < am->agent_count; j++) {
                if (i != j) {
                    // Can't be colliding with ourselves, lads
                    float overlap = collide(&am->agent_list[i], &am->agent_list[j]);
                    if (overlap > max_overlap) {
                        max_overlap = overlap;
                    }
                }
            }
        }
        printf("max_overlap: %f\n", max_overlap);
        if ((max_overlap < AGENT_RADIUS/5.0) && (max_overlap > 1)) {
            break;
        }
    }
}

void uninit_manager(AgentManager *am) {
    free(am->agent_list);
    int grid_dimensions[2] = {(int) ceil(WINDOW_WIDTH  / (float)AGENT_RADIUS), 
                              (int) ceil(WINDOW_HEIGHT / (float)AGENT_RADIUS)};

    for (size_t i = 0; i < grid_dimensions[0]; i++) {
        for (size_t j = 0; j < grid_dimensions[1]; j++) {
            free(am->grid_cells[i][j].occupants);
        }
        free(am->grid_cells[i]);
    }
    free(am->grid_cells);
}
