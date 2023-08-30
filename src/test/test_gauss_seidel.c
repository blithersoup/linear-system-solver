#include <Python.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "../solverlib/gauss_seidel.h"


int main(int argc, char *argv[]) {
    Py_Initialize();
    
    double _A[5][5] = {
      { 15., 2., 0.0, 6.5, 4. },
      { 2., 21.5, -5., 3., 0.0 },
      { -9., 4., 18., 1., -2.4, },
      { 0.0, -4., -1., 16., 3. },
      { 5., 3.1, 6., 1., 17., }
    };

    double _b[5] = {
      -53.,
      103.,
      23.1,
      70.,
      -16.1
    };

    double sol[5] = { -6.5, 4.0, -3.0, 5.0, 1.0 };
    
    PyObject *A = PyList_New(5);

    for (int i = 0; i < 5; i++) {
        PyObject *innerList = PyList_New(5);

        for (int j = 0; j < 5; j++) {
            PyObject *value = PyFloat_FromDouble(_A[i][j]);
            PyList_SetItem(innerList, j, value);
        }

        PyList_SetItem(A, i, innerList);
    }

    PyObject *b = PyList_New(5);
    for (int i = 0; i < 5; i++) {
        PyObject *value = PyFloat_FromDouble(_b[i]);
        PyList_SetItem(b, i, value);
    }
    
    PyObject *ret = gauss_seidel(A, b);
    
    for (int i = 0; i < 5; i++) {
      PyObject *val = PyList_GetItem(ret, i);
      double x = PyFloat_AsDouble(val);
      if (fabs(x - sol[i]) > 1e-5) return 1;
    }

    printf("TESTS PASS\n");
    printf("==============================================\n\n");
    
    Py_Finalize();
}