This project is focusing on AVL Tree implementation and is the 4th project in Advanced Data Structures and Algorithms (CMSC 3613) at the University of Central Oklahoma. 

This project implements the core balancing and deletion operations for an AVL (Adelson-Velsky and Landis) tree in C++. The program builds upon a provided Binary Search Tree (BST) framework, adding the self-balancing logic required for an AVL tree.

## Implemented Functions

This implementation successfully completes the three "TODO" functions within the `avl_tree.h` file:

* **`rotate_right()`**: Performs a single right rotation on a given subtree root. This function is used to correct a left-heavy imbalance (a balance factor of +2) when the left child is also left-heavy (or balanced).
* **`left_balance()`**: This function is called when a subtree becomes left-heavy (balance factor of +2) after an insertion or deletion. It checks the balance factor of the left child to determine whether a single `rotate_right()` or a double `left_right()` rotation (a `rotate_left()` followed by a `rotate_right()`) is necessary to restore the AVL property.
* **`avl_delete()`**: This function recursively finds and deletes a node from the tree. It uses the standard BST deletion logic and then proceeds to update balance factors on its way back up the recursion stack. It uses the `shorter` boolean flag to signal when a subtree's height has decreased. If an imbalance is detected, it calls `left_balance()` or `right_balance()` to rebalance the tree.

## Compilation

This program is written in standard C++ and can be compiled using `g++`. The executable **must** be named `p04` as per the project requirements.

To compile the program, navigate to the directory containing the source files (`.h` and `.cpp` files) and run the following command:

`make`

To run the program (choosing 1 the 2 given files):
`./p04.exe input1.dat`
`./p04.exe input2.dat`

The expected output:

++++++++++++++++++++++

92: 90 95

90: 70 -

95: 93 110

++++++++++++++++++++++
