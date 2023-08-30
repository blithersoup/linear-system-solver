from setuptools import Extension, setup

setup(
    ext_modules = [
        Extension(
            name = "solverlib",
            sources = [
                "src/solverlib/solverlib.c",
                "src/solverlib/jacobi.c",
                "src/solverlib/gauss_seidel.c"
            ]
        ),
    ]
)
