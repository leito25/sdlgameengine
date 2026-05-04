# TwoDEngine Python Game Script
# This script handles the game logic for the Python Game example

import math
import random

# Game constants
WINDOW_WIDTH = 800
WINDOW_HEIGHT = 600
MAX_ENEMIES = 10

# Global variables
player_x = 400
player_y = 300
player_health = 100
player_score = 0

enemies = []
dt = 0
is_game_over = False

# Initialize enemy positions for C++ to access
for i in range(MAX_ENEMIES):
    globals()[f"enemy{i}_x"] = random.randint(50, WINDOW_WIDTH - 50)
    globals()[f"enemy{i}_y"] = random.randint(50, WINDOW_HEIGHT - 50)

# Initialize the game
def init():
    global player_x, player_y, player_health, player_score, enemies, is_game_over

    print("Initializing Python game...")

    # Reset player
    player_x = 400
    player_y = 300
    player_health = 100
    player_score = 0
    is_game_over = False

    # Create initial enemies
    enemies = []
    for i in range(3):
        enemies.append({
            'x': random.randint(50, WINDOW_WIDTH - 50),
            'y': random.randint(50, WINDOW_HEIGHT - 50),
            'speed': random.randint(1, 3),
            'health': 100,
            'active': True
        })

    # Update enemy position variables
    update_enemy_positions()

    return True

# Update game state
def update():
    global player_health, player_score, is_game_over, enemies

    if is_game_over:
        return

    # Update enemies
    for enemy in enemies:
        if not enemy['active']:
            continue

        # Move towards player
        dx = player_x - enemy['x']
        dy = player_y - enemy['y']
        dist = math.sqrt(dx*dx + dy*dy)

        if dist > 0:
            enemy['x'] += (dx / dist) * enemy['speed']
            enemy['y'] += (dy / dist) * enemy['speed']

        # Check collision with player
        if dist < 50:  # Collision radius
            player_health -= 1
            if player_health <= 0:
                player_health = 0
                is_game_over = True

    # Spawn new enemy occasionally
    if random.random() < 0.01 * dt and len(enemies) < MAX_ENEMIES:
        # Spawn from edge of screen
        side = random.randint(0, 3)
        if side == 0:  # Top
            x = random.randint(0, WINDOW_WIDTH)
            y = 0
        elif side == 1:  # Right
            x = WINDOW_WIDTH
            y = random.randint(0, WINDOW_HEIGHT)
        elif side == 2:  # Bottom
            x = random.randint(0, WINDOW_WIDTH)
            y = WINDOW_HEIGHT
        else:  # Left
            x = 0
            y = random.randint(0, WINDOW_HEIGHT)

        enemies.append({
            'x': x,
            'y': y,
            'speed': random.randint(1, 3),
            'health': 100,
            'active': True
        })

    # Update enemy position variables for C++
    update_enemy_positions()

# Update enemy position variables for C++ to access
def update_enemy_positions():
    # Set active enemy positions
    for i, enemy in enumerate(enemies):
        if i >= MAX_ENEMIES:
            break
        if enemy['active']:
            globals()[f"enemy{i}_x"] = enemy['x']
            globals()[f"enemy{i}_y"] = enemy['y']

# Player shoots
def player_shoot():
    global player_score, enemies

    # Increase score
    player_score += 10

    # Check if hit any enemies
    hit_enemy = False
    for enemy in enemies:
        if not enemy['active']:
            continue

        dx = enemy['x'] - player_x
        dy = enemy['y'] - player_y
        dist = math.sqrt(dx*dx + dy*dy)

        if dist < 100:  # Shooting range
            enemy['health'] -= 50
            if enemy['health'] <= 0:
                enemy['active'] = False
                hit_enemy = True
                player_score += 50

    # Clean up inactive enemies occasionally
    if len(enemies) > 5:
        enemies = [e for e in enemies if e['active']]

    return hit_enemy

# Reset the game
def reset_game():
    init()
    print("Game reset from Python")

# Get game statistics
def get_stats():
    return {
        'player_health': player_health,
        'player_score': player_score,
        'enemy_count': len([e for e in enemies if e['active']]),
        'is_game_over': is_game_over
    }

print("Python game script loaded successfully!")
