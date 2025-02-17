/**
 * Implements a class representing a 2d grid of cells.
 *      - New cells are initialized to Cell::DEAD.
 *      - Grids can be resized while retaining their contents in the remaining area.
 *      - Grids can be rotated, cropped, and merged together.
 *      - Grids can return counts of the alive and dead cells.
 *      - Grids can be serialized directly to an ascii std::ostream.
 *
 * You are encouraged to use STL container types as an underlying storage mechanism for the grid cells.
 *
 * @author 965217
 * @date March, 2020
 */
#include "grid.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

/**
 * Grid::Grid()
 *
 * Construct an empty grid of size 0x0.
 * Can be implemented by calling Grid::Grid(square_size) constructor.
 *
 * @example
 *
 *      // Make a 0x0 empty grid
 *      Grid grid;
 *
 */

Grid::Grid() : Grid(0, 0) {
}

/**
 * Grid::Grid(square_size)
 *
 * Construct a grid with the desired size filled with dead cells.
 * Single value constructors should be marked "explicit" to prevent them
 * being used to implicitly cast ints to grids on construction.
 *
 * Can be implemented by calling Grid::Grid(width, height) constructor.
 *
 * @example
 *
 *      // Make a 16x16 grid
 *      Grid x(16);
 *
 *      // Also make a 16x16 grid
 *      Grid y = Grid(16);
 *
 *      // This should be a compiler error! We want to prevent this from being allowed.
 *      Grid z = 16;
 *
 * @param square_size
 *      The edge size to use for the width and height of the grid.
 */
Grid::Grid(const int square_size) : Grid(square_size, square_size) {
}

/**
 * Grid::Grid(width, height)
 *
 * Construct a grid with the desired size filled with dead cells.
 *
 * @example
 *
 *      // Make a 16x9 grid
 *      Grid grid(16, 9);
 *
 * @param width
 *      The width of the grid.
 *
 * @param height
 *      The height of the grid.
 */
Grid::Grid(const int width, const int height) : width(width), height(height) {
    // If the grid is of size 0*0 then it's simply empty
    if (this->width == 0 && this->height == 0) {
        this->grid.empty();
    } else {
        this->grid = std::vector<Cell>((width * height), Cell::DEAD);
    }
}

/**
 * Grid::get_width()
 *
 * Gets the current width of the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the width of the grid to the console
 *      std::cout << grid.get_width() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the width of the grid to the console
 *      std::cout << read_only_grid.get_width() << std::endl;
 *
 * @return
 *      The width of the grid.
 */
int Grid::get_width() const {
    return this->width;
}

/**
 * Grid::get_height()
 *
 * Gets the current height of the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the height of the grid to the console
 *      std::cout << grid.get_height() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the height of the grid to the console
 *      std::cout << read_only_grid.get_height() << std::endl;
 *
 * @return
 *      The height of the grid.
 */

int Grid::get_height() const {
    return this->height;
}

/**
 * Grid::get_total_cells()
 *
 * Gets the total number of cells in the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the total number of cells on the grid to the console
 *      std::cout << grid.get_total_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the total number of cells on the grid to the console
 *      std::cout << read_only_grid.get_total_cells() << std::endl;
 *
 * @return
 *      The number of total cells.
 */
int Grid::get_total_cells() const {
    const int total = this->width * this->height;
    return total;
}

/**
 * Grid::get_alive_cells()
 *
 * Counts how many cells in the grid are alive.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the number of alive cells to the console
 *      std::cout << grid.get_alive_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the number of alive cells to the console
 *      std::cout << read_only_grid.get_alive_cells() << std::endl;
 *
 * @return
 *      The number of alive cells.
 */
int Grid::get_alive_cells() const {
    const int sum = std::count(grid.begin(), grid.end(), Cell::ALIVE);
    return sum;
}

/**
 * Grid::get_dead_cells()
 *
 * Counts how many cells in the grid are dead.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the number of dead cells to the console
 *      std::cout << grid.get_dead_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the number of dead cells to the console
 *      std::cout << read_only_grid.get_dead_cells() << std::endl;
 *
 * @return
 *      The number of dead cells.
 */

int Grid::get_dead_cells() const {
    return (get_total_cells() - get_alive_cells());
}

