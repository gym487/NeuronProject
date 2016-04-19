#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
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
#if 0
struct kdtree{
float x,y,z;//location
struct kdtree *l,*r,*p;//left child, right chaild, parent
void* po;//poniter
int deepth;
};

int jy(float a){
if(a>0)
return 1;
if(a<0)
return -1;
if(a==0)
return 0;
}
struct NeuList{
struct IzhNeu** nps;//Neuron PointerS
int num;
};
int compx(const void* a,const void* b){
if(a!=NULL&&b!=NULL)
return jy((((struct IzhNeu*)a)->x)-(((struct IzhNeu*)b)->x));
}
int compz(const void* a,const void* b){
if(a!=NULL&&b!=NULL)
return jy((((struct IzhNeu*)a)->z)-(((struct IzhNeu*)b)->z));
}
int compy(const void* a,const void* b){
if(a!=NULL&&b!=NULL)
return jy((((struct IzhNeu*)a)->y)-(((struct IzhNeu*)b)->y));
}

void NeuSortX(struct NeuList* in){
qsort((*(in->nps)),(in->num),sizeof(struct IzhNeu),compx);
}
void NeuSortY(struct NeuList* in){
qsort((*(in->nps)),(in->num),sizeof(struct IzhNeu),compy);
}
void NeuSortZ(struct NeuList* in){
qsort((*(in->nps)),(in->num),sizeof(struct IzhNeu),compz);
}
struct NeuList* NeuListGen(struct Network* in){
struct NeuList* nl=malloc(sizeof(struct NeuList*));
nl->num=in->NeuNum;
nl->nps=malloc((in->NeuNum)*sizeof(struct IzhNeu*));
for(int i=0;i<(in->NeuNum);i++){
nl->nps[i]=in->Neus[i];
}
return nl;
}
struct kdtree* kdNodeGen(struct NeuList* xnl,int xbegin,int xend,
		struct NeuList* ynl,int ybegin,int yend,
		struct NeuList* znl,int zbegin,int zend,
				struct kdtree* pa,int dep){
int mid=0;

//printf("%d %d %d\n",dep,xbegin,xend);
struct kdtree* node=NULL;

if(dep%3==0){
mid=(xbegin+xend)/2;
if(mid!=xbegin&&mid!=xend){
node=malloc(sizeof(struct kdtree));
p++;
node->deepth=dep;
//printf("%d %d %d %d\n",dep,xbegin,mid,xend);
node->x=xnl->nps[mid]->x;
node->y=xnl->nps[mid]->y;
node->z=xnl->nps[mid]->z;
node->po=xnl->nps[mid];

node->p=pa;

node->l=kdNodeGen(xnl,xbegin,mid,ynl,ybegin,yend,znl,zbegin,zend,node,dep+1);
node->r=kdNodeGen(xnl,mid,xend,ynl,ybegin,yend,znl,zbegin,zend,node,dep+1);
}
}
if(dep%3==1){
mid=(ybegin+yend)/2;
if(mid!=ybegin&&mid!=yend){
node=malloc(sizeof(struct kdtree));
p++;
node->deepth=dep;
node->x=ynl->nps[mid]->x;
node->y=ynl->nps[mid]->y;
node->z=ynl->nps[mid]->z;
node->po=ynl->nps[mid];
node->p=pa;
node->l=kdNodeGen(xnl,xbegin,xend,ynl,ybegin,mid,znl,zbegin,zend,node,dep+1);
node->r=kdNodeGen(xnl,xbegin,xend,ynl,mid,yend,znl,zbegin,zend,node,dep+1);
}
}
if(dep%3==2){
mid=(ybegin+yend)/2;
if(mid!=ybegin&&mid!=yend){
node=malloc(sizeof(struct kdtree));
p++;
node->deepth=dep;
node->x=znl->nps[mid]->x;
node->y=znl->nps[mid]->y;
node->z=znl->nps[mid]->z;
node->po=znl->nps[mid];
node->p=pa;
node->l=kdNodeGen(xnl,xbegin,xend,ynl,ybegin,yend,znl,zbegin,mid,node,dep+1);
node->r=kdNodeGen(xnl,xbegin,xend,ynl,ybegin,yend,znl,mid,zend,node,dep+1);
}
}
return node;
}
struct kdtree* kdGen(struct Network* in){
struct NeuList* nlx=NeuListGen(in);
struct NeuList* nly=NeuListGen(in);
struct NeuList* nlz=NeuListGen(in);

NeuSortX(nlx);
NeuSortY(nlx);//
NeuSortZ(nlx);

return kdNodeGen(nlx,-1,in->NeuNum,nly,-1,in->NeuNum,nlz,-1,in->NeuNum,NULL,0);
}
#endif

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
printf("%d a\n",i);
for(int j=0;j<g;j++){

dis[j]=sqrt(FSqur((*((*net).Neus[i])).x-(*((*net).Neus[j])).x)+FSqur((*((*net).Neus[i])).y-(*((*net).Neus[j])).y)+FSqur((*((*net).Neus[i])).z+(*((*net).Neus[j])).z));//TODO: Here needs change to KD-TREE to find the nearest neuron. The speed now is TOO SLOW to do anything.
}
for(int j=0;j<g;j++){
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

//free(dis);
dis=NULL;

free(yes);
yes=NULL;

/*
struct kdtree* ptree;
ptree=kd_create(3);
for(int i=0;i<in->NeuNum;i++){
kd_insert3(ptree,in->Neus[i]->x,in->Neus[i]->y,in->Neus[i]->z,in->Neus[i]);
}
for(int i=0;i<in->NeuNum;i++){
}
}
*/
void StepI(struct IzhNeu* Neu){

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
