---
name: unreal-course-log
description: Use when updating this Unreal Engine course learning log after commits, analyzing git commits against ProjectLog.md sessions, adding brief commit notes, and marking course progress checkboxes without inventing unsupported work.
metadata:
  short-description: Update Unreal course learning log from commits
---

# Unreal Course Log

Use this skill when the user asks to update, analyze, mark progress, or add comments/details in `ProjectLog.md` after a git commit or course-work session for the Unreal Lab UI project.

## Workflow

1. Read `ProjectLog.md`.
2. Inspect the target commit, defaulting to `HEAD`:
   - `git show --stat --summary HEAD`
   - `git show --name-status --format=fuller HEAD`
   - Read changed source/config/docs files when the stat is not enough.
3. Match the commit to one learning session using the strongest evidence:
   - Common UI setup, test map, player controller, layout, subsystem -> Session 02.
   - Async widget pushing, press-any-key, developer settings, function library -> Session 03.
   - Main menu, buttons, input data, confirmation, quit -> Session 04.
   - Options tabs, tab list, data registry, data collections -> Session 05.
   - Gameplay settings, list entries, reset/default settings -> Session 06.
   - Audio settings, sliders, volume, HDR audio -> Session 07.
   - Video settings, resolution, quality, VSync, frame limit -> Session 08.
   - Controls, key remapping, input icons, input preprocessor -> Session 09.
   - Loading screen, credits, rich text, camera tags -> Session 10.
   - Documentation, cleanup, project baseline, logging -> Session 01 or Session 11 depending on whether it starts or wraps up work.
4. Update only the matched session unless the commit clearly spans multiple sessions.
5. Under `Related commits`, add one short bullet:
   - ``- `shortsha` - Brief learning-focused note.``
6. Mark only checklist items directly supported by the commit:
   - Change `- [ ]` to `- [x]`.
   - Do not mark an item complete from filenames alone if the behavior is unclear.
7. Update `Status` conservatively:
   - `Not started` -> `In progress` when any checklist item or related commit is added.
   - `In progress` -> `Completed` only when every checklist item in that session is checked.
8. Add a blocker or follow-up only when the commit or build output shows one.
9. Preserve user notes, existing commit history, and unrelated file changes.

## Output Rules

- Keep notes brief and factual.
- Prefer course-learning language over raw implementation detail.
- Do not claim tests passed unless they were run.
- If no confident session match exists, add the commit to the closest session with a `Follow-up` note explaining what needs human confirmation.

## Helper Script

This repo includes two helper scripts.

Use this to gather commit context:

```bash
scripts/course-log-commit-context.sh
scripts/course-log-commit-context.sh --commit HEAD~1
scripts/course-log-commit-context.sh --diff
```

Use this to add a manual dated note:

```bash
scripts/add-comment-to-log --session 1 --comment "Configured the course-log automation workflow."
scripts/add-comment-to-log --session 2 --detail "Confirmed Common UI plugin settings."
```

The commit-context script does not call an AI service and does not edit files. The comment script edits only `ProjectLog.md`.
