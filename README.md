# Introduction

Tatulib is a generic, type-safe library in plain C that implements common data storage and manipulation algorithms that we usually have to apply to a variety of different implementations. Most of these use cases are embedded systems that don't support or can't fit a complex C++/Python/JVM/Golang system. 

The use of plain C language with generics is known for being _dangerous_ as it mutes most of compiler's ability to issue warnings and tests. Thus the best way we found of handling this caveat is the use of _access_ functions or macros that enforce data types, while keeping the generic `void*`s in the backend. We found that this approach minimizes memory footprint and keeps the knife-throwing, fire-eating within well-contained, tested units.

We also wrapped them in several unit tests.

This library tries *not* to rely too much on preprocessing as it often brings its own hydra heads to the problem at hand.

# Current implementatations
- Stack
- Swap
- Swiss Cheese Array

# Wishlist 
- Queue
- Some good hashing function
- Map
- Graph
- Linked List

# Algorithm Wishlist (To be deployed as Preguilib)

- Quicksort and mergesort
- Binary Tree / BFS / DFS
- Balanced Trees
- Lee algorithm
- Flood fill Algorithm
- Floyd’s Cycle Detection Algorithm
- All-Pairs Shortest Paths — Floyd Warshall Algorithm
- Dijkstra’s Algorithm
- Kruskal’s Algorithm for finding Minimum Spanning Tree
- Kadane’s algorithm
- Hamming distance
- Damerau-Levenshtein distance

# Design Templates Wishlist

- Grand Central Dispatcher

# Installation

- Clone repository
```bash
git clone https://github.com/rochaferraz/tatulib.git
```

- Fetch Google Test submodule
```bash
git gubmodule update
```

- Build Google Test
```bash
cd googletest
cmake .
make
```

- Build Tatulib
```bash
cd [your cloned repository folder]
cmake .
make
```
