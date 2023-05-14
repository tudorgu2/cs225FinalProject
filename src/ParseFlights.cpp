#include "ParseFlights.hpp"

#include <string>

using namespace std;

/* helpers */
// Splits a given string into a vector of strings based on the delimiter
vector<string> Split(const string& str, char delimiter) {
    size_t last = 0;
    vector<string> substrs;
    for (size_t i = 0; i != str.length(); ++i) {
        if (str[i] == delimiter || str[i] == '\r') {
            string substr = str.substr(last, i - last);
            last = i + 1;
            substrs.push_back(substr);
        }
    }
    if (last != str.size()) {
        string substr = str.substr(last, str.length() - last);
        substrs.push_back(substr);
    }
    return substrs;
}

// Converts a given angle in degrees to radians
long double toRadians(const long double degree) {
    return ((M_PI) / 180) * degree;
}

// Calculates distance between two points on Earth using the Haversine formula
long double HaversineDistance(long double first_lat, long double first_long,
                     long double second_lat, long double second_long) {
    // Convert latitudes to radians.
    first_lat = toRadians(first_lat);
    second_lat = toRadians(second_lat);
    // convert longitudes to radians
    first_long = toRadians(first_long); 
    second_long = toRadians(second_long);
    // Haversine Formula 
    long double lat_difference = second_lat - first_lat;
    long double long_difference = second_long - first_long;
    long double haverisine = pow(sin(lat_difference / 2), 2) + cos(first_lat) * cos(second_lat) * pow(sin(long_difference / 2), 2);
    // Radius of Earth --> 6371 Kilometer
    long double radius = 6371;
    haverisine = 2 * asin(sqrt(haverisine));

    return haverisine * radius;
}

bool ParseFlights::isVertexInGraph(const string& airport_node) {
    return airportIndex.find(airport_node) != airportIndex.end();
}
// Reconstruct the path from BFS using parent map
vector<string> ParseFlights::reconstructPath(unordered_map<string, string>& parent, const string& end) {
    vector<string> path;
    for (string currentNode = end; currentNode != "-1"; currentNode = parent[currentNode]) {
        path.push_back(currentNode);
    }
    // Reverse path to get the correct order
    reverse(path.begin(), path.end());
    return path;
}

double ParseFlights::airportDistance(string starting_airport, string destination_airport) {
    // Starting airport's latitude/longitude
    long double starting_latitude = airportIndex[starting_airport].latitude;
    long double starting_longitude = airportIndex[starting_airport].longitude;
    // Destination airport's latitude/longitude
    long double dest_latitude = airportIndex[destination_airport].latitude;
    long double dest_longitude = airportIndex[destination_airport].longitude;
    // Distance using the Haversine formula.
    long double distance = HaversineDistance(starting_latitude, starting_longitude, dest_latitude, dest_longitude);
    // Calculated distance.
    return distance;

}

/* Deliverables*/
ParseFlights::ParseFlights(const string& airportFile, const string& routesFile) {
    ifstream routes(routesFile);
    if(routes.is_open() == false) {
        throw runtime_error("Unable to open");
    }
    ifstream airports(airportFile);
    if(airports.is_open() == false) {
        throw runtime_error("Unable to open");
    }
    // Read routesFile data
    vector<vector<string>> routeData;
    string routeLine;
    while(getline(routes, routeLine)){
        vector<string> string_ = Split(routeLine, ',');
        if (string_.size() == 9) {
            routeData.push_back(string_);
        }
    }
    // Read airportFile data
    string line;
    while(getline(airports, line)){
        vector<string> string_ = Split(line, ',');
        string cur_country;
        Airport cur_airport;
        cur_airport.index = airportCount;
        if (string_.size() <= 14) {
            // Extract current country information
            size_t country_length = string_[3].size() - 2;
            cur_country = string_[3].substr(1, country_length);
            // Extract airport name
            size_t name_length = string_[1].size() - 2;
            cur_airport.name = string_[1].substr(1, name_length);
            // Extract airport IATA code
            size_t code_length = string_[4].size() - 2;
            cur_airport.IATA = string_[4].substr(1, code_length);
            // Extract latitude and longitude
            cur_airport.latitude = stod(string_[6]);
            cur_airport.longitude = stod(string_[7]);
        } else {
            // Extract current country information
            size_t country_length = string_[4].size() - 2;
            cur_country = string_[4].substr(1, country_length);
            // Extract airport name
            size_t name_length = string_[1].size() - 1;
            cur_airport.name = string_[1].substr(1, name_length);
            // Extract airport IATA code
            size_t code_length = string_[5].size() - 2;
            cur_airport.IATA = string_[5].substr(1, code_length);
            // Extract latitude and longitude
            cur_airport.latitude = stod(string_[7]);
            cur_airport.longitude = stod(string_[8]);
        }
        adjacencyList[cur_airport.IATA] = {};
        indexs_.push_back(cur_airport.IATA);
        // Check if current airport not in airportIndex map
        if (airportIndex.count(cur_airport.IATA) == 0) {
            // Add the current airport to map
            airportIndex[cur_airport.IATA] = cur_airport;
            // Increment the airportCount
            airportCount++;
        }
    }
    
    // Process routes data --> eliminate outlier data
    for (auto route_entry : routeData) {
        // Source airport code from the route entry
        string starting_airport = route_entry[2];
        if (isVertexInGraph(starting_airport)) {
            string desination_airport = route_entry[4];
            // Check if the destination airport exists in the graph
            if (isVertexInGraph(desination_airport)) {
                Neighboring destination = {desination_airport, airportDistance(starting_airport, desination_airport)};
                adjacencyList[starting_airport].push_back(destination);
            }
        }
    }

    routes.close();
    airports.close();
}

