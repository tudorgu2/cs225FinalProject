# Flight Routefinder

Flight Routefinder is a C++ program that calculates the best route between two airports using BFS, Dijkstra's algorithm, and Pagerank. The distance between two airports is calculated using the Haversine formula. The program parses csv data pertaining to the flight data.

## About
Flight Routefinder is a C++ program that calculates the best route between two airports, using BFS, Dijkstra's algorithm.

Link to the final presentation video: https://clipchamp.com/watch/DP9fXiJ4E4P  

## Installation

The code for Flight Routefinder can be found at https://github.com/tudorgu2/cs225FinalProject. The code is found in `ParseFlights.hpp`, the data in `airports.dat` and `routes.dat`, the tests in `test_student.cpp`, and the written report in `results.md`.

## Usage

The program can find the best route between any two airports. By default, it finds the route between JFK and a target airport. To run the program:

1. Clone the repository from the [GitHub link](https://github.com/tudorgu2/cs225FinalProject)
2. Navigate to the `build` directory in the cloned repository using the terminal.
3. Run the following command: `./main`

Note: A new executable can be built by modifying the code in `main.cpp` located in the entry folder, and building it by running `make` in the terminal of the build folder.

## Contact Information

For any questions or inquiries, please contact the developers at:
- tudorgu2@illinois.edu
- rishis4@illinois.edu
- eliseh2@illinois.edu
