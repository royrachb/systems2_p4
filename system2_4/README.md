# Tree Visualization Project

This project implements a generic tree data structure with various traversal algorithms and a graphical user interface (GUI) to display the tree using the SFML library.

## Project Structure

- **Demo.cpp**: Demonstrates the functionality of the tree and its GUI.
- **Test.cpp**: Contains tests for the tree functionalities.
- **tree.hpp / tree.tpp**: Defines the `Tree` class with various traversal iterators (PreOrder, PostOrder, BFS, DFS, InOrder).
- **node.hpp / node.tpp**: Defines the `Node` class used in the tree structure.
- **gui.hpp / gui.tpp**: Provides the GUI implementation using SFML for tree visualization.
- **Makefile**: Contains build rules for compiling the project.

## Requirements

- **SFML**: The Simple and Fast Multimedia Library (SFML) is required to run the GUI. You can install it via your package manager or from the [SFML website](https://www.sfml-dev.org/download.php).

## Compilation

To compile the project, use the provided `Makefile`. It includes targets for building the demo and test executables.

### Makefile Targets

- **all**: Builds both the demo and test executables.
- **demo**: Compiles and links the demo program.
- **test**: Compiles and links the test program.
- **clean**: Removes all object files and executables.

### Commands

```sh
# To build everything
make all

# To build the demo
make demo

# To build the tests
make test

# To clean up the build
make clean
