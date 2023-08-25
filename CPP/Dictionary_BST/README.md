## Files

- `Order.cpp`: Top-level client for pa7. Usage: `./Order <input file> <output file>`. 

- `Dictionary.h`: Header file with class definition for the Dictionary ADT. 

- `Dictionary.cpp`: Implementation file for the Dictionary class/ADT. 

- `DictionaryTest.cpp`: Test client for Dictionary ADT. 

- `Makefile`: Usage:
  - `make`: Compiles `Order`
  - `make DictionaryTest`: Compiles `DictionaryTest`
  - `make clean`: Removes all binaries
  - `make OrderCheck`: Runs `Order` under valgrind on `in5` and `junk5`
  - `make DictionaryCheck`: Runs `DictionaryTest` under valgrind

## Usage

To compile and run the different test clients:

```bash
make                 # Compiles Order
make DictionaryTest  # Compiles DictionaryTest

# To run valgrind checks
make OrderCheck      # Runs Order under valgrind on in5 and junk5
make DictionaryCheck # Runs DictionaryTest under valgrind
