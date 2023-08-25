## Files

- `List.h`: Header file for the List ADT. Included in `List.c`, `Lex.c`, and `ListClient.c`.

- `List.c`: Implementation file for the List ADT.

- `ListClient.c`: Test client for the List ADT. 

- `Lex.c`: Client module for the List ADT. 

- `Makefile` Usage:
  - `make`: Compiles `Lex`
  - `make ListClient`: Compiles `ListClient`
  - `make clean`: Removes all binaries
  - `make checkClient`: Checks `ListClient` for memory errors
  - `make checkLex`: Checks `Lex` for memory errors

- `in`: Example input file for `make checkLex`. 

## Usage

To compile `Lex` and `ListClient`:

```bash
make           # Compiles Lex
make ListClient  # Compiles ListClient
