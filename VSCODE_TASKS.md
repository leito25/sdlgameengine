# VS Code Tasks and Debugging for TwoDEngine

This document explains the VS Code tasks and debugging configurations for TwoDEngine development.

## Available Tasks

The following tasks are available in VS Code:

### Engine Tasks

1. **Build Engine (Debug)**
   - Builds the TwoDEngine in debug mode
   - Includes debugging symbols
   - No optimization
   - Output: `bin/main.exe`

2. **Build Engine (Release)**
   - Builds the TwoDEngine in release mode
   - Optimized with `-O3` flag
   - Defines `NDEBUG` to disable assertions
   - Output: `bin/main.exe`

3. **Run Engine (Debug)**
   - First builds the engine in debug mode
   - Then runs the executable
   - Useful for testing and debugging the engine

4. **Run Engine (Release)**
   - First builds the engine in release mode
   - Then runs the executable
   - Useful for performance testing

### Sample Game Tasks

5. **Build Sample Game (Debug)**
   - Builds the sample game in debug mode
   - Includes debugging symbols
   - No optimization
   - Output: `examples/SimpleGame.exe`

6. **Build Sample Game (Release)**
   - Builds the sample game in release mode
   - Optimized with `-O3` flag
   - Defines `NDEBUG` to disable assertions
   - Output: `examples/SimpleGame.exe`

7. **Run Sample Game (Debug)**
   - First builds the sample game in debug mode
   - Then runs the executable
   - Useful for testing and debugging the sample game

8. **Run Sample Game (Release)**
   - First builds the sample game in release mode
   - Then runs the executable
   - Useful for performance testing

9. **Pack Sample Game (Debug)**
   - Builds the sample game in debug mode
   - Creates a `dist-debug` directory
   - Copies the executable, DLLs, and assets to the `dist-debug` directory
   - Creates a standalone distribution package with debugging symbols

10. **Pack Sample Game (Release)**
    - Builds the sample game in release mode
    - Creates a `dist` directory
    - Copies the executable, DLLs, and assets to the `dist` directory
    - Creates an optimized standalone distribution package

### Python Game Tasks

11. **Build Python Game (Debug)**
    - Builds the Python game example in debug mode
    - Includes debugging symbols
    - No optimization
    - Output: `bin/PythonGame.exe`

12. **Build Python Game (Release)**
    - Builds the Python game example in release mode
    - Optimized with `-O3` flag
    - Defines `NDEBUG` to disable assertions
    - Output: `bin/PythonGame.exe`

13. **Run Python Game (Debug)**
    - First builds the Python game in debug mode
    - Then runs the executable
    - Useful for testing and debugging the Python game

14. **Run Python Game (Release)**
    - First builds the Python game in release mode
    - Then runs the executable
    - Useful for performance testing

15. **Pack Python Game (Debug)**
    - Builds the Python game in debug mode
    - Creates a `dist-python-debug` directory
    - Copies the executable, DLLs, Python files, and assets to the `dist-python-debug` directory
    - Creates a standalone distribution package with debugging symbols

16. **Pack Python Game (Release)**
    - Builds the Python game in release mode
    - Creates a `dist-python` directory
    - Copies the executable, DLLs, Python files, and assets to the `dist-python` directory
    - Creates an optimized standalone distribution package

## How to Run Tasks

There are several ways to run these tasks in VS Code:

### Using the Command Palette

1. Press `Ctrl+Shift+P` (Windows/Linux) or `Cmd+Shift+P` (macOS) to open the Command Palette
2. Type "Tasks: Run Task"
3. Select the task you want to run from the dropdown list

### Using the Terminal Menu

1. Click on "Terminal" in the top menu
2. Select "Run Task..."
3. Choose the task you want to run

### Using Keyboard Shortcuts

1. Press `Ctrl+Shift+B` (Windows/Linux) or `Cmd+Shift+B` (macOS) to run the default build task
2. For other tasks, you can configure custom keyboard shortcuts in VS Code

## Debugging Configurations

The following debugging configurations are available:

### Engine Debugging

1. **Debug Engine**
   - Launches the engine executable with the debugger attached
   - Automatically builds the engine in debug mode before launching
   - Allows setting breakpoints, inspecting variables, etc.

2. **Attach to Engine**
   - Attaches the debugger to an already running engine process
   - Useful when you want to debug an issue that occurs after some interaction

### Sample Game Debugging

3. **Debug Sample Game**
   - Launches the sample game executable with the debugger attached
   - Automatically builds the sample game in debug mode before launching
   - Allows setting breakpoints, inspecting variables, etc.

4. **Attach to Sample Game**
   - Attaches the debugger to an already running sample game process
   - Useful when you want to debug an issue that occurs after some interaction

### Python Game Debugging

5. **Debug Python Game**
   - Launches the Python game executable with the debugger attached
   - Automatically builds the Python game in debug mode before launching
   - Allows setting breakpoints, inspecting variables, etc.
   - Useful for debugging the C++ side of the Python game

