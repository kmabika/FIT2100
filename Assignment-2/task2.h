#define MAX 11

typedef enum {
  READY,
  RUNNING,
  EXIT
}process_state_t;

typedef struct {
  char processName[MAX];
  int pid;
  int waitingTime;
  int turnaroundTime;
  int entryTime;
  int serviceTime;
  int quatum;
  int remainingTime;
  int rowIndex;
  int completed;
  process_state_t state;
}pcb_t;

char * filename;
char * pstate;
pcb_t pcb[MAX];
pcb_t ready_q[MAX];
int rowIndex, length[MAX],i,blankspace_length;
int flag,exit_time;
int blankspace[MAX];
int remain,n,wait_time,turnaround_time,count,time;

void roundRobin();
void calculations(pcb_t pcb[],int count,int completed);
char * processStatus(int status);
int readFromFile(char * fileName,pcb_t pcb[]);
