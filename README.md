# CacheSimulation

The Cache Simulator is a program that simulates the behavior of a cache memory. It takes a trace file as input and outputs the hit rate for a given cache configuration which is created by the user. The user has the option to create a Fully Associative, Direct Mapped, or Set Associative cache. The user will also specify whether they would like to use the FIFO or LRU replacement policy for the appropriate cache design.

*Created by Amay Patel for CDA3101 - Introduction to Computer Organization on 11/28/22*

## Installation and Usage

1. Clone the repository with `git clone` or download the zip file.
2. Place the 'Trace files' folder into the same directory as the executable. 
3. Open the project in an IDE like CLion/Visual Studio or in a code editor like Visual Studio Code. 
4. Build the project and run the executable. 
5. Follow the instructions in the program and enter the appropriate values for the cache configuration.*

*\*Note: The program will ask for a positive number of bytes that you want for the cache and a positive number of bytes per block. These values need to be a power of 2 i.e. 512, 1024 and the number of bytes per block needs to be at least 4*