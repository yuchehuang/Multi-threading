#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include <time.h>

// Disable the warning 
#pragma warning( disable : 4996 )
int *dynamic_array_1, *dynamic_array_2,*result,*TLB, size, thread_num;

//-----Thread Function-----------------//
int start_opint_calculate(int threadID)
{
	int start_opint = 0;
	for (int id = 0; id < TLB[3 * threadID]; id++)			// TLB[2*id+1]= The number of elements this thread will execute
		start_opint = start_opint + TLB[3 * id + 1];		//start_opint= before this thread how many element has been execute ------> thread_3's start point is  thread_1's number of element  + thread_2's number of element	
	
	//printf("Thread %d start point is: %d\n ", threadID, start_opint);
	return start_opint;
}
int execute_element_number(int order_of_element)
{
	int temp = 0, array_1_row, array_2_col;
	array_1_row = order_of_element / size;
	array_2_col = order_of_element % size;

	for (int element = 0; element < size; element++)
		temp = temp + dynamic_array_1[size*array_1_row + element] * dynamic_array_2[size*element + array_2_col];
	return temp;
}

DWORD WINAPI Thread_dynamic(LPVOID lpParam) 
{
	int id = (int)lpParam,temp;
			
	//printf("Thread %3d start point is %d  execute to %d\n",id, TLB[3 * id + 2], TLB[3 * id + 2] +TLB[3 * id+1]-1); //Test Each thread can get their own variable
	
	for (int element = TLB[3 * id + 2]; element < TLB[3 * id + 2] + TLB[3 * id+1]; element++)
	{	
		temp= execute_element_number(element);
		result[element] = temp;
	}
	return 0;
}

//------Dynamic creating array Function-------//
void number_of_each_thread_calculated_Table()
{	
	for (int i = 0; i < thread_num; i++)
		printf("Thread %2d start from: %2d to %2d of elements  Execute %4d elements\n", i, TLB[3 * i + 2], TLB[3 * i + 1]+ TLB[3 * i + 2]-1, TLB[3 * i + 1]);
}
bool Check_error(HANDLE thread1,  DWORD thread_id,int id)
{
	if (thread1 == NULL)
	{
		printf("Thread creation occur Error, Error num:   ");
		printf("%d\n", GetLastError());
		return 1;
	}
	//printf("Thread creation successful\n");
	//printf("Thread%3d ID: %d\n", id,thread_id);
	return 0;
}
void print_matrix(int *boj ,int n)
{
	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
			printf("%10d ", *(boj+col+n*row));
		printf("\n");
	}
}
void dynamic_assign_array_data(void)
{
	int square;
	printf("Enter the size of matrix: ");
	scanf("%d", &size);
	square = size * size;
	dynamic_array_1 = new int[square];
	dynamic_array_2 = new int[square];
	result = new int[square];
	for (int i = 0; i < square; i++)
	{
		dynamic_array_1[i] = i;
		dynamic_array_2[i] = square - i;
	}
}
void thread_input(void)
{
	printf("Enter the number of thread: ");
	scanf("%d", &thread_num);
	TLB = new int[3 * thread_num];		// calculate  number of element  for per thread
	//---------------Assign the number of element per thread will execute------------------------------//
/*			      TLB:   ID		Time	start point
				Thread	 0		 10			0
				Thread	 1		 10			10
				Thread	 2		 10			20
				Thread	 3		 10			30
*/
}
void assign()
{
	int  remain;
	remain = (size*size) % thread_num;
	for (int i = 0; i < thread_num; i++)
	{
		TLB[3*i] = i;
		TLB[3*i+1] = (size*size) / thread_num;
	}	
	for (int i = remain; i > 0; i--)
		TLB[3*(remain - i)+ 1] = TLB[3*(remain - i)+ 1] + 1;

	for (int i = 0; i < thread_num; i++)
		TLB[3 * i + 2] = start_opint_calculate(i);
}
void print_input()
{
	printf("-------------dynamic_array_1--------------\n");
	print_matrix(dynamic_array_1, size);
	printf("-------------dynamic_array_2--------------\n");
	print_matrix(dynamic_array_2, size);
}
int main(void)
{
	//---------Create array------------------------------//
	dynamic_assign_array_data();
	thread_input();
	assign();
	//print_input();
	//number_of_each_thread_calculated_Table();
	
//--Threading program & confirm every thread can create  within the limitation---//
	HANDLE *thread = new HANDLE[thread_num];
	DWORD  *thread_id = new DWORD[thread_num];
	for (int i = 0; i < thread_num; i++)
	{
		thread[i] = CreateThread(NULL, 0, Thread_dynamic, (void*)TLB[3 * i], 0x00000004, &thread_id[i]); //(void*) to make variable compactable to the function	
		if (Check_error(thread[i], thread_id[i], i))				//if one of thread occurs error change the total number of thread
		{
			thread_num = i - 1;
			printf("Only can create %d of Threads\n", thread_num);
			assign();		//	reassigned
			break;
		}
	}
	//--------Enable every Thread to start execute matrix moultiplication---------------//
	clock_t time = clock();
	for (int i = 0; i < thread_num; i++)
		ResumeThread(thread[i]);

	//------------Wait for all thread to complete & Print the execute time-------------//
	for (int i = 0; i < thread_num; i++)
		WaitForSingleObject(thread[i], INFINITE);
	time = clock() - time;
	//printf("Exetution time: %4f Sec \n", ((double)time) / CLOCKS_PER_SEC);
	
	//---------- Release the Thread---------------------//
	for (int i = 0; i < thread_num; i++)
	{
		CloseHandle(thread[i]);
		TerminateThread(thread[i], NULL);
	}

	//-----------Print result-----------------------------//	
		//printf("-------------result--------------\n");
		//print_matrix(result, size);

	//-----clear all Register & release the memory-------//
	free(dynamic_array_1);
	free(dynamic_array_2);
	free(TLB);
	free(thread);
	free(thread_id);
	free(result);
	//printf("----------------------------------------\n");
	
	//system("pause");
	return 0;
}
