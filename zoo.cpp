/**
 * Implements a Zoo namespace with methods for constructing Grid objects containing various creatures in the Game of Life.
 *      - Creatures like gliders, light weight spaceships, and r-pentominos can be spawned.
 *          - These creatures are drawn on a Grid the size of their bounding box.
 *
 *      - Grids can be loaded from and saved to an ascii file format.
 *          - Ascii files are composed of:
 *              - A header line containing an integer width and height separated by a space.
 *              - followed by (height) number of lines, each containing (width) number of characters,
 *                terminated by a newline character.
 *              - (space) ' ' is Cell::DEAD, (hash) '#' is Cell::ALIVE.
 *
 *      - Grids can be loaded from and saved to an binary file format.
 *          - Binary files are composed of:
 *              - a 4 byte int representing the grid width
 *              - a 4 byte int representing the grid height
 *              - followed by (width * height) number of individual bits in C-style row/column format,
 *                padded with zero or more 0 bits.
 *              - a 0 bit should be considered Cell::DEAD, a 1 bit should be considered Cell::ALIVE.
 *
 * @author 965217
 * @date March, 2020
 */
#include <string>
#include <fstream>
#include "zoo.h"
#include "grid.h"


// Include the minimal number of headers needed to support your implementation.
// #include ...

/**
 * Zoo::glider()
 *
 * Construct a 3x3 grid containing a glider.
 * https://www.conwaylife.com/wiki/Glider
 *
 * @example
 *
 *      // Print a glider in a Grid the size of its bounding box.
 *      std::cout << Zoo::glider() << std::endl;
 *
 *      +---+
 *      | # |
 *      |  #|
 *      |###|
 *      +---+
 *
 * @return
 *      Returns a Grid containing a glider.
 */

Grid Zoo::glider() {
    Grid g(3);
    g(1, 0) = Cell::ALIVE;
    g(2, 1) = Cell::ALIVE;
    g(0, 2) = Cell::ALIVE;
    g(1, 2) = Cell::ALIVE;
    g(2, 2) = Cell::ALIVE;

    return g;
}

/**
 * Zoo::r_pentomino()
 *
 * Construct a 3x3 grid containing an r-pentomino.
 * https://www.conwaylife.com/wiki/R-pentomino
 *
 * @example
 *
 *      // Print an r-pentomino in a Grid the size of its bounding box.
 *      std::cout << Zoo::r_pentomino() << std::endl;
 *
 *      +---+
 *      | ##|
 *      |## |
 *      | # |
 *      +---+
 *
 * @return
 *      Returns a Grid containing a r-pentomino.
 */

Grid Zoo::r_pentomino() {
    Grid g(3);
    g(1, 0) = Cell::ALIVE;
    g(2, 0) = Cell::ALIVE;
    g(0, 1) = Cell::ALIVE;
    g(1, 1) = Cell::ALIVE;
    g(1, 2) = Cell::ALIVE;

    return g;
}

/**
 * Zoo::light_weight_spaceship()
 *
 * Construct a 3x3 grid containing a light weight spaceship.
 * https://www.conwaylife.com/wiki/Lightweight_spaceship
 *
 * @example
 *
 *      // Print a light weight spaceship in a Grid the size of its bounding box.
 *      std::cout << Zoo::light_weight_spaceship() << std::endl;
 *
 *      +-----+
 *      | #  #|
 *      |#    |
 *      |#   #|
 *      |#### |
 *      +-----+
 *
 * @return
 *      Returns a grid containing a light weight spaceship.
 */

Grid Zoo::light_weight_spaceship() {
    Grid g(5, 4);
    g(1, 0) = Cell::ALIVE;
    g(4, 0) = Cell::ALIVE;
    g(0, 1) = Cell::ALIVE;
    g(0, 2) = Cell::ALIVE;
    g(4, 2) = Cell::ALIVE;
    g(0, 3) = Cell::ALIVE;
    g(1, 3) = Cell::ALIVE;
    g(2, 3) = Cell::ALIVE;
    g(3, 3) = Cell::ALIVE;

    return g;
}

/**
 * Zoo::load_ascii(path)
 *
 * Load an ascii file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an ascii file from a directory
 *      Grid grid = Zoo::load_ascii("path/to/file.gol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The parsed width or height is not a positive integer.
 *          - Newline characters are not found when expected during parsing.
 *          - The character for a cell is not the ALIVE or DEAD character.
 *
 */

Grid Zoo::load_ascii(std::string path) {
    std::string data;
    std::ifstream file;
    try {
        file.open(path);
        // Throw an exception if the file cannot be opened.
        if (!file.good()) {
            throw std::runtime_error(std::string("Error Opening file"));
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    int width, height = 0;
    if (file >> data) {
        width = stoi(data);
        file >> height;
    }
    // Throw an exception if width or height are non-positive
    try {
        if (width <= 0 || height <= 0) {
            throw std::runtime_error(std::string("Wrong width or height"));
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        exit(1);

    }
    Grid g(width, height);
    //Skipping the first line before the loop
    std::getline(file, data);
    // Throw an exception if a cell is not either DEAD or ALIVE or if newline char is missing
    try {
        for (int i = 0; i < height; i++) {
            std::getline(file, data);
            for (int j = 0; j < width; j++) {
                if (data[0] == '#') {
                    g(j, i) = Cell::ALIVE;
                } else if (data[0] != ' ') {
                    throw std::runtime_error(std::string("Corrupted ASCII file!"));
                }
                // Delete first element of the line
                data.erase(0, 1);
            }
            // Throws an exception if \n is missing
            if ((int)data.back() != 0) {
                throw std::runtime_error(std::string("Missing newline character!"));
            }
        }
    } catch (const std::exception &e){
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    file.close();
    return g;
}


/**
 * Zoo::save_ascii(path, grid)
 *
 * Save a grid as an ascii .gol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an ascii file in a directory
 *      try {
 *          Zoo::save_ascii("path/to/file.gol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
 */

void Zoo::save_ascii(std::string path, Grid grid) {
    std::ofstream file;
    file.open(path);
    // Throw an exception if a file cannot be opened
    if(!file) {
        throw std::runtime_error(std::string("Can't open the file!"));
    }
    int width = grid.get_width();
    int height = grid.get_height();
    // Write width and height to a file
    file << width << " " << height << std::endl;
    // Write every cell to a file
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (grid(j, i) == Cell::ALIVE) {
                file << '#';
            } else {
                file << ' ';
            }
        }
        file << std::endl;
    }
    file.close();
}


/**
 * Zoo::load_binary(path)
 *
 * Load a binary file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an binary file from a directory
 *      Grid grid = Zoo::load_binary("path/to/file.bgol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The file ends unexpectedly.
 */


/**
 * Zoo::save_binary(path, grid)
 *
 * Save a grid as an binary .bgol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an binary file in a directory
 *      try {
 *          Zoo::save_binary("path/to/file.bgol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
 */

void Zoo::save_binary(std::string path, Grid grid) {
    /*std::ofstream file;
    file.open(path,std::ios::out | std::ios::binary);
    // Throw an exception if a file cannot be opened
    if(!file) {
        throw std::runtime_error(std::string("Can't open the file!"));
    }
    int width = grid.get_width();
    int height = grid.get_height();
    // Write width and height to a file
    file.write((char*) &width, sizeof(int));
    file.write((char*) &height, sizeof(int));
    // Write every cell to a file
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (grid(j, i) == Cell::ALIVE) {
                file << '#';
            } else {
                file << ' ';
            }
        }
        file << std::endl;
    }
    file.close();*/
}