vector<string> ParseFlights::DjikstrasAlgorithm(const string& starting_airport, const string& destination_airport, double& distance) {
    // Track visited airport nodes
    unordered_set<string> visited;
    // Priority queue to store the next airport nodes to visit --> sort by distance
    priority_queue<pair<double, string>,
                        vector<pair<double, string>>,
                        greater<pair<double, string>>> to_visit;
    // Store the shortest distance from the starting_airport node to each airport
    vector<double> shortest_distance(indexs_.size(), numeric_limits<int>::max());
    // Store the parent airport node for each node in the shortest path
    map<string, string> parent;

    // Check if staring airport is in graph
    if (isVertexInGraph(starting_airport) == false) {
        return {"-1"};
    }
    // Check if destination airport is in graph
    if (isVertexInGraph(destination_airport) == false) {
        return {"-1"};
    }

    // Initialize the starting airport distance and parent
    to_visit.push({0, starting_airport});
    shortest_distance[airportIndex[starting_airport].index] = 0;
    parent.insert({starting_airport, "to fill in"});

    while (to_visit.empty() == false) {
        // Airport with the shortest distance
        string current_airport = to_visit.top().second;
        double current_distance = to_visit.top().first;
        to_visit.pop();
        // Skip if already visited
        if (visited.find(current_airport) != visited.end()) {
            continue;
        }
        // Mark the current airport as visited
        visited.insert(current_airport);
        // Check if the destination airport has been reached
        if (current_airport == destination_airport) {
            string current_node = current_airport;
            distance = current_distance;
            vector<string> return_path;
            // Iterate parent map to construct the path
            for (; current_node != "to fill in"; current_node = parent[current_node]) {
                return_path.push_back(current_node);
            }
            // Correct order from the starting airport to the destination airport
            reverse(return_path.begin(), return_path.end());
            return return_path;
        }
        // Destination airport as not been reached, go to neighbors
        for (size_t i = 0; i < adjacencyList[current_airport].size(); i++) {
            auto neighbor = adjacencyList[current_airport][i];
            // Skip the neighbor if visited
            if (visited.find(neighbor.IATA) != visited.end()) {
                continue;
            }
            // Distance to the neighbor
            double new_distance = current_distance + neighbor.distance;
            // Update the shortest distance and parent if new distance shorter
            if (shortest_distance[airportIndex[neighbor.IATA].index] > new_distance) {
                shortest_distance[airportIndex[neighbor.IATA].index] = new_distance;
                parent[neighbor.IATA] = current_airport;
                to_visit.push({new_distance, neighbor.IATA});
            }
        } 
    }
    // No path found
    return {"-1"};
}

vector<string> ParseFlights::BfsAlgorithm(const string& starting_airport, const string& destination_airport) {
    unordered_set<string> visited;
    queue<pair<string, int>> toVisit;
    unordered_map<string, string> parent;
    // Check starting airport is valid
    if (isVertexInGraph(starting_airport) == false) {
        return {"-1"};
    }
    // Check destination airport is valid
    if (isVertexInGraph(destination_airport) == false) {
        return {"-1"};
    }
    // Initialize queue for BFS and visited set w/ starting_airport
    toVisit.push({starting_airport, 0});
    visited.insert(starting_airport);
    parent[starting_airport] = "-1";
    // Iterating through queue...
    while (toVisit.empty() == false) {
        auto current = toVisit.front();
        string currentNode = current.first;
        int currentDistance = current.second;
        toVisit.pop();
        // If current node is at destination, call in reconstruct path of parent and current node
        if (currentNode == destination_airport) {
            return reconstructPath(parent, currentNode);
        }
        // Iterate neighbors of current node
        // Add unvisited neighbors to queue
        for (auto neighbor : adjacencyList[currentNode]) {
            if (visited.find(neighbor.IATA) == visited.end()) {
                visited.insert(neighbor.IATA);
                parent[neighbor.IATA] = currentNode;
                toVisit.push({neighbor.IATA, currentDistance + 1});
            }
        }
    }
    return {"-1"}; 
}

vector<string> ParseFlights::Topairports() {
    // Implementation of google pagerank
    // Initialize number of airports
    airportCount = airportIndex.size();
    // Initialize transition matrix
    vector<vector<double>> transitionMatrix(airportCount, vector<double>(airportCount, 0.0));
    // Lambda matrix multiplication function
    auto MultiplyMatrix = [](const vector<vector<double>>& l, const vector<vector<double>>& r) {
        if (l[0].size() != r.size()) {
            return vector<vector<double>>(l.size(), vector<double>(r[0].size(), -1.0));
        }
        vector<vector<double>> result(l.size(), vector<double>(r[0].size(), 0.0));
        for(unsigned i = 0; i < l.size(); ++i)
            for(unsigned j = 0; j < r[0].size(); ++j)
                for(unsigned k = 0; k < l[0].size(); ++k)
                    result[i][j] += l[i][k] * r[k][j];
        return result;
    }
}
