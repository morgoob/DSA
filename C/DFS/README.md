## Files

- `List.h`: Header file for the List ADT. Included in `List.c`, `Graph.c`, `Graph.h`, `GraphTest.c`, and `FindComponents.c`.

- `List.c`: Implementation file for the List ADT. 

- `Graph.c`: Implementation file for the Graph ADT. In function `DFS()`, `time` is local, and `&time` is passed to `Visit()`.

- `Graph.h`: Header file for the Graph ADT. Included in `Graph.c`, `GraphTest.c`, and `FindComponents.c`.

- `GraphTest.c`: Test client for Graph ADT. 

- `FindComponents.c`: Client program using the Graph ADT. Finds strongly connected components of a digraph. Usage: `./FindComponents <input file> <output file>`.

- `Makefile` Usage:
  - `make`: Compiles `FindPath`
  - `make GraphTest`: Compiles `GraphTest`
  - `make clean`: Removes all binaries
  - `make checkFind`: Checks `FindComponents` for memory leaks
  - `make checkTest`: Checks `GraphTest` for memory leaks

## Usage

To compile `FindComponents` and `GraphTest`:

```bash
make                 # Compiles FindComponents
make GraphTest       # Compiles GraphTest
