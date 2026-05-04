#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <glm/glm.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_sdl.h>
#include <python/PythonBinding.h>

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

    glm::vec2 getPosition() const {
        return position;
    }

    bool hasTexture() const {
        return texture != nullptr;
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

        if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_UP]) vy = -PLAYER_SPEED;
        if (keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_DOWN]) vy = PLAYER_SPEED;
        if (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT]) vx = -PLAYER_SPEED;
        if (keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT]) vx = PLAYER_SPEED;

        setVelocity(vx, vy);
    }

    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
    }

    int getHealth() const { return health; }
    int getScore() const { return score; }
    void addScore(int points) { score += points; }
    void setHealth(int newHealth) { health = newHealth; }
    void setScore(int newScore) { score = newScore; }
};

class Enemy : public GameObject {
private:
    float targetX;
    float targetY;

public:
    Enemy(SDL_Renderer* renderer, const char* imagePath, float x, float y)
        : GameObject(renderer, imagePath, x, y, 48, 48), targetX(x), targetY(y) {}

    void setTarget(float x, float y) {
        targetX = x;
        targetY = y;
    }

    void updateAI() {
        // Move towards target
        float dx = targetX - position.x;
        float dy = targetY - position.y;
        float distance = sqrt(dx*dx + dy*dy);

        if (distance > 0) {
            dx /= distance;
            dy /= distance;
        }

        // Set velocity based on direction and speed
        setVelocity(dx * ENEMY_SPEED, dy * ENEMY_SPEED);
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
        "TwoDEngine Python Game",
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
        // Try alternate path
        font = TTF_OpenFont("../assets/fonts/arial.ttf", 24);
        if (!font) {
            std::cerr << "Failed to load font from alternate path: " << TTF_GetError() << std::endl;
        } else {
            std::cout << "Loaded font from alternate path" << std::endl;
        }
    }

    // Load sound effects
    Mix_Chunk* collectSound = Mix_LoadWAV("assets/sounds/helicopter.wav");
    if (!collectSound) {
        // Try alternate path
        collectSound = Mix_LoadWAV("../assets/sounds/helicopter.wav");
        if (collectSound) {
            std::cout << "Loaded sound from alternate path" << std::endl;
        }
    }

    // Initialize Python
    PythonBinding python;
    if (!python.isInitialized()) {
        std::cerr << "Failed to initialize Python" << std::endl;
        return 1;
    }

    // Load Python script
    if (!python.runScriptFile("assets/scripts/pythongame.py")) {
        std::cerr << "Failed to load Python script" << std::endl;
        // Try alternate path
        if (!python.runScriptFile("../assets/scripts/pythongame.py")) {
            std::cerr << "Failed to load Python script from alternate path" << std::endl;
            return 1;
        } else {
            std::cout << "Loaded Python script from alternate path" << std::endl;
        }
    }

    // Call Python init function
    python.callFunction("init");

    // Create game objects
    Player player(renderer, "assets/images/chopper.png",
                 WINDOW_WIDTH / 2 - 32, WINDOW_HEIGHT / 2 - 32);

    // If player texture failed to load, try alternate path
    if (!player.hasTexture()) {
        player = Player(renderer, "../assets/images/chopper.png",
                      WINDOW_WIDTH / 2 - 32, WINDOW_HEIGHT / 2 - 32);
        if (player.hasTexture()) {
            std::cout << "Loaded player texture from alternate path" << std::endl;
        }
    }

    std::vector<Enemy> enemies;
    for (int i = 0; i < 3; i++) {
        float x = static_cast<float>(rand() % WINDOW_WIDTH);
        float y = static_cast<float>(rand() % WINDOW_HEIGHT);
        enemies.emplace_back(renderer, "assets/images/tank-tiger-right.png", x, y);

        // If enemy texture failed to load, try alternate path
        if (!enemies.back().hasTexture()) {
            enemies.pop_back();
            enemies.emplace_back(renderer, "../assets/images/tank-tiger-right.png", x, y);
        }
    }

    // Game loop variables
    bool running = true;
    bool gameOver = false;
    Uint32 lastTime = SDL_GetTicks();
    SDL_Event event;

    // Main game loop
    while (running) {
        // Calculate delta time
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        // Handle events
        while (SDL_PollEvent(&event)) {
            // ImGui event handling is done automatically in ImGui::NewFrame()

            if (event.type == SDL_QUIT)
                running = false;

            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    running = false;

                if (event.key.keysym.sym == SDLK_SPACE) {
                    // Player shoot - call Python function
                    python.callFunction("player_shoot");
                    if (collectSound) Mix_PlayChannel(-1, collectSound, 0);
                }

                if (event.key.keysym.sym == SDLK_r && gameOver) {
                    // Reset game - call Python function
                    python.callFunction("reset_game");
                    gameOver = false;
                }
            }
        }

        // Start ImGui frame
        ImGui::NewFrame();

        // Update game state if not game over
        if (!gameOver) {
            // Handle player input
            const Uint8* keystate = SDL_GetKeyboardState(NULL);
            player.handleInput(keystate);
            player.update();

            // Update Python game state
            python.setFloat("dt", deltaTime);

            // Call Python update function
            python.callFunction("update");

            // Get player stats from Python
            int playerHealth = python.getInt("player_health", 100);
            int playerScore = python.getInt("player_score", 0);
            bool isGameOver = python.getBool("is_game_over", false);

            // Update player stats
            player.setHealth(playerHealth);
            player.setScore(playerScore);
            gameOver = isGameOver;

            // Update enemy positions from Python
            for (size_t i = 0; i < enemies.size() && i < 10; i++) {
                std::string enemyXVar = "enemy" + std::to_string(i) + "_x";
                std::string enemyYVar = "enemy" + std::to_string(i) + "_y";

                float enemyX = python.getFloat(enemyXVar, enemies[i].getPosition().x);
                float enemyY = python.getFloat(enemyYVar, enemies[i].getPosition().y);

                enemies[i].setTarget(enemyX, enemyY);
                enemies[i].updateAI();
                enemies[i].update();
            }

            // Update Python with player position
            python.setFloat("player_x", player.getPosition().x);
            python.setFloat("player_y", player.getPosition().y);
        }

        // Create ImGui window
        ImGui::Begin("Game Stats");
        ImGui::Text("Health: %d", player.getHealth());
        ImGui::Text("Score: %d", player.getScore());

        if (gameOver) {
            ImGui::TextColored(ImVec4(1, 0, 0, 1), "GAME OVER!");
            ImGui::Text("Press R to restart");
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

        // Render ImGui
        ImGui::Render();
        ImGuiSDL::Render(ImGui::GetDrawData());

        SDL_RenderPresent(renderer);

        // Cap to 60 FPS
        SDL_Delay(1000 / 60);
    }

    // Cleanup
    if (collectSound) Mix_FreeChunk(collectSound);
    if (font) TTF_CloseFont(font);

    ImGuiSDL::Deinitialize();
    ImGui::DestroyContext();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    std::cout << "Game closed successfully!" << std::endl;

    return 0;
}
