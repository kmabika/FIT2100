//FIT2100 Assignment #2 data creation utility.
//Written by Daniel Kos, Sep 2019.

//This program can be used to generate process data files in the format
//required to be read in by your program. 
//(NOTE: You are *not* required to understand all the code in this file to
//complete the assignment.)

//To compile: gcc create-data.c -o create-data
//To run:     iol -- ./create-data


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char processName[11];
    int entryTime;
    int serviceTime;
    
} proc_data_t;

//hold data for up to 10 processes.
proc_data_t processInfo[10];
int numProcesses = 0;


void takeProcessData() {
//reads process data from the terminal

    //read in the process name
    fgets(processInfo[numProcesses].processName, 11, stdin);

    //validate process name: remove any spaces or newlines by terminating
    //the string at the first instance of either.
    char* invalidCharPosition = strpbrk(processInfo[numProcesses].processName, " \n");
    if(invalidCharPosition) *invalidCharPosition='\0';    
    if(processInfo[numProcesses].processName[0]=='\0') { //blank name!
        strcpy(processInfo[numProcesses].processName, "?");
    }
    
    //now read in the entry and service times; these are separated by a comma:
    scanf(" %d,%d", &(processInfo[numProcesses].entryTime), 
          &(processInfo[numProcesses].serviceTime));
          
    //append the new process data to the table on the screen
    printf("<tabl.push <tr <td {%s}><td {%d}><td {%d}>>>\n",
           processInfo[numProcesses].processName,
           processInfo[numProcesses].entryTime,
           processInfo[numProcesses].serviceTime
    );      
          
    numProcesses++;
    
    if(numProcesses >= 10) {
        printf("<processEntry = {Max 10 processes already entered}>");
    }

}


void writeFile(const char* filename) {
//writes the contents of the (global) processInfo array to the specified file.

    FILE* filePtr = fopen(filename, "w");
    if(!filePtr) { //file error
        printf("Error opening file: %s for writing!</n>\n",filename);
        return;
    }
    
    for(int i=0; i<numProcesses; i++) {
    //write the proceses from the array into the file
        fprintf(filePtr, "%s %d %d\n", 
                processInfo[i].processName,
                processInfo[i].entryTime,
                processInfo[i].serviceTime
        );
    }
    
    fclose(filePtr);
    printf("File %s written successfully.</n>", filename);

}


int main(int argc, char* argv[]) {
    char filename[256];
    
    
    char* termType = getenv("TERM");
    if(strcmp(getenv("TERM"), "iol") != 0) {
	//program must be run through ioL environment.
        fprintf(stderr, "Usage: run the command as follows:\n iol -- %s\n",argv[0]);
	exit(1);
    }

    printf("<program.title {FIT2100 process data creation utility}>");

    printf("<span size=24,{pt} {Welcome to the process data creation utility.</n>}>");
    printf("You can enter information for up to 10 processes, then save the data to a file.</n>");
    printf("This produces the same file data as your assignment is expected to read.</p></p>");

    //print a table of entered processes
	printf("<tabl:table <tr bold=true <td {Process name |}><td {Entry time |}><td {Service time }>>>");

    //print a dialog box for entering new processes
	printf(
		"</p></p><processEntry:box {<span bold=true {Add process...}></p>"
		"    Process name: <pn:input maxLength=10></n>"
		"    Entry time: <et:input maxLength=2 width=3,{em}></n>"
		"    Service time: <st:input maxLength=2 width=3,{em}></n>"
		"    <button {Add record} onClick="
		"        <putLn {A<pn></n><et>,<st>}>,"
		"        <pn.clear>,<et.clear>,<st.clear>"
		"    >"
		"}></t>"
    );
	      
    //print a dialog box for writing the process data to a file
    printf(
        "<save:box rotate=0 {<span bold=true {Write process data...}></p>"
        "    <filename:input {process-data.txt} maxLength=255>"
        "    <button {Save} onClick=<putLn {S<filename>}>></n>"
        "    <span size=12 {Note: will overwrite existing file contents.}>"
        "}></p>"
    );
    
    //this is used for the file saving animation...
    printf("<saveSpin:timer angle=1 limit=18 onTimer=<save.rotate=<add 20, save.rotate>>>");


    while(1) {	
	    switch(getchar()) {
	        case 'A': //add process
	            takeProcessData();
	            break;
	        case 'S': //save file
                fgets(filename, 256, stdin); //read filename from stdin
                char* nlPosition = strpbrk(filename, "\n");
                if(nlPosition) *nlPosition='\0'; //trim any newline from end.
                printf("<saveSpin.angle=1><saveSpin=1,{ms}>");
                writeFile(filename);
	            break;
	        default: //possibly a newline to skip
	            continue;
	    }
	}
    return 0;	
}

