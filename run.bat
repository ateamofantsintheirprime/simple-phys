gcc agent.c draw.c basic.c agent_manager.c -c -lpthread -O1 -Wall -std=c11 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
gcc main.c agent.o basic.o draw.o agent_manager.o -o game.exe -lpthread -O1 -Wall -std=c11 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
