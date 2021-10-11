


# Overview

This repository contains a library and an executable used to illustrates a 
robot planning capability. The robot planning library employs 
[Dijkstra's algorithm](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)
in order to derive the shortest
path between 2 specified points. The associated Qt application (qtPathFinder) creates
a Qt Widget with a randomized start point, end point, and obstacles. It then
uses the library to derive and illustrate the shortest path using the PathFinder 
library.

# Dependencies
The PathFinder library is written in C++ (17) and leverages Google Test for the 
unit tests. 

The qtPathFinder executable was also written in C++ (17) and utilizes Qt5.

Both applications were built using CMake 3.20.4.

# Building:
In order to build the PathFinder library, create a directory (.e.g. build) that
is where you will execute CMake from. The process below can be used to build the
PathFinder library.
* `git clone https://github.com/bruckart/robot_planning_library.git`
* `cd robot_planning_library`
* `cd PathFinder`
* `mkdir build`
* `cd build`
* `cmake ../`
* `make`

Subsequently, change directories to the qtPathFinder directory and repeat.

* `cd qtPathFinder`
* `mkdir build`
* `cd build`
* `cmake ../`
* `make`

Since the qtPathFinder executable utilizies the PathFinder library, do not forget 
to update the CMakeLists.txt target_link_libraries to reference the newly created library.

# Testing
The PathFinder library contains 3 unit tests (SimpleGraph, MultiGraph, NegativeTest) that can
be executed via specifying the CMake flag `-DCMAKE_TESTING_ENABLED` in order to build
the unit test. The test output should contain the following:

```
[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from PathFinder
[ RUN      ] PathFinder.SimpleGraph
[       OK ] PathFinder.SimpleGraph (0 ms)
[ RUN      ] PathFinder.MultiGraph
[       OK ] PathFinder.MultiGraph (0 ms)
[----------] 2 tests from PathFinder (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 2 tests.
```

# Known Issues / Further Work
* The qtPathFinder executable needs to be fully integrated to use the PathFinder library via the creation of Nodes and Edges that resemble the map scene.
* The save/load feature should be refactored to it's indepdent class.
* The creation of the BB-8 create start/end points need to be
disabled if these items are in the scene.



# Contributing
Please feel free to contribute to this project. 
For questions or comments, feel free to reach out to me on GitHub or my email at bruckart@gmail.com.

    1. Fork it ( https://github.com/bruckart/robot_planning_library.git)
    2. Create your feature branch (git checkout -b feature/fooBar)
    3. Commit your changes (git commit -am 'Add some fooBar')
    4. Push to the branch (git push origin feature/fooBar)
    5. Create a new Pull Request

# References/Credits:

* [Dijkstra's algorithm from Wikipedia](https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm) 
* [Dijkstra's Algorithm from Progamiz](https://www.programiz.com/dsa/dijkstra-algorithm)
* [Stack Overflow Question and Discussion](https://stackoverflow.com/questions/53388098/find-the-shortest-path-between-two-points-with-obstacles)
* [Abdul Bari's YouTube on Dijkstra's Algorithm including Relaxation](https://www.youtube.com/watch?v=XB4MIexjvY0)