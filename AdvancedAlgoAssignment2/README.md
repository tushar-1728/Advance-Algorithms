# Problem 1​:
Write a program that solves the assembly line problem with arbitrary number of assembly lines(similar to the 2-assembly line problem given in CLRS in the dynamic programming section).
1. Here there are ​N​ assembly lines in the factory, that exist on the factory floor placed inorder.
2. Each assembly line has ​M​ stations.
3. There is an entry time and exit time defined for each assembly line.
4. Each station on an assembly line has a processing time.
5. Transfers are allowed only between adjacent lines from the ith station to  the (i+1)thstation.(For example from the 2nd station on the 4th assembly line we can only move to the 3rd station on the 3rd, 4th, or 5th assembly line)
6. For more details refer to the assembly line problem described in CLRS.
## Input format:
- The first line consists of N and then M.
- Then the next N lines consist of M+2 integers each where each line represents the entry time, exit time and then the list of  processing times for the M stations for each assemblyline.
- Then the 2(N-1) lines contain M-1 integers each.
- The first line in the ith pair of lines represent the list of transfer times of the stations from ith assembly line to (i+1)th assembly line, while the second line of the ith pair represents the list of transfer times of the stations from the (i+1)th assembly line to the ith line.
### Input example:
2 6  
2 3 7 9 3 4 8 4  
4 2 8 5 6 4 5 7  
2 3 1 3 4  
2 1 2 2 1  
Represents the following assembly line  
![alt text](../assets/example_1.jpg "Title")