/**
 * Grid::resize(square_size)
 *
 * Resize the current grid to a new width and height that are equal. The content of the grid
 * should be preserved within the kept region and padded with Grid::DEAD if new cells are added.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Resize the grid to be 8x8
 *      grid.resize(8);
 *
 * @param square_size
 *      The new edge size for both the width and height of the grid.
 */

void Grid::resize(const int square_size) {
    resize(square_size, square_size);
}

/**
 * Grid::resize(width, new_height)
 *
 * Resize the current grid to a new width and new_height. The content of the grid
 * should be preserved within the kept region and padded with Grid::DEAD if new cells are added.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Resize the grid to be 2x8
 *      grid.resize(2, 8);
 *
 * @param new_width
 *      The new width for the grid.
 *
 * @param new_height
 *      The new new_height for the grid.
 */

void Grid::resize(const int new_width, const int new_height) {
    if (this->width == new_width && this->height == new_height) {
        std::cout << "The new grid size is the same as the old one!";
    }
    //Creating new Grid to store resized data
    Grid g(new_width, new_height);
    // If the resized vector is smaller than the original
    if (new_width * new_height < this->width * this->get_height()) {
        for (int i = 0; i < new_height; i++) {
            for (int j = 0; j < new_width; j++) {
                // Mapping 1D representation of a vector to a 2D one
                const int idx = j + (i * new_width);
                const int newX = idx % new_width;
                const int newY = (idx - j) / new_width;
                // Cloning values from old vector to a new one w.r.t new coordinates
                g(newX, newY) = this->get(j, i);
            }
        }
        // Alternatively if the resized vector is larger than the original
    } else {
        for (int i = 0; i < this->height; i++) {
            for (int j = 0; j < this->width; j++) {
                // Mapping 1D representation of a vector to a 2D one
                const int idx = j + (i * new_width);
                const int newX = idx % new_width;
                const int newY = (idx - j) / new_width;
                // Cloning values from old vector to a new one w.r.t new coordinates
                g(newX, newY) = this->get(j, i);
            }
        }
    }
    // Updating fields
    this->width = new_width;
    this->height = new_height;
    this->grid = g.grid;
}

/**
 * Grid::get_index(x, y)
 *
 * Private helper function to determine the 1d index of a 2d coordinate.
 * Should not be visible from outside the Grid class.
 * The function should be callable from a constant context.
 *
 * @param x
 *      The x coordinate of the cell.
 *
 * @param y
 *      The y coordinate of the cell.
 *
 * @return
 *      The 1d offset from the start of the data array where the desired cell is located.
 */
int Grid::get_index(const int x, const int y) const {
    const int index = y * this->width + x;
    return index;
}

/**
 * Grid::get(x, y)
 *
 * Returns the value of the cell at the desired coordinate.
 * Specifically this function should return a cell value, not a reference to a cell.
 * The function should be callable from a constant context.
 * Should be implemented by invoking Grid::operator()(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Read the cell at coordinate (1, 2)
 *      Cell cell = grid.get(1, 2);
 *
 * @param x
 *      The x coordinate of the cell to update.
 *
 * @param y
 *      The y coordinate of the cell to update.
 *
 * @return
 *      The value of the desired cell. Should only be Grid::ALIVE or Grid::DEAD.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */

Cell Grid::get(const int x, const int y) const {
    if (x >= this->width || x < 0) throw std::exception();
    if (y >= this->height || y < 0) throw std::exception();

    const Cell value = (*this)(x, y);
    return value;
}

/**
 * Grid::set(x, y, value)
 *
 * Overwrites the value at the desired coordinate.
 * The function should be callable from a constant context.
 * Should be implemented by invoking Grid::operator()(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Assign to a cell at coordinate (1, 2)
 *      grid.set(1, 2, Cell::ALIVE);
 *
 * @param x
 *      The x coordinate of the cell to update.
 *
 * @param y
 *      The y coordinate of the cell to update.
 *
 * @param value
 *      The value to be written to the selected cell.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */

void Grid::set(const int x, const int y, const Cell value) {
    if (x >= this->width || x < 0) throw std::exception();
    if (y >= this->height || y < 0) throw std::exception();
    this->operator()(x, y) = value;
}

