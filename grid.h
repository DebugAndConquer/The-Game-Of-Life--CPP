/**
 * Declares a class representing a 2d grid of cells.
 * Rich documentation for the api and behaviour the Grid class can be found in grid.cpp.
 *
 * The test suites provide granular BDD style (Behaviour Driven Development) test cases
 * which will help further understand the specification you need to code to.
 *
 * @author 965217
 * @date March, 2020
 */
#pragma once

// Add the minimal number of includes you need in order to declare the class.
// #include ...
#include <iostream>
#include <vector>

/**
 * A Cell is a char limited to two named values for Cell::DEAD and Cell::ALIVE.
 */
enum Cell : char {
    DEAD  = ' ',
    ALIVE = '#'
};

/**
 * Declare the structure of the Grid class for representing a 2d grid of cells.
 */
class Grid {
    // How to draw an owl:
    //      Step 1. Draw a circle.
    //      Step 2. Draw the rest of the owl.
private:
    int width,height;
    std::vector<Cell> grid;                    // 2D Vector for storing the grid
    int get_index(const int x , const int y) const ;       // Gets 1D index of a 2D coordinate
public:
    // Public functions
    Grid();                                              // Default Constructor with grid size = 0
    explicit Grid(const int square_size);               // Overloaded Constructor with grid size = squareSize*squareSize
    Grid(const int width, const int height);           // Overloaded Constructor with grid size = width*height
    Cell& operator() (const int x, const int y);
    Cell& operator() (const int x, const int y) const;

    // Member Functions
    int get_width() const ;
    int get_height() const ;
    int get_total_cells() const ;
    int get_alive_cells() const ;
    int get_dead_cells() const ;
    void resize(const int square_size);             // Resize the grid with new width=height
    void resize(const int width, const int height); // Resize the grid with new width and new height
    Cell get(const int x, const int y) const;       // Returns the value of the cell at the desired coordinate
    void set(const int x, const int y,
            const Cell value) const;                // Updates the value of the cell at the desired coordinate
};