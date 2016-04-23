#include<stdio.h>
#define __USE_FILE_OFFSET64
//#include"Neuron.h"
#include<sys/io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#define sit sizeof(off_t)
//TODO:Add the function of Saving / Loading network on disk file HERE.
off_t nuw(struct IzhNeu *nu,off_t a,void *in){
int i;
*(int*)(in+a)=nu->InNum;
for(i=0;i<nu->InNum;i++){
*(int*)(in+a+(i+1)*sizeof(int))=nu->InNeus[i]->Nnum;
}
return a+(i+1)*sizeof(int);
}
off_t ntw(struct Network *nt,off_t a,void *in){
int i;
off_t b,c;
*(int*)(in+a)=nt->NeuNum;
c=a+sizeof(int);
b=a+sizeof(int)+sit*nt->NeuNum;
for(i=0;i<nt->NeuNum;i++){
*(off_t*)(c+sit*i+in)=b;
b=nuw(nt->Neus[i],b,in);
}
return b;
}



void NetUSave(char* a,struct NetU* netu){
int fp;
fp=open(a,O_RDWR|O_CREAT,0777);
//long b,c,d,e,f;
off_t b;
b=sizeof(int);
for(int i=0;i<netu->NetNum;i++){
b+=sizeof(int);
b+=sit;
for(int j=0;j<netu->NetList[i]->NeuNum;j++){
b+=sizeof(int);
b+=sit;
b+=sizeof(int)*netu->NetList[i]->Neus[j]->InNum;
}
}
printf("size:%ld\n",b);
void *memm=malloc(b);
int k;
off_t c,d;
*(int*)(memm)=netu->NetNum;
c=sizeof(int);
b=sizeof(int)+sit*netu->NetNum;
for(int i=0;i<netu->NetNum;i++){
*(off_t*)(c+sit*i+memm)=d;
b=ntw(netu->NetList[i],d,memm);
}
write(fp,memm,b);
free(memm);
close(fp);
}
struct Network* NetLoad(char* a){
int fp;
fp=fp=open(a,O_RDONLY);
//
}


