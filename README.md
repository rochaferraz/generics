# Introduction

Tatulib is a generic, type-safe library in plain C that implements common data storage and manipulation algorithms that we usually have to apply to a variety of different implementations. Most of these use cases are embedded systems that don't support or can't fit a complex C++/Python/JVM/Golang system. 

The use of plain C language with generics is known for being _dangerous_ as it mutes most of compiler's ability to issue warnings and tests. The best way we fould of handling this caveat is to use _access_ functions or macros that enforce data types, while keeping the generic `void*`s in the backend. We found that this approach minimizes memory footprint and keeps the knife-throwing, fire-eating within well-contained, tested units.

# Current implementatations
- Stack
- Swap

# Wishlist 
- Queue
- Some good hashing function
- Map
- Graph
- Linked List

# Algorithm Wishlist (To be deployed as Preguilib)

- Quicksort and mergesort
- Binary Tree / BFS / DFS
- Lee algorithm
- Flood fill Algorithm
- Floyd’s Cycle Detection Algorithm
- All-Pairs Shortest Paths — Floyd Warshall Algorithm
- Dijkstra’s Algorithm
- Kruskal’s Algorithm for finding Minimum Spanning Tree
- Kadane’s algorithm

# Installation

- Fetch Google Test submodule
- Build Google Test
	cd googletest
	cmake .
	make
- Build 
	cmake .
	make
