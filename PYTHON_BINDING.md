# TwoDEngine Python Binding

This document describes the Python binding system used in TwoDEngine, which allows game logic to be written in Python while the core engine functionality is implemented in C++.

## Overview

TwoDEngine provides a Python binding system that enables developers to:
- Write game logic in Python
- Access C++ engine functionality from Python
- Pass data between C++ and Python
- Call Python functions from C++

The binding system is implemented in the `PythonBinding` class, which provides a simple interface for loading Python scripts and exchanging data between C++ and Python.

## PythonBinding Class

The `PythonBinding` class is defined in `libs/python/PythonBinding.h` and provides the following functionality:

### Initialization

```cpp
PythonBinding python;
if (!python.isInitialized()) {
    std::cerr << "Failed to initialize Python" << std::endl;
    return 1;
}
```

### Loading Python Scripts

```cpp
if (!python.runScriptFile("assets/scripts/myscript.py")) {
    std::cerr << "Failed to load Python script" << std::endl;
    return 1;
}
```

### Calling Python Functions

```cpp
// Call a Python function with no arguments
python.callFunction("init");

// Call a Python function that handles player shooting
python.callFunction("player_shoot");
```

### Data Exchange

The binding system supports exchanging various data types between C++ and Python:

#### Integers

```cpp
// Set an integer variable in Python
python.setInt("player_health", 100);

// Get an integer variable from Python
int health = python.getInt("player_health", 0); // Default value is 0 if not found
```

#### Floating Point Numbers

```cpp
// Set a float variable in Python
python.setFloat("player_x", 400.0f);

// Get a float variable from Python
float x = python.getFloat("player_x", 0.0f); // Default value is 0.0f if not found
```

#### Strings

```cpp
// Set a string variable in Python
python.setString("player_name", "Player1");

// Get a string variable from Python
std::string name = python.getString("player_name", "Unknown"); // Default value is "Unknown" if not found
```

#### Booleans

```cpp
// Set a boolean variable in Python
python.setBool("is_game_over", false);

// Get a boolean variable from Python
bool gameOver = python.getBool("is_game_over", false); // Default value is false if not found
```

## Python Script Structure

Python scripts used with TwoDEngine should follow a specific structure to work properly with the binding system:

```python
# Game constants
WINDOW_WIDTH = 800
WINDOW_HEIGHT = 600

# Global variables
player_x = 400
player_y = 300
player_health = 100
player_score = 0
is_game_over = False

# Initialize the game
def init():
    global player_x, player_y, player_health, player_score, is_game_over
    player_x = 400
    player_y = 300
    player_health = 100
    player_score = 0
    is_game_over = False
    print("Game initialized from Python")

# Update game state
def update():
    global player_health, player_score, is_game_over
    # Update game logic here
    pass

# Handle player shooting
def player_shoot():
    global player_score
    player_score += 10
    return True

# Reset the game
def reset_game():
    init()
    print("Game reset from Python")
```

## Example Usage

The `examples/PythonGame.cpp` file demonstrates how to use the Python binding system in a simple game:

1. Initialize the Python binding system
2. Load a Python script
3. Call Python functions for game logic
4. Exchange data between C++ and Python
5. Update the game state based on Python logic

To run the example, use the `build_run_python_game.bat` script:

```
build_run_python_game.bat
```

## Troubleshooting

If you encounter issues with the Python binding system:

1. Make sure Python is properly installed and configured
2. Check that the Python script exists and is in the correct location
3. Verify that the Python script defines all the functions being called from C++
4. Ensure that all required DLLs are in the correct location
5. Check the console output for error messages

## Implementation Details

The current implementation of the `PythonBinding` class is a simulation that doesn't actually use Python. Instead, it simulates the behavior of Python for demonstration purposes. In a real implementation, it would use a library like pybind11 to interact with the Python interpreter.

## Pybind11 Example

TwoDEngine includes a practical example of using pybind11 for real C++/Python integration. This example demonstrates how to:

