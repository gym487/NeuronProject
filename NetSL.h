#include<stdio.h>
#include"neuron.h"
//TODO:Add the function of Saving / Loading network on disk file HERE.
void NetSave(char* a,struck Network* net){
FILE* fp=NULL;
fp=fopen(a,"wb");
//

for(int i=0;i<(*net).NeuNum;i++){

}
fclose(fp);
}
struct Network* NetLoad(char* a){
FILE* fp=NULL;
fp=fopen(a,"rb");
//
}


