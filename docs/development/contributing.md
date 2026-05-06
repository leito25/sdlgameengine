# Contributing to TwoDEngine

Thank you for your interest in contributing to TwoDEngine! This guide will help you get started.

## Ways to Contribute

There are many ways to contribute to TwoDEngine:

- 🐛 **Report Bugs**: Help us identify and fix issues
- 💡 **Suggest Features**: Share ideas for new features
- 📝 **Improve Documentation**: Fix typos, add examples, clarify explanations
- 💻 **Submit Code**: Fix bugs or implement new features
- 🎨 **Create Examples**: Share sample projects and tutorials
- 🧪 **Write Tests**: Improve test coverage
- 🌍 **Translate**: Help translate documentation

## Getting Started

### 1. Fork the Repository

Click the "Fork" button on the [TwoDEngine GitHub page](https://github.com/yourusername/TwoDEngine).

### 2. Clone Your Fork

```bash
git clone https://github.com/YOUR_USERNAME/TwoDEngine.git
cd TwoDEngine
```

### 3. Set Up Development Environment

```bash
# Run setup script
setup.bat  # Windows
./setup.sh # Linux/macOS

# Build the project
make

# Run tests
make test
```

### 4. Create a Branch

```bash
git checkout -b feature/your-feature-name
# or
git checkout -b fix/your-bug-fix
```

## Code Contribution Guidelines

### Code Style

TwoDEngine follows these coding standards:

#### Naming Conventions

```cpp
// Classes: PascalCase
class GameEngine { };

// Functions/Methods: PascalCase
void Initialize();
void ProcessInput();

// Variables: camelCase
int playerHealth;
float deltaTime;

// Constants: UPPER_SNAKE_CASE
const int MAX_ENTITIES = 1000;

// Private members: camelCase with no prefix
class Game
{
private:
    bool isRunning;  // Not m_isRunning or _isRunning
};
```

#### Formatting

```cpp
// Braces on new line
void Function()
{
    if (condition)
    {
        // Code here
    }
}

// Spaces around operators
int result = a + b;

// No spaces inside parentheses
Function(arg1, arg2);

// Indent with 4 spaces (no tabs)
void Function()
{
    if (condition)
    {
        DoSomething();
    }
}
```

#### Comments

```cpp
// Use Doxygen-style comments for public APIs
/**
 * @brief Brief description
 *
 * Detailed description here.
 *
 * @param paramName Parameter description
 * @return Return value description
 */
void Function(int paramName);

// Use // for inline comments
int value = 42;  // The answer to everything

// Use /* */ for multi-line explanations
/*
 * This is a complex algorithm that requires
 * multiple lines of explanation.
 */
```

### Documentation

All public APIs must be documented:

```cpp
/**
 * @file Game.h
 * @brief Core game engine class
 */

/**
 * @class Game
 * @brief Main game engine class
 *
 * The Game class manages the entire game lifecycle including
 * initialization, the main game loop, and cleanup.
 *
 * @code
 * Game game;
 * game.Initialize();
 * game.Run();
 * game.Destroy();
 * @endcode
 */
class Game
{
public:
    /**
     * @brief Initialize the game engine
     *
     * Initializes all subsystems including SDL, window, renderer,
     * and asset manager.
     *
     * @throws std::runtime_error if initialization fails
     *
     * @see Run(), Destroy()
     */
    void Initialize();
};
```

### Testing

Add tests for new features:

```cpp
// tests/GameTest.cpp
#include "Game.h"
#include <gtest/gtest.h>

TEST(GameTest, InitializeSucceeds)
{
    Game game;
    EXPECT_NO_THROW(game.Initialize());
}

TEST(GameTest, DestroyIsIdempotent)
{
    Game game;
    game.Initialize();
    game.Destroy();
    EXPECT_NO_THROW(game.Destroy());  // Should not crash
}
```

## Commit Guidelines

### Commit Message Format

```
<type>(<scope>): <subject>

<body>

<footer>
```

#### Types

- **feat**: New feature
- **fix**: Bug fix
- **docs**: Documentation changes
- **style**: Code style changes (formatting, no logic change)
- **refactor**: Code refactoring
- **test**: Adding or updating tests
- **chore**: Maintenance tasks

#### Examples

```bash
# Good commit messages
git commit -m "feat(renderer): add sprite batching support"
git commit -m "fix(input): handle controller disconnect properly"
git commit -m "docs(api): add examples to Game class documentation"

# Bad commit messages
git commit -m "fixed stuff"
git commit -m "WIP"
git commit -m "asdf"
```

### Detailed Commit Message

```
feat(audio): add spatial audio support

Implement 3D positional audio using SDL_mixer. This allows
sounds to be positioned in 3D space with distance attenuation
and stereo panning.

Features:
- Set sound position in 3D space
- Automatic distance attenuation
- Stereo panning based on position
- Configurable falloff curves

Closes #123
```

## Pull Request Process

### 1. Update Your Branch

```bash
# Fetch latest changes
git fetch upstream
git rebase upstream/main
```

### 2. Run Tests

```bash
# Build and test
make clean && make
make test

# Check code style
make lint
```

### 3. Push Your Changes

```bash
git push origin feature/your-feature-name
```

### 4. Create Pull Request

1. Go to your fork on GitHub
2. Click "New Pull Request"
3. Fill out the PR template
4. Link related issues

### Pull Request Template

```markdown
## Description
Brief description of changes

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Breaking change
- [ ] Documentation update

## Testing
- [ ] All tests pass
- [ ] Added new tests
- [ ] Manual testing completed

## Checklist
- [ ] Code follows style guidelines
- [ ] Documentation updated
- [ ] No new warnings
- [ ] Commit messages follow guidelines

## Related Issues
Closes #123
```

## Code Review Process

### What to Expect

1. **Initial Review**: Within 2-3 days
2. **Feedback**: Constructive comments and suggestions
3. **Iteration**: Make requested changes
4. **Approval**: At least one maintainer approval required
5. **Merge**: Maintainer will merge your PR

### Responding to Feedback

```bash
# Make requested changes
git add .
git commit -m "refactor: address review comments"
git push origin feature/your-feature-name
```

## Building Documentation

### Generate Doxygen Docs

```bash
# Generate API documentation
doxygen Doxyfile

# View documentation
start docs/api/html/index.html  # Windows
xdg-open docs/api/html/index.html  # Linux
open docs/api/html/index.html  # macOS
```

### Generate MkDocs Site

```bash
# Install MkDocs
pip install mkdocs mkdocs-material

# Serve locally
mkdocs serve

# Build static site
mkdocs build
```

## Community Guidelines

### Code of Conduct

- Be respectful and inclusive
- Welcome newcomers
- Provide constructive feedback
- Focus on the code, not the person
- Assume good intentions

### Communication Channels

- **GitHub Issues**: Bug reports and feature requests
- **GitHub Discussions**: Questions and general discussion
- **Pull Requests**: Code review and collaboration

## Recognition

Contributors are recognized in:

- **CONTRIBUTORS.md**: List of all contributors
- **Release Notes**: Mention in changelog
- **Documentation**: Author credits

## Questions?

If you have questions:

1. Check the [documentation](../index.md)
2. Search [existing issues](https://github.com/yourusername/TwoDEngine/issues)
3. Ask in [GitHub Discussions](https://github.com/yourusername/TwoDEngine/discussions)

---

Thank you for contributing to TwoDEngine! 🎮
