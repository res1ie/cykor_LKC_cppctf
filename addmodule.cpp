#include <Python.h>

// Define the method "add" which takes two integer arguments and returns their sum
static PyObject* add(PyObject* self, PyObject* args) {
    long int x, y;
    
    // Parse the arguments as integers
    if (!PyArg_ParseTuple(args, "ll", &x, &y)) {
        return NULL;
    }
    
    // Compute the sum and return it as a new Python integer object
    PyObject* sum = PyLong_FromLong(x + y);
    return sum;
}

// Define the module methods
static PyMethodDef AddMethods[] = {
    {"add", add, METH_VARARGS, "Add two integers."},
    {NULL, NULL, 0, NULL}  // sentinel to indicate end of methods
};

// Define the module structure
static struct PyModuleDef addmodule = {
    PyModuleDef_HEAD_INIT,
    "add",   // name of the module
    NULL,    // module documentation
    -1,      // size of the per-interpreter state of the module, or -1 if the module keeps state in global variables.
    AddMethods
};

// Create the module object
PyMODINIT_FUNC PyInit_add(void) {
    return PyModule_Create(&addmodule);
}