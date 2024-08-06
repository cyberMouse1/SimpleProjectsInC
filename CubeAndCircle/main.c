#include "stdlib.h"
#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PLAYER_SPEED 5
#define ENEMY_SPEED 2
#define BULLET_SPEED 10

typedef struct {
    Vector2 position;
    Vector2 velocity;
} Entity;

Entity player;
Entity enemies[10];
Entity bullets[10];

int enemyCount = 10;
int bulletCount = 10;

void UpdatePlayer() {
    if (IsKeyDown(KEY_W)) {
        player.velocity.y = -PLAYER_SPEED;
    } else if (IsKeyDown(KEY_S)) {
        player.velocity.y = PLAYER_SPEED;
    } else {
        player.velocity.y = 0;
    }

    player.position.y += player.velocity.y;

    if (player.position.y < 0) {
        player.position.y = 0;
    }
    if (player.position.y > SCREEN_HEIGHT) {
        player.position.y = SCREEN_HEIGHT;
    }
}

void UpdateBullets() {
    for (int i = 0; i < bulletCount; i++) {
        bullets[i].position.x += BULLET_SPEED;

        if (bullets[i].position.x > SCREEN_WIDTH) {
            for (int j = i; j < bulletCount - 1; j++) {
                bullets[j] = bullets[j + 1];
            }
            bulletCount--;
            i--;
        }
    }
}

void CheckCollisions() {
    for (int j = 0; j < bulletCount; j++) {
        Rectangle bulletRect = { bullets[j].position.x, bullets[j].position.y, 10, 10 };
        for (int i = 0; i < enemyCount; i++) {
            Rectangle enemyRect = { enemies[i].position.x, enemies[i].position.y, 10, 10 };
            if (CheckCollisionRecs(bulletRect, enemyRect)) {
                for (int k = i; k < enemyCount - 1; k++) {
                    enemies[k] = enemies[k + 1];
                }
                enemyCount--;

                for (int k = j; k < bulletCount - 1; k++) {
                    bullets[k] = bullets[k + 1];
                }
                bulletCount--;

                printf("Data:\nEnemy:%d\nBullet: %d\n", enemyCount, bulletCount);
                break;
            }
        }
    }
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Space Shooter");

    player.position = (Vector2){ 50, SCREEN_HEIGHT/2 };
    player.velocity = (Vector2){ 0, 90 };
    printf("Data:\nEnemy:%d\nBullet: %d\n", enemyCount, bulletCount);

    for (int i = 0; i < 10; i++) {
        enemies[i].position.x = SCREEN_WIDTH/2 + 350;
        enemies[i].position.y = GetRandomValue(0, SCREEN_HEIGHT);
        enemies[i].velocity.y = 2;
    }

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdatePlayer();
        UpdateBullets();
        CheckCollisions();
        if (IsKeyPressed(KEY_SPACE) && bulletCount <= 10) {
            bullets[bulletCount].position = (Vector2){ player.position.x, player.position.y + 25};
            bullets[bulletCount].velocity = (Vector2){ 0, -BULLET_SPEED };
            bulletCount++;
        }

        BeginDrawing();
            ClearBackground(BLACK);

            DrawRectangle(player.position.x, player.position.y, 50, 50, WHITE);

            for (int i = 0; i < 10; i++) {
                enemies[i].position.y += enemies[i].velocity.y;
                if (enemies[i].position.y < 0 || enemies[i].position.y > SCREEN_HEIGHT) {
                    enemies[i].velocity.y = -enemies[i].velocity.y;
                }
            }

            for (int i = 0; i < enemyCount; i++) {
                DrawCircle(enemies[i].position.x, enemies[i].position.y, 10, RED);
            }

            for (int i = 0; i < bulletCount; i++) {
                DrawCircle(bullets[i].position.x, bullets[i].position.y, 10, WHITE);
            }

            printf("Data:\nEnemy:%d\nBullet: %d\n", enemyCount, bulletCount);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
