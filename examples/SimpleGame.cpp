#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_sdl.h>
#include <sol/sol.hpp>

// Game constants
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int PLAYER_SPEED = 5;
const int ENEMY_SPEED = 2;

// Game classes
class GameObject {
protected:
    glm::vec2 position;
    glm::vec2 velocity;
    SDL_Rect rect;
    SDL_Texture* texture;

public:
    GameObject(SDL_Renderer* renderer, const char* imagePath, float x, float y, int w, int h) 
        : position(x, y), velocity(0.0f, 0.0f) {
        
        rect.x = static_cast<int>(x);
        rect.y = static_cast<int>(y);
        rect.w = w;
        rect.h = h;
        
        SDL_Surface* surface = IMG_Load(imagePath);
        if (!surface) {
            std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
            texture = nullptr;
            return;
        }
        
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        
        if (!texture) {
            std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        }
    }
    
    ~GameObject() {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }
    
    void update() {
        position += velocity;
        rect.x = static_cast<int>(position.x);
        rect.y = static_cast<int>(position.y);
        
        // Keep object within screen bounds
        if (rect.x < 0) rect.x = 0;
        if (rect.y < 0) rect.y = 0;
        if (rect.x > WINDOW_WIDTH - rect.w) rect.x = WINDOW_WIDTH - rect.w;
        if (rect.y > WINDOW_HEIGHT - rect.h) rect.y = WINDOW_HEIGHT - rect.h;
        
        position.x = static_cast<float>(rect.x);
        position.y = static_cast<float>(rect.y);
    }
    
    void render(SDL_Renderer* renderer) {
        if (texture) {
            SDL_RenderCopy(renderer, texture, nullptr, &rect);
        } else {
            // Fallback rendering if texture loading failed
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
    
    SDL_Rect getRect() const {
        return rect;
    }
    
    void setVelocity(float vx, float vy) {
        velocity.x = vx;
        velocity.y = vy;
    }
};

class Player : public GameObject {
private:
    int score;
    int health;

public:
    Player(SDL_Renderer* renderer, const char* imagePath, float x, float y)
        : GameObject(renderer, imagePath, x, y, 64, 64), score(0), health(100) {}
    
    void handleInput(const Uint8* keystate) {
        float vx = 0.0f;
        float vy = 0.0f;
        
        if (keystate[SDL_SCANCODE_UP]) vy -= PLAYER_SPEED;
        if (keystate[SDL_SCANCODE_DOWN]) vy += PLAYER_SPEED;
        if (keystate[SDL_SCANCODE_LEFT]) vx -= PLAYER_SPEED;
        if (keystate[SDL_SCANCODE_RIGHT]) vx += PLAYER_SPEED;
        
        setVelocity(vx, vy);
    }
    
    void increaseScore(int points) {
        score += points;
    }
    
    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
    }
    
    int getScore() const {
        return score;
    }
    
    int getHealth() const {
        return health;
    }
};

class Enemy : public GameObject {
private:
    glm::vec2 targetPosition;

public:
    Enemy(SDL_Renderer* renderer, const char* imagePath, float x, float y)
        : GameObject(renderer, imagePath, x, y, 48, 48), targetPosition(x, y) {}
    
    void setTarget(float x, float y) {
        targetPosition.x = x;
        targetPosition.y = y;
    }
    
    void updateAI() {
        glm::vec2 direction = targetPosition - position;
        
        // Normalize direction if not zero
        float length = glm::length(direction);
        if (length > 0) {
            direction = direction / length;
        }
        
        // Set velocity based on direction and speed
        setVelocity(direction.x * ENEMY_SPEED, direction.y * ENEMY_SPEED);
    }
};

// Collision detection function
bool checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    return (a.x < b.x + b.w && a.x + a.w > b.x && a.y < b.y + b.h && a.y + a.h > b.y);
}

