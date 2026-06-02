# SDL Game Engine Log

Learning log for the SDL 2D game engine project, based on the course:
C++ Game Engine Programming by Pikuma.

Course reference:
https://pikuma.com/courses/cpp-2d-game-engine-development

Use the learning sessions to record what was practiced, what was implemented in this repo, and what still needs follow-up. Keep the commit log as the technical history.

## Log Automation

Use these helper patterns to keep the learning log current:

- Add commit hashes under the related session after meaningful project changes.
- Add dated notes under **Log notes** when a session has learning evidence that is not obvious from git history.
- Keep checklists factual. Mark an item complete only when the code, docs, or captured evidence exists in this repo.

## Learning Sessions

### Session 01 - Introduction and Course Baseline

**Status:** In progress

**Related commits**
- _None yet._

**Course focus**
Motivations, learning outcomes, how to take the course, and the project baseline.

**Project work**
- Confirm this repository is the working SDL game engine project.
- Record the course source and log format.
- Review the current engine README, source tree, asset folders, and build scripts.

**Progress checklist**
- [x] Create the SDL game engine learning log.
- [x] Confirm the repo build target and current executable entry point.
- [x] Record the compiler, OS, SDL version, and build command used locally.
- [x] Capture the first successful build or launch evidence.

**What to learn**
- What this engine is expected to become by the end of the course.
- How to separate a learning log from the git commit log.
- Which existing repo files represent course work versus support tooling.

**Evidence to capture**
- Build command used.
- First successful window launch.
- Current dependency versions.

**Log notes**
- 2026-05-26 - Created the course learning log from the Pikuma C++ 2D game engine course outline.
- 2026-05-27 - Verified Linux target `SDLGameEngine` from `Makefile.linux`, current entry point `src/Main.cpp`, build command `make -f Makefile.linux all`, compiler `g++ 15.2.0`, OS Linux `7.0.0-15-generic`, SDL `2.32.10`, and existing executable/build outputs.

**Next step**
Verify dependencies and build tooling before changing engine code.

### Session 02 - Libraries and Dependencies

**Status:** In progress

**Related commits**
- `644156d` - Updated Linux and macOS Makefiles to compile all `src/*.cpp` files automatically, and added current engine source files to the CMake executable definitions.

**Course focus**
Project technologies, Linux/macOS/Windows setup, compilation, linking, Makefiles, Visual Studio setup, static libraries, and dynamic libraries.

**Project work**
- Audit SDL2, SDL2_image, SDL2_ttf, SDL2_mixer, GLM, Dear ImGui, Sol2, Lua, Python, and pybind11 setup.
- Confirm Linux, macOS, and Windows build scripts are documented accurately.
- Keep dependency setup scripts aligned with the current project structure.

**Progress checklist**
- [x] Confirm SDL2 is available to the build.
- [x] Confirm SDL2_image is available to the build.
- [x] Confirm SDL2_ttf is available to the build.
- [x] Confirm SDL2_mixer is available to the build.
- [x] Confirm GLM include paths.
- [x] Confirm Dear ImGui source/include setup.
- [x] Confirm Lua and Sol2 setup.
- [x] Confirm Python and pybind11 setup.
- [ ] Document static versus dynamic library expectations for this repo.

**What to learn**
- How C++ compilation and linking affect SDL projects.
- Why runtime DLL/shared-library placement matters.
- How Makefiles and CMake encode include paths, libraries, and output targets.

**Evidence to capture**
- Successful dependency test output.
- Any platform-specific setup issue and its fix.
- Final build command per supported platform.

**Next step**
Run or repair the basic SDL window build.

### Session 03 - Displaying the Game Window

**Status:** In progress

**Related commits**
- `52cf755` - Switched the executable entry point from the library integration demo to the `Game` lifecycle for SDL window work, preserving the previous Linux demo main as a backup source file.

**Course focus**
Game loop, Game class, creating an SDL window, polling SDL events, rendering the SDL window, fullscreen modes, SDL GPU acceleration, and VSync.

