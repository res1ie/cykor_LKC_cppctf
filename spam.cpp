#include <Python.h>
static PyObject* SpamError = nullptr;

static PyObject*
spam_system(PyObject* , PyObject* args) {
    const char* command = nullptr;
    if(!PyArg_ParseTuple(args, "s", &command)) {
        return nullptr;
    }
    const int sts = system(command);
    if(sts != 0) {
        PyErr_SetString(SpamError, "System command failed");
        return nullptr;
    }
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef SpamMethods[] = {
        {"system", spam_system, METH_VARARGS, "Execute a shell command"},
        {nullptr, nullptr, 0, nullptr}
};

static struct PyModuleDef spammodule = {
        PyModuleDef_HEAD_INIT,
        "spam",
        "SPAM SPAM SPAM",
        -1,
        SpamMethods
};

PyMODINIT_FUNC
PyInit_spam() {
    PyObject* module = PyModule_Create(&spammodule);
    if(nullptr == module) return nullptr;
    SpamError = PyErr_NewExceptionWithDoc(
            "spam.error", "Error in spamming", nullptr, nullptr);
    Py_INCREF(SpamError);
    PyModule_AddObject(module, "error", SpamError);
    return module;
}