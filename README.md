# Word Ladder Solver & Game (C++)

## Project Overview
This project is a C++ program that allows users to build and solve word ladders. 
A word ladder is a sequence of words where each step changes only one letter while still forming a valid English word. 
The goal is to transform a starting word into a final word using the shortest possible sequence. 
For example, a ladder can transform "data" into "code" by changing one letter at a time. 
The program includes both an interactive game mode and an automatic solver that guarantees the shortest path. 
This project demonstrates problem solving, data structures, and algorithm design. It also focuses heavily on memory management and efficiency.

## What the Program Does
The program first loads a dictionary file and filters words based on a user-selected length. 
It then allows the user to either play a game where they manually build a word ladder or skip directly to solving. 
In game mode, the user enters words step-by-step, and the program checks if each word is valid. After the game ends, the solver runs and finds the shortest possible ladder between the two words. 
The final ladder is displayed clearly with visual indicators showing which letters changed. If no ladder exists, the program informs the user.

## How It Was Built
This project was built in C++ using dynamic memory allocation and custom data structures. 
Linked lists are used to represent individual word ladders, and a separate linked list structure is used to manage multiple ladders during the solving process. 
The solver is implemented using a breadth-first search algorithm,

 which guarantees the shortest path. The program also uses binary search to efficiently find words in the dictionary. 
Careful memory management was required to avoid leaks, including freeing all allocated nodes and arrays.

## Key Features & Concepts
- Linked Lists
- Dynamic Memory Management
- Binary Search for dictionary lookup
- String comparison and validation logic
- Interactive user input and validation system

## Challenges & Debugging
One of the biggest challenges was managing memory correctly while copying and freeing ladders during the BFS process. 
It was easy to accidentally create memory leaks or free memory too early. 
Another challenge was ensuring that words were only used once to avoid infinite loops in the algorithm. 
Debugging required testing individual functions like string comparison and ladder copying. 
I also tested the program using smaller dictionaries before scaling up to larger ones. 
These steps helped ensure correctness and efficiency.

DEMO/SMALL EXPLANATION:

https://github.com/user-attachments/assets/a2cfab33-5055-43c7-bc1b-e01467c34825