**Project work**
- Review `src/Game.h`, `src/Game.cpp`, and `src/Main.cpp`.
- Ensure the Game class owns initialization, event processing, update, render, and destroy flow.
- Confirm the SDL window and renderer lifecycle is explicit and cleaned up correctly.

**Progress checklist**
- [x] Implement or verify the Game class lifecycle.
- [x] Create and display an SDL window.
- [x] Poll SDL events.
- [x] Render a clear color to the SDL window.
- [x] Add or verify fullscreen behavior.
- [x] Enable accelerated rendering and VSync where appropriate.

**What to learn**
- How the core game loop is structured.
- What SDL owns versus what engine code owns.
- How fake fullscreen and real fullscreen differ.

**Evidence to capture**
- Screenshot or note showing the window launches.
- Renderer flags used.
- Any shutdown or cleanup issue discovered.

**Next step**
Render simple SDL objects and textures.

### Session 04 - Rendering SDL Objects

Double buffering means the game draws the next frame into a hidden back buffer while the current frame stays visible.
When all draw calls are done, `SDL_RenderPresent()` swaps the back buffer to the screen.
This avoids showing half-drawn frames, reducing flicker and visual tearing.
In practice: clear, draw everything for one frame, then present once.

**Status:** In progress

**Related commits**
- `cc0d954` - Added a colored SDL rectangle to the render pass for the Session 04 drawing test.
- `6a64ed4` - Loaded `assets/images/tank-panther-right.png` as an SDL surface, converted it to a texture, and rendered it into a destination rectangle.

**Course focus**
Drawing SDL rectangles, double-buffered rendering, loading PNG textures, and game loop rendering behavior.

**Project work**
- Draw a simple rectangle through SDL.
- Load a PNG from `assets/images`.
- Verify the render loop clears, draws, and presents consistently.

**Progress checklist**
- [x] Draw an SDL rectangle.
- [x] Confirm double-buffered rendering flow.
- [x] Load and render a PNG texture.
- [x] Document texture asset paths used for verification.

**What to learn**
- How SDL renderer draw calls compose a frame.
- Why presentation happens once per frame.
- How image loading extends base SDL behavior.

**Evidence to capture**
- Screenshot of rectangle rendering.
- Screenshot of PNG texture rendering.
- Notes on image-loading errors and fixes.

**Next step**
Add timestep control and movement.

### Session 05 - Game Loop Timestep

**Status:** In progress

**Related commits**
- `7914078` - Initialized sprite position and velocity in setup, updated the position each frame, and rendered the texture at the moving position.
- `9cd0679` - Replaced the manual tick-wait loop with an `SDL_Delay`-based frame wait before applying per-frame movement.
- `67bec83` - Added delta-time calculation from SDL ticks and scaled sprite movement by elapsed frame time, with the target framerate set to 60 FPS.

**Course focus**
Object movement, velocity vectors, fixed framerate, SDL delay, variable delta time, uncapped framerate, and determinism.

**Timing note**
- Fixed rate updates run game logic in equal-size steps, which keeps movement and physics more predictable across machines.
- Delta time uses the elapsed time since the previous frame to scale movement, so animation speed is less tied to FPS.
- This matters because real games run on hardware with different frame times; bad timing makes motion too fast, too slow, or unstable.
- References: https://gafferongames.com/post/fix_your_timestep/ and https://wiki.libsdl.org/SDL2/SDL_Delay

**Project work**
- Add time-based movement to a visible object.
- Compare fixed framerate and variable delta-time behavior.
- Record the loop timing strategy used by this repo.

**Progress checklist**
- [x] Move an object using velocity.
- [x] Implement or verify fixed framerate behavior.
- [x] Use SDL delay intentionally.
- [x] Add variable delta-time movement.
- [ ] Record framerate and determinism tradeoffs.

**What to learn**
- Why frame time matters for movement.
- How deterministic updates differ from variable rendering.
- How to avoid movement tied to machine speed.

