# Maze Generator

A maze generator is a program that creates mazes from "map" files. You can also create random "map" files.

## Table of Contents

- [Installation](#installation)
- [Structure](#structure)
- [Usage](#usage)
- [Todo](#todo)

## Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/your-username/maze-generator.git
    ```

2. Navigate to the project directory:

    ```bash
    cd maze-generator
    ```

3. Compile the project:

    ```bash
    make compile-all
    ```

You can clean all obj and bin with:

    make clean

## Structure

The "map" files have the following structure:
    • the first line contains the width and the height of the map separated by a space
    • the other lines contains the edges cost for each node of the map (first value for “down” direction, then for “right” direction)

Example:
```
2 2
-5 6
-1 3
11 3
-15 15
```

## Usage

To generate a maze (print and pbm image) from a map file, you can run the command:

    ./bin/app-generate-maze filepath scaling_factor_image

To generate a random map (map file within data_map folder), you can run the following command:

    ./bin/app-generate-random-map width height file_subfix

## Todo

Implement heap to increase speed generation!
