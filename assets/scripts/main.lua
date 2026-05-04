-- TwoDEngine main Lua script
-- This script demonstrates how to use Lua with the engine

-- Global variables
local player = {
    x = 400,
    y = 300,
    speed = 5,
    health = 100,
    score = 0
}

local enemies = {}
local gameTime = 0
local isGameOver = false

-- Initialize the game
function init()
    print("Initializing game from Lua...")
    
    -- Create some enemies
    for i = 1, 5 do
        table.insert(enemies, {
            x = math.random(50, 750),
            y = math.random(50, 550),
            speed = math.random(1, 3),
            size = math.random(20, 40)
        })
    end
    
    return true
end

-- Update game state
function update(dt)
    if isGameOver then
        return
    end
    
    -- Update game time
    gameTime = gameTime + dt
    
    -- Update player position based on input
    -- Note: The actual input handling is done in C++
    -- This function would receive the input state
    
    -- Update enemies
    for i, enemy in ipairs(enemies) do
        -- Move towards player
        local dx = player.x - enemy.x
        local dy = player.y - enemy.y
        local dist = math.sqrt(dx*dx + dy*dy)
        
        if dist > 0 then
            enemy.x = enemy.x + (dx / dist) * enemy.speed
            enemy.y = enemy.y + (dy / dist) * enemy.speed
        end
        
        -- Check collision with player
        if dist < (enemy.size + 30) then
            player.health = player.health - 1
            if player.health <= 0 then
                isGameOver = true
            end
        end
    end
    
    -- Spawn new enemy occasionally
    if math.random() < 0.01 and #enemies < 10 then
        table.insert(enemies, {
            x = math.random(50, 750),
            y = math.random(50, 550),
            speed = math.random(1, 3),
            size = math.random(20, 40)
        })
    end
    
    return player.x, player.y, player.health, player.score, isGameOver
end

-- Handle player movement
function movePlayer(dx, dy)
    player.x = player.x + dx * player.speed
    player.y = player.y + dy * player.speed
    
    -- Keep player within bounds
    player.x = math.max(30, math.min(770, player.x))
    player.y = math.max(30, math.min(570, player.y))
end

-- Player shoots
function playerShoot()
    -- Increase score
    player.score = player.score + 10
    
    -- Check if hit any enemies
    local hitEnemy = false
    for i = #enemies, 1, -1 do
        local enemy = enemies[i]
        local dx = enemy.x - player.x
        local dy = enemy.y - player.y
        local dist = math.sqrt(dx*dx + dy*dy)
        
        if dist < 100 then
            table.remove(enemies, i)
            hitEnemy = true
            player.score = player.score + 50
        end
    end
    
    return hitEnemy
end

-- Get enemy positions for rendering
function getEnemies()
    local result = {}
    for i, enemy in ipairs(enemies) do
        table.insert(result, {
            x = enemy.x,
            y = enemy.y,
            size = enemy.size
        })
    end
    return result
end

-- Reset the game
function resetGame()
    player.x = 400
    player.y = 300
    player.health = 100
    player.score = 0
    
    enemies = {}
    for i = 1, 5 do
        table.insert(enemies, {
            x = math.random(50, 750),
            y = math.random(50, 550),
            speed = math.random(1, 3),
            size = math.random(20, 40)
        })
    end
    
    gameTime = 0
    isGameOver = false
    
    print("Game reset from Lua")
end

-- Return game statistics
function getStats()
    return {
        playerHealth = player.health,
        playerScore = player.score,
        enemyCount = #enemies,
        gameTime = gameTime,
        isGameOver = isGameOver
    }
end

print("Lua script loaded successfully!")