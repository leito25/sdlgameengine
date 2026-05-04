#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>

// A simple data structure to demonstrate C++ to Python data exchange
struct DataPoint {
    std::string name;
    int value;
    double x;
    double y;

    DataPoint(const std::string& n, int v, double x_val, double y_val)
        : name(n), value(v), x(x_val), y(y_val) {}

    std::string toString() const {
        return "DataPoint: " + name + ", value=" + std::to_string(value) +
               ", coordinates=(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }
};

// A simple data processor class
class DataProcessor {
private:
    std::vector<DataPoint> dataPoints;

public:
    void addDataPoint(const DataPoint& point) {
        dataPoints.push_back(point);
    }

    void clearData() {
        dataPoints.clear();
    }

    const std::vector<DataPoint>& getData() const {
        return dataPoints;
    }

    int calculateSum() const {
        int sum = 0;
        for (const auto& point : dataPoints) {
            sum += point.value;
        }
        return sum;
    }

    double calculateAverage() const {
        if (dataPoints.empty()) return 0.0;
        return static_cast<double>(calculateSum()) / dataPoints.size();
    }
};

// Function to write data to a file for Python to read
void writeDataToFile(const DataProcessor& processor, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }

    // Write the number of data points
    file << processor.getData().size() << std::endl;

    // Write each data point
    for (const auto& point : processor.getData()) {
        file << point.name << "," << point.value << "," << point.x << "," << point.y << std::endl;
    }

    file.close();
}

// Function to read data from a file that Python wrote
void readDataFromFile(DataProcessor& processor, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading: " << filename << std::endl;
        return;
    }

    processor.clearData();

    // Read the number of data points
    int numPoints;
    file >> numPoints;
    file.ignore(); // Skip the newline

    // Read each data point
    for (int i = 0; i < numPoints; ++i) {
        std::string line;
        std::getline(file, line);

        std::stringstream ss(line);
        std::string name;
        int value;
        double x, y;

        std::getline(ss, name, ',');
        ss >> value;
        ss.ignore(); // Skip the comma
        ss >> x;
        ss.ignore(); // Skip the comma
        ss >> y;

        processor.addDataPoint(DataPoint(name, value, x, y));
    }

    file.close();
}

int main() {
    std::cout << "Simple Python Example" << std::endl;
    std::cout << "====================" << std::endl;

    // Create C++ data
    DataProcessor processor;
    processor.addDataPoint(DataPoint("Point A", 10, 1.0, 2.0));
    processor.addDataPoint(DataPoint("Point B", 20, 3.0, 4.0));

    // Print initial data
    std::cout << "Initial data in C++:" << std::endl;
    for (const auto& point : processor.getData()) {
        std::cout << point.toString() << std::endl;
    }
    std::cout << "Sum: " << processor.calculateSum() << std::endl;
    std::cout << "Average: " << processor.calculateAverage() << std::endl;
    std::cout << std::endl;

    // Write data to file for Python to read
    std::cout << "Writing data to file for Python..." << std::endl;
    writeDataToFile(processor, "cpp_data.txt");

    // Run Python script to process the data
    std::cout << "Running Python script to process data..." << std::endl;
    int result = system("..\\python-3.10.11\\python.exe assets/scripts/simple_python_example.py");
    if (result != 0) {
        std::cerr << "Error running Python script. Error code: " << result << std::endl;
        return 1;
    }

    // Read processed data from Python
    std::cout << "Reading processed data from Python..." << std::endl;
    readDataFromFile(processor, "python_data.txt");

    // Print processed data
    std::cout << "Data after Python processing:" << std::endl;
    for (const auto& point : processor.getData()) {
        std::cout << point.toString() << std::endl;
    }
    std::cout << "Sum: " << processor.calculateSum() << std::endl;
    std::cout << "Average: " << processor.calculateAverage() << std::endl;

    std::cout << "\nSimple Python example completed successfully!" << std::endl;
    return 0;
}