/**
 * Grid::operator()(x, y)
 *
 * Gets a modifiable reference to the value at the desired coordinate.
 * Should be implemented by invoking Grid::get_index(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Get access to read a cell at coordinate (1, 2)
 *      Cell cell = grid(1, 2);
 *
 *      // Directly assign to a cell at coordinate (1, 2)
 *      grid(1, 2) = Cell::ALIVE;
 *
 *      // Extract a reference to an individual cell to avoid calculating it's
 *      // 1d index multiple times if you need to access the cell more than once.
 *      Cell &cell_reference = grid(1, 2);
 *      cell_reference = Cell::DEAD;
 *      cell_reference = Cell::ALIVE;
 *
 * @param x
 *      The x coordinate of the cell to access.
 *
 * @param y
 *      The y coordinate of the cell to access.
 *
 * @return
 *      A modifiable reference to the desired cell.
 *
 * @throws
 *      std::runtime_error or sub-class if x,y is not a valid coordinate within the grid.
 */
Cell &Grid::operator()(const int x, const int y) {
    if (x >= this->width || x < 0) throw std::runtime_error(std::string("x is out of bounds!"));
    if (y >= this->height || y < 0) throw std::runtime_error(std::string("y is out of bounds!"));

    const int t = this->get_index(x, y);
    return grid[t];
}

/**
 * Grid::operator()(x, y)
 *
 * Gets a read-only reference to the value at the desired coordinate.
 * The operator should be callable from a constant context.
 * Should be implemented by invoking Grid::get_index(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Constant reference to a grid (does not make a copy)
 *      const Grid &read_only_grid = grid;
 *
 *      // Get access to read a cell at coordinate (1, 2)
 *      Cell cell = read_only_grid(1, 2);
 *
 * @param x
 *      The x coordinate of the cell to access.
 *
 * @param y
 *      The y coordinate of the cell to access.
 *
 * @return
 *      A read-only reference to the desired cell.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */

Cell &Grid::operator()(const int x, const int y) const {
    if (x >= this->width || x < 0) throw std::runtime_error(std::string("x is out of bounds!"));

    if (y >= this->height || y < 0) throw std::runtime_error(std::string("y is out of bounds"));

    const int t = this->get_index(x, y);
    const Cell &res = grid[t];
    return const_cast<Cell &>(res);

}

/**
 * Grid::crop(x0, y0, x1, y1)
 *
 * Extract a sub-grid from a Grid.
 * The cropped grid spans the range [x0, x1) by [y0, y1) in the original grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid y(4, 4);
 *
 *      // Crop the centre 2x2 in y, trimming a 1 cell border off all sides
 *      Grid x = y.crop(x, 1, 1, 3, 3);
 *
 * @param x0
 *      Left coordinate of the crop window on x-axis.
 *
 * @param y0
 *      Top coordinate of the crop window on y-axis.
 *
 * @param x1
 *      Right coordinate of the crop window on x-axis (1 greater than the largest index).
 *
 * @param y1
 *      Bottom coordinate of the crop window on y-axis (1 greater than the largest index).
 *
 * @return
 *      A new grid of the cropped size containing the values extracted from the original grid.
 *
 * @throws
 *      std::exception or sub-class if x0,y0 or x1,y1 are not valid coordinates within the grid
 *      or if the crop window has a negative size.
 */

Grid Grid::crop(const int x0, const int y0, const int x1, const int y1) {
    if (x0 > this->get_width() || x0 < 0 ||
        x1 > this->get_width() || x1 < 0 ||
        y0 > this->get_height() || y0 < 0 ||
        y1 > this->get_height() || y1 < 0) {
        throw std::runtime_error(std::string("One of the arguments is not a valid coordinate!"));
    }
    // Get the size of the new grid
    const int cropped_width = x1 - x0;
    const int cropped_height = y1 - y0;
    if (cropped_width < 0 || cropped_height < 0) {
        throw std::runtime_error(std::string("A window has a negative size!"));
    }
    Grid g(cropped_width, cropped_height);
    // j and i represent x and y of the original grid. We start at x0 until x1, at y0 until y1 because this is the part
    // which should remain in the cropped grid.
    // new_j and new_i represent x and y of the new grid. We need to fully iterate through it, so we start from 0.
    for (int i = y0, new_i = 0; i < y1; i++, new_i++) {
        for (int j = x0, new_j = 0; j < x1; j++, new_j++) {
            if (this->get(j, i) == Cell::ALIVE) {
                g(new_j, new_i) = Cell::ALIVE;
            }
        }
    }

    // Updating fields
    this->width = cropped_width;
    this->height = cropped_height;
    this->grid = g.grid;
    return g;
}


