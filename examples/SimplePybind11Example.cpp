#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <string>
#include <vector>

namespace py = pybind11;

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

    void updateValue(int newValue) {
        value = newValue;
    }

    void updateCoordinates(double new_x, double new_y) {
        x = new_x;
        y = new_y;
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

// Create the Python module
PYBIND11_MODULE(cpp_data, m) {
    m.doc() = "Simple pybind11 example module for TwoDEngine";

    // Expose the DataPoint class to Python
    py::class_<DataPoint>(m, "DataPoint")
        .def(py::init<const std::string&, int, double, double>())
        .def("toString", &DataPoint::toString)
        .def("updateValue", &DataPoint::updateValue)
        .def("updateCoordinates", &DataPoint::updateCoordinates)
        .def_readwrite("name", &DataPoint::name)
        .def_readwrite("value", &DataPoint::value)
        .def_readwrite("x", &DataPoint::x)
        .def_readwrite("y", &DataPoint::y);

    // Expose the DataProcessor class to Python
    py::class_<DataProcessor>(m, "DataProcessor")
        .def(py::init<>())
        .def("addDataPoint", &DataProcessor::addDataPoint)
        .def("clearData", &DataProcessor::clearData)
        .def("getData", &DataProcessor::getData, py::return_value_policy::reference)
        .def("calculateSum", &DataProcessor::calculateSum)
        .def("calculateAverage", &DataProcessor::calculateAverage);
}
