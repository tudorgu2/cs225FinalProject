# Results


## Data Parsing
The program parses two data files: `airports.dat` and `routes.dat`. `airports.dat` contains information about the country, airport name, airport code, and its latitude and longitude. `routes.dat` contains the starting airport and destination airport, which it stores along with the distance between the airports calculated using the Haversine formula.

## Haversine Formula
The Haversine formula is used to calculate the great-circle distance between two points on a sphere given their longitudes and latitudes.

## BFS (Breadth-First Search)
BFS is a traversal algorithm used in graph theory to traverse and search through the nodes of a graph. In the context of the Flight Routefinder project, BFS is used to find the shortest path between two airports.

## Dijkstra's Algorithm
Dijkstra's algorithm is a shortest path algorithm that is used in graph theory to solve the single-source shortest path problem for a graph with non-negative edge weights. In the context of the Flight Routefinder project, Dijkstra's algorithm is used to find the shortest path between two airports.

## Testing Information
To facilitate testing, smaller route and airport files were created to parse as the original files had missing data, resulting in issues with indexing. These smaller files helped to identify necessary information such as airport IATA code, locations using longitude and latitude, and airport names, as well as to test the functions and spot errors. Test cases were set up to verify the constructor for the route and airport file data, as well as test adjacency lists for the BFS and Dijkstra's algorithms to ensure that the least connections and distances were calculated correctly.

## Conclusion
Our goal was to demonstrate the efficiency of using data structure traversal methods to find the shortest path. We used BFS and Dijkstra's to answer it. We were vastly successful in our work. 
