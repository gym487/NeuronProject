#include"Neuron.h"
#include<stdio.h>
#include <unistd.h>
//#include<time.h>

int main(){
//print_time();
struct Network* Net1;
Net1=NetGen(1000000);
NetInit(Net1);
ConInit(Net1);
for(int j=0;j<=100000;j++){
StepNet(Net1);
printf("%d\n",j);
//print_time();
}
//pause();
}