**Evidence to capture**
- FPS or frame-time notes.
- Movement behavior before and after delta time.

**Next step**
Add structured engine logging.

### Session 06 - Logging

**Status:** In progress

**Related commits**
- `cebec65` - Added a custom `MyLogger` utility with timestamped info/error entries, stored log messages, console output, and an initial constructor log call.

**Course focus**
Logger class, logging game information, coding a logger, common C++ logging libraries, and logger design tradeoffs.

**Project work**
- Create or verify a lightweight engine logger.
- Use the logger for startup, shutdown, asset loading, and SDL errors.
- Avoid scattering raw `std::cout` calls through engine systems.

**Progress checklist**
- [x] Create a Logger class.
- [x] Log game initialization and shutdown.
- [ ] Log SDL errors with useful context.
- [x] Document whether the project uses a custom logger or third-party logger.

**What to learn**
- What information is useful during engine startup.
- How logging supports debugging without stepping through every frame.
- When a third-party logger is worth adding.

**Evidence to capture**
- Sample startup log.
- Sample asset-loading failure log.

**Next step**
Clean up the project folder structure.

### Session 07 - Project Folder Structure

**Status:** In progress

**Related commits**
- _None yet._

**Course focus**
Project subfolders and Makefile variables.

**Project work**
- Keep `src`, `assets`, `libs`, `docs`, scripts, and generated documentation clearly separated.
- Ensure build files reference folders through variables where practical.
- Avoid committing generated output unless it is intentionally part of the repo.

**Progress checklist**
- [x] Review current project subfolders.
- [x] Review Makefile variables.
- [ ] Confirm asset paths used by the executable.
- [ ] Decide which generated documentation folders should stay tracked.

**What to learn**
- How folder layout affects build simplicity.
- How asset paths should be resolved at runtime.
- How generated files can create noisy commits.

**Evidence to capture**
- Folder map after cleanup.
- Any build script path issue and its fix.

**Next step**
Start organizing game objects and engine ownership.

### Session 08 - Organizing Game Objects

**Status:** Not started

**Related commits**
- _None yet._

**Course focus**
Creating C++ objects, object creation examples, organizing game objects, object inheritance design, and C++ object tradeoffs.

**Project work**
- Review how entities or objects are currently represented.
- Identify where inheritance is useful and where composition is better.
- Keep game-object ownership explicit.

**Progress checklist**
- [ ] Create simple C++ game objects.
- [ ] Document object lifetime and ownership.
- [ ] Compare inheritance-based and component-based designs.
- [ ] Identify code that will move into ECS later.

**What to learn**
- Why naive inheritance grows brittle in games.
- How C++ object lifetime affects engine architecture.
- How to prepare for ECS without overbuilding early.

**Evidence to capture**
- Current object model notes.
- Example object creation path.

**Next step**
Design the ECS architecture.

### Session 09 - ECS Design

**Status:** Not started

**Related commits**
- _None yet._

**Course focus**
Component-based design, Entity-Component-System architecture, ECS folder structure, system signatures, C++ templates, component type templates, entity membership, erase-remove idiom, and entity operators.

**Project work**
- Create the initial ECS folder structure.
- Define component, entity, system, and registry responsibilities.
- Plan component signatures and system membership updates.

**Progress checklist**
- [ ] Add ECS folder structure.
- [ ] Define component type identifiers.
- [ ] Define system component signatures.
- [ ] Add entity add/remove behavior for systems.
- [ ] Use the erase-remove idiom where appropriate.
- [ ] Add entity comparison/operator support if needed.

**What to learn**
- How ECS separates data from behavior.
- Why component signatures let systems query relevant entities.
- How templates can remove repetitive component code.

**Evidence to capture**
- ECS class diagram or notes.
- Example system signature.

**Next step**
Implement the ECS registry and component storage.

### Session 10 - ECS Implementation

**Status:** Not started

**Related commits**
- _None yet._

**Course focus**
Component pools, Pool class, registry systems, entity signatures, entity creation, adding/removing components, and implementing system functions.

