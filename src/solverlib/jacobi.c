#include "jacobi.h"
#include <math.h>
#include <stdbool.h>

PyObject*
jacobi(PyObject *_A, PyObject *_b) {
  int rows = (int) PyList_Size(_b);
  int cols = (int) PyList_Size(PyList_GetItem(_A, 0));

  double **A = malloc(rows * cols * sizeof(double));
  for (int i = 0; i < rows; i++) 
    A[i] = malloc(cols * sizeof(double));

  double  *b = malloc(rows * sizeof(double));
  double  *x = malloc(rows * sizeof(double));
  double  *x_new = malloc(rows * sizeof(double));

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

  double margin = 1e-10, sum, coeff;

  bool close;

  for (int iterations = 1000; iterations--;) {
      
      
      for (int i = 0; i < rows; i++) {
          coeff = 1 / A[i][i];
          sum = 0;

          for (int j = 0; j < cols; j++)
              if (j != i)
                  sum += A[i][j] * x[j];
          
          x_new[i] = coeff * (b[i] - sum);
      }

      close = true;
      for (int i = 0; i < rows; i++) {
          if (fabs(x[i] - x_new[i]) < margin) close = false; 
          x[i] = x_new[i];

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
  free(x_new);
  
  return ret;
}