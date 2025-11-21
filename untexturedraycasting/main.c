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
            double sideDistY;

            /* length of ray from one x or y-side to the next */
            double deltaDistX = (rayDirX ==0.0) ? 1e30 : fabs(1.0 / rayDirX);
            double deltaDistY = (rayDirY ==0.0) ? 1e30 : fabs(1.0 / rayDirY);

            double perpWallDist;

            /* direction to step in x(+1) or y(-1)-direction*/
            int stepX;
            int stepY;

            int hit = 0; //check wall hit
            int side; //was a North-South or East-West wall hit?

            //calculate step and initial sideDist
            if(rayDirX < 0.0){
                stepX = -1;
                sideDistX = (posX - mapX) * deltaDistX;
            } else {
                stepX = 1;
                sideDistX = (mapX + 1.0 - posX) * deltaDistX;
            }
            if(rayDirY < 0.0){
                stepY = -1;
                sideDistY = (posY- mapY) * deltaDistY;
            }else {
                stepY = 1;
                sideDistY = (mapY + 1.0 - posY) * deltaDistY;
            }

            /* DDA : A loop that increments the ray with 1 square everytime, until a wall is hit */
            while (hit == 0)
            {
                /* jump to next map square in x or y direction */
                if (sideDistX < sideDistY){
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = 0;
                } else {
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }
                /* Check if ray has hit a wall */
                if(worldMap[mapX][mapY] > 0) hit = 1;
            }

            /* Calculate distance projected on camera direction */
                if(side == 0) perpWallDist = (sideDistX - deltaDistX);
                else perpWallDist = (sideDistY - deltaDistY);
            
                /* Calculate height of line to be drawn on screen */
                int h;

                int lineHeight = (int)(h / perpWallDist);

                /* Calculate lowest and highest pixel to fill in current stripe */
                int drawStart = -lineHeight/2 + h/ 2;
                if(drawStart < 0)drawStart = 0;
                int drawEnd = lineHeight/ 2 + h / 2;
                if(drawEnd >= h)drawEnd = h - 1;

            /* Choose wall color */
            ColorRGB color;
            switch (worldMap[mapX][mapY])
            {
            case 1: color = RGB_Red; break;  // red
            case 2: color = RGB_Green; break;  // green
            case 3: color = RGB_Blue; break;  // blue
            case 4: color = RGB_White break;  // white
            
            default: color = RGB_Yellow;    // yellow
                break;
            }

            /* give x and y different brightness */
            if(side == 1)
            {
                color = ColorRGB_divide(color,2)
            }

            verLine(x, drawStart, drawEnd, color)

        }
    }
    
}

