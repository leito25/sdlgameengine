# TwoDEngine main Python script
# This script demonstrates how to use Python with the engine

# Global variables
player = {
    'x': 400,
    'y': 300,
    'speed': 5,
    'health': 100,
    'score': 0
}

enemies = []
game_time = 0
is_game_over = False

# Initialize the game
def init():
    print("Initializing game from Python...")

    # Create some enemies
    import random
    for i in range(5):
        enemies.append({
            'x': random.randint(50, 750),
            'y': random.randint(50, 550),
            'speed': random.randint(1, 3),
            'size': random.randint(20, 40)
        })

    return True

# Update game state
def update(dt):
    global game_time, is_game_over

    if is_game_over:
        return

    # Update game time
    game_time += dt

    # Update enemies
    import math
    for enemy in enemies:
        # Move towards player
        dx = player['x'] - enemy['x']
        dy = player['y'] - enemy['y']
        dist = math.sqrt(dx*dx + dy*dy)

        if dist > 0:
            enemy['x'] += (dx / dist) * enemy['speed']
            enemy['y'] += (dy / dist) * enemy['speed']

        # Check collision with player
        if dist < (enemy['size'] + 30):
            player['health'] -= 1
            if player['health'] <= 0:
                is_game_over = True

    # Spawn new enemy occasionally
    import random
    if random.random() < 0.01 and len(enemies) < 10:
        enemies.append({
            'x': random.randint(50, 750),
            'y': random.randint(50, 550),
            'speed': random.randint(1, 3),
            'size': random.randint(20, 40)
        })

    return player['x'], player['y'], player['health'], player['score'], is_game_over

# Handle player movement
def move_player(dx, dy):
    player['x'] += dx * player['speed']
    player['y'] += dy * player['speed']

    # Keep player within bounds
    player['x'] = max(30, min(770, player['x']))
    player['y'] = max(30, min(570, player['y']))

# Player shoots
def player_shoot():
    # Increase score
    player['score'] += 10

    # Check if hit any enemies
    hit_enemy = False
    for i in range(len(enemies)-1, -1, -1):
        enemy = enemies[i]
        dx = enemy['x'] - player['x']
        dy = enemy['y'] - player['y']
        import math
        dist = math.sqrt(dx*dx + dy*dy)

        if dist < 100:
            enemies.pop(i)
            hit_enemy = True
            player['score'] += 50

    return hit_enemy

# Get enemy positions for rendering
def get_enemies():
    result = []
    for enemy in enemies:
        result.append({
            'x': enemy['x'],
            'y': enemy['y'],
            'size': enemy['size']
        })
    return result

# Reset the game
def reset_game():
    global player, enemies, game_time, is_game_over

    player['x'] = 400
    player['y'] = 300
    player['health'] = 100
    player['score'] = 0

    enemies = []
    import random
    for i in range(5):
        enemies.append({
            'x': random.randint(50, 750),
            'y': random.randint(50, 550),
            'speed': random.randint(1, 3),
            'size': random.randint(20, 40)
        })

    game_time = 0
    is_game_over = False

    print("Game reset from Python")

# Return game statistics
def get_stats():
    return {
        'player_health': player['health'],
        'player_score': player['score'],
        'enemy_count': len(enemies),
        'game_time': game_time,
        'is_game_over': is_game_over
    }

print("Python script loaded successfully!")
