#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <locale>

#include "ParseFlights.hpp"

TEST_CASE("Constructor for airports") {
  ParseFlights test("/workspaces/cs225FinalProject/entry/airportTEST.dat", 
                     "/workspaces/cs225FinalProject/entry/routesTEST.dat");
                     
  Airport gka = {0,"Goroka Airport", -6.081689834590001, 145.391998291, "GKA"};
  Airport mag = {1,"Madang Airport", -5.20707988739, 145.789001465, "MAG"};
  Airport hgu = {2,"Mount Hagen Kagamuga Airport", -5.826789855957031, 144.29600524902344, "HGU"};
  Airport lae = {3,"Nadzab Airport", -6.569803, 146.725977, "LAE"};
  Airport pom = {4,"Port Moresby Jacksons International Airport", -9.443380355834961, 147.22000122070312, "POM"};
  Airport wwk = {5,"Wewak International Airport", -3.58383011818,143.669006348, "WWK"};
  Airport uak = {6,"Narsarsuaq Airport", 61.1604995728,-45.4259986877, "UAK"};
  Airport goh = {7,"Godthaab / Nuuk Airport", 64.19090271,-51.6781005859, "GOH"};
  Airport sfj = {8,"Kangerlussuaq Airport", 67.0122218992,-50.7116031647, "SFJ"};
  Airport thu = {9,"Thule Air Base", 76.5311965942,-68.7032012939, "THU"};
  Airport yqw = {10,"North Battleford Airport", 52.76919937133789, -108.24400329589844, "YQW"};
  Airport yqx = {11,"Gander International Airport", 48.9369010925293,-54.56809997558594, "YQX"};
  Airport yqy = {12,"Sydney / J.A. Douglas McCurdy Airport", 46.1614,-60.047798, "YQY"};
  Airport yqz = {13,"Quesnel Airport", 53.026100158691406,-122.51000213623047, "YQZ"};
  Airport yrb = {14,"Resolute Bay Airport", 74.7169036865,-94.9693984985, "YRB"};

  REQUIRE(gka == test.airportIndex["GKA"]);
  REQUIRE(mag == test.airportIndex["MAG"]);
  REQUIRE(hgu == test.airportIndex["HGU"]);
  REQUIRE(lae == test.airportIndex["LAE"]);
  REQUIRE(pom == test.airportIndex["POM"]);
  REQUIRE(wwk == test.airportIndex["WWK"]);
  REQUIRE(uak == test.airportIndex["UAK"]);
  REQUIRE(goh == test.airportIndex["GOH"]);
  REQUIRE(sfj == test.airportIndex["SFJ"]);
  REQUIRE(thu == test.airportIndex["THU"]);
  REQUIRE(yqw == test.airportIndex["YQW"]);
  REQUIRE(yqw == test.airportIndex["YQW"]);
  REQUIRE(yqx == test.airportIndex["YQX"]);
  REQUIRE(yqy == test.airportIndex["YQY"]);
  REQUIRE(yqz == test.airportIndex["YQZ"]);
  REQUIRE(yrb == test.airportIndex["YRB"]);
  
}
TEST_CASE("Constructor for Routes") {
  ParseFlights test("/workspaces/cs225FinalProject/entry/airportTEST.dat", 
                     "/workspaces/cs225FinalProject/entry/routesTEST.dat");
  vector<Neighboring> gka = {{"MAG",test.airportDistance("GKA", "MAG")},
                          {"HGU",test.airportDistance("GKA", "HGU")},
                          {"LAE",test.airportDistance("GKA", "LAE")},
                          {"POM",test.airportDistance("GKA", "POM")}};
  vector<Neighboring> sna = {};
  vector<Neighboring> mag = {{"HGU",test.airportDistance("MAG", "HGU")},
                          {"LAE",test.airportDistance("MAG", "LAE")}};
  vector<Neighboring> thu = {{"MAG",test.airportDistance("THU", "MAG")},
                          {"HGU",test.airportDistance("THU", "HGU")}};
  vector<Neighboring> pom = {{"SFJ",test.airportDistance("POM", "SFJ")}};
  vector<Neighboring> wwk = {{"UAK",test.airportDistance("WWK", "UAK")}};
  vector<Neighboring> uak = {{"WWK",test.airportDistance("WWK", "UAK")}};
  vector<Neighboring> sfj = {{"MAG",test.airportDistance("SFJ", "MAG")}};
  
  
  REQUIRE(gka == test.adjacencyList["GKA"]);
  REQUIRE(mag == test.adjacencyList["MAG"]);
  REQUIRE(thu == test.adjacencyList["THU"]);
  REQUIRE(pom == test.adjacencyList["POM"]);
  REQUIRE(wwk == test.adjacencyList["WWK"]);
  REQUIRE(uak == test.adjacencyList["UAK"]);
  REQUIRE(sfj == test.adjacencyList["SFJ"]);
  REQUIRE(sna == test.adjacencyList["SNA"]);
  
  
}
TEST_CASE("Djikstras Algorithm for Shortest Path") {
  ParseFlights test;
  test.indexs_ = {"0", "1", "2", "3", "4", "5", "6", "7", "8"};

  test.adjacencyList = {{"0", {{"1", 1}, {"2", 2}}},
                        {"1", {{"0", 1}, {"3", 1}}},
                        {"2", {{"0", 2}, {"3", 2}, {"4", 1}}},
                        {"3", {{"1", 1}, {"2", 2}, {"5", 3}}},
                        {"4", {{"2", 1}, {"6", 1}, {"7", 2}}},
                        {"5", {{"3", 3}, {"6", 2}}},
                        {"6", {{"4", 1}, {"5", 2}, {"8", 1}}},
                        {"7", {{"4", 2}, {"8", 3}}},
                        {"8", {{"6", 1}, {"7", 3}}}};

  test.airportIndex = {{"0", {0, "0", 0, 0, "0"}},
                       {"1", {1, "1", 0, 0, "1"}},
                       {"2", {2, "2", 0, 0, "2"}},
                       {"3", {3, "3", 0, 0, "3"}},
                       {"4", {4, "4", 0, 0, "4"}},
                       {"5", {5, "5", 0, 0, "5"}},
                       {"6", {6, "6", 0, 0, "6"}},
                       {"7", {7, "7", 0, 0, "7"}},
                       {"8", {8, "8", 0, 0, "8"}}};

  double distance_1 = 0;
  vector<string> test_1 = {"4", "2", "3"};
  REQUIRE(test.DjikstrasAlgorithm("4", "3", distance_1) == test_1);
  REQUIRE(distance_1 == 3);

  double distance_2 = 0;
  vector<string> test_2 = {"5", "3", "1", "0"};
  REQUIRE(test.DjikstrasAlgorithm("5", "0", distance_2) == test_2);
  REQUIRE(distance_2 == 5);

  double distance_3 = 0;
  vector<string> test_3 = {"1", "0", "2"};
  REQUIRE(test.DjikstrasAlgorithm("1", "2", distance_3) == test_3);
  REQUIRE(distance_3 == 3);

  double distance_4 = 0;
  vector<string> test_4 = {"0", "2", "4", "6"};
  REQUIRE(test.DjikstrasAlgorithm("0", "6", distance_4) == test_4);
  REQUIRE(distance_4 == 4);
}

