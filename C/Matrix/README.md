## Files

- `List.h`: Header file for the List ADT. 

- `List.c`: Implementation file for the List ADT. 

- `ListTest.c`: Test client for List ADT. 

- `Matrix.c`: Implementation file for the Matrix ADT.

- `Matrix.h`: Header file for the Matrix ADT. 

- `MatrixTest.c`: Test client for the Matrix ADT. 

- `Sparse.c`: Client file for the Matrix ADT. Usage: `./Sparse <input file> <output file>`.

- `Makefile`: Usage:
  - `make`: Compiles `Sparse`
  - `make MatrixTest`: Compiles `MatrixTest`
  - `make ListTest`: Compiles `ListTest`
  - `make clean`: Removes all binaries
  - `make SparseCheck`: Runs `Sparse` in valgrind on `in5`
  - `make MatrixCheck`: Runs `MatrixTest` in valgrind
  - `make ListCheck`: Runs `ListTest` in valgrind

## Usage

To compile and run the different test clients:

```bash
make                 # Compiles Sparse
make MatrixTest      # Compiles MatrixTest
make ListTest        # Compiles ListTest

# To run valgrind checks
make SparseCheck     # Runs Sparse in valgrind on in5
make MatrixCheck     # Runs MatrixTest in valgrind
make ListCheck       # Runs ListTest in valgrind
