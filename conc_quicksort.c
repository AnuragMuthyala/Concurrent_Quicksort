#define _POSIX_C_SOURCE 199309L 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <limits.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>
#include <inttypes.h>
#include <math.h>

void QuickSort(int*,int,int);
void swap(int*,int*);
void normal_quicksort(int*,int,int);
int partition(int*,int,int);

void main(){

struct timespec ts;
key_t key = IPC_PRIVATE;
int n,*s,*b;
scanf("%d",&n);
int shmid = shmget(key,n * sizeof(int),0666|IPC_CREAT);
s = (int*)shmat(shmid,(void*)0,0);
b = malloc(n * sizeof(int));
for(int i = 0;i < n;i++){
scanf("%d",&s[i]);
b[i] = s[i];
}

printf("Done..\n");

clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
long double st = ts.tv_nsec/(1e9)+ts.tv_sec;

QuickSort(s,0,n - 1);

clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
long double en = ts.tv_nsec/(1e9)+ts.tv_sec;

long double t1 = en - st;

clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
st = ts.tv_nsec/(1e9)+ts.tv_sec;

printf("Done..\n");

normal_quicksort(b,0,n - 1);

printf("Done..\n");
clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
en = ts.tv_nsec/(1e9)+ts.tv_sec;

long double t2 = en - st;

printf("time:%Lf\n",t1);
printf("time:%Lf\n",t2);

printf("Normal quicksort is [%Lf] faster than concurrent quicksort\n",t1/t2); 

}

void QuickSort(int *s,int low,int high){

if(low >= high)
_exit(1);

else if(high - low <= 4){
int i,j,temp;
for(i = low + 1;i <= high;i++){
temp = s[i]; 
for(j = i - 1;j >= low && s[j] > temp;j--)
s[j + 1] = s[j];
s[j + 1] = temp;
}
_exit(1);
}

else{
int pivot;
pivot = (low + high / 2);
int i,j,pos;
swap(&s[low],&s[pivot]);
pivot = low;
i = low + 1,j = high;
while(i < j){
while(i != high && s[i] < s[pivot])
i++;

while(j != low && s[j] > s[pivot])
j--;

if(i < j)
swap(&s[i++],&s[j--]);

if(i >= j)
swap(&s[j],&s[pivot]);
}

int pid;

pid = fork();

if(pid == 0){
QuickSort(s,low,j - 1);
_exit(1);
}
else
{
int pid1;
pid1 = fork();

if(pid1 == 0){
QuickSort(s,j + 1,high);
_exit(1);
}

else
waitpid(pid1,NULL,0);
waitpid(pid,NULL,0);

}
}
}

void swap(int *a,int *b){
int temp;
temp = *a;
*a = *b;
*b = temp;
}

void normal_quicksort(int *s,int low,int high){

if(low < high){

int j = partition(s,low,high);
normal_quicksort(s,low,j - 1);
normal_quicksort(s,j + 1,high);

}
}

int partition(int *s,int low,int high){

int pivot;
pivot = (low + high / 2);
int i,j;
swap(&s[low],&s[pivot]);
pivot = low;
i = low + 1,j = high;
while(i < j){
while(i != high && s[i] < s[pivot])
i++;

while(j != low && s[j] > s[pivot])
j--;

if(i < j)
swap(&s[i++],&s[j--]);

if(i >= j)
swap(&s[j],&s[pivot]);
}
return j;

}
