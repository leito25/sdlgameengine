#include <pybind11/embed.h>
#include <iostream>

namespace py = pybind11;

int main(int argc, char* argv[]) {
    py::scoped_interpreter guard{};

    py::exec("result = 2 + 2");
    int result = py::globals()["result"].cast<int>();

    std::cout << "✓ Python initialized successfully!" << std::endl;
    std::cout << "✓ pybind11 is working!" << std::endl;
    std::cout << "Python computed: 2 + 2 = " << result << std::endl;

    return 0;
}
