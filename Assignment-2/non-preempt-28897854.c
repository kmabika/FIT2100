/*Name : Kudzai Mabika 
  Student ID : 28897854
  Start date-7 October 2019 End date-14 October 2019
  
Main for non-preempt-28897854 Task 1 program to simulate a fcfs scheduling:
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "process-visualiser.h"
#include "task1.h"

int main(int argc, char * argv[]) {
  initInterface("white", "black");
  //Check if there is an argument entered if not then define the default file name make sure it's in your directory. Simple if else used.	
  	if (argc > 1) {
    	//Argv[] value which is the filename is stored to our string.
    	filename = argv[1];
    	//Call to fcfs function.
    	fcfs();
    	waitExit();
  	}else{
    	filename = "process-data.txt";
    	//Call to fcfs function.
	fcfs();
    	waitExit();
  	}
}
