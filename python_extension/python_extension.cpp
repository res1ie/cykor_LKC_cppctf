#include "python_extension.h"

static PyObject *py_EC_ADD(PyObject *self, PyObject *args)
{
    char *p_str, *a_str, *b_str, *x1_str, *y1_str, *x2_str, *y2_str;
    if (!PyArg_ParseTuple(args, "sssssss", &p_str, &a_str, &b_str, &x1_str, &y1_str, &x2_str, &y2_str))
        return NULL;

    mpz_class p(p_str), a(a_str), b(b_str), x1(x1_str), y1(y1_str), x2(x2_str), y2(y2_str);
    EC_point P1(x1, y1, false), P2(x2, y2, false), Q = EC_ADD(p, a, b, P1, P2);

    if (Q.isO)
        return Py_BuildValue("s", "O");

    return Py_BuildValue("ss", (Q.x).get_str().c_str(), (Q.y).get_str().c_str());
}

static PyObject *py_EC_DOUBLE(PyObject *self, PyObject *args)
{
    char *p_str, *a_str, *b_str, *x_str, *y_str;
    if (!PyArg_ParseTuple(args, "sssss", &p_str, &a_str, &b_str, &x_str, &y_str))
        return NULL;

    mpz_class p(p_str), a(a_str), b(b_str), x(x_str), y(y_str);
    EC_point P(x, y, false), Q = EC_DOUBLE(p, a, b, P);

    if (Q.isO)
        return Py_BuildValue("s", "O");

    return Py_BuildValue("ss", (Q.x).get_str().c_str(), (Q.y).get_str().c_str());
}

static PyObject *py_EC_MUL(PyObject *self, PyObject *args)
{
    char *p_str, *a_str, *b_str, *x_str, *y_str, *c_str;
    if (!PyArg_ParseTuple(args, "sssssss", &p_str, &a_str, &b_str, &x_str, &y_str, &c_str))
        return NULL;

    mpz_class p(p_str), a(a_str), b(b_str), x(x_str), y(y_str), c(c_str);
    EC_point P(x, y, false), Q = EC_MUL(p, a, b, P, c);

    if (Q.isO)
        return Py_BuildValue("s", "O");

    return Py_BuildValue("ss", (Q.x).get_str().c_str(), (Q.y).get_str().c_str());
}

static PyMethodDef methods[] = {
    {"EC_ADD", py_EC_ADD, METH_VARARGS, "Add two points on an elliptic curve."},
    {"EC_DOUBLE", py_EC_DOUBLE, METH_VARARGS, "Double a point on an elliptic curve."},
    {"EC_MUL", py_EC_MUL, METH_VARARGS, "Multiply a point on an elliptic curve by a scalar."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "elliptic_curve.python_extension",
    NULL,
    -1,
    methods
};

PyMODINIT_FUNC PyInit_python_extension(void)
{
    return PyModule_Create(&moduledef);
}