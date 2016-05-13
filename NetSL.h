#include<stdio.h>
#define __USE_FILE_OFFSET64
#include<sys/io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#define sit sizeof(off_t)
void* fpp;
int fps=0;
int fpps=0;
void mwri( int g,void* b,int c){
if(fps>9000000){
write(g,fpp,fps);
fps=0;
}

memcpy(fpp+fps,b,c);
fps+=c;
}
void mrri(int g,void *b,int c){

if(fpps>=9000000){
lseek(g,-1000000,SEEK_CUR);
read(g,fpp,10000000);
fpps-=9000000;
}
memcpy(b,fpp+fpps,c);
fpps+=c;
}

void NetUSave(char* a,struct NetU* netu){
int fp;
fpp=malloc(10000000*sizeof(char));

fp=open(a,O_RDWR|O_CREAT,0777);

mwri(fp,&netu->NetNum,sizeof(netu->NetNum));
printf("Saving NetU..%d nets\n",netu->NetNum);
for(int i=0;i<netu->NetNum;i++){
printf("Saving Net %d \n",i);
mwri(fp,&netu->NetList[i]->NeuNum,sizeof(netu->NetList[i]->NeuNum));
for(int j=0;j<netu->NetList[i]->NeuNum;j++){
printf("Saving Neu %d \n",j);
mwri(fp,&netu->NetList[i]->Neus[j]->InNum,sizeof(netu->NetList[i]->Neus[j]->InNum));
mwri(fp,&netu->NetList[i]->Neus[j]->a,sizeof(netu->NetList[i]->Neus[j]->a));
mwri(fp,&netu->NetList[i]->Neus[j]->b,sizeof(netu->NetList[i]->Neus[j]->b));
mwri(fp,&netu->NetList[i]->Neus[j]->c,sizeof(netu->NetList[i]->Neus[j]->c));
mwri(fp,&netu->NetList[i]->Neus[j]->d,sizeof(netu->NetList[i]->Neus[j]->d));
mwri(fp,&netu->NetList[i]->Neus[j]->u,sizeof(netu->NetList[i]->Neus[j]->u));
mwri(fp,&netu->NetList[i]->Neus[j]->v,sizeof(netu->NetList[i]->Neus[j]->v));
mwri(fp,&netu->NetList[i]->Neus[j]->I,sizeof(netu->NetList[i]->Neus[j]->I));
mwri(fp,&netu->NetList[i]->Neus[j]->x,sizeof(netu->NetList[i]->Neus[j]->x));
mwri(fp,&netu->NetList[i]->Neus[j]->y,sizeof(netu->NetList[i]->Neus[j]->y));
mwri(fp,&netu->NetList[i]->Neus[j]->z,sizeof(netu->NetList[i]->Neus[j]->z));
for(int k=0;k<netu->NetList[i]->Neus[j]->InNum;k++){
mwri(fp,&netu->NetList[i]->Neus[j]->InNeus[k]->Nnum,sizeof(netu->NetList[i]->Neus[j]->InNeus[k]));
mwri(fp,&netu->NetList[i]->Neus[j]->S[k],sizeof(float));
}
}
}
write(fp,fpp,fps);
fps=0;
free(fpp);
close(fp);
}
struct NetU* NetULoad(char* a){
int fp;
int nnum;
fpp=malloc(10000000*sizeof(char));

fp=open(a,O_RDWR|O_CREAT,0777);
read(fp,fpp,10000000);
struct NetU* netu=malloc(sizeof(struct NetU));
mrri(fp,&netu->NetNum,sizeof(netu->NetNum));
netu->NetList=malloc(netu->NetNum*sizeof(void*));
for(int i=0;i<netu->NetNum;i++){
netu->NetList[i]=malloc(sizeof(struct Network));
}
printf("Loading NetU..%d nets\n",netu->NetNum);
for(int i=0;i<netu->NetNum;i++){

mrri(fp,&netu->NetList[i]->NeuNum,sizeof(netu->NetList[i]->NeuNum));
printf("Loading Net %d \n",i);

netu->NetList[i]->Neus=malloc(netu->NetList[i]->NeuNum*sizeof(void *));
for(int j=0;j<netu->NetList[i]->NeuNum;j++){
netu->NetList[i]->Neus[j]=malloc(sizeof(struct IzhNeu));
}
for(int j=0;j<netu->NetList[i]->NeuNum;j++){
mrri(fp,&netu->NetList[i]->Neus[j]->InNum,sizeof(netu->NetList[i]->Neus[j]->InNum));
mrri(fp,&netu->NetList[i]->Neus[j]->a,sizeof(netu->NetList[i]->Neus[j]->a));
mrri(fp,&netu->NetList[i]->Neus[j]->b,sizeof(netu->NetList[i]->Neus[j]->b));
mrri(fp,&netu->NetList[i]->Neus[j]->c,sizeof(netu->NetList[i]->Neus[j]->c));
mrri(fp,&netu->NetList[i]->Neus[j]->d,sizeof(netu->NetList[i]->Neus[j]->d));
mrri(fp,&netu->NetList[i]->Neus[j]->u,sizeof(netu->NetList[i]->Neus[j]->u));
mrri(fp,&netu->NetList[i]->Neus[j]->v,sizeof(netu->NetList[i]->Neus[j]->v));
mrri(fp,&netu->NetList[i]->Neus[j]->I,sizeof(netu->NetList[i]->Neus[j]->I));
mrri(fp,&netu->NetList[i]->Neus[j]->x,sizeof(netu->NetList[i]->Neus[j]->x));
mrri(fp,&netu->NetList[i]->Neus[j]->y,sizeof(netu->NetList[i]->Neus[j]->y));
mrri(fp,&netu->NetList[i]->Neus[j]->z,sizeof(netu->NetList[i]->Neus[j]->z));
netu->NetList[i]->Neus[j]->S=malloc(netu->NetList[i]->Neus[j]->InNum*sizeof(float));
netu->NetList[i]->Neus[j]->InNeus=malloc(netu->NetList[i]->Neus[j]->InNum*sizeof(void*));

for(int k=0;k<netu->NetList[i]->Neus[j]->InNum;k++){
mrri(fp,&nnum,sizeof(netu->NetList[i]->Neus[j]->InNeus[k]));
netu->NetList[i]->Neus[j]->InNeus[k]=netu->NetList[i]->Neus[nnum];
mrri(fp,&netu->NetList[i]->Neus[j]->S[k],sizeof(float));
}
}
}

fps=0;
free(fpp);
close(fp);
return netu;
}