**Project work**
- Implement component pools.
- Implement the registry.
- Add entity creation and component add/remove APIs.
- Keep tests or examples focused on real ECS behavior.

**Progress checklist**
- [ ] Implement a Pool class.
- [ ] Implement registry-owned systems.
- [ ] Create entities through the registry.
- [ ] Add components to entities.
- [ ] Remove components from entities.
- [ ] Update system membership when signatures change.

**What to learn**
- How dense component storage improves iteration.
- How entity signatures drive system membership.
- Where component lifetime is managed.

**Evidence to capture**
- Minimal ECS example.
- Output showing entity/system membership updates.

**Next step**
Create the first real entities and components.

### Session 11 - Creating Entities and Components

**Status:** Not started

**Related commits**
- _None yet._

**Course focus**
First entity, smart pointers, converting ECS code to smart pointers, raw pointers for SDL, first component, `size_t` versus `int`, entity class component helpers, and cyclic dependency warnings.

**Project work**
- Create the first entity through ECS.
- Add transform and sprite-style components.
- Decide where smart pointers are useful and where SDL APIs require raw pointers.

**Progress checklist**
- [ ] Create the first ECS entity.
- [ ] Add the first component.
- [ ] Add entity helper methods for component access.
- [ ] Review smart pointer usage.
- [ ] Avoid cyclic dependencies in ECS headers.

**What to learn**
- How entity handles differ from component data.
- Why SDL handles often remain raw pointers.
- How integer types can create subtle bugs in indexing code.

**Evidence to capture**
- Example entity creation code.
- Notes on pointer ownership decisions.

**Next step**
Create movement and render systems.

### Session 12 - Creating Systems

**Status:** Not started

**Related commits**
- _None yet._

**Course focus**
Movement system, movement with delta time, and render system.

**Project work**
- Implement movement as a system over transform and velocity components.
- Implement rendering as a system over transform and sprite components.
- Keep system update order explicit.

**Progress checklist**
- [ ] Add MovementSystem.
- [ ] Update movement with delta time.
- [ ] Add RenderSystem.
- [ ] Render ECS entities through the SDL renderer.
- [ ] Document system update order.

**What to learn**
- How ECS systems process matching entities.
- Why update order matters.
- How render data should stay separate from movement logic.

**Evidence to capture**
- Moving sprite or rectangle.
- Notes on system ordering.

**Next step**
Add asset management.

### Session 13 - Managing Assets

**Status:** Not started

**Related commits**
- _None yet._

**Course focus**
Game assets, Asset Store, textures in the render system, tilemap rendering, rendering order, and sorting sprites by z-index.

**Project work**
- Implement or refine an Asset Store.
- Load textures once and reuse them by asset id.
- Render tilemaps and sprites with z-index ordering.

**Progress checklist**
- [ ] Add an Asset Store.
- [ ] Load textures into the Asset Store.
- [ ] Render texture assets through RenderSystem.
- [ ] Display a tilemap.
- [ ] Sort sprites by z-index.

**What to learn**
- Why asset ownership should be centralized.
- How z-index controls draw order.
- How tilemaps differ from individual sprites.

**Evidence to capture**
- Tilemap screenshot.
- Asset ids and file paths used.

**Next step**
Add animated sprites.

### Session 14 - Animation System

**Status:** Not started

**Related commits**
- _None yet._

**Course focus**
Animated sprites, animation system, and identifying animations by name.

**Project work**
- Add animation data to sprite entities.
- Update source rectangles based on animation timing.
- Identify animations by name for gameplay and scripting.

**Progress checklist**
- [ ] Add AnimationComponent.
- [ ] Add AnimationSystem.
- [ ] Update frames over time.
- [ ] Support named animations.

**What to learn**
- How sprite sheets map to animation frames.
- How animation state should be represented.
- How timing interacts with the game loop.

**Evidence to capture**
- Animated sprite screenshot or recording note.
- Animation component fields.

