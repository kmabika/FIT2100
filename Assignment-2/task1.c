#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "process-visualiser.h"
#include "task1.h"

/*Function to perform the first come first serve schdeuling 
	Function performs fcfs until the process is complete and then moves to the second process
        A red dotted line will display the waiting time of each process showing when it entered the system in ready state
*/
void fcfs() {
  
  int n = 0, i, pid = 0, time = 0;

  /*The function readFile returns an integer value which is stored as the total number of processes represented by variable n	
   */
  n = readFile(filename, pcb);

  //Loop which performs our fcfs will loop until the counter i is equal to the number of total processes;
  for (i = 0; i < n; i++) {
    //Assign serviceTime to length to avoid messing with pcb values.
    length[i] = pcb[i].serviceTime;
    //Row index is appended by the process name.
    rowIndex = appendRow(pcb[i].processName);
    //This creates pid of each process which will be used in other conditional statements as pid is unique.
    pcb[i].pid = pid;
    pid++;
    //For our first row has to be special because waiting time is obviously 0
    	if (rowIndex == 0) {
      		//Call to findWaitTime to get the values of waiting time and turnaround time
      		findWaitTurnAround(pcb, pcb[i].serviceTime, pcb[i].entryTime, pcb[i].processName, pcb[i].pid);
      		//Start appending processes to gantt chart if the apppendBar appears
      		appendBar(rowIndex, length[i], "red", pcb[i].processName, 0);
      		printf("</n>Process %s has entered the system at %d seconds", pcb[i].processName, pcb[i].entryTime);
      		if (time == pcb[i].entryTime) {
        		printf("%s entered the system at %d seconds", pcb[i].processName, pcb[i].entryTime);
      		}
      		pcb[i].state = RUNNING;
      		process_state = processStatus(pcb[i].state);
      		printf("</n> %s is in %s state.", pcb[i].processName, process_state);
      		sleep(2);
      		//Store our values from the findWaitTurn to our particular process control block turnaroundtime and waitime
      		pcb[i].turnaroundTime = pcb-> turnaroundTime;
      		pcb[i].waitingTime = pcb-> waitingTime;
      		//Process is complete display turnaround and wait time and put process in exit time
      		printf("</n>%s is completed.Waiting time is:%d Turnaround time is:%d", pcb[i].processName, pcb[i].waitingTime, pcb[i].turnaroundTime);
      		pcb[i].state = EXIT;
      		process_state = processStatus(pcb[i].state);
      		printf("</n> %s is in %s state.", pcb[i].processName, process_state);
    } 	else if (rowIndex > 0) {
      	   	if (indicator == 0) {
        	//Call to function to calculate waiting time and turnaround to get the values of waiting time and turnaround time
        	findWaitTurnAround(pcb, pcb[i].serviceTime, pcb[i].entryTime, pcb[i].processName, pcb[i].pid);
        	//Store our values from the findWaitTurn to our particular process control block turnaroundtime and waitime
        	pcb[i].turnaroundTime = pcb-> turnaroundTime;
        	pcb[i].waitingTime = pcb-> waitingTime;
        	printf("</n>Process %s has entered the system at %d seconds", pcb[i].processName, pcb[i].entryTime);
		
        	appendBlank(rowIndex, pcb[i].entryTime);
        	appendBar(rowIndex, pcb[i].waitingTime, "red", pcb[i].processName, 1);
        	sleep(2);
        	appendBar(rowIndex, length[i], "red", pcb[i].processName, 0);
        	//indicator the inform next statement that we have to treat the next processes differently     
        	indicator = 1;
        	pcb[i].state = RUNNING;
        	process_state = processStatus(pcb[i].state);
        	printf("</n> %s is in %s state.", pcb[i].processName, process_state);
        	//Process is complete display turnaround and wait time and put process in exit time
        	printf("</n>%s is completed.Waiting time is:%d Turnaround time is:%d", pcb[i].processName, pcb[i].waitingTime, pcb[i].turnaroundTime);
        	pcb[i].state = EXIT;
        	process_state = processStatus(pcb[i].state);
        	printf("</n> %s is in %s state.", pcb[i].processName, process_state);
      		} else if (indicator == 1) {
        	findWaitTurnAround(pcb, pcb[i].serviceTime, pcb[i].entryTime, pcb[i].processName, pcb[i].pid);
        	pcb[i].turnaroundTime = pcb-> turnaroundTime;
        	pcb[i].waitingTime = pcb-> waitingTime;
        	printf("</n>Process %s has entered the system at %d seconds", pcb[i].processName, pcb[i].entryTime);
        	appendBlank(rowIndex, pcb[i].entryTime);
        	appendBar(rowIndex, pcb[i].waitingTime, "red", pcb[i].processName, 1);
        	sleep(2);
        	appendBar(rowIndex, length[i], "red", pcb[i].processName, 0);
        	pcb[i].state = RUNNING;
        	process_state = processStatus(pcb[i].state);
        	printf("</n> %s is in %s state.", pcb[i].processName, process_state);
        	pcb[i].turnaroundTime = pcb->turnaroundTime;
        	pcb[i].waitingTime = pcb->waitingTime;
        	printf("</n>%s is completed.Waiting time is:%d Turnaround time is:%d", pcb[i].processName, pcb[i].waitingTime, pcb[i].turnaroundTime);
        	pcb[i].state = EXIT;
        	process_state = processStatus(pcb[i].state);
        	printf("</n> %s is in %s state.", pcb[i].processName, process_state);
      			}

    		}

  	}

 }

