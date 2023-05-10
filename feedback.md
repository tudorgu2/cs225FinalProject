# Feedback

The project you ontlined has a very interesting idea. I liked your idea to use BFS and Djikstras in order to find the shortest paths in terms of both distance and number of connections, so that they can be compared.

However, since the project specifications stated that you would need three deliverables, and you were not able to implement the pagerank algorithm, the initial conditions to qualify you for any points at all was not met.

That said, I will still provide feedback on the portion of the project you were able to complete.

## Presentation, Report, and Readme
Your formatting of the readme and the results files were very nice, with the readme only focusing on cloning and running instructions. Since not everyone has make installed locally, but you do provide a dockerfile, I would have liked to see a small note about being able to run it in the CS225 environment. Additionally, the installation topic seems a bit out of place, as the information underneath it is only information about where the files are located. But the instructions for setup and running are all very clear, and it's nice that you provide direct links as well.

The results section provides a very comprehensive overview of the algorithms you used, as well as some insight into the design choices you made. I would have liked to see some more information about what you were able to learn from doing this project. For example, maybe some information as to which destination seems the most convenient, by considering either the number of connections, the distance, or both. Also, since the end result only had a finite set of results, it would have been nice to see a list of all the information you were able to gather for all the destinations.

The presentation was very nice, and you guys clearly explained your reasons for making certain implementation decisions, as well as how you dealt with bad data. There were some things you were vague about, and I would have liked to see some more clarification as to how you can get your results from comparing the two algorithms, such as how you know one path has shorter distance than the other, to really demonstrate your knowledge of the two algorithms. Overall, it provided a lot of insight into your motiviations for the project, as well as your ideas, so it was very well done.

## Deliverables

Class Overview:
I liked how you split the airports themselves and the neighboring airports into their own structs for easy use. I think you may have been able to store an Airport in the Neighboring struct so that you could easily tell exactly which airports were neighbors, and keep the distance. In the constructor, some of your data structures are pretty complex, so it was a little difficult to tell what each member variable in the ParseFlights class was doing. However, the comments were very helpful, and they went a long way in telling me how you parsed the flights and routes files.

Deliverables:
Your Djikstras algorithm looks good. There were a lot of comments to tell what was going on. Most of the comments in this section were really nice to complement the code itselt, and sectioned it effectively. The same can be said for your BFS algorithm. I think there might be some ways to better check if points have been visited, since I see you use both sets and maps, but there is probably a way to make it quicker using an O(1) check like we did in mp traversals.

Tests:
The tests you have seem fairly good - there are a lot of assertions for each test. I would have liked to see some tests with the graph algorithms being performed on the dataset itself, but I understand it's difficult to get concrete data for something that large by hand. Also, trivial tests will usually pass, but they're always good to have just as a sanity check, so it would have been nice to see some very simple tests along with some edge case tests. Additionally, the number of tests is pretty small, and these algorithsm can be pretty complex, so including some more test cases would have been nice as well. However, the tests you did include seem to do a good job of actually testing that the algorithms work.

Your main method does a good job of displaying your results and interacting with the user, including checking for invalid inputs, which is really nice to see. It also does a good job of telling the user how the two routes differ, if they do at all. I would have liked to also see you include the distance it takes to get from New York to the destination if you found that the other route had a shorter distance. Also, for destination 5, I get this output:

Leaving from New York to 5 the flight with shortest distance traveled is: 

Bringing your total distance traveled to 0

Leaving from New York to 5 the flight with the least connections is: 

Bringing your total number of connections to: 1

We can conclude...
Both flight patterns are the same!

I'm not sure if this means you weren't able to find a path to the destination from New York, or if the path you found had distance 0. This seems like something that should be specified somewhere, and also could indicate a small bug that the tests and I weren't able to catch.

Overall, the deliverables that were submitted were of pretty good quality, and besides the bug to get to destination 5, everything else seems to be running about right.

I hope everyone has a nice summer!