**Next step**
Add collision detection.

### Session 15 - Collision System

**Status:** Not started

**Related commits**
- _None yet._

**Course focus**
Entity collision checks, collision system implementation, rendering collider rectangles, and 2D collision basics.

**Project work**
- Add collider components.
- Implement collision checks between relevant entities.
- Add optional debug rendering for collider rectangles.

**Progress checklist**
- [ ] Add ColliderComponent.
- [ ] Add CollisionSystem.
- [ ] Detect entity collisions.
- [ ] Render collider rectangles for debugging.
- [ ] Log or emit collision events for follow-up systems.

**What to learn**
- How AABB collision works.
- How collision data should be separate from sprite size.
- Why debug visualization matters.

**Evidence to capture**
- Collider debug screenshot.
- Collision detection example.

**Next step**
Implement entity removal.

### Session 16 - Killing Entities

**Status:** Not started

**Related commits**
- _None yet._

**Course focus**
Killing entities, reusing IDs, and implementing entity removal.

**Project work**
- Add an entity kill/remove flow.
- Ensure killed entities are removed from systems and component pools.
- Decide how entity IDs are reused.

**Progress checklist**
- [ ] Mark entities for removal.
- [ ] Remove killed entities from systems.
- [ ] Remove killed entity components.
- [ ] Document entity ID reuse behavior.

**What to learn**
- Why immediate removal during iteration can be unsafe.
- How cleanup affects ECS consistency.
- How ID reuse can cause stale handle bugs.

**Evidence to capture**
- Example of entity spawn, kill, and cleanup.
- Notes on stale entity safety.

**Next step**
Add an event system.

### Session 17 - Event System

**Status:** Not started

**Related commits**
- _None yet._

**Course focus**
Event system introduction, design options, handlers, emitting events, subscribing to events, key pressed event exercise, design patterns, and event system quiz topics.

**Project work**
- Implement a simple event bus.
- Subscribe systems to events.
- Emit input and collision events.

**Progress checklist**
- [ ] Add EventBus or equivalent.
- [ ] Define base event handling pattern.
- [ ] Subscribe handlers to events.
- [ ] Emit events from input or collision code.
- [ ] Add a key pressed event.

**What to learn**
- How events decouple systems.
- When direct calls are simpler than events.
- How subscriptions should be cleaned up.

**Evidence to capture**
- Event flow notes.
- Example event type and subscriber.

**Next step**
Add gameplay systems for input, camera, projectiles, and health.

### Session 18 - Other Components and Systems

**Status:** Not started

**Related commits**
- _None yet._

**Course focus**
Keyboard control, camera follow, fixed-position sprites, projectile emitter, projectile duration, health component, shooting projectiles, and DRY code.

**Project work**
- Add keyboard-controlled movement.
- Add camera follow behavior.
- Add projectile spawning and lifetime.
- Add health tracking.

**Progress checklist**
- [ ] Add KeyboardControlSystem.
- [ ] Add CameraFollowSystem.
- [ ] Support fixed-position sprites.
- [ ] Add ProjectileEmitterComponent.
- [ ] Add projectile duration cleanup.
- [ ] Add HealthComponent.
- [ ] Implement shooting projectiles.

**What to learn**
- How input maps into ECS components.
- How camera movement affects rendering.
- How gameplay systems compose without hard dependencies.

**Evidence to capture**
- Screenshot or note showing player movement.
- Projectile spawn and cleanup notes.

**Next step**
Add entity tags and groups.

### Session 19 - Entity Tags and Groups

**Status:** Not started

**Related commits**
- _None yet._

**Course focus**
Tags, groups, optimized tag/group access, projectile collisions with player and enemies, and compilation times.

**Project work**
- Add entity tags for unique roles.
- Add groups for sets of related entities.
- Use tags/groups to simplify collision and gameplay queries.

**Progress checklist**
- [ ] Add tag support.
- [ ] Add group support.
- [ ] Optimize tag and group lookup.
- [ ] Handle projectile collisions with the player.
- [ ] Handle projectile collisions with enemies.
- [ ] Record compile-time observations if template/header changes become expensive.

