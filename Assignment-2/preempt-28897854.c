/*Name : Kudzai Mabika 
  Student ID : 28897854
  Start date-7 October 2019 End date-15 October 2019
  
Main for preempt-28897854 Task 1 program to simulate a fcfs scheduling:
This code makes different output than that specified from specifications, The time slice for this round robin is 2
The program will compute round robin perfectly for time slice = but 2 does not append the bars properly on the graph
The calculations for Waiting Time and Turnaround time will be correct and the program will display the running state and which process is in running correctly.
The program will sleep for 1 second durring "executio"
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "process-visualiser.h"
#include "task2.h"

int main(int argc,char * argv[]){
	initInterface("white","black");
	 
	//Check if more than two arguments have been entered by the user
	if(argc > 1){       
	filename = argv[1];
	//Call to our round robin program
	roundRobin();
	waitExit();	
	}else {
        //If more there are no arguments entered by the user then default filename is used.
	filename = "process-data.txt";
        //Call to our round robin program
	roundRobin();
	waitExit();	
	}
}
