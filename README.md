# How to Compile

Operating Systems Course: This lab was designed to test our ability to implement the safety algorithm in regards to the resource allocation problem.

On Mac and Linux operating systems, enter the command "c++ program.cpp -o program"
(-o program is optional but I like to do it for simplicity). Then to run the program,
enter the command "./program [four integer values for available resources]". For example,
[./program 10 7 9 12]. When running the program, the user input has six inputs that you
need to specify. First input is either "RQ", or "RL". Second input is the number of
the process (0-4). Inputs 3-6 are the number of resources you want to either request or
release. You can also type "*" by itself to display all of the data structures.
