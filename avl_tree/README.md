Author: Keaton Morales
Date: 20OCT2025
Class: CSCE 2110 Data Structures and Algorithms

This project implements a self balancing AVL Tree using an iterative stack based approach for insertion and deletion of nodes.
Using rotations maintains the balance and keeping O(log n) for insert and delete operations.

Files:
	* avl.cpp - insert, remove, rebalance, print, and rotation functions
	* avl.h - declarations
	* input1.txt - example input file 

Compile:

	* g++ -std=c++0x avl.cpp || g++ avl.h avl.cpp -o avl_tree

Run with file:

	* ./a.out input1.txt || ./avl_tree.exe input1.txt

Note:

	* Duplicate values are not allowed
	* Balancing occurs with each insert, remove operation using a stack to track the path
