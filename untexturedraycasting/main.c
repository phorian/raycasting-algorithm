#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "./header/quickcg.h"

/*
Compile with C99 standard:
gcc *.c -std=c99 -lSDL -lm -O3 -Wall -Wextra
or with Clang:
clang *.c -std=c99 -lSDL -lm -O3 -Wall -Wextra

For C11 standard:
gcc *.c -std=c11 -lSDL -lm -O3 -Wall -Wextra
*/

#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
    {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int main(int argc, char *argv[]){
    double posX = 22, posY = 12;    //x and y player start position
    double dirX = -1, dirY = 0;     //initial direction vector
    double planeX = 0, planeY = 0.66;  //2d raycaster version of camera plane

    double time = 0.0;  //time of current frame
    double oldTime = 0.0; // time of previous frame

    int x;
    double w;

    (void)argc;
    (void)argv; //won't raise unused parameter warning

    //draw screen
    screen(screenWidth, screenHeight, 0, "Raycaster");

    //start loop
    while (!done())
    {
        for(int x = 0; x < w; x++ ){
            /* Calculate ray position and direction */
            double cameraX = 2.0 * x /(double)w - 1.0; //x-coordinate in camera space
            double rayDirX = dirX + planeX * cameraX;
            double rayDirY = dirY + planeY * cameraX;

            /* Which box of map we are in */
            int mapX = (int)posX;
            int mapY = (int)posY;

            /* length of ray from player X current position to next x or y-side */
            double sideDistX;
            double sideDisty;

            /* length of ray from one x or y-side to the next */
            double deltaDistX = (rayDirX ==0.0) ? 1e30 : fabs(1.0 / rayDirX);
            double deltaDistY = (rayDirY ==0.0) ? 1e30 : fabs(1.0 / rayDirY);

            double perpWallDist;

            /* direction to step in x(+1) or y(-1)-direction*/
            int stepX;
            int stepY;

            int hit = 0; //check wall hit
            int side; //was a North-South or East-West wall hit?

        }
    }
    
}

