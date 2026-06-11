---
name: sdl-engine-log
description: Use when updating this SDL game engine course learning log after commits, analyzing git commits against ProjectLog.md sessions, adding brief commit notes, and marking course progress checkboxes without inventing unsupported work.
metadata:
  short-description: Update SDL engine course learning log from commits
---

# SDL Engine Log

Use this skill when the user asks to update, analyze, mark progress, or add comments/details in `ProjectLog.md` after a git commit or course-work session for the SDL C++ 2D Game Engine project (Pikuma course).

## Workflow

1. Read `ProjectLog.md`.
2. Inspect the target commit, defaulting to `HEAD`:
   - `git show --stat --summary HEAD`
   - `git show --name-status --format=fuller HEAD`
   - Read changed source, header, or script files when the stat is not enough.
3. Match the commit to one or more learning sessions using the strongest evidence:
   - SDL window creation, SDL_Init, SDL_CreateWindow, renderer setup → Session 03.
   - SDL_RenderCopy, SDL_LoadBMP, texture, rect, sprite rendering → Session 04.
   - delta time, fixed timestep, SDL_GetTicks, FPS cap, game loop → Session 05.
   - Logger, log levels, spdlog, console output, `Logger.h/.cpp` → Session 06.
   - Folder structure, header organization, src/ layout, CMakeLists → Session 07.
   - GameObject, Transform, Velocity, rigid-body structs without ECS → Session 08.
   - ECS design notes, Registry concept, Component/Entity/System design → Session 09.
   - Registry, IComponent, ComponentPool, Pool class, ECS base classes → Session 10.
   - AddComponent, AddEntity, CreateEntity, component IDs → Session 11.
   - System, RequireComponent, AddEntityToSystem, GetSystemEntities → Session 12.
   - AssetStore, texture map, LoadTexture, GetTexture → Session 13.
   - AnimationComponent, AnimationSystem, frame rate, sprite sheet → Session 14.
   - BoxColliderComponent, CollisionSystem, AABB → Session 15.
   - KillEntity, OnUpdate despawn, health component, entity removal → Session 16.
   - EventBus, Event, CollisionEvent, SubscribeToEvent, EmitEvent → Session 17.
   - ProjectileComponent, ProjectileEmit, HealthComponent, CameraFollow → Session 18.
   - Tag, Group, GetEntityByTag, GetEntitiesByGroup → Session 19.
   - data-oriented refactor, SoA, pool alignment, benchmark → Session 20.
   - TTF_OpenFont, RenderText, TextLabelComponent, SDL_ttf → Session 21.
   - imgui_sdl, ImGui::Begin, ImGuiSDL, RenderGUISystem, debug panel → Session 22.
   - Culling, map bounds, invisible entity, sprite flip, camera clamp → Session 23.
   - sol::state, Lua tables, LevelLoader, ScriptSystem, Lua bindings → Session 24.
   - Final cleanup, README update, dead code removal, shutdown review → Session 25.
   - Tilemap editor, map format, editor controls → Session 26.
   - License audit, post-course roadmap, distribution notes → Session 27.
   - Build scripts, Makefile, dependencies, SDL setup, pybind11, Python → Session 02.
   - Repo init, README, course baseline, first build, first window → Session 01.
4. Update only the matched session unless the commit clearly spans multiple sessions.
5. Under `Related commits`, add one short bullet:
   - `` - `shortsha` - Brief learning-focused note. ``
6. Mark only checklist items directly supported by the commit:
   - Change `- [ ]` to `- [x]`.
   - Do not mark an item complete from filenames alone if the behavior is unclear.
7. Update `Status` conservatively:
   - `Not started` → `In progress` when any checklist item or related commit is added.
   - `In progress` → `Completed` only when every checklist item in that session is checked.
8. Add a blocker or follow-up note only when the commit or build output shows one.
9. Preserve user notes, existing commit history, and unrelated file changes.

## Output Rules

- Keep notes brief and factual.
- Prefer course-learning language over raw implementation detail.
- Do not claim tests passed unless they were run.
- If no confident session match exists, add the commit to the closest session with a `Follow-up` note explaining what needs human confirmation.

## Helper Commands

Gather context for a commit:

```powershell
git show --stat --summary HEAD
git show --name-status --format=fuller HEAD
git log --oneline -10
```

Add a manual dated note to `ProjectLog.md` under the relevant session's **Log notes** block:

```
- YYYY-MM-DD - Your note here.
```

Do not fabricate Log notes. Only write notes grounded in the commit diff or the user's explicit statement.
