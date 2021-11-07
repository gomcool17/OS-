#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/wait.h>

#define TOTALFORK 21
#define N 700

void cul(int n)
{
	int A[N][N], B[N][N], C[N][N];
			
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++) {		
			A[i][j] = 1;
			B[i][j] = i;
		}
		
			
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			for(int k=0;k<n;k++){
				C[i][j]+=A[i][k]*B[k][j];
			}  
		}
	}

	return;
}

int main()
{
	pid_t pids[TOTALFORK], pid;
	int which = PRIO_PROCESS;
	int runProc = 0;
	int status;
	int cnt = 1;

	for(int i=0;i<TOTALFORK;i++) {
		pids[runProc] = fork();
		
		if(pids[runProc] < 0) {
			printf("error\n");
			return -1;
		}
		else if(pids[runProc] == 0) {
			int ret;
			int which = PRIO_PROCESS;
			
			if(i>=0 && i<7) {
				nice(19);
				cul(300);
			}
			else if(i>=7 && i<14) {
				nice(0);
				cul(450);
			}
			else {
				nice(-19);
				cul(600);
			}
			
			//printf("%ld process pri = %d, i = %d\n", (long)getpid(), ret, i);
			//cul();
  		
 			ret = getpriority(which,0); 
			printf("%ld process ends\n", (long)getpid());
			
			exit(0);
		}
		else {
			int ret;
			
			printf("%d process begins\n", pids[runProc]);
		}

	}

	for(int i=0; i<TOTALFORK;i++)
		wait(&status);

	printf("-------- All processes end --------\n");
    return 0;
}