int main(int argc, char* argv[]) {
    // Initialize SDL and extensions
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        return 1;
    }
    
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        std::cerr << "Error initializing SDL_image: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    
    if (TTF_Init() != 0) {
        std::cerr << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
        IMG_Quit();
        SDL_Quit();
        return 1;
    }
    
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Error initializing SDL_mixer: " << Mix_GetError() << std::endl;
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }
    
    // Create window and renderer
    SDL_Window* window = SDL_CreateWindow(
        "TwoDEngine Simple Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    
    if (!window) {
        std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
        Mix_CloseAudio();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    if (!renderer) {
        std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        Mix_CloseAudio();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }
    
    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGuiSDL::Initialize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
    
    // Load font
    TTF_Font* font = TTF_OpenFont("assets/fonts/arial.ttf", 24);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }
    
    // Load sound effects
    Mix_Chunk* collectSound = Mix_LoadWAV("assets/sounds/collect.wav");
    Mix_Chunk* hitSound = Mix_LoadWAV("assets/sounds/hit.wav");
    
    // Initialize Lua
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::math);
    
    // Create game objects
    Player player(renderer, "assets/images/chopper.png", 
                 WINDOW_WIDTH / 2 - 32, WINDOW_HEIGHT / 2 - 32);
    
    std::vector<Enemy> enemies;
    for (int i = 0; i < 3; i++) {
        float x = static_cast<float>(rand() % WINDOW_WIDTH);
        float y = static_cast<float>(rand() % WINDOW_HEIGHT);
        enemies.emplace_back(renderer, "assets/images/tank-tiger-right.png", x, y);
    }
    
    // Game loop
    bool running = true;
    Uint32 lastTime = SDL_GetTicks();
    SDL_Event event;
    
    while (running) {
        // Calculate delta time
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;
        
        // Handle events
        while (SDL_PollEvent(&event)) {
            // Process ImGui events manually
            if (event.type == SDL_QUIT)
                running = false;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)
                running = false;
            if (event.type == SDL_MOUSEMOTION) {
                io.MousePos = ImVec2(event.motion.x, event.motion.y);
            } else if (event.type == SDL_MOUSEWHEEL) {
                io.MouseWheel = event.wheel.y;
            } else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
                int button = event.button.button - 1;
                if (button >= 0 && button < 3) {
                    io.MouseDown[button] = (event.type == SDL_MOUSEBUTTONDOWN);
                }
            } else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
                io.KeysDown[event.key.keysym.scancode] = (event.type == SDL_KEYDOWN);
                io.KeyShift = ((SDL_GetModState() & KMOD_SHIFT) != 0);
                io.KeyCtrl = ((SDL_GetModState() & KMOD_CTRL) != 0);
                io.KeyAlt = ((SDL_GetModState() & KMOD_ALT) != 0);
            } else if (event.type == SDL_TEXTINPUT) {
                io.AddInputCharactersUTF8(event.text.text);
            }
        }
        
        // Handle player input
        const Uint8* keystate = SDL_GetKeyboardState(NULL);
        player.handleInput(keystate);
        
        // Update game objects
        player.update();
        
        for (auto& enemy : enemies) {
            // Set enemy target to player position
            SDL_Rect playerRect = player.getRect();
            enemy.setTarget(playerRect.x + playerRect.w / 2, playerRect.y + playerRect.h / 2);
            enemy.updateAI();
            enemy.update();
            
            // Check for collision with player
            if (checkCollision(player.getRect(), enemy.getRect())) {
                player.takeDamage(1);
                if (hitSound) Mix_PlayChannel(-1, hitSound, 0);
            }
        }
        
        // Start ImGui frame
        ImGui::NewFrame();
        
        // Create ImGui window
        ImGui::Begin("Game Stats");
        ImGui::Text("Health: %d", player.getHealth());
        ImGui::Text("Score: %d", player.getScore());
        ImGui::Text("FPS: %.1f", 1.0f / deltaTime);
        if (ImGui::Button("Quit")) {
            running = false;
        }
        ImGui::End();
        
        // Render
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        // Render game objects
        player.render(renderer);
        for (auto& enemy : enemies) {
            enemy.render(renderer);
        }
        
        // Render text
        if (font) {
            SDL_Color textColor = {255, 255, 255, 255};
            std::string healthText = "Health: " + std::to_string(player.getHealth());
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, healthText.c_str(), textColor);
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            SDL_Rect textRect = {10, 10, textSurface->w, textSurface->h};
            SDL_FreeSurface(textSurface);
            SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
            SDL_DestroyTexture(textTexture);
        }
        
        // Render ImGui
        ImGui::Render();
        ImGuiSDL::Render(ImGui::GetDrawData());
        
        SDL_RenderPresent(renderer);
        
        // Cap to 60 FPS
        SDL_Delay(1000 / 60);
        
        // Check game over condition
        if (player.getHealth() <= 0) {
            std::cout << "Game Over! Final Score: " << player.getScore() << std::endl;
            running = false;
        }
    }
    
    // Cleanup
    if (font) TTF_CloseFont(font);
    if (collectSound) Mix_FreeChunk(collectSound);
    if (hitSound) Mix_FreeChunk(hitSound);
    
    ImGuiSDL::Deinitialize();
    ImGui::DestroyContext();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    
    return 0;
}