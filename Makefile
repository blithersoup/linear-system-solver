.PHONY: build test

build: 
	python3 -m venv .venv
	. .venv/bin/activate
	python3 -m pip install build
	python3 -m build .
	python3 -m pip install dist/*.whl --force-reinstall

test: build
	. .venv/bin/activate
	pytest
	gcc $(shell python3-config --cflags --embed --ldflags) src/solverlib/gauss_seidel.c src/test/test_gauss_seidel.c -o dist/test_gauss_seidel
	gcc $(shell python3-config --cflags --embed --ldflags) src/solverlib/jacobi.c src/test/test_jacobi.c -o dist/test_jacobi
	dist/test_jacobi
	dist/test_gauss_seidel
