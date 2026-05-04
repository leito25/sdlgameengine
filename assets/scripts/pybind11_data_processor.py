# TwoDEngine Pybind11 Data Processor Example
# This script demonstrates data exchange between C++ and Python using pybind11

import cpp_data

def process_data(processor):
    """
    Process data received from C++

    Args:
        processor: A C++ DataProcessor object

    Returns:
        str: A message indicating completion
    """
    print("Processing data in Python...")

    # Access C++ data from Python
    data = processor.getData()
    print(f"Received {len(data)} data points from C++")

    for point in data:
        print(f"Python sees: {point.name}, value={point.value}, coordinates=({point.x}, {point.y})")

        # Modify the data in Python
        point.value *= 2
        point.x += 0.5
        point.y += 0.5

    # Add a new data point from Python
    processor.addDataPoint(cpp_data.DataPoint("Point C", 30, 5.0, 6.0))

    # Calculate statistics
    print(f"Sum calculated in Python: {processor.calculateSum()}")
    print(f"Average calculated in Python: {processor.calculateAverage()}")

    return "Data processing completed in Python"

# This function will be called directly from Python
def create_data_point():
    """
    Create a new data point in Python

    Returns:
        DataPoint: A new data point object
    """
    return cpp_data.DataPoint("Point D", 40, 7.0, 8.0)

print("Pybind11 data processor module loaded successfully!")
