# Hash Table

Simple Hash Table implemented in C99. Public header ansi-C compatible.

## Build

	clang -std=c99 -pedantic -Wall -c hash_table.c

## Implementation

This hash table is created with two arguments representing power of twos of two important data structures:
- The hash table's buckets array
- A bucket's default size

The hash table's bucket array is of fixed size, whereas each bucket is dynamically resized when filled.
In theory, the optimal size is the next power of two after your average objects count (if each keys are considered in an equally distributed range).

