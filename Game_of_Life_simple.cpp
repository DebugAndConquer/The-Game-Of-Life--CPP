/**
* @author Dr. Joss Whittle
* @date March, 2020
*/

#include <iostream>

#include "grid.h"
#include "world.h"
#include "zoo.h"

int main(int argc, char *argv[]) {
    Grid w(8);
    Grid w_a(4);
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
           w_a.set(x, y, Cell::ALIVE);
        }
    }
    std::cout << w << w_a;
    w.merge(w_a,2,2,true);
    std::cout << w;
    /* Grid g(6);
    g(2,1) = Cell::ALIVE;
    g(3,2) = Cell::ALIVE;
    g(1,3) = Cell::ALIVE;
    g(2,3) = Cell::ALIVE;
    g(3,3) = Cell::ALIVE;
    std::cout << g << std::endl;
    Zoo::save_binary(R"(../test_inputs/myG.bgol)",g);*/
    //Grid g1 = Zoo::load_binary(R"(../test_inputs/GLIDER.bgol)");
    //std::cout << g1;


    /* Grid glider    = Zoo::glider(),
          glider90  = glider.rotate(1),
          glider180 = glider.rotate(2),
          glider270 = glider.rotate(3);

     // Place gliders in the 4 corners all flying towards the centre
     grid.merge(glider, 1, 1, true);

     grid.merge(glider90, ((grid.get_width() - 1) - glider90.get_width()), 1, true);

     grid.merge(glider180, ((grid.get_width() - 1) - glider180.get_width()),
             ((grid.get_height() - 1) - glider180.get_height()), true);

     grid.merge(glider270, 1, ((grid.get_height() - 1) - glider180.get_height()), true);

     // Place an r-pentomino (little shape that explodes huge) in the centre of the grid.
     grid.merge(Zoo::r_pentomino(), (grid.get_width() / 2), (grid.get_height() / 2), true);

     // Print the initial state of the grid
     std::cout << grid << std::endl;

     // Save the grid to a file
     try {
         Zoo::save_ascii("output.gol", grid);
         Zoo::save_binary("output.bgol", grid);
     }
     catch (const std::exception &ex) {
         std::cerr << ex.what() << std::endl;
         std::exit(-1);
     }*/

    // Destructors handle all the memory deallocation
    return 0;
}
