#include"Neuron.h"
#include<stdio.h>
#include <unistd.h>
#include"NetSL.h"
//#include<time.h>

int main(){
//print_time();
struct NetU* u=NetUGen(10);
struct Network* Net1;
//u->NetNum=1;

//u->NetList[0]=NetGen(10000);
//NetInit(u->NetList[0]);
//ConInit(u->NetList[0]);
NetULoad("./tt");
//for(int j=0;j<=100000;j++){
//StepNet(u->NetList[0]);
//printf("%d\n",j);
//print_time();
//}
//pause();
}
