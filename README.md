# Dynamic-Time-Warping-Algorithm (2016)
Time-series classification using the dynamic time warping algorithm  

Compilation:  
For the recursive implementation:  
gcc -o dtwrec distdtw.c dtwImplementation.c -DREC  
For the dynamic programming implementation:  
gcc -o dtwdp distdtw.c dtwImplementation.c  

There are also two txt files which contain two example sets of time series.

Typically, when we are interested in finding the DTW distance of two time series, they have the same length.  
In this case, it is very likely that we consider it unreasonable for the distances of their elements that are in several distant positions  to contribute to the distance of the two time series.  
Then, we put a limit (restriction) c on the spacing of the two-element positions.  
That c can be given as an argument when executing the program.  

Example:  
$ ./dtwdp 1  
5  
1.0 2.0 0.0 -1.0 -2.0  
-1.0 0.0 2.0 3.0 1.0  

Example:  
$ cat train_FaceFour.txt test_FaceFour.txt | ./dtwdp

Example:  
$ cat train_FaceFour.txt test_FaceFour.txt | ./dtwdp 0

In the following link one can find more files with time series data, but in a different format.  
http://www.cs.ucr.edu/~eamonn/time_series_data/
