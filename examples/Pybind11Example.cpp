#include <iostream>
#include <vector>
#include <string>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include <pybind11/stl.h>

namespace py = pybind11;

// A simple data structure to demonstrate C++ to Python data exchange
struct DataPoint {
    std::string name;
    int value;
    double coordinates[2];

    DataPoint(const std::string& n, int v, double x, double y)
        : name(n), value(v) {
        coordinates[0] = x;
        coordinates[1] = y;
    }

    void print() const {
        std::cout << "DataPoint: " << name << ", value=" << value
                  << ", coordinates=(" << coordinates[0] << ", " << coordinates[1] << ")" << std::endl;
    }

    void updateValue(int newValue) {
        value = newValue;
    }

    void updateCoordinates(double x, double y) {
        coordinates[0] = x;
        coordinates[1] = y;
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

    std::vector<DataPoint>& getData() {
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

// Python module definition
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

int main(int argc, char* argv[]) {
    // Start the Python interpreter
    py::scoped_interpreter guard{};

    try {
        std::cout << "Pybind11 Data Exchange Example" << std::endl;
        std::cout << "==============================" << std::endl;

        // Create C++ objects
        DataProcessor processor;
        processor.addDataPoint(DataPoint("Point A", 10, 1.0, 2.0));
        processor.addDataPoint(DataPoint("Point B", 20, 3.0, 4.0));

        std::cout << "Initial data in C++:" << std::endl;
        for (const auto& point : processor.getData()) {
            point.print();
        }
        std::cout << "Sum: " << processor.calculateSum() << std::endl;
        std::cout << "Average: " << processor.calculateAverage() << std::endl;
        std::cout << std::endl;

        // Import the Python script
        std::cout << "Loading Python script..." << std::endl;
        py::module_ dataProcessor;
        try {
            dataProcessor = py::module_::import("assets.scripts.pybind11_data_processor");
            std::cout << "Python script loaded successfully." << std::endl;
        } catch (const py::error_already_set& e) {
            std::cerr << "Error importing Python script: " << e.what() << std::endl;
            std::cerr << "Creating a simple Python module on the fly..." << std::endl;

            // Create a simple Python module on the fly if the import fails
            py::exec(R"(
import cpp_data

def process_data(processor):
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
            )");

            // Get the module from the main namespace
            dataProcessor = py::module_::import("__main__");
        }

        // Pass C++ object to Python and process it
        std::cout << "\nCalling Python function with C++ object..." << std::endl;
        std::string result = dataProcessor.attr("process_data")(py::cast(processor));
        std::cout << "Python returned: " << result << std::endl;

        // Check the modified data back in C++
        std::cout << "\nData after Python processing:" << std::endl;
        for (const auto& point : processor.getData()) {
            point.print();
        }
        std::cout << "Sum: " << processor.calculateSum() << std::endl;
        std::cout << "Average: " << processor.calculateAverage() << std::endl;

        // Create a new data point in Python and pass it back to C++
        std::cout << "\nCreating a new data point in Python and passing it to C++..." << std::endl;
        py::exec(R"(
import cpp_data

# Create a new data point in Python
new_point = cpp_data.DataPoint("Point D", 40, 7.0, 8.0)
        )");

        DataPoint newPoint = py::eval("new_point").cast<DataPoint>();
        processor.addDataPoint(newPoint);

        // Final data check
        std::cout << "\nFinal data in C++:" << std::endl;
        for (const auto& point : processor.getData()) {
            point.print();
        }
        std::cout << "Sum: " << processor.calculateSum() << std::endl;
        std::cout << "Average: " << processor.calculateAverage() << std::endl;

    } catch (const py::error_already_set& e) {
        std::cerr << "Python error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << "\nPybind11 example completed successfully!" << std::endl;

    return 0;
}
