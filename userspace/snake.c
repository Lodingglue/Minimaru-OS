/*
 * Copyright (C) 2025 Lodingglue
 *
 * This file is part of Minimaru-OS.
 *
 * Minimaru-OS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Minimaru-OS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Minimaru-OS.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include "string.h"

#define WIDTH 40
#define HEIGHT 20
#define MAX_SNAKE 100

static int snake_x[MAX_SNAKE], snake_y[MAX_SNAKE];
static int length, food_x, food_y;
static char direction = 'd'; // w: up, s: down, a: left, d: right

static void place_food() {
    food_x = (timer_get_ticks() % (WIDTH - 2)) + 1;
    food_y = (timer_get_ticks() % (HEIGHT - 2)) + 1;
}

void snake_main() {
    clear_screen();
    length = 3;
    snake_x[0] = WIDTH / 2;
    snake_y[0] = HEIGHT / 2;
    for (int i = 1; i < length; i++) {
        snake_x[i] = snake_x[0] - i;
        snake_y[i] = snake_y[0];
    }
    place_food();

    while (1) {
        // Check for keyboard input
        char c = read_key();
        if (c == 'w' && direction != 's') direction = 'w';
        else if (c == 's' && direction != 'w') direction = 's';
        else if (c == 'a' && direction != 'd') direction = 'a';
        else if (c == 'd' && direction != 'a') direction = 'd';
        else if (c == 'q') break;

        // Update snake position
        for (int i = length - 1; i > 0; i--) {
            snake_x[i] = snake_x[i - 1];
            snake_y[i] = snake_y[i - 1];
        }
        if (direction == 'w') snake_y[0]--;
        else if (direction == 's') snake_y[0]++;
        else if (direction == 'a') snake_x[0]--;
        else if (direction == 'd') snake_x[0]++;

        // Check collision
        if (snake_x[0] <= 0 || snake_x[0] >= WIDTH - 1 || snake_y[0] <= 0 || snake_y[0] >= HEIGHT - 1) {
            print_string("Game Over\n");
            break;
        }
        for (int i = 1; i < length; i++) {
            if (snake_x[0] == snake_x[i] && snake_y[0] == snake_y[i]) {
                print_string("Game Over\n");
                break;
            }
        }

        // Check food
        if (snake_x[0] == food_x && snake_y[0] == food_y) {
            length++;
            place_food();
        }

        // Draw
        clear_screen();
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1) {
                    print_char('#');
                } else if (x == food_x && y == food_y) {
                    print_char('*');
                } else {
                    int is_snake = 0;
                    for (int i = 0; i < length; i++) {
                        if (x == snake_x[i] && y == snake_y[i]) {
                            print_char('o');
                            is_snake = 1;
                            break;
                        }
                    }
                    if (!is_snake) print_char(' ');
                }
            }
            print_string("\n");
        }

        // Delay
        for (int i = 0; i < 1000000; i++) asm("nop");
    }
}