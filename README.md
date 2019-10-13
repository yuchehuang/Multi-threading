# Multiple-threads

* This project analyze the performance variation by using different number of threads when operating the matrix multiplication
* The work is acheived by C and adopts [windows.h](https://docs.microsoft.com/en-us/windows/win32/procthread/creating-threads) library to control and assign the task to each thread
* The result of the experiment is shown as the [report](https://github.com/yuchehuang/Multiple-threads/blob/master/Report/Thread%20performance%20analysis.pdf)

## Abstract

The technique of multi-thread has been widely used for solving multi-task such as matrix multiplication. The performance variation of the matrix operation by using the different number of threads is investigated in this project. The work demonstrates that multi-thread offers a faster performance due to the task is separated into several segments and operated simultaneously. However, the thread efficiency suffers from a lower utilization while using massive threads to execute the task due to each of it spends significant time on synchronization.


## Methodlolgy
The main point to improve the performance of multiplication operation is not only increasing the number of threads but also making sure tasks are equality assigned into each thread. With mapping equally, it prevents main thread from waiting long time for one of thread still executing when others have completed their own tasks. Therefore, it leads in a lower CPU utilization and higher executing time. The work allocates tasks to each thread by the total number of elements which depend on the size of matrix. In addition, to observe the multi-threading performance flexibly, dynamic memory allocation is adopted in the program to create the matrixes and threads by difference value of input (as shown as following figure).
<br/>

![alt text](https://github.com/yuchehuang/Multiple-threads/blob/master/picture/equally%20assign.PNG)


