#pragma once

#include <vector> 
#include <unordered_map> 
#include <unordered_set>
#include <map>
#include <queue>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <string>
#include <stdio.h>


using namespace std;

struct Airport {
    int index;
    string name;
    double latitude;
    double longitude;
    string IATA; //International Air Transport Association Location Identifier

    bool operator==(const Airport& compare) const {
        return (compare.index == index &&
                compare.name == name &&
                compare.latitude == latitude &&
                compare.longitude == longitude &&
                compare.IATA == IATA);
    }
};

struct Neighboring {
    string IATA;
    double distance;

    bool operator==(const Neighboring& compare) const {
        return (compare.IATA == IATA && 
                compare.distance == distance);
    }
};

class ParseFlights {

    public:
        // constructor that reads airport and route data
        // constructs a graph and initialized its data members

        /* Main deliverables*/
        ParseFlights() = default;
        ParseFlights(const string& airportFile, const string& routesFile);
        vector<string> DjikstrasAlgorithm(const string& starting_airport,const string& destination_airport, double& distance);
        vector<string> BfsAlgorithm(const string& starting_airport, const string& desination_airport);

        /* Varibales and such */
        double airportDistance(string starting_airport, string destination_airport);
        unordered_map<string, Airport> airportIndex;
        vector<string> indexs_;
        unordered_map<string, vector<Neighboring>> adjacencyList; 
        vector<string> Topairports();
        

    private:

        /* Additional helper functions/variables */
        bool isVertexInGraph(const string& airport_node);
        vector<string> reconstructPath(unordered_map<string, string>& parent, const string& end);

        int airportCount = 0; 
    
    
};



