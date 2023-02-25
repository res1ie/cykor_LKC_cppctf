#pragma once

#include <Python.h>
#include "../src/elliptic_curve.h"

static PyObject *py_EC_ADD(PyObject *self, PyObject *args);
static PyObject *py_EC_DOUBLE(PyObject *self, PyObject *args);
static PyObject *py_EC_MUL(PyObject *self, PyObject *args);