- Expose C++ classes and functions to Python
- Pass data between C++ and Python
- Call Python functions from C++
- Modify C++ objects in Python

### Example Components

The pybind11 example consists of the following files:

- `examples/Pybind11Example.cpp`: C++ implementation that defines data structures, exposes them to Python, and demonstrates data exchange
- `assets/scripts/pybind11_data_processor.py`: Python script that processes data received from C++
- `build_run_pybind11_example.bat`: Script to build and run the example

### Data Structures

The example defines two main C++ data structures:

```cpp
// A simple data structure
struct DataPoint {
    std::string name;
    int value;
    double coordinates[2];

    // Methods for manipulating the data
    void print() const;
    void updateValue(int newValue);
    void updateCoordinates(double x, double y);
};

// A data processor class
class DataProcessor {
    std::vector<DataPoint> dataPoints;

public:
    void addDataPoint(const DataPoint& point);
    void clearData();
    std::vector<DataPoint>& getData();
    int calculateSum() const;
    double calculateAverage() const;
};
```

### Exposing C++ to Python

The example uses pybind11 to expose these C++ structures to Python:

```cpp
PYBIND11_EMBEDDED_MODULE(cpp_data, m) {
    // Expose the DataPoint class to Python
    py::class_<DataPoint>(m, "DataPoint")
        .def(py::init<const std::string&, int, double, double>())
        .def("print", &DataPoint::print)
        .def("updateValue", &DataPoint::updateValue)
        .def("updateCoordinates", &DataPoint::updateCoordinates)
        .def_readwrite("name", &DataPoint::name)
        .def_readwrite("value", &DataPoint::value)
        .def_property("x",
            [](const DataPoint& p) { return p.coordinates[0]; },
            [](DataPoint& p, double x) { p.coordinates[0] = x; })
        .def_property("y",
            [](const DataPoint& p) { return p.coordinates[1]; },
            [](DataPoint& p, double y) { p.coordinates[1] = y; });

    // Expose the DataProcessor class to Python
    py::class_<DataProcessor>(m, "DataProcessor")
        .def(py::init<>())
        .def("addDataPoint", &DataProcessor::addDataPoint)
        .def("clearData", &DataProcessor::clearData)
        .def("getData", &DataProcessor::getData, py::return_value_policy::reference)
        .def("calculateSum", &DataProcessor::calculateSum)
        .def("calculateAverage", &DataProcessor::calculateAverage);
}
```

### Python Script

The Python script (`pybind11_data_processor.py`) processes data received from C++:

```python
import cpp_data

def process_data(processor):
    """Process data received from C++"""
    # Access C++ data from Python
    data = processor.getData()

    # Modify the data in Python
    for point in data:
        point.value *= 2
        point.x += 0.5
        point.y += 0.5

    # Add a new data point from Python
    processor.addDataPoint(cpp_data.DataPoint("Point C", 30, 5.0, 6.0))

    # Calculate statistics
    print(f"Sum calculated in Python: {processor.calculateSum()}")
    print(f"Average calculated in Python: {processor.calculateAverage()}")

    return "Data processing completed in Python"
```

### Data Exchange Flow

The example demonstrates bidirectional data exchange:

1. C++ creates data objects and passes them to Python
2. Python accesses and modifies the C++ objects
3. Python creates new C++ objects and passes them back
4. C++ accesses the modified data and new objects

### Running the Example

To run the pybind11 example, use the `build_run_pybind11_example.bat` script:

```
build_run_pybind11_example.bat
```

This will build the example, copy the necessary files, and run it.

### Key Differences from PythonBinding

Unlike the simulated `PythonBinding` class, the pybind11 example:

- Uses actual Python integration through the pybind11 library
- Provides direct access to C++ objects in Python
- Allows Python to modify C++ objects directly
- Supports more complex data structures and interactions
- Demonstrates bidirectional data exchange

