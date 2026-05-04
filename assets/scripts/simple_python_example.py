# TwoDEngine Simple Python Example
# This script demonstrates data exchange between C++ and Python using files

def read_data_from_cpp(filename):
    """
    Read data from a file written by C++

    Args:
        filename: The name of the file to read

    Returns:
        A list of dictionaries containing the data points
    """
    data_points = []

    try:
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

        print(f"Read {len(data_points)} data points from C++")

    except Exception as e:
        print(f"Error reading data from file: {e}")

    return data_points

def write_data_to_cpp(data_points, filename):
    """
    Write data to a file for C++ to read

    Args:
        data_points: A list of dictionaries containing the data points
        filename: The name of the file to write
    """
    try:
        with open(filename, 'w') as file:
            # Write the number of data points
            file.write(f"{len(data_points)}\n")

            # Write each data point
            for point in data_points:
                file.write(f"{point['name']},{point['value']},{point['x']},{point['y']}\n")

        print(f"Wrote {len(data_points)} data points for C++")

    except Exception as e:
        print(f"Error writing data to file: {e}")

def process_data(data_points):
    """
    Process the data points

    Args:
        data_points: A list of dictionaries containing the data points

    Returns:
        The processed data points
    """
    print("Processing data in Python...")

    # Print the data points
    for point in data_points:
        print(f"Python sees: {point['name']}, value={point['value']}, coordinates=({point['x']}, {point['y']})")

    # Modify the data points
    for point in data_points:
        point['value'] *= 2  # Double the value
        point['x'] += 0.5    # Add 0.5 to x
        point['y'] += 0.5    # Add 0.5 to y

    # Add a new data point
    data_points.append({
        'name': 'Point C',
        'value': 30,
        'x': 5.0,
        'y': 6.0
    })

    # Calculate statistics
    total = sum(point['value'] for point in data_points)
    average = total / len(data_points) if data_points else 0

    print(f"Sum calculated in Python: {total}")
    print(f"Average calculated in Python: {average}")

    return data_points

def main():
    print("Simple Python Example - Python Side")
    print("===================================")

    # Read data from C++
    data_points = read_data_from_cpp("cpp_data.txt")

    # Process the data
    processed_data = process_data(data_points)

    # Write data back to C++
    write_data_to_cpp(processed_data, "python_data.txt")

    print("Python processing completed successfully!")

if __name__ == "__main__":
    main()
