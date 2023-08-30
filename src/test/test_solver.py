from solverlib import jacobi, gauss_seidel
import pytest

A_1 = [
    [ 15., 2., 0.0, 6.5, 4. ],
    [ 2., 21.5, -5., 3., 0.0 ],
    [ -9., 4., 18., 1., -2.4, ],
    [ 0.0, -4., -1., 16., 3. ],
    [ 5., 3.1, 6., 1., 17., ]
]

b_1 = [
    -53.,
    103.,
    23.1,
    70.,
    -16.1
]

x_1 = [ -6.5, 4.0, -3.0, 5.0, 1.0 ]

A_2 = [
    [10., -1., 2., 0.],
    [-1., 11., -1., 3.],
    [2., -1., 10., -1.],
    [0.0, 3., -1., 8.]
]

b_2 = [ 6., 25., -11., 15. ]

x_2 = [ 1., 2., -1., 1. ]


@pytest.mark.parametrize("A,b,x", [
    (A_1, b_1, x_1),
    (A_2, b_2, x_2)
])
def test_jacobi(A, b, x):
    ret = jacobi(A, b)
    ret = [round(val, 2) for val in ret]
    assert ret == x

@pytest.mark.parametrize("A,b,x", [
    (A_1, b_1, x_1),
    (A_2, b_2, x_2)
])
def test_gauss_seidel(A, b, x):
    ret = gauss_seidel(A, b)
    ret = [round(val, 2) for val in ret]
    assert ret == x