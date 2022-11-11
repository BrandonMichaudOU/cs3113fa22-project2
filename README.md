# Brandon Michaud

# How to Build and Run
Use `make all` to build the executable program. After this has been done, the program can be run by issuing the following command: `./project2 TYPE N filename` where TYPE is the desired scheduling algorithm (BESTFIT, FIRSTFIT, NEXTFIT, or WORSTFIT), N is the total memory allocation, and filename is the path to a script file that will be used for input.

# Assumptions
The program operates under the assumption that the executable call will be formatted as described in the project description and that the input file will also be formatted as described in the project description.

# Functions
The program begins in the main function and then calls other functions depending on the input line from the file. There are fittingly named functions which perform the job of best fit request, first fit request, next fit request, worst fit request, release, list available, list assigned, and find. 

# Bugs
There seems to be a bug with next fit requests where the next fit pointer desynchronizes with the expected pointer.

# Libraries/Sources
No external libraries or web sources were used in this program.
