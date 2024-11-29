# BTree Implementation in C++

This project is an implementation of a **BTree** data structure in standard C++. The BTree is a self-balancing search tree that maintains sorted data and allows for efficient insertion, deletion, and search operations. This implementation is generic, supports various data types, and works for any specified order.

## Features
- **Generic Data Types**: Works with any data type (e.g., `int`, `float`, `string`, etc.).
- **Configurable Order**: The order of the BTree can be specified during instantiation.
- **Efficient Operations**:
    - Insert: \(O(\log n)\)
    - Print: \(O(n)\)
- **Custom Implementation**: No external libraries (except basic input/output) are used.

## How It Works
The BTree is implemented using two classes:
1. `BTreeNode`: Represents a single node in the BTree.
2. `BTree`: Manages the overall tree structure and provides methods for insertion and in-order traversal.

### Operations
- **Insert(T key)**: Inserts a key into the BTree.
- **Print()**: Prints all the keys in the tree in sorted order (in-order traversal).
