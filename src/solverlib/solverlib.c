#include <Python.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include "gauss_seidel.h"
#include "jacobi.h"

static PyObject*
py_gauss_seidel(PyObject *self, PyObject *args) 
{
  PyObject *A, *b;

  if (!PyArg_ParseTuple(args, "OO", &A, &b)) {
    return NULL;
  }
  PyObject *ret = gauss_seidel(A, b);

  return ret;
}

static PyObject*
py_jacobi(PyObject *self, PyObject *args) 
{
  PyObject *A, *b;

  if (!PyArg_ParseTuple(args, "OO", &A, &b)) {
    return NULL;
  }
  PyObject *ret = jacobi(A, b);

  return ret;
}

static PyMethodDef SolverlibMethods[] = 
{
  { "jacobi", py_jacobi, METH_VARARGS, "Jacobi method, computes x solution to A and b" },
  { "gauss_seidel", py_gauss_seidel, METH_VARARGS, "Gauss-Seidel method, computes x solution to A and b" },
  { NULL }
};

static struct PyModuleDef SolverlibModule = 
{
  PyModuleDef_HEAD_INIT,
  "solverlib",
  "Jacobi and Gauss-Seidel method linear solutions",
  -1,
  SolverlibMethods
};

PyMODINIT_FUNC 
PyInit_solverlib(void)
{
  return PyModule_Create(&SolverlibModule);
};