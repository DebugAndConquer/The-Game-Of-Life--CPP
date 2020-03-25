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
#include <bitset>
#include "grid.h"
#include "zoo.h"

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

Grid Zoo::load_ascii(const std::string &path) {
    std::string data;
    std::ifstream file;
    file.open(path);

    // Throw an exception if the file cannot be opened.
    if (!file.good()) {
        throw std::runtime_error(std::string("Error Opening file"));
    }

    int width = 0, height = 0;
    if (file >> data) {
        width = stoi(data);
        file >> height;
    }
    // Throw an exception if width or height are non-positive
    if (width <= 0 || height <= 0) {
        throw std::runtime_error(std::string("Wrong width or height"));
    }

    Grid g(width, height);
    //Skipping the first line before the loop
    std::getline(file, data);
    // Throw an exception if a cell is neither DEAD or ALIVE or if newline char is missing
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
        // Throws an exception if \n is missing. For some reason if (data[0] != '\n') does not work, so had to use 0
        if (data[0] != 0) {
            throw std::runtime_error(std::string("Missing newline character!"));
        }
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

void Zoo::save_ascii(const std::string &path, Grid &grid) {
    std::ofstream file;
    file.open(path);
    // Throw an exception if a file cannot be opened
    if (!file) {
        throw std::runtime_error(std::string("Can't open the file!"));
    }
    const int width = grid.get_width();
    const int height = grid.get_height();
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
Grid Zoo::load_binary(const std::string &path) {
    std::ifstream bFile;
    bFile.open(path, std::ios::in | std::ios::binary);
    if (!bFile.good()) {
        throw std::runtime_error(std::string("Error Opening file"));
    }

    // Traversing to the end of the file to fetch the size
    bFile.seekg(0, std::ios::end);
    unsigned int size = (int) bFile.tellg();
    // Getting back to the beginning of the file to start reading
    bFile.seekg(0, std::ios::beg);
    // Reading the size of a grid and constructing it
    int width, height;
    bFile.read(reinterpret_cast<char *>(&width), sizeof(int));
    bFile.read(reinterpret_cast<char *>(&height), sizeof(int));

    // The size of file should be 2*sizeof(int) for w and h +
    // number of bytes to store w*h bits + number of padding bytes

    Grid g(width, height);

    // Calculating padding value
    int padding = 0;
    int loopValue;
    if (width * height % 8 != 0) {
        // padding indicates a number of bits needed to finish the byte
        padding = width * height % 8;
        // loopValue makes sure we loop on every byte which might contain the information
        loopValue = (width * height + padding) / 8;
    } else {
        loopValue = width * height / 8;
    }

    //Checking rather the file ends unexpectedly or no
    unsigned int minimal_expected_file_size = (2 * sizeof(int)) + ((width * height + padding) / 8);
    if (size < minimal_expected_file_size) {
        throw std::runtime_error(std::string("File Ends unexpectedly!"));

    }

    // A container for every byte, initialized with empty strings
    std::vector<std::string> bytes(loopValue, "");
    // Reading bytes corresponding to the grid (without the padding)
    for (int i = 0; i < loopValue; i++) {
        unsigned char currVal;
        bFile.read(reinterpret_cast<char *>(&currVal), sizeof(char));
        // A current byte we are reading
        std::string currentByte;
        for (unsigned int bit = 0; bit < 8; bit++) {
            // += syntax will create our current byte by adding each bit separately
            currentByte += std::to_string(((currVal >> bit) & 0x1));
        }
        bytes[i] = currentByte;
    }
    // Append all bytes into one string
    std::string byte;
    for (const auto &i : bytes) {
        byte += i;
    }

    // Write the data to the Grid structure
    for (unsigned int i = 0; i < byte.size(); i++) {
        if (byte[i] == '1') {
            // Get x, y using the idx
            const int x = i % width;
            const int y = (i - x) / width;
            // Assertion to not go outside the bounds of the grid
            if (!(x == width || y == height)) {
                g(x, y) = Cell::ALIVE;
            }
        }
    }
    bFile.close();
    return g;
}

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

void Zoo::save_binary(const std::string &path, Grid &grid) {
    std::ofstream file;
    file.open(path, std::ios::out | std::ios::binary);
    // Throw an exception if a file cannot be opened
    if (!file) {
        throw std::runtime_error(std::string("Can't open the file!"));
    }
    const int width = grid.get_width();
    const int height = grid.get_height();
    std::bitset<8> bitset; // A convenient container for 8 bit values

    // Write width and height to a file
    file.write((char *) &width, sizeof(int));
    file.write((char *) &height, sizeof(int));
    // A counter which keeps track of bit we are currently focusing on
    int bitset_count = 0;
    const int padding = width * height % 8;
    unsigned const int content_bytes = (width * height + padding) / 8;
    unsigned int current_bytes = 0;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (grid(j, i) == Cell::ALIVE) {
                bitset[bitset_count] = 1;
            } else {
                bitset[bitset_count] = 0;
            }
            bitset_count++;
            if (bitset_count == 8 || (content_bytes - current_bytes == 1)) {
                // Counting the byte size of content. When the difference between the actual size and a current one
                // will be 1, it will mean that only padding is left to be written to a file.
                if (bitset_count == 8) {
                    current_bytes++;
                }
                file.write((char *) &bitset, sizeof(char));
                bitset_count = 0;
            }
        }
    }

    file.close();
}


