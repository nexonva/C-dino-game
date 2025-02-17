#include <stdio.h>
#include <stdlib.h>
#include <conio.h>  // _kbhit(), _getch() functions
#include <windows.h> // Sleep() function

#define SCREEN_WIDTH 40
#define SCREEN_HEIGHT 10
#define GROUND_Y SCREEN_HEIGHT - 1

typedef struct {
    int x, y;
    int isJumping;
    int jumpHeight;
} Dinosaur;

typedef struct {
    int x, y;
} Obstacle;

void initDinosaur(Dinosaur* dino) {
    dino->x = 5;
    dino->y = GROUND_Y;
    dino->isJumping = 0;
    dino->jumpHeight = 0;
}

void initObstacle(Obstacle* obstacle) {
    obstacle->x = SCREEN_WIDTH;
    obstacle->y = GROUND_Y;
}

void drawScreen(Dinosaur* dino, Obstacle* obstacle) {
    system("cls"); // Clear screen
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            if (i == dino->y && j == dino->x) {
                printf("D"); // Dinosaur
            } else if (i == obstacle->y && j == obstacle->x) {
                printf("O"); // Obstacle
            } else if (i == GROUND_Y) {
                printf("-"); // Ground
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void updateDinosaur(Dinosaur* dino) {
    if (dino->isJumping) {
        if (dino->jumpHeight < 3) {
            dino->y--;
            dino->jumpHeight++;
        } else if (dino->jumpHeight < 6) {
            dino->y++;
            dino->jumpHeight++;
        } else {
            dino->isJumping = 0;
            dino->jumpHeight = 0;
        }
    }
}

void updateObstacle(Obstacle* obstacle) {
    obstacle->x--;
    if (obstacle->x < 0) {
        obstacle->x = SCREEN_WIDTH;
    }
}

int main() {
    Dinosaur dino;
    Obstacle obstacle;
    
    initDinosaur(&dino);
    initObstacle(&obstacle);

    while (1) {
        drawScreen(&dino, &obstacle);
        
        // Handle user input
        if (_kbhit()) {
            char ch = _getch();
            if (ch == ' ' && !dino.isJumping) {
                dino.isJumping = 1;
            }
        }

        // Check for collision between dinosaur and obstacle
        if (dino.x == obstacle.x && dino.y == obstacle.y) {
            printf("Game Over! Collision Detected!\n");
            break;
        }

        // Update game state
        updateDinosaur(&dino);
        updateObstacle(&obstacle);

        // Control game speed
        Sleep(100); // Update screen every 100ms
    }

    return 0;
}
