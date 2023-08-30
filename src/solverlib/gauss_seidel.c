#include <math.h>
#include <stdbool.h>

#include "gauss_seidel.h"

PyObject*
gauss_seidel(PyObject *_A, PyObject *_b) {
  int rows = (int) PyList_Size(_b);
  int cols = (int) PyList_Size(PyList_GetItem(_A, 0));

  double **A = malloc(rows * cols * sizeof(double));
  for (int i = 0; i < rows; i++) 
    A[i] = malloc(cols * sizeof(double));

  double  *b = malloc(rows * sizeof(double));
  double  *x = malloc(rows * sizeof(double));

  for (int i = 0; i < rows; i++) {
    PyObject *val = PyList_GetItem(_b, i);
    b[i] = PyFloat_AsDouble(val);
    x[i] = 0;
  }

  for (int i = 0; i < rows; i++) {
    PyObject *row = PyList_GetItem(_A, i);
    for (int j = 0; j < cols; j++) {
      PyObject *val = PyList_GetItem(row, j);
      A[i][j] = PyFloat_AsDouble(val);
    }
  }

  double margin = 1e-10, sum1, sum2, coeff, new_val;

  bool close;

  for (int iterations = 1000; iterations--;) {
      
      close = true;

      for (int i = 0; i < rows; i++) {
        coeff = 1 / A[i][i];
        sum1 = 0;
        sum2 = 0;

        for (int j = 0; j < i; j++)
          sum1 += A[i][j] * x[j]; // already changed values

        for (int j = i + 1; j < cols; j++)
          sum2 += A[i][j] * x[j]; // old values

        new_val = coeff * (b[i] - sum1 - sum2);
        if (fabs(x[i] - new_val) < margin) close = false; 
        x[i] = new_val;
      }

      if (!close) break;
  }

  PyObject* ret = PyList_New(rows);

  for (int i = 0; i < rows; i++) {
    PyObject *val = Py_BuildValue("d", x[i]);
    PyList_SetItem(ret, i, val);
  }
  
  for (int i = 0; i < rows; i++) free(A[i]); 
  free(A);
  free(b);
  free(x);
  
  return ret;
}