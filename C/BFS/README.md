# Programming Assignment 2: Introduction to Data Structures and Algorithms

Programming Assignment 2 for the Introduction to Data Structures and Algorithms course by Morgan Lloyd (moclloyd@ucsc.edu).

## Files Submitted

- `List.h`: Header file for the List ADT. Included in `List.c`, `FindPath.c`, `Graph.c`, `Graph.h`, and `GraphTest.c`. Written by me.

- `List.c`: Implementation file for the List ADT. Written by me. Some areas were referenced from the `Queue.c` example.

- `Graph.c`: Implementation file for the Graph ADT. Written by me. Pseudocode on the webpage was referenced.

- `Graph.h`: Header file for the Graph ADT. Included in `Graph.c`, `FindPath.c`, and `GraphTest.c`.

- `GraphTest.c`: Test client for Graph ADT. Written by me.

- `FindPath.c`: Client program using the Graph ADT. Finds shortest paths between pairs of vertices. Usage: `./FindPath <input file> <output file>`.

- `Makefile`: Makefile for the assignment. Written by me. Usage:
  - `make`: Compiles `FindPath`
  - `make GraphClient`: Compiles `GraphClient`
  - `make clean`: Removes all binaries
  - `make checkFind`: Checks `FindPath` for memory leaks on `in7`
  - `make checkClient`: Checks `GraphClient` for memory leaks

## Usage

To compile `FindPath` and `GraphClient`:

```bash
make             # Compiles FindPath
make GraphClient  # Compiles GraphClient