6. **Attach to Python Game**
   - Attaches the debugger to an already running Python game process
   - Useful when you want to debug an issue that occurs after some interaction
   - Note: This only debugs the C++ code, not the Python scripts themselves

## How to Start Debugging

There are several ways to start debugging in VS Code:

### Using the Run and Debug View

1. Click on the Run and Debug icon in the Activity Bar (or press `Ctrl+Shift+D`)
2. Select the debugging configuration from the dropdown at the top
3. Click the green play button or press `F5`

### Using the Command Palette

1. Press `Ctrl+Shift+P` (Windows/Linux) or `Cmd+Shift+P` (macOS) to open the Command Palette
2. Type "Debug: Start Debugging"
3. Select the debugging configuration from the dropdown

### Using Keyboard Shortcuts

1. Press `F5` to start debugging with the currently selected configuration
2. Press `Ctrl+F5` to run without debugging

## Debugging Controls

Once debugging has started, you can use the following controls:

- **Continue/Pause** (`F5`): Continue execution or pause at the current line
- **Step Over** (`F10`): Execute the current line and move to the next line
- **Step Into** (`F11`): Step into a function call
- **Step Out** (`Shift+F11`): Step out of the current function
- **Restart** (`Ctrl+Shift+F5`): Restart the debugging session
- **Stop** (`Shift+F5`): Stop the debugging session

## Setting Breakpoints

To set a breakpoint:

1. Click in the gutter to the left of the line number
2. Or place the cursor on a line and press `F9`

## Inspecting Variables

During debugging, you can inspect variables in several ways:

1. **Variables Panel**: Shows local and global variables
2. **Watch Panel**: Shows variables you've added to watch
3. **Hover**: Hover over a variable in the code to see its value
4. **Debug Console**: Use the debug console to evaluate expressions

## Task Dependencies

Some tasks depend on other tasks:

- **Run Engine (Debug)** depends on **Build Engine (Debug)**
- **Run Engine (Release)** depends on **Build Engine (Release)**
- **Run Sample Game (Debug)** depends on **Build Sample Game (Debug)**
- **Run Sample Game (Release)** depends on **Build Sample Game (Release)**
- **Run Python Game (Debug)** depends on **Build Python Game (Debug)**
- **Run Python Game (Release)** depends on **Build Python Game (Release)**
- **Pack Sample Game (Debug)** depends on **Build Sample Game (Debug)**
- **Pack Sample Game (Release)** depends on **Build Sample Game (Release)**
- **Pack Python Game (Debug)** depends on **Build Python Game (Debug)**
- **Pack Python Game (Release)** depends on **Build Python Game (Release)**

When you run a task with dependencies, VS Code will automatically run the dependent tasks first.

## Customizing Tasks and Debug Configurations

If you need to customize these tasks or debug configurations:

1. Open the `.vscode/tasks.json` or `.vscode/launch.json` file
2. Modify the configuration as needed
3. Save the file

## Troubleshooting

If you encounter issues with tasks or debugging:

1. **Task fails to run**: Make sure you have MinGW installed and added to your PATH
2. **Build errors**: Check the error messages in the terminal for specific issues
3. **Debugger not attaching**: Ensure GDB is installed and in your PATH
4. **DLL not found**: Ensure all required DLLs are in the correct directories
5. **Path issues**: Verify that the paths in the configurations are correct for your system
6. **Python integration issues**:
   - Make sure Python embedded distribution is correctly downloaded and extracted
   - Verify that pybind11 is correctly downloaded and extracted
   - Check that Python scripts are in the correct location (assets/scripts/)
   - Ensure Python DLLs (.pyd files) are included when packaging
7. **Python script errors**:
   - Check for syntax errors in Python scripts
   - Verify that function names in C++ code match those defined in Python scripts
   - Make sure all required Python modules are available in the embedded distribution

## Example: Debugging the Sample Game

1. Set breakpoints in the sample game code
2. Press `Ctrl+Shift+D` to open the Run and Debug view
3. Select "Debug Sample Game" from the dropdown
4. Press `F5` to start debugging
5. The sample game will build and launch with the debugger attached
6. When execution reaches a breakpoint, it will pause
7. Use the debugging controls to step through the code
8. Inspect variables to understand the program state
9. Press `Shift+F5` to stop debugging when done

## Example: Debugging the Python Game

1. Set breakpoints in the Python game C++ code (examples/PythonGame.cpp)
2. Press `Ctrl+Shift+D` to open the Run and Debug view
3. Select "Debug Python Game" from the dropdown
4. Press `F5` to start debugging
5. The Python game will build and launch with the debugger attached
6. When execution reaches a breakpoint, it will pause
7. Use the debugging controls to step through the C++ code
8. Inspect variables to understand the program state
9. To debug Python scripts, add print statements in the Python code
10. Press `Shift+F5` to stop debugging when done