/*Function to read from file returns the number of processes, uses string to store values strtok works like the java deliminator
 This functions moves through the file line by line skipping if there is space between chars in the file and then the values are then stored in an item string.
*/
int readFile(char * fileName, process_cb pcb[]) {

  	FILE * filehandle;

  	//String where our line will be stored set it to 50 which should be okay
  	char * item;
  	char line[50];
  	//Counter to count the total number of processes in the file increments at  of while loop
  	int count = 0;

  	/* open file For read only and perform our error handling if user enters wrong filename*/
  	filehandle = fopen(fileName, "r");

  	if (filehandle == NULL) {
	//Error handling
    	printf("Failed to open file %s", fileName);
  	}else{
    		/* Read file line by line */

    		while (fgets(line, 120, filehandle)) {
		item = strtok(line, " ");
      		strcpy(pcb[count].processName, item);

      		item = strtok(NULL, " ");
  		/*From the file contents we know that the next variable  will be an int 
		we make sure it's converterd to integer from string using atoi().	
		*/
      		pcb[count].entryTime = atoi(item);

      		item = strtok(NULL, "\n");
		/*From the file contents we know that the next variable  will be an int 
		we make sure it's converterd to integer from string using atoi().	
		*/
      		pcb[count].serviceTime = atoi(item);

      		count++;
    		}		

    	/* Close file */
    	fclose(filehandle);
  	}	
  	return count;

}


/*Function to calculate the wait time and turnaround time of a process it does not return
  any value but accepts the pcb_t array as input, the current processes serviceTime/burstTime,current process entryTime and the current processName and the processId of current process.
All the information is passed through loops in the function that calls this fucntion.
*/
void findWaitTurnAround(process_cb pcb[], int burst_time, int entry_time, char * process_name, int process_id) {
  	char * process = process_name;
  	/*PID TO CHECK PROCCESS WAITING TIME 
        This function does not have a counter loop so the process control data has to be stored in process control block struct instance
	with a current pointer which will be used later on.
	*/
  	if (process_id == 0) {
    		//Start process will have waitTime of 0
    		waitingTime = 0;
	        //Store the turnroundtime into pcb current pointer used the formula serviceTime/burstTime + waitingTime;
    		pcb->turnaroundTime = burst_time + pcb->waitingTime;
		//Made serviceTime 0 so as to initialise the previous service time to be used for calculating waitingtime and turnaround    		
		service_time = 0;
    		pservice_time = service_time;
    		pburst_time = burst_time;	
	 }else  {
		//Waiting Time = serviceTIme  - entryTime in this instance and the values are stored to pointer
    		service_time = pservice_time + pburst_time;
    		pcb->waitingTime = service_time - entry_time;
  		//The values are stored to a pointer of the current process
    		pcb->turnaroundTime = burst_time + pcb->waitingTime;
    		pburst_time = burst_time;
    		pservice_time = service_time;  	
		}
}

/*
The enum values of the states are integers so this my simple code of converting the number into a integer
*/
char * processStatus(int status) {
  char * process_state;
  if (status == 0) {
    process_state = "READY";
  } else if (status == 1) {
    process_state = "RUNNING";
  } else if (status == 2) {
    process_state = "EXIT";
  }
  return process_state;
}
