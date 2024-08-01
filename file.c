# include "../MLX42/include/MLX42/MLX42.h"
#include <math.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define MOVE_SPEED 0.05
#define ROT_SPEED 0.05

int worldMap[MAP_WIDTH][MAP_HEIGHT] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

typedef struct {
    double posX, posY;  // Player position
    double dirX, dirY;  // Direction vector
    double planeX, planeY; // Camera plane
    bool moveForward, moveBackward, moveLeft, moveRight;
} Player;

void render(mlx_t *mlx, mlx_image_t *image, Player *player) {
    // Clear the image to black
    // mlx_delete_image(mlx, image);

    for (int x = 0; x < SCREEN_WIDTH; x++) {
        // Calculate ray position and direction
        double cameraX = 2 * x / (double)SCREEN_WIDTH - 1; // x-coordinate in camera space
        double rayDirX = player->dirX + player->planeX * cameraX;
        double rayDirY = player->dirY + player->planeY * cameraX;

        // Which box of the map we're in
        int mapX = (int)player->posX;
        int mapY = (int)player->posY;

        // Length of ray from current position to next x or y-side
        double sideDistX;
        double sideDistY;

        // Length of ray from one x or y-side to next x or y-side
        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;

        // Direction to go in x and y
        int stepX;
        int stepY;

        int hit = 0; // was there a wall hit?
        int side; // was a NS or a EW wall hit?

        // Calculate step and initial sideDist
        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (player->posX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - player->posX) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (player->posY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - player->posY) * deltaDistY;
        }

        // Perform DDA
        while (hit == 0) {
            // Jump to next map square, OR in x-direction, OR in y-direction
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            // Check if ray has hit a wall
            if (worldMap[mapX][mapY] > 0) hit = 1;
        }

        // Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
        if (side == 0) perpWallDist = (mapX - player->posX + (1 - stepX) / 2) / rayDirX;
        else perpWallDist = (mapY - player->posY + (1 - stepY) / 2) / rayDirY;

        // Calculate height of line to draw on screen
        int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

        // Calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

        // Draw the pixels of the stripe as a vertical line
        for (int y = drawStart; y < drawEnd; y++) {
            mlx_put_pixel(image, x, y, 0xFF0000FF); // Red color for walls
        }
    }
}

void update(Player *player) {
    if (player->moveForward) {
        if (worldMap[(int)(player->posX + player->dirX * MOVE_SPEED)][(int)player->posY] == 0) player->posX += player->dirX * MOVE_SPEED;
        if (worldMap[(int)player->posX][(int)(player->posY + player->dirY * MOVE_SPEED)] == 0) player->posY += player->dirY * MOVE_SPEED;
    }
    if (player->moveBackward) {
        if (worldMap[(int)(player->posX - player->dirX * MOVE_SPEED)][(int)player->posY] == 0) player->posX -= player->dirX * MOVE_SPEED;
        if (worldMap[(int)player->posX][(int)(player->posY - player->dirY * MOVE_SPEED)] == 0) player->posY -= player->dirY * MOVE_SPEED;
    }
    if (player->moveLeft) {
        double oldDirX = player->dirX;
        player->dirX = player->dirX * cos(-ROT_SPEED) - player->dirY * sin(-ROT_SPEED);
        player->dirY = oldDirX * sin(-ROT_SPEED) + player->dirY * cos(-ROT_SPEED);
        double oldPlaneX = player->planeX;
        player->planeX = player->planeX * cos(-ROT_SPEED) - player->planeY * sin(-ROT_SPEED);
        player->planeY = oldPlaneX * sin(-ROT_SPEED) + player->planeY * cos(-ROT_SPEED);
    }
    if (player->moveRight) {
        double oldDirX = player->dirX;
        player->dirX = player->dirX * cos(ROT_SPEED) - player->dirY * sin(ROT_SPEED);
        player->dirY = oldDirX * sin(ROT_SPEED) + player->dirY * cos(ROT_SPEED);
        double oldPlaneX = player->planeX;
        player->planeX = player->planeX * cos(ROT_SPEED) - player->planeY * sin(ROT_SPEED);
        player->planeY = oldPlaneX * sin(ROT_SPEED) + player->planeY * cos(ROT_SPEED);
    }
}

void key_callback(mlx_key_data_t keydata, void *param) {
    Player *player = (Player *)param;

    if (keydata.action == MLX_PRESS || keydata.action == MLX_RELEASE) {
        bool isPressed = (keydata.action == MLX_PRESS);

        switch (keydata.key) {
            case 87: // W key
                player->moveForward = isPressed;
                break;
            case 1: // S key
                player->moveBackward = isPressed;
                break;
            case 0: // A key
                player->moveLeft = isPressed;
                break;
            case 2: // D key
                player->moveRight = isPressed;
                break;
            default:
                break;
        }
    }
}

void hook(void *param) {
    mlx_t *mlx = (mlx_t *)param;
    Player player = {22, 12, -1, 0, 0, 0.66, false, false, false, false}; // Initial position and direction

    mlx_image_t *image = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!image) {
        printf("Failed to create image\n");
        mlx_terminate(mlx);
        exit(EXIT_FAILURE);
    }

    update(&player);
    render(mlx, image, &player);
    mlx_image_to_window(mlx, image, 0, 0);
}

int main(void) {
    mlx_t *mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "MLX42 Raycaster", true);
    if (!mlx) {
        printf("MLX42 initialization failed\n");
        return EXIT_FAILURE;
    }

    Player player = {22, 12, -1, 0, 0, 0.66, false, false, false, false}; // Initial position and direction

    mlx_key_hook(mlx, key_callback, &player);
    mlx_loop_hook(mlx, hook, mlx);
    mlx_loop(mlx);

    mlx_terminate(mlx);
    return 0;
}
