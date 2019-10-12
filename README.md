# Multiple-threads

* This project is analyze the performance variation by using different number of threads when operating the matrix multiplication
* The work is using C and adopts [windows.h](https://docs.microsoft.com/en-us/windows/win32/procthread/creating-threads) library to control and assignment the task to each thread
* The result of the experiment is shown as the [report](https://github.com/yuchehuang/Multiple-threads/blob/master/Report/Thread%20performance%20analysis.pdf)

## Abstract

The main point to improve the performance is not only increasing the number of threads but also making sure tasks are equality assigned into each thread. With mapping equally, it prevents main thread from waiting long time for one of thread still executing when others have completed their own tasks. Therefore, it leads in a lower CPU utilization and higher executing time. The work allocates tasks to each thread by the total number of elements which depend on the size of matrix. In addition, to observe the multi-threading performance flexibly, dynamic memory allocation is adopted in the program to create the matrixes and threads by difference value of input (as shown as following figure).

