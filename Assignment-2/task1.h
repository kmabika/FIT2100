#define MAX 11

typedef enum {
  READY,
  RUNNING,
  EXIT
}process_state_t;
//Struct which we added waiting time and turnarond time of each process dont forget to change the name process_cb;when you change it change everything.
typedef struct {
  char processName[MAX];
  int pid;
  int waitingTime;
  int turnaroundTime;
  int entryTime;
  int serviceTime;
  process_state_t state;
}process_cb;

int i,indicator,rowIndex,length[MAX];
char * filename;
process_cb pcb[MAX];
int pburst_time,pservice_time,waitingTime,service_time;
char * process_state;


void fcfs();
int readFile(char * fileName,process_cb pcb[]);
void findWaitTurnAround(process_cb pcb[], int burst_time, int entry_time, char * process_name, int process_id);
char * processStatus(int status);
