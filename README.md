# Introduction

Generics is a generic type library in plain C that implements common algorithms that I usually have to apply to a variety of different implementations. Most of these use cases are embedded systems that don't support or can't fit a complex C++/Python/JVM/Golang system. 

The use of plain C language with generics is known for being _dangerous_ as it mutes most of compiler's ability to issue warnings and tests. The best way I fould of handling this caveat is to use _access_ functions or macros that enforce data types, while keeping the generic `void*`s in the backend. I found that this approach minimizes memory footprint and keeps the knife-throwing, fire-eating within well-contained, tested units.

# Current implementatations
- Stack
- Swap

# Wishlist
- Queue
- Some good hashing
- Map
- Graph
- Linked List
- Quicksort and mergesort
- Binary Tree / BFS / DFS
- Lee algorithm
- Flood fill Algorithm
- Floyd’s Cycle Detection Algorithm
- All-Pairs Shortest Paths — Floyd Warshall Algorithm
- Dijkstra’s Algorithm
- Kruskal’s Algorithm for finding Minimum Spanning Tree

# Non-generic wishlist
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
