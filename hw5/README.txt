README

Programed by Jospeh Crandall
November 21st 2015
Disk Scheduling Algorithm
pg 501 OS-Book 9th edition

Instructions
1)Type make -> the program will compile

2)Type ./a.out _______ -> pick a value between 0 and 4999 to be the initial head position, the program will use this starting position for the duration of the program

3)example
make
.a/out 2523

4)The program will run the following scheduling algorithms
FCFS (First Come First Serve)
SSTF (Shortest Seek Time First)
SCAN (Scan)
C-SCAN (Circular Scan)
LOOK (Look)
C-LOOK (Circular Look)
on the same data set and will record the head movments for each

5)The program will repeat this process 1000 times taking an average of head movments from all runs with random cylinder posiionts on each run

Note)
the average head movment is the total head movement for a single scheduling algorihm divided by the number of runs

head movement for a sungle run is the sum of all cylinders the head passed over moving between different required cylinders so that the head could (hypothetically)read data