/**
 * Grid::merge(other, x0, y0, alive_only = false)
 *
 * Merge two grids together by overlaying the other on the current grid at the desired location.
 * By default merging overwrites all cells within the merge reason to be the value from the other grid.
 *
 * Conditionally if alive_only = true perform the merge such that only alive cells are updated.
 *      - If a cell is originally dead it can be updated to be alive from the merge.
 *      - If a cell is originally alive it cannot be updated to be dead from the merge.
 *
 * @example
 *
 *      // Make two grids
 *      Grid x(2, 2), y(4, 4);
 *
 *      // Overlay x as the upper left 2x2 in y
 *      y.merge(x, 0, 0);
 *
 *      // Overlay x as the bottom right 2x2 in y, reading only alive cells from x
 *      y.merge(x, 2, 2, true);
 *
 * @param other
 *      The other grid to merge into the current grid.
 *
 * @param x0
 *      The x coordinate of where to place the top left corner of the other grid.
 *
 * @param y0
 *      The y coordinate of where to place the top left corner of the other grid.
 *
 * @param alive_only
 *      Optional parameter. If true then merging only sets alive cells to alive but does not explicitly set
 *      dead cells, allowing whatever value was already there to persist. Defaults to false.
 *
 * @throws
 *      std::exception or sub-class if the other grid being placed does not fit within the bounds of the current grid.
 */
void Grid::merge(const Grid &other, const int x0, const int y0) {
    if (other.get_width() > this->get_width() || other.get_height() > this->get_height()) {
        throw std::runtime_error(std::string
        ("The other grid doesn't fit within the bounds of the current one!"));
    }
    if ((x0 < 0 || x0 > this->get_width()) || y0 < 0 || y0 > this->get_width()) {
        throw std::runtime_error(std::string("Either x or y is has a non-reasonable value!"));
    }
    // i and j keep track of indexes in the original grid, new_i and new_j keep track of indexes in the other grid
    for (int i = y0, new_i = 0; new_i < other.get_height(); i++, new_i++) {
        for (int j = x0, new_j = 0; new_j < other.get_width(); j++, new_j++) {
            //Set current cell to alive if matching cell from the other grid is alive
            if (other.get(new_j, new_i) == Cell::ALIVE) {
                (*this)(j, i) = Cell::ALIVE;
            } else {
                (*this)(j, i) = Cell::DEAD;
            }
        }
    }

}

// Overloaded version does not allow alive cells to become dead
void Grid::merge(const Grid &other, const int x0, const int y0, const bool alive_only) {
    if (!alive_only) {
        merge(other, x0, y0);
    } else {
        if (other.get_width() > this->get_width() || other.get_height() > this->get_height()) {
            throw std::runtime_error(std::string
                                             ("The other grid doesn't fit within the bounds of the current one!"));
        }
        if ((x0 < 0 || x0 > this->get_width()) || y0 < 0 || y0 > this->get_width()) {
            throw std::runtime_error(std::string("Either x or y is has a non-reasonable value!"));
        }
        // i and j keep track of indexes in the original grid, new_i and new_j keep track of indexes in the other grid
        for (int i = y0, new_i = 0; new_i < other.get_height(); i++, new_i++) {
            for (int j = x0, new_j = 0; new_j < other.get_width(); j++, new_j++) {
                // if current cell is alive but the other is dead, don't change anything
                // if current cell is dead but the other is alive, make current alive
                if ((other.get(new_j, new_i) == Cell::DEAD && this->get(j, i) == Cell::ALIVE) ||
                    (other.get(new_j, new_i) == Cell::ALIVE && this->get(j, i) == Cell::DEAD)) {
                    (*this)(j, i) = Cell::ALIVE;
                } else {
                    (*this)(j, i) = Cell::DEAD;
                }
            }
        }
    }
}

