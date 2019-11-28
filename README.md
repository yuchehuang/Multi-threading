# Multiple-threads

* This project demonstrates the performance variation via operating the matrix multiplication by using different number of threads
* The work is acheived by C and adopts [windows.h](https://docs.microsoft.com/en-us/windows/win32/procthread/creating-threads) library to control and assign the task to each thread
* The result of the experiment is shown as the [report](https://github.com/yuchehuang/Multiple-threads/blob/master/Report/Thread%20performance%20analysis.pdf)

## Abstract

The technique of multi-thread has been widely used for solving multi-task such as matrix multiplication. The performance variation of the matrix operation by using the different number of threads is investigated in this project. The work demonstrates that multi-thread offers a faster performance due to the task is separated into several segments and operated simultaneously. However, the thread efficiency suffers from a lower utilization while using massive threads to execute the task due to each of it spends significant time on synchronization.


## Methodlolgy
The main point to improve the performance of multiplication operation is not only increasing the number of threads but also making sure tasks are equality assigned to each thread. With mapping equally, it prevents main thread from waiting a long time for one of thread still executing when others have completed their own tasks. Therefore, it leads in a lower CPU utilization and higher executing time. The work allocates tasks to each thread by the total number of elements which depend on the size of the matrix. In addition, to observe the multi-threading performance flexibly, dynamic memory allocation is adopted by the program to create the matrixes and threads by difference value of the input (as shown as the following figure). <br/>

![alt text](https://github.com/yuchehuang/Multiple-threads/blob/master/picture/equally%20assign.PNG)

To estimate the operating time of matrix multiplication accurately, the timer is only triggered while thread executing matrix multiplication. After checking threads and assigning tasks, the main function enable the timer after all of the threads start operating the calculation until all of them have been marked into finish state. As a result, the executing time can be more accurate and not affected by the other processes in the main program. 
<br/>

## Result

The following figure illustrates the matrix multiplication is complemented by only one thread and took up 1/8 of CPU utilisation. Due to the thread can be executed amount 8 physical cores, the task can be achieved without any time-consuming caused by synchronization and preemption. <br/>  


![alt text](https://github.com/yuchehuang/Multi-threading/blob/master/picture/1_thread_%20size_1000.jpg)
![alt text](https://github.com/yuchehuang/Multi-threading/blob/master/picture/1_thread_size_1000_core.jpg)

By using multi-threading, the executing time decreases dramatically due the task is distributed equally to each thread to execute. However, there is a limitation of using massive thread. 
The following picture demonstrates an example that using 400 threads to execute the task. The result shows that although this strategy occupies almost 100% of CPU resource, each thread has only 3% time to execute the task compared with 79% in synchronisation during the task.<br/> 

![alt text](https://github.com/yuchehuang/Multi-threading/blob/master/picture/400_thread_size_1000.png)
![alt text](https://github.com/yuchehuang/Multi-threading/blob/master/picture/400_thread_size_1000_core.JPG)

By using the number of thread which equal to the physical cores, the issue of synchronisation will be eliminated and thread efficiency can be optimised due to none of the thread needs to wait for the other thread to finish its task. The result of this experiment is illustrated as the following picture which shown there are 93% of timeline in execution status.<br/>

![alt text](https://github.com/yuchehuang/Multi-threading/blob/master/picture/8_thread_size_1000.JPG)
![alt text](https://github.com/yuchehuang/Multi-threading/blob/master/picture/8_thread_size_1000_core.JPG)


## Concluison
![alt text](https://github.com/yuchehuang/Multi-threading/blob/master/picture/1000x1000_in_n_thread.jpg)
