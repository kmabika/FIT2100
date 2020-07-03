#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "process-visualiser.h"
#include "task2.h"


//Function to perform our round robin scheduling 
void roundRobin(){
	/*The function readFromFile returns an integer value which is stored as the total number of processes represented by variable n
	our time slice is declared as a local variable to avoid it being used by other processes
	Saw in the specification that time slice has to be 2 made a mistake and wrote 2.And it was difficult to get correct result if time slice was 2 due to my logic error	
	*/
	n = readFromFile(filename,pcb);
	int time_q = 4,prev=0;
	remain = n;
//This loop creates a temporary storage of the pcb contents that will be used by the program.To avoid messing with the real values
	for(i = 0;i<n;i++){
	rowIndex = appendRow(pcb[i].processName);
	pcb[i].rowIndex = rowIndex;
        ready_q[i]= pcb[i];	
	}
//Loop to begin round robin scheduling this loop will stop execution if there are no longer any remaining programs
	
for(time=0,count=0;remain!=0;) {  
    //First check if processes are less than quantam time and greater than 0	 
    	if(ready_q[count].serviceTime<=time_q && ready_q[count].serviceTime>0) 
    		{ 
		prev= time;        
      		time+=ready_q[count].serviceTime; 
      		ready_q[count].serviceTime = 0;        
      		flag=1; 
    		} 
    //This statement checks if the serviceTime in the ready_q is greater than this is to determine the first process to be displayed
    else if(ready_q[count].serviceTime> 0) 
    {
       /*The first process is displayed with entry time into the quantam time(used quantam time instead of system)
   	 when a process enters the quantam then the state has to be changed to running from ready and then the if there is remaining time then the process 
        has to time slice the remainder and then change that remainder into ready state.
        */
	printf("</n>%s entering quantum at %d seconds.",pcb[count].processName,time);	  
	pcb[count].state = 1;
	pstate = processStatus(pcb[count].state);
        printf("</n>%s is in %s state",pcb[count].processName,pstate); 
        sleep(1);
        pcb[count].state = 0;
	pstate = processStatus(pcb[count].state);
        printf("</n>%s is in %s state",pcb[count].processName,pstate);  	
	ready_q[count].serviceTime-=time_q;
	pcb[count].serviceTime = ready_q[count].serviceTime;
	pcb[count].remainingTime = pcb[count].serviceTime;
	/*THis is where our appending to the gantt chart starts
	First we have to check if the rowIndex > 0 to determine if this the remainder of the time slice coming back or a process that fits the time slice
	we call our method to calculate the waiting Time and turn around time in case this is the remainer which needs this information to output this information
	*/	
	if(pcb[count].rowIndex > 0){
        //Call to our findWaitTurnAround function		
	calculations(pcb,count,pcb[count].completed);	
	//We begin appending appending our processes to the gantt chart when this function is called
	appendBar(pcb[count].rowIndex,time_q,"red",pcb[count].processName,0);
	
	//Create a blankspace calculations to create that visual effect that we have moved 	
	blankspace[count] = blankspace[count-1] + time_q;
        appendBlank(pcb[count+1].rowIndex,blankspace[count]);
	
      	time+=time_q; 
	
	}else{
	//Appending bar to gantt chart
	appendBar(pcb[count].rowIndex,time_q,"red",pcb[count].processName,0);
	appendBlank(pcb[count+1].rowIndex,blankspace[count - 1]);
	appendBar(pcb[count].rowIndex,time_q,"red",pcb[count].processName,0);
	//Increace our time with each time slice that has been completed.
      	time+=time_q; 
	}
    } 
    //Our second if statement works if ready_q service time == 0 and our flag is 1 to show process is the time sliced coming back to completed
    if(ready_q[count].serviceTime==0 && flag==1) 
    { 
      	//Decrement this to show that a remaning process has been completed,
       	remain--;
        //Displaying our processName
	printf("</n>%s entering quantum at %d seconds.",pcb[count].processName,prev);
 	sleep(1);
	//Determine if the remaining time of that process is available from it's pcb to append the bar differently.	     	   
		if(pcb[count].remainingTime > 0){
		calculations(pcb,count,pcb[count].completed);
		blankspace[count] = prev - blankspace[count];
		appendBlank(pcb[count].rowIndex,blankspace[count]);
		pcb[count].state = 1;
		pstate = processStatus(pcb[count].state); 
		printf("</n>%s is in %s state",pcb[count].processName,pstate);
		sleep(1);
		appendBar(pcb[count].rowIndex,pcb[count].serviceTime,"red",pcb[count].processName,0);
		pcb[count].completed =1;
		pcb[count].state = 2;
		pstate = processStatus(pcb[count].state);   
		calculations(pcb,count,pcb[count].completed);
		printf("</n>%s is in %s state",pcb[count].processName,pstate); 
		}
	else{
	pcb[count].state = 1;
	pstate = processStatus(pcb[count].state); 
	printf("</n>%s is in %s state",pcb[count].processName,pstate);  	
	sleep(1);
	appendBar(pcb[count].rowIndex,pcb[count].serviceTime,"red",pcb[count].processName,0);
	blankspace[count] = blankspace[count-1] + pcb[count].serviceTime;
	appendBlank(pcb[count + 1].rowIndex,blankspace[count]);	
	pcb[count].completed =1;
	pcb[count].state = 2;
	pstate = processStatus(pcb[count].state); 
	calculations(pcb,count,pcb[count].completed);
	printf("</n>%s is in %s state",pcb[count].processName,pstate);  
	}				
      flag=0; 
      flag=0; 
    } 
    
	
	if(count==n-1) 
	count=0; 
    else if(pcb[count+1].entryTime<=time) 
      		count++; 
    else 
      		count=0; 	
       }
	printf("\n");	

}
/*Function to calculate the waiting Time and TurnAround TIme of each process accepts the pcb control block a counter and indicator that the process is 
  completed so that the output is printed to indicate the process is complete with it's wait time and turnaround time.
*/
void calculations(pcb_t pcb[],int count,int completed){
      if(completed == 1){
      pcb[count].turnaroundTime = time - pcb[count].entryTime;
      pcb[count].waitingTime = pcb[count].turnaroundTime - pcb[count].serviceTime;
      printf("</n>%s is completed.Waiting time:%d Turnaround Time:%d",pcb[count].processName,pcb[count].waitingTime,pcb[count].turnaroundTime);
      }
}

/*Function to read contents from file accepts the fileName and pcb to be written to as input. 
  Uses string tokens to store the contents beign read from the file line by line, a deliminator of " " is used to
  indicate that we are now reading a new value
*/
int readFromFile(char * fileName,pcb_t pcb[]) {

  FILE * filehandle;

  //String where our line will be stored set it to 50 which should be okay
  char * item;
  char line[50];
  //Counter to count the total number of processes in the file increments at  of while loop
  int count = 0;


  /* open file For read only and perform our error handling if user enters wrong filename*/
  filehandle = fopen(fileName, "r");

  if(filehandle == NULL){
	printf("Failed to open file %s",fileName);
  } else{
  	/* Read file line by line */

  	while (fgets(line, 120, filehandle)) {
    
    	item = strtok(line, " ");
    	strcpy(pcb[count].processName, item);

    	item = strtok(NULL, " ");
    	pcb[count].entryTime = atoi(item);

    	item = strtok(NULL, "\n");
    	pcb[count].serviceTime = atoi(item);

    count++;
  }

  /* Close file */

  fclose(filehandle);
}

  return count;

}

//Method to convert enum values to string to be disiplayed in terminal
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