/**
 * Grid::rotate(rotation)
 *
 * Create a copy of the grid that is rotated by a multiple of 90 degrees.
 * The rotation can be any integer, positive, negative, or 0.
 * The function should take the same amount of time to execute for any valid integer input.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a 1x3 grid
 *      Grid x(1,3);
 *
 *      // y is size 3x1
 *      Grid y = x.rotate(1);
 *
 * @param _rotation
 *      An positive or negative integer to rotate by in 90 intervals.
 *
 * @return
 *      Returns a copy of the grid that has been rotated.
 */
Grid Grid::rotate(const int rotation) const {
    // Note: Time Complexity: O(n^2). Access complexity: O(1) in EVERY CASE except when rotation = 0 and multiples.
    Grid newgrid;
    int actual_rotation = rotation;
    // Any rotation can be brought down to 4 cases => 0, 90 ,-90, 180 degrees, so when a user passes e.g 3 (270 degree)
    // it will be equivalent to -1 (-90 degree) rotation. actual_rotation will get this number and then apply it
    // for the further calculations.
    while (!(actual_rotation == 0 || actual_rotation == 1 || actual_rotation == -1 || actual_rotation == 2
             || actual_rotation == -2)) {
        if (actual_rotation > 0) {
            actual_rotation -= 4;
        } else {
            actual_rotation += 4;
        }
    }

    // If rotation angle is 360 degrees, create a copy of a current grid and return
    if (actual_rotation == 0 || abs(actual_rotation) % 4 == 0) {
        newgrid = *this;
        return newgrid;
    }
    // If rotation angle is a multiple of 180 degrees, the new grid will have the same dimensions as the current one
    if (abs(actual_rotation) % 2 == 0) {
        newgrid = Grid(this->width, this->height);
        for (int i = 0, new_i = this->height - 1; i < this->height; i++, new_i--) {
            for (int j = 0, new_j = this->width - 1; j < this->width; j++, new_j--) {
                newgrid(j, i) = (*this)(new_j, new_i);
            }
        }
        // If rotation angle is a multiple of 90 degrees, the new grid will have inverted dimensions
    } else {
        newgrid = Grid(this->height, this->width);
        // new_i keeps track of the correct index during CCW rotation and new_j during CW rotation.
        for (int i = 0, new_i = this->width - 1; i < newgrid.height; i++, new_i--) {
            for (int j = 0, new_j = newgrid.width - 1; j < newgrid.width; j++, new_j--) {
                // If CW apply first formula, if CCW apply another...
                if (actual_rotation > 0) {
                    newgrid(j, i) = (*this)(i, new_j);
                } else {
                    newgrid(j, i) = (*this)(new_i, j);
                }
            }
        }
    }
    return newgrid;


}

/**
 * operator<<(output_stream, grid)
 *
 * Serializes a grid to an ascii output stream.
 * The grid is printed wrapped in a border of - (dash), | (pipe), and + (plus) characters.
 * Alive cells are shown as # (hash) characters, dead cells with ' ' (space) characters.
 *
 * The function should be callable on a constant Grid.
 *
 * @example
 *
 *      // Make a 3x3 grid with a single alive cell
 *      Grid grid(3);
 *      grid(1, 1) = Cell::ALIVE;
 *
 *      // Print the grid to the console
 *      std::cout << grid << std::endl;
 *
 *      // The grid is printed with a border of + - and |
 *
 *      +---+
 *      |   |
 *      | # |
 *      |   |
 *      +---+
 *
 * @param os
 *      An ascii mode output stream such as std::cout.
 *
 * @param grid
 *      A grid object containing cells to be printed.
 *
 * @return
 *      Returns a reference to the output stream to enable operator chaining.
 */
std::ostream &operator<<(std::ostream &os, const Grid &g) {
    std::string border;
    os << "+";
    border += "+";
    for (int i = 0; i < g.width; i++) {
        os << "-";
        border += "-";
    }
    os << "+" << std::endl;
    border += "+";

    for (int i = 0; i < g.height; i++) {
        os << "|";
        for (int j = 0; j < g.width; j++) {
            if (g.get(j, i) == Cell::ALIVE) {
                os << "#";
            } else {
                os << " ";
            }
        }
        os << "|" << std::endl;
    }


    os << border;
    os << std::endl;
    return os;
}
