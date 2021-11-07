#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TOTALFORK 21
#define N 600

int cul(int n)
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

}

int main()
{
	pid_t pids[TOTALFORK], pid;
	int runProc = 0;
	int status;

	for(int i=0;i<TOTALFORK;i++) {
		pids[runProc] = fork();

		if(pids[runProc] < 0) {
			printf("error\n");
			return -1;
		}
		else if(pids[runProc] == 0) {

			// 3개의 그룹으로 연산의 횟수를 다르게 줌
			/*if(i >= 0 && i <7)
				cul(200);
			else if(i>=7 && i<14)
				cul(400);
			else
				cul(600);*/

			cul(200); //다 같은 연산을 줌

			printf("%ld process ends\n", (long)getpid());
			exit(0);
		}
		else {
			printf("%d process begins\n", pids[runProc]);
		}

	}

	for(int i=0;i<TOTALFORK;i++)
		wait(&status);

//	wait(&status);
//	sleep(5);
	printf("-------- All processes end --------\n");
    return 0;
}
