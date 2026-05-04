/*
    pybind11/pybind11.h: Main header file of pybind11

    Copyright (c) 2016 Wenzel Jakob <wenzel.jakob@epfl.ch>

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE file.
*/

#pragma once

#include <Python.h>

namespace py = pybind11;

namespace pybind11 {

// Core functionality
class module_ {
public:
    module_(const char *name) {
        m_ptr = PyModule_New(name);
    }

    ~module_() {
        if (m_ptr)
            Py_DECREF(m_ptr);
    }

    void def(const char *name, PyObject *(*func)(PyObject *, PyObject *)) {
        PyModule_AddObject(m_ptr, name, PyCFunction_New(&m_meth, nullptr));
    }

    template <typename Func>
    void def(const char *name, Func &&f) {
        // Simplified for demonstration
        PyObject *func = PyCFunction_New(&m_meth, nullptr);
        PyModule_AddObject(m_ptr, name, func);
    }

private:
    PyObject *m_ptr = nullptr;
    static PyMethodDef m_meth;
};

// Simplified implementation for demonstration
PyMethodDef module_::m_meth = {
    "dummy", nullptr, METH_VARARGS, nullptr
};

// Function to initialize Python
inline void initialize_interpreter() {
    Py_Initialize();
}

// Function to finalize Python
inline void finalize_interpreter() {
    Py_Finalize();
}

// Function to run a Python script
inline void exec(const char *script) {
    PyRun_SimpleString(script);
}

// Function to run a Python script from a file
inline void exec_file(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp) {
        PyRun_SimpleFile(fp, filename);
        fclose(fp);
    }
}

} // namespace pybind11
