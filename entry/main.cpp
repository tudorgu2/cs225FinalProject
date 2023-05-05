#include "ParseFlights.hpp"

using namespace std;

// Function to find index of a given item in a vector
int findIndex(vector<string> vector_, string item) {
    for (size_t i = 0; i < vector_.size(); ++i) {
        if (vector_[i] == item) 
            return i;
    }
    return -1;
}

int main() {
    vector<string> airportIATAcodes = {"YUM", "SCL", "FAT", "AGP", "JAD", "TNR", "MRU", "MRS","ECN"};
    vector<string> destinations = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
    ParseFlights test("/workspaces/cs225FinalProject/entry/airports.dat",
                   "/workspaces/cs225FinalProject/entry/routes.dat");

    // Display the top 9 sunniest places in the world
    cout << "Escape from the miserable weather to a sunny place abroad!" << '\n';
    cout << "Here are the top 9 sunniest places in the world" << '\n';
    cout<< "1. Yuma, Arizona" << '\n' 
        << "2. San Pedro de Atacama, Chile" <<'\n' 
        << "3. Fresno, California" << '\n'
        << "4. Costa del Sol, Spain" << '\n'
        << "5. Perth, Australia" << '\n'
        << "6. Tulear, Madagascar" << '\n'
        << "7. Belle Mare, Mauritius" << '\n'
        << "8. Marseille, France" << '\n'
        << "9. Limassol, Cyprus" << '\n';

    // Loop until user decides to quit
    while (true) {
        // Ask user for the destination they want to fly out of New York
        cout << "\nWhich of the locations would you like to fly out of New York. Just type out the country or press q to quit: ";

        string destination;  

        // Validate user input

        while(!(cin >> destination) || (findIndex(destinations, destination) == -1 && destination != "q") ) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << '\n' << "Hmm, please select where to go from the list provided:  ";
        }
        // Break the loop if user enters 'q'
        if (destination == "q") {
            cout << "Thank you and Safe Travels!" << endl;
            break;
        }
        
        cout << '\n' << "Leaving from New York to " << destination << " the flight with shortest distance traveled is: " << '\n';

        // Find shortest distance flight from JFK to selected destination
        double dist = 0;
        vector<string> dijkstra = test.DjikstrasAlgorithm("JFK", airportIATAcodes[findIndex(destinations, destination)], dist);
        for (size_t i = 0; i < dijkstra.size(); ++i) {
            cout << test.airportIndex[dijkstra[i]].name;
            if (i != dijkstra.size() - 1) cout << " ---> ";
        }
        cout << '\n' << "Bringing your total distance traveled to " << dist << '\n';


        // Find flight with least connections from JFK to selected destination
        cout << '\n' << "Leaving from New York to " << destination << " the flight with the least connections is: " << '\n';

        // Get flight path using BFS algorithm
        vector<string> bfs = test.BfsAlgorithm("JFK", airportIATAcodes[findIndex(destinations, destination)]);
        for (size_t i = 0; i < bfs.size(); ++i) {
            cout << test.airportIndex[bfs[i]].name;
            if (i != bfs.size() - 1) cout << " ---> ";
        }
        cout << '\n' << "Bringing your total number of connections to: " << bfs.size() << '\n';

        cout << '\n' << "We can conclude..." << '\n';
        // Compare flight paths and provide recommendation to user
        if (bfs == dijkstra) {
            cout << "Both flight patterns are the same!" << '\n';
        } else if (bfs.size() == dijkstra.size()) {
            cout << "While both flights have minimal connections, the second route is shorter in distance!" << '\n';
        } else {
            cout << "The first route involves fewer connections, but the second route is shorter in distance!" << '\n';
        }

        // Ask user if they want to find information about other locations
        cout << "\nCurious to find out more information about other loactions? Enter yes or no:  ";

        string userResponse;
        // Validate user input
        while (!(cin >> userResponse) || (userResponse != "yes" && userResponse != "no")) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout  << "Sorry, I didn't catch that. Was that a yes? ";
        }
        // Exit the loop if user doesn't want to more information
        if (userResponse == "no") {
            cout << "Thank you and Safe Travels!" << endl;
            break;
        }
    }
}