**What to learn**
- How tags and groups complement component signatures.
- Why optimized lookup matters in gameplay loops.
- How header-heavy code affects compile time.

**Evidence to capture**
- Tag/group API examples.
- Projectile collision behavior notes.

**Next step**
Review data-oriented design and component storage performance.

### Session 20 - Data-Oriented Design

**Status:** Not started

**Related commits**
- _None yet._

**Course focus**
Data-oriented design, cache hits and misses, avoiding data gaps, packed component pools, arrays of structs versus structs of arrays, Valgrind cache profiling, and popular C++ ECS libraries.

**Project work**
- Review ECS storage layout.
- Identify avoidable memory gaps.
- Compare the current implementation with common ECS library patterns.

**Progress checklist**
- [ ] Review component pool packing.
- [ ] Document array-of-structs versus struct-of-arrays tradeoffs.
- [ ] Run profiling if Valgrind or another tool is available.
- [ ] Compare current ECS design with common C++ ECS libraries.

**What to learn**
- How memory layout affects iteration performance.
- Why data gaps hurt cache behavior.
- When to keep a custom ECS versus using a library.

**Evidence to capture**
- Profiling command and result, if available.
- Notes on storage layout decisions.

**Next step**
Render text with TrueType fonts.

### Session 21 - Displaying True-Type Fonts

**Status:** Not started

**Related commits**
- _None yet._

**Course focus**
Adding fonts to the Asset Store, render text system, and rendering health values.

**Project work**
- Add font loading to the Asset Store.
- Render text using SDL_ttf.
- Display health or another dynamic value.

**Progress checklist**
- [ ] Add fonts to the Asset Store.
- [ ] Add RenderTextSystem.
- [ ] Render static text.
- [ ] Render dynamic health values.

**What to learn**
- How SDL_ttf creates surfaces and textures.
- How text rendering differs from sprite rendering.
- How UI-style entities can fit into ECS.

**Evidence to capture**
- Screenshot of rendered text.
- Font asset path used.

**Next step**
Add Dear ImGui tooling.

### Session 22 - Dear ImGui

**Status:** Not started

**Related commits**
- _None yet._

**Course focus**
Dear ImGui introduction, SDL integration, demo window, immediate-mode GUI paradigm, render GUI system, spawning enemies with buttons, customizing new enemies, and Dear ImGui quiz topics.

**Project work**
- Integrate Dear ImGui with SDL renderer flow.
- Add a simple debug/tools panel.
- Use UI controls to spawn or modify game entities.

**Progress checklist**
- [ ] Initialize Dear ImGui with SDL.
- [ ] Show the ImGui demo window.
- [ ] Add RenderGUISystem.
- [ ] Add a button to spawn enemies.
- [ ] Add controls for customizing spawned enemies.

**What to learn**
- How immediate-mode UI differs from retained UI.
- How debug tools can inspect engine state.
- How UI code should avoid corrupting gameplay state.

**Evidence to capture**
- Screenshot of the ImGui panel.
- Notes on ImGui frame lifecycle.

**Next step**
Add culling and map control.

### Session 23 - Culling and Map Control

**Status:** Not started

**Related commits**
- _None yet._

**Course focus**
Killing entities outside map limits, flipping sprites on collision, invisible entities and obstacles, keeping the player inside the map, and culling sprites outside the camera view.

**Project work**
- Remove or disable entities outside map bounds.
- Keep the player constrained to valid map space.
- Cull rendering outside the camera view.

**Progress checklist**
- [ ] Kill entities outside map limits.
- [ ] Flip sprites on collision where needed.
- [ ] Add invisible obstacle support.
- [ ] Keep the player inside the map.
- [ ] Cull sprites outside the camera view.

**What to learn**
- How world bounds differ from camera bounds.
- Why culling matters for render performance.
- How invisible gameplay geometry should be represented.

