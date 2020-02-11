# cellular-automaton 👾

A simple C++ implementation of the John Horton Conway's **game of life**.

## Concept and rules

This program generates a grid of a certain size, divided into cells. Each cell embodies a living cell which can be in two different states: dead or alive.

The initial state is randomly set but each new generation is calculated following a set of rules:
* a dead cell with exactly three neighboring living cells becomes alive;
* a living cell with two or three neighboring living cells stays alive, else it dies.

## Installation

### Requirements

This project was made using the SFML (2.5) library.

You will need the SFML headers to generate the binary. You can download them on the SFML website: https://www.sfml-dev.org/download-fr.php

### Build

Run 
```
make
``` 
in the project directory to generate a binary called `automaton`.
