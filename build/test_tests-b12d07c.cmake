add_test( [==[Constructor for airports]==] /workspaces/cs225FinalProject/build/test [==[Constructor for airports]==]  )
set_tests_properties( [==[Constructor for airports]==] PROPERTIES WORKING_DIRECTORY /workspaces/cs225FinalProject/build)
add_test( [==[Constructor for Routes]==] /workspaces/cs225FinalProject/build/test [==[Constructor for Routes]==]  )
set_tests_properties( [==[Constructor for Routes]==] PROPERTIES WORKING_DIRECTORY /workspaces/cs225FinalProject/build)
add_test( [==[Djikstras Algorithm for Shortest Path]==] /workspaces/cs225FinalProject/build/test [==[Djikstras Algorithm for Shortest Path]==]  )
set_tests_properties( [==[Djikstras Algorithm for Shortest Path]==] PROPERTIES WORKING_DIRECTORY /workspaces/cs225FinalProject/build)
add_test( [==[BFS Algorithm for Shortest Path]==] /workspaces/cs225FinalProject/build/test [==[BFS Algorithm for Shortest Path]==]  )
set_tests_properties( [==[BFS Algorithm for Shortest Path]==] PROPERTIES WORKING_DIRECTORY /workspaces/cs225FinalProject/build)
set( test_TESTS [==[Constructor for airports]==] [==[Constructor for Routes]==] [==[Djikstras Algorithm for Shortest Path]==] [==[BFS Algorithm for Shortest Path]==])