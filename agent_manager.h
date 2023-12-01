#ifndef AGENT_MANAGER_H
#define AGENT_MANAGER_H

#include "include/raylib.h"
#include "include/raymath.h"
#include "agent.h"
#include "basic.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct GridCell {
    Agent *occupants;
    int capacity;
    int occupant_count;
}GridCell;

typedef struct AgentManager {
  Agent *agent_list;
  GridCell **grid_cells;
  int agent_count;
}AgentManager;

void allocate_agents_cells(AgentManager *am);
void new_agent(AgentManager *am, Vector2 mouse_pos);
void update_agents(AgentManager *am, float delta_time);
void move_agents(AgentManager *am, float delta_time);
void collide_agents(AgentManager *am);
void init_manager(AgentManager *am);
void uninit_manager(AgentManager *am);

#endif