TEST_CASE("BFS Algorithm for Shortest Path") {
  ParseFlights test;
  test.indexs_ = {"0", "1", "2", "3", "4", "5", "6", "7", "8"};

  test.adjacencyList = {{"0", {{"1", 1}, {"2", 2}}},
                        {"1", {{"0", 1}, {"3", 1}}},
                        {"2", {{"0", 2}, {"3", 2}, {"4", 1}}},
                        {"3", {{"1", 1}, {"2", 2}, {"5", 3}}},
                        {"4", {{"2", 1}, {"6", 1}, {"7", 2}}},
                        {"5", {{"3", 3}, {"6", 2}}},
                        {"6", {{"4", 1}, {"5", 2}, {"8", 1}}},
                        {"7", {{"4", 2}, {"8", 3}}},
                        {"8", {{"6", 1}, {"7", 3}}}};

  test.airportIndex = {{"0", {0, "0", 0, 0, "0"}},
                       {"1", {1, "1", 0, 0, "1"}},
                       {"2", {2, "2", 0, 0, "2"}},
                       {"3", {3, "3", 0, 0, "3"}},
                       {"4", {4, "4", 0, 0, "4"}},
                       {"5", {5, "5", 0, 0, "5"}},
                       {"6", {6, "6", 0, 0, "6"}},
                       {"7", {7, "7", 0, 0, "7"}},
                       {"8", {8, "8", 0, 0, "8"}}};

  vector<string> test_1 = {"4", "2", "0", "1"};
  REQUIRE(test.BfsAlgorithm("4", "1") == test_1);

  vector<string> test_2 = {"5", "3", "1", "0"};
  REQUIRE(test.BfsAlgorithm("5", "0") == test_2);

  vector<string> test_3 = {"0", "1", "3"};
  REQUIRE(test.BfsAlgorithm("0", "3") == test_3);

  vector<string> test_4 = {"7", "4", "6", "5"};
  REQUIRE(test.BfsAlgorithm("7", "5") == test_4);

  vector<string> test_5 = {"8", "6", "5", "3"};
  REQUIRE(test.BfsAlgorithm("8", "3") == test_5);

  vector<string> test_6 = {"6", "4", "2"};
  REQUIRE(test.BfsAlgorithm("6", "2") == test_6);
}
