# Contributing to TwoDEngine

Thank you for considering contributing to TwoDEngine! This document provides guidelines and instructions for contributing to the project.

## Code of Conduct

By participating in this project, you agree to abide by our Code of Conduct. Please be respectful and considerate of others.

## How to Contribute

There are many ways to contribute to TwoDEngine:

1. **Reporting Bugs**: If you find a bug, please create an issue with a detailed description.
2. **Suggesting Enhancements**: Have an idea for a new feature? Create an issue to discuss it.
3. **Code Contributions**: Want to fix a bug or add a feature? Submit a pull request.
4. **Documentation**: Help improve the documentation by fixing errors or adding examples.
5. **Examples**: Create new example applications that demonstrate how to use TwoDEngine.

## Development Setup

1. Fork the repository
2. Clone your fork: `git clone https://github.com/yourusername/TwoDEngine.git`
3. Set up the development environment:
   - Windows: Run `setup.bat` or `cmake_setup.bat`
   - Linux/macOS: Follow the instructions in README.md

## Pull Request Process

1. Create a new branch for your feature or bugfix: `git checkout -b feature/your-feature-name`
2. Make your changes
3. Run tests to ensure your changes don't break existing functionality
4. Update documentation if necessary
5. Submit a pull request with a clear description of the changes

## Coding Standards

Please follow these coding standards when contributing:

1. **C++ Style**:
   - Use 4 spaces for indentation (no tabs)
   - Follow the existing code style
   - Use meaningful variable and function names
   - Add comments for complex code sections

2. **Commit Messages**:
   - Use clear, descriptive commit messages
   - Start with a verb in the present tense (e.g., "Add feature" not "Added feature")
   - Reference issue numbers when applicable

3. **Documentation**:
   - Document all public functions and classes
   - Keep documentation up-to-date with code changes
   - Use clear, concise language

## Testing

Before submitting a pull request, please test your changes:

1. Build the project: `mingw32-make` or `cmake --build build`
2. Run the main application: `bin/main.exe`
3. Build and run the examples: `cd examples && mingw32-make && SimpleGame.exe`

## License

By contributing to TwoDEngine, you agree that your contributions will be licensed under the project's MIT License.

## Questions?

If you have any questions about contributing, please create an issue or contact the project maintainers.

Thank you for your contributions!