This example serves as a reference for implementing real Python integration in TwoDEngine or other C++ applications.

## Simple Python Example

TwoDEngine also includes a simpler approach to C++/Python integration that doesn't require pybind11 or Python development headers. This example demonstrates:

- Exchanging data between C++ and Python using files
- Launching Python from C++
- Processing data in Python and returning results to C++

### Example Components

The simple Python example consists of the following files:

- `examples/SimplePythonExample.cpp`: C++ implementation that creates data, writes it to a file, launches Python, and reads the processed data
- `assets/scripts/simple_python_example.py`: Python script that reads data from a file, processes it, and writes results back to a file
- `build_run_simple_python_example.bat`: Script to build and run the example

### Data Exchange Approach

Unlike the pybind11 example which directly exposes C++ classes to Python, this example uses a simpler file-based approach:

1. C++ writes data to a text file in a simple format
2. C++ launches the Python interpreter to run a script
3. Python reads the data from the file
4. Python processes the data
5. Python writes the processed data to another file
6. C++ reads the processed data from the file

### C++ Implementation

The C++ side handles data serialization and launching Python:

```cpp
// Write data to a file for Python to read
void writeDataToFile(const DataProcessor& processor, const std::string& filename) {
    std::ofstream file(filename);
    // Write data in a simple format
    file << processor.getData().size() << std::endl;
    for (const auto& point : processor.getData()) {
        file << point.name << "," << point.value << "," << point.x << "," << point.y << std::endl;
    }
}

// Read data from a file that Python wrote
void readDataFromFile(DataProcessor& processor, const std::string& filename) {
    std::ifstream file(filename);
    // Read data in the same format
    int numPoints;
    file >> numPoints;
    // Parse each data point
    for (int i = 0; i < numPoints; ++i) {
        // Read and parse the data
        // Add to the processor
    }
}

// In main():
// Write data to file
writeDataToFile(processor, "cpp_data.txt");

// Run Python script
system("python-3.10.11/python.exe assets/scripts/simple_python_example.py");

// Read processed data
readDataFromFile(processor, "python_data.txt");
```

### Python Implementation

The Python script reads, processes, and writes data:

```python
def read_data_from_cpp(filename):
    data_points = []
    with open(filename, 'r') as file:
        # Read the number of data points
        num_points = int(file.readline().strip())
        # Read each data point
        for _ in range(num_points):
            line = file.readline().strip()
            name, value, x, y = line.split(',')
            data_points.append({
                'name': name,
                'value': int(value),
                'x': float(x),
                'y': float(y)
            })
    return data_points

def write_data_to_cpp(data_points, filename):
    with open(filename, 'w') as file:
        # Write the number of data points
        file.write(f"{len(data_points)}\n")
        # Write each data point
        for point in data_points:
            file.write(f"{point['name']},{point['value']},{point['x']},{point['y']}\n")

def process_data(data_points):
    # Modify the data points
    for point in data_points:
        point['value'] *= 2
        point['x'] += 0.5
        point['y'] += 0.5

    # Add a new data point
    data_points.append({
        'name': 'Point C',
        'value': 30,
        'x': 5.0,
        'y': 6.0
    })

    return data_points

# Main function
data_points = read_data_from_cpp("cpp_data.txt")
processed_data = process_data(data_points)
write_data_to_cpp(processed_data, "python_data.txt")
```

### Running the Example

To run the simple Python example, use the `build_run_simple_python_example.bat` script:

```
build_run_simple_python_example.bat
```

This will build the example, copy the necessary files, and run it.

### Advantages of This Approach

This approach has several advantages:

- No need for Python development headers or libraries
- Works with any Python installation
- Simple to understand and implement
- No complex build requirements
- Can be extended to support more complex data structures

It's particularly useful when:

- You don't have access to Python development headers
- You want a simpler integration approach
- You need to exchange data between separate C++ and Python processes
- You're working with a runtime-only Python installation
