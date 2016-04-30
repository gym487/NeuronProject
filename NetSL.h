#include<stdio.h>
#define __USE_FILE_OFFSET64
//#include"Neuron.h"
#include<sys/io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#define sit sizeof(off_t)
//TODO:Rewrite ALL.
void* fpp;
int fps=0;
void mwri( int g,void* b,int c){
if(fps>9000000){
write(g,fpp,fps);
fps=0;
}
fps+=c;
memcpy(fpp+fps,b,c);
}


void NetUSave(char* a,struct NetU* netu){
int fp;
fpp=malloc(10000000*sizeof(char));

fp=open(a,O_RDWR|O_CREAT,0777);

mwri(fp,&netu->NetNum,sizeof(netu->NetNum));
printf("Saving NetU..\n");
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
}
}
}
write(fp,fpp,fps);
fps=0;
free(fpp);
close(fp);
}
struct Network* NetLoad(char* a){
int fp;
fp=fp=open(a,O_RDONLY);
//
}


