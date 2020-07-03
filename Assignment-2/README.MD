# TASK1 && TASK2 Program Instruction Manual

## How To Compile The Program.
1. Go to your linux terminal environment
2. Make sure you are in the directory where non-preempt-28897854 is located.
3. Enter the following on the terminal :```make -f Makefile```<br>
You have to specify which program you want to compile by typing either :```make task1.o```or ```make task2.o```
4. After you have complied using makefile then your executable exists.<br>
To run the program of your choice enter: ```iol -- ./task1.o``` or ```iol -- ./task2.o```
5. You can enter a custom filename to the argument :```iol -- ./task2.o kudzai.txt``` the file has to be in the same directory


### How to add process data.
1. To add data to the file you can do this manually or use a cool program called create-data.
2. When adding manually you need to know the file must store :
- processName which should be less than 10.
- processArrivalTime in seconds.
- processService in seconds.<br>
  There must be a space between this data in the file and don’t leave an empty line at the end of the file.
3. Go to your linux environment again and compile the create-data file by typing ```gcc -g create-data.c - o create-data```<br>
   And run the executable by typing ```iol -- ./create-data```.

### Functionality offered by Task 1 Program.
1. The program is a `non preemptive` first come first serve scheduling algorithm.
2. The program will accept process arrival time and service/bust time and the process name to be used in the scheduler.
3. The program will append each of the processes in a `FCFS` manner to the gantt chart and show their wait time on the chart.
4. The program will display the name of the process in the scheduler and the processes turn around and wait time when done.
5. Whilst "executing" the processes the scheduler will display the process states of each of the processes.
6. The program will sleep for a second when a process is executing.
7. The program also accepts a custom user input file which contains process data if there is no file the program will refer to default file process-data.txt

### Functionality offered by Task 2 Program.
1. The program prints out the time of each process on the gantt chart whilst under the time slice.
2. The program displays the process Turnaround of each process and the corresponding waiting time.
3. The program works out if the process is in ready state or running state by checking constantly whether a process is completed
4. The program displays the  state of the process as it changes from ready to exit.
5. The program also accepts a custom user file as an argument input but the file has to be a text of else a file handling error will occur make sure you type a file such as data.txt.
6. If there is no custom file then the program will use the default process-data.txt.
