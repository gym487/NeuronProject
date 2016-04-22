#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include <ctype.h>
#include"kdtree.c"
int p;
struct IzhNeu{
float a,b,c,d,u,v,I;		//Basic arguments of Izhikevich Neuron
float x,y,z;
unsigned int InNum,Nnum;
char fired;
struct IzhNeu** InNeus;//In fact it is the list of output-to neurons.
float* S;
};
struct Network{
struct IzhNeu** Neus;
unsigned int NeuNum;
unsigned int NetNum;//
};
unsigned long seed=0;
void SeedInti(){		//Intitial a seed for Rand()
srand((unsigned)time(NULL));
}
int RandIntiFlag=0;
float FloatRandNum(){
				//Generate a random number in float
				// between 0 and 1 
float a;
if(RandIntiFlag==0)
a=rand()/(float)RAND_MAX;
return a;
}
float FSqur(float a){
return a*a;
}

void ExNeuInit(struct IzhNeu* Neu){
if(Neu!=NULL){
float re=FloatRandNum();
re=re*re;
(*Neu).a=0.02;
(*Neu).b=0.2;
(*Neu).c=-65+15*re;
(*Neu).d=8-6*re;
(*Neu).v=-65;
(*Neu).u=((*Neu).b)*((*Neu).v);
}
}
void InNeuInit(struct IzhNeu* Neu){
if(Neu!=NULL){
float re=FloatRandNum();
re=re*re;
(*Neu).a=0.02+0.08*re;
(*Neu).b=0.2-0.05*re;
(*Neu).c=-65;
(*Neu).d=2;
(*Neu).v=-65;
(*Neu).u=((*Neu).b)*((*Neu).v);

}
}
void ExWeightsInit(struct IzhNeu* Neu){
if(Neu!=NULL){
for(unsigned int i=0;i<(*Neu).InNum;i++){
(*Neu).S[i]=FloatRandNum()*0.5;
}
}
}
void InWeightsInit(struct IzhNeu* Neu){
if(Neu!=NULL){
for(unsigned int i=0;i<(*Neu).InNum;i++){
(*Neu).S[i]=-FloatRandNum();
}
}
}
struct IzhNeu* ExNeuGen(unsigned int num,unsigned int nnum){
struct IzhNeu* Neu=malloc(sizeof(struct IzhNeu));
if(Neu!=NULL){
(*Neu).InNum=num;
ExNeuInit(Neu);
(*Neu).S=malloc(num*sizeof(float));
(*Neu).InNeus=malloc(num*sizeof(struct IzhNeu*));
(*Neu).Nnum=nnum;
}
ExWeightsInit(Neu);
return Neu;
}
//
struct IzhNeu* InNeuGen(unsigned int num,unsigned int nnum){
struct IzhNeu* Neu=malloc(sizeof(struct IzhNeu));
if(Neu!=NULL){
(*Neu).InNum=num;
InNeuInit(Neu);
(*Neu).S=malloc(num*sizeof(float));
(*Neu).InNeus=malloc(num*sizeof(struct IzhNeu*));
(*Neu).Nnum=nnum;
}
InWeightsInit(Neu);
return Neu;
}
void NetInit(struct Network* in){//
if(in!=NULL){
for(unsigned int i=0;i<(*in).NeuNum;i++){
if(FloatRandNum()>0.8){
(*in).Neus[i]=InNeuGen(1000,i);
//puts("e");
}else{
(*in).Neus[i]=ExNeuGen(1000,i);
//puts("i");
}
}
}
}
struct Network* NetGen(unsigned int num){

struct Network* Net;
Net=malloc(sizeof(struct Network));

(*Net).NeuNum=num;

(*Net).Neus=malloc(num*(sizeof(struct IzhNeu*)));

return Net;
}

void StepV(struct IzhNeu* Neu){
(*Neu).fired=0;

if((*Neu).v>=30){

(*Neu).fired=1;
(*Neu).v=(*Neu).b;
(*Neu).u=(*Neu).d+(*Neu).u;

}
(*Neu).v=(*Neu).v+(0.04*(*Neu).v*(*Neu).v+5*(*Neu).v+140-(*Neu).u+(*Neu).I);

(*Neu).u=(*Neu).u+(*Neu).a*((*Neu).b*(*Neu).v-(*Neu).u);
(*Neu).I=0;
}
void ConInit(struct Network* net){
puts("ok");
struct heap* pre;
struct kdtree* ptree;
double pos[3],pt[3];
ptree=kd_create(3);
int j=0;
for(int i=0;i<(*net).NeuNum;i++){

(*((*net).Neus[i])).x=FloatRandNum();
(*((*net).Neus[i])).y=FloatRandNum();
(*((*net).Neus[i])).z=FloatRandNum();
}
for(int i=0;i<net->NeuNum;i++){
kd_insert3(ptree,(double)net->Neus[i]->x,(double)net->Neus[i]->y,(double)net->Neus[i]->z,(net->Neus)[i]);
printf("inserting tree...%d x y z %f %f %f\n",i,net->Neus[i]->x,net->Neus[i]->y,net->Neus[i]->z);
}
puts("ok2");
for(int i=0;i<net->NeuNum;i++){
printf("Init...%d of %d Neurons...\n",i,net->NeuNum);
pt[0]=net->Neus[i]->x;
pt[1]=net->Neus[i]->y;
pt[2]=net->Neus[i]->z;
pre=kd_nearest_n( ptree, pt, 800,1 );
for(j=0;j<(*net).NeuNum*0.8&&(pre->size>0);j++){
net->Neus[i]->InNeus[j]=(struct IzhNeu*)heap_get_max(pre)->item->data;
heap_remove_max(pre);
}
printf("%d\n ",j);
//puts("ok");
for(int j=(*net).NeuNum*0.8;j<(*net).NeuNum;j++){
(*((*net).Neus[i])).InNeus[j]=(*net).Neus[rand()%(*net).NeuNum];
}
  heap_free(pre);

}
 // kd_free(ptree);
//puts("ok");
}
void StepI(struct IzhNeu* Neu){
float pt[3];
struct IzhNeu* in;
if((*Neu).fired==1){
for(int i=0;i<(*Neu).InNum;i++){

(*((*Neu).InNeus[i])).I=(*Neu).S[i]+(*Neu).S[i]+(*((*Neu).InNeus[i])).I;
}
}
}
void StepNet(struct Network* net){
for(int i=0;i<(*net).NeuNum;i++){

StepV((*net).Neus[i]);

//StepI((*net).Neus[i]);

}
}
