#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
struct IzhNeu{
float a,b,c,d,u,v,I;		//Basic arguments of Izhikevich Neuron
float x,y,z;
unsigned int InNum,Nnum;
char fired;
struct IzhNeu** InNeus;
float* S;
};
struct Network{
struct IzhNeu** Neus;
unsigned int NeuNum;
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

}
void ConInit(struct Network* net){
float* dis;
int* yes;
dis=malloc(((*net).NeuNum)*sizeof(float));
yes=malloc(((*net).NeuNum)*sizeof(int));
for(int i=0;i<(*net).NeuNum;i++){

(*((*net).Neus[i])).x=FloatRandNum();
(*((*net).Neus[i])).y=FloatRandNum();
(*((*net).Neus[i])).z=FloatRandNum();
}

for(int i=0;i<((*net).NeuNum);i++){
int g=(*net).NeuNum*0.8;
memset(dis,0,(*net).NeuNum*sizeof(float));
memset(yes,0,(*net).NeuNum*sizeof(int));
printf("%d \n",i);
for(int j=0;j<g;j++){

dis[j]=sqrt(FSqur((*((*net).Neus[i])).x-(*((*net).Neus[j])).x)+FSqur((*((*net).Neus[i])).y-(*((*net).Neus[j])).y)+FSqur((*((*net).Neus[i])).z+(*((*net).Neus[j])).z));//TODO: Here needs change to KD-TREE to find the nearest neuron. The speed now is TOO SLOW to do anything.
}
for(int j=0;j<((*((*net).Neus[i])).InNum);j++){
float l=1000;
int m=0;
for(int k=0;k<g;k++){//
if(l>dis[k]&&yes[k]!=1){
l=dis[k];
m=k;
}
}
yes[m]=1;
(*((*net).Neus[i])).InNeus[j]=(*net).Neus[m];
}
for(int j=g;j<(*net).NeuNum;j++){
(*((*net).Neus[i])).InNeus[j]=(*net).Neus[rand()%(*net).NeuNum];
}
}

free(dis);
free(yes);
}
void StepI(struct IzhNeu* Neu){
(*Neu).I=0;
struct IzhNeu* in;
for(int i=0;i<(*Neu).InNum;i++){
in=(*Neu).InNeus[i];
(*Neu).I=(*Neu).I+(*in).fired*(*Neu).S[i];
}
}
void StepNet(struct Network* net){
for(int i=0;i<(*net).NeuNum;i++){

StepV((*net).Neus[i]);

StepI((*net).Neus[i]);

}
}