**Evidence to capture**
- Map bounds notes.
- Culling behavior screenshot or debug output.

**Next step**
Load levels and behavior from Lua.

### Session 24 - Lua Scripting

**Status:** Not started

**Related commits**
- _None yet._

**Course focus**
Game scripting, Lua, Sol C++ wrapper, Lua state, reading Lua tables, default values, Lua functions, Level Loader class, assets from Lua, multiple objects in Lua levels, day/night tilemap scripting, entity behavior scripts, script system, Lua bindings, multiple Lua functions, loading different Lua levels, and C++/Lua responsibilities.

**Project work**
- Initialize Lua through Sol2.
- Load level data from Lua tables.
- Bind selected C++ functions to Lua.
- Keep the C++/Lua boundary explicit and documented.

**Progress checklist**
- [ ] Initialize Lua state.
- [ ] Read Lua tables.
- [ ] Handle missing Lua values safely.
- [ ] Add LevelLoader.
- [ ] Load assets from Lua.
- [ ] Load entities from Lua.
- [ ] Add ScriptSystem.
- [ ] Bind C++ functions to Lua.
- [ ] Load more than one Lua level.
- [ ] Document what belongs in C++ versus Lua.

**What to learn**
- How embedded scripting changes engine workflow.
- How Sol2 maps Lua data into C++ code.
- How to prevent scripts from owning core engine invariants.

**Evidence to capture**
- Lua level file path.
- Example Lua table and loaded entity result.
- Notes on exposed bindings.

**Next step**
Finish and clean up course code.

### Session 25 - Conclusion and Cleanup

**Status:** Not started

**Related commits**
- _None yet._

**Course focus**
Finishing the code and next steps.

**Project work**
- Review the full engine flow from startup to shutdown.
- Remove dead code and stale experiments.
- Update README, docs, and this log with the final course state.

**Progress checklist**
- [ ] Review startup and shutdown flow.
- [ ] Review ECS, assets, systems, events, UI, and scripting.
- [ ] Remove stale code or quarantine experiments.
- [ ] Update README with accurate build/run guidance.
- [ ] Update this learning log with final status.

**What to learn**
- How to evaluate a learning engine honestly.
- Which course patterns are worth keeping.
- Which parts need redesign before future projects.

**Evidence to capture**
- Final feature list.
- Known limitations.
- Recommended next refactors.

**Next step**
Optionally build the tilemap editor project.

### Session 26 - Bonus Tilemap Editor

**Status:** Not started

**Related commits**
- _None yet._

**Course focus**
Proposed tilemap editor project.

**Project work**
- Decide whether the editor belongs in this repo.
- Sketch editor requirements before implementation.
- Reuse engine rendering, input, assets, and ImGui tooling where possible.

**Progress checklist**
- [ ] Decide editor scope.
- [ ] Define map format.
- [ ] Define editor controls.
- [ ] Save and load tilemaps.
- [ ] Document editor workflow.

**What to learn**
- How engine tooling differs from game runtime code.
- How file formats affect iteration speed.
- How to keep tools from complicating runtime systems.

**Evidence to capture**
- Tilemap editor design notes.
- Example saved map file.

**Next step**
Record moving-forward goals.

### Session 27 - Moving Forward

**Status:** Not started

**Related commits**
- _None yet._

**Course focus**
Moving forward, copyright, and content distribution.

**Project work**
- Define the next project goal after the course.
- Audit third-party assets and licenses.
- Record what can be redistributed and what must stay local.

**Progress checklist**
- [ ] Define post-course roadmap.
- [ ] Audit asset licenses.
- [ ] Audit third-party library licenses.
- [ ] Document distribution constraints.
- [ ] List candidate engine improvements.

**What to learn**
- How to turn course code into a personal engine foundation.
- How licensing affects packaging and sharing.
- How to prioritize the next technical improvements.

**Evidence to capture**
- License audit notes.
- Roadmap entries.
- Packaging/distribution notes.

**Next step**
Use this log as the project trace while continuing engine development.
