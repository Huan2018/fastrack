# [FaSTrack](https://hjreachability.github.io/fastrack/)

[![Build Status](https://travis-ci.org/HJReachability/fastrack.svg?branch=master)](https://travis-ci.org/HJReachability/fastrack)
[![License](https://img.shields.io/badge/license-BSD-blue.svg)](LICENSE)

[FaSTrack](https://hjreachability.github.io/fastrack/) (Fast and Safe Tracking): fast planning methods with slower, reachability-based safety guarantees for online safe trajectory planning. Auto-generated documentation may be found [here](https://hjreachability.github.io/fastrack/doc/html).

## Repository organization
All code in this repository is written in the Robot Operating System (ROS) framework, and as such is broken up into atomic packages that implement specific functionality. The `ros/` directory is the root workspace, and individual packages live inside the `ros/src/` directory.

## Usage
First, make sure you have ROS installed on your system. The project was developed in Jade, but it should be compatible with anything past Hydro. Please let us know if you have any compatibility issues.

The core `fastrack`, `fastrack_msgs`, and `fastrack_srvs` have no significant external dependencies other than those listed below. However, the `fastrack_crazyflie_demos` package depends upon the [crazyflie_clean](https://github.com/dfridovi/crazyflie_clean) repository, which contains drivers and utilities for the HSL's Crazyflie 2.0 testbed.

Other dependencies:
* [Gtest](https://github.com/google/googletest) -- Google's C++ unit testing library
* [Eigen](https://eigen.tuxfamily.org) -- a header-only linear algebra library for C++
* [OMPL](http://ompl.kavrakilab.org) -- an open C++ library for motion planning (recommend v1.2.1 to avoid g++5 dependency)
* [MATIO](https://github.com/tbeu/matio) -- an open C library for MATLAB MAT file I/O
* [FLANN](http://www.cs.ubc.ca/research/flann/) -- an open source library for fast (approximate) nearest neighbors

To build the entire workspace, you must begin by building and sourcing the `crazyflie_clean` repository. Instructions may be found in that project's README. Once you have done that, open a terminal window and navigate to the `ros/` directory. Then run:
```
catkin_make
```

If you only wish to build the `fastrack` core packages (_not_ `fastrack_crazyflie_demos`) then you may instead run:
```
catkin_make --pkg=fastrack
```

Every time you open a new terminal, you'll have to tell ROS how to find this package. Do this by running the following command from the `ros/` directory:
```
source devel/setup.bash
```


To run unit tests, type:
```
catkin_make run_tests
```

## C++ reference materials
We attempt to adhere to the philosophy put forward in the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html). Our code is written _for the reader, not the writer_. We write comments liberally and use inheritance whenever it makes sense.

A few tips, tricks, and customs that you'll find throughout our code:
* Lines of code are no longer than 80 characters.
* The names of all member variables of a class end with an underscore, e.g. `foo_`.
* When iterating through a vector, we name the index something like `ii` instead of just `i`. This makes it super easy to find and replace the iterator later.
* We use the `const` specifier whenever possible.
* We try to include optional guard statements with meaningful debug messages wherever possible. These may be toggled on/off with the `ENABLE_DEBUG_MESSAGES` cmake option.
* Whenever it makes sense, we write unit tests for self-contained functionality and integration tests for dependent functions and classes. These are stored in the `test/` directory.
