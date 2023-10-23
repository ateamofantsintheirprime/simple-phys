gcc agent.c draw.c basic.c -c -lpthread -O1 -Wall -std=c11 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
gcc main.c agent.o basic.o draw.o -o game.exe -lpthread -O1 -Wall -std=c11 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
