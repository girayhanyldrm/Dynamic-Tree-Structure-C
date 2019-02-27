#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int outputArray[1000];
int outputSize=0;

typedef struct node{
    int data;
    int cocuksayisi;
    struct node** array;

}node;

struct node* newNode(int data)
{
     node* n = (node*)malloc(sizeof(node));
     n->data = data;
     n->cocuksayisi =0;
     n->array=malloc(sizeof(node)*0);


     return(n);
}
void cocukekle(node* baba,int cocuk){

      baba->array=realloc(baba->array,sizeof(node*)*cocuk);

}
void printPre(node* root){
    int i;

    outputArray[outputSize]=root->data;
    if(root->cocuksayisi==0){

        return;
      }

    for(i=0;i<root->cocuksayisi;i++){
        outputSize+=1;
        //printf("%d",outputSize);
        printPre(root->array[i]);

    }


}

node** leafUpdated(node** leafArray,int* leafLength){
        int i,j,k;
        int index=0;
        int totalcocuk=0;
        for(i=0;i<(*leafLength);i++){
            totalcocuk+=(leafArray[i]->cocuksayisi);
        }
        if(totalcocuk>=(*leafLength)){
        node** temp = (node**)malloc(sizeof(node*)*totalcocuk);

        for(i=0;i<(*leafLength);i++){
            for(j=0;j<leafArray[i]->cocuksayisi;j++){
                  temp[index]=leafArray[i]->array[j];
                  index+=1;
                  }
          }
        *leafLength=totalcocuk;
         leafArray=temp;

        }


        else{
          node** temp2 = (node**)malloc(sizeof(node*)*(*leafLength));
          for(i=0;i<(*leafLength);i++){
            for(j=0;j<leafArray[i]->cocuksayisi;j++){
                  temp2[index]=leafArray[i]->array[j];
                  index+=1;
                  }
            }

            for(k=index;k<(*leafLength);k++){

                temp2[k]=leafArray[k];

            }

          leafArray=temp2;
          }

        return(leafArray);

  }
void tree2(node** leafArray,int data,int* size,int length){
    if(*size<length-1){
          leafArray[*size]->cocuksayisi+=1;
          cocukekle(leafArray[*size],leafArray[*size]->cocuksayisi);
          leafArray[*size]->array[leafArray[*size]->cocuksayisi-1]=newNode(data);
          *size=*size+1;
      }
    else{

          leafArray[*size]->cocuksayisi+=1;
          cocukekle(leafArray[*size],leafArray[*size]->cocuksayisi);
          leafArray[*size]->array[leafArray[*size]->cocuksayisi-1]=newNode(data);
          *size=0;
      }

}
void tree1(node** leafArray,node* node,int data){

        node->cocuksayisi+=1;
        cocukekle(node,node->cocuksayisi);
        node->array[node->cocuksayisi-1]=newNode(data);
        leafArray[node->cocuksayisi-1]=node->array[node->cocuksayisi-1];
}


void search(node* root,int data,int* j,node** temp1,node** temp2,int* kacinci){
    int i;
    if(root->data==data){
      *temp2=root;

      *j=*j+1;
      return;
      }
    if(root->cocuksayisi==0){

        return;
      }

    for(i=0;i<root->cocuksayisi;i++){

    search(root->array[i],data,j,temp1,temp2,kacinci);
    if(*j==1){
        *temp1=root;
        *j=*j+1;
        *kacinci=i;
        }
    }


}

void deleting(node* temp1,node* temp2,int kacinci,node** root){


  if(temp2==*root){
    int newSize=((temp2->cocuksayisi)+(temp2->array[0]->cocuksayisi)-1);

  node** newArray=malloc(sizeof(node*)*newSize);
  int xx;
  int top=1;
  for(xx=0;xx<newSize;xx++){

    if(xx<(temp2->array[0]->cocuksayisi)){

      newArray[xx]=temp2->array[0]->array[xx];
      }
    else{
      newArray[xx]=temp2->array[top];
      top++;
      }
  }
  temp2->array[0]->cocuksayisi=newSize;

  temp2->array[0]->array=newArray;
  *root=temp2->array[0];
  temp2=NULL;
  }





  else{
  int newSize=(temp1->cocuksayisi+temp2->cocuksayisi-1);
  node** newArray=malloc(sizeof(node*)*newSize);
  temp1->cocuksayisi=newSize;
  int eklenecek=temp2->cocuksayisi;
  int x;
  int t=0;
  int l=0;
  for(x=0;x<newSize;x++){
    if(x<kacinci){
      newArray[x]=temp1->array[t];
        t++;
      }
    else if(x>eklenecek+kacinci-1){
            t++;
            newArray[x]=temp1->array[t];
            kacinci++;
      }
    else{
            newArray[x]=temp2->array[l];
            l++;
      }
    }

    temp1->array=newArray;

    }




}


int main()
{
    int sizeArray[100];
    int index=0;

    int value1;
    int value2;
    char dosya1[100];
    char dosya2[100];
    char* param1;
    char* param2;
    scanf("%s",&dosya1);
    scanf("%s",&dosya2);
    param1=strtok(dosya1," ");
    param2=strtok(dosya2," ");

    FILE *input1;
    input1=fopen(dosya1,"r");


    while (!feof(input1)){
            fscanf(input1,"%d",&value1);
            fscanf(input1,"%d ",&value2);
            sizeArray[index]=value2;
            index++;
            }
    fclose(input1);

    FILE *input11;
    input11=fopen(param1,"r");
    int indexCon=0;
    int a=0;
    int level=1;
    fscanf(input11,"%d",&value1);
    fscanf(input11,"%d ",&value2);



    node** leafArray=(node**)malloc(sizeof(node*)*value2);
    node* root=newNode(value1);
    node* temp1;
    node* temp2=NULL;
    int times=value2;
    int size=0;
    int leafArrayLength=value2;
    int x;

    int control=0;
    int kacinci=0;

    for(x=0;x<times;x++){
        fscanf(input11,"%d",&value1);
        fscanf(input11,"%d ",&value2);
        tree1(leafArray,root,value1);

    }
    while (!feof(input11)){
            if(a!=sizeArray[indexCon+1]){
            fscanf(input11,"%d",&value1);
            fscanf(input11,"%d ",&value2);
            //printf("%d %d %d\n",value1,size,leafArrayLength);
            tree2(leafArray,value1,&size,leafArrayLength);
            //printf("--------\n");

            a++;

            }
            else{

                leafArray=leafUpdated(leafArray,&leafArrayLength);

                a=0;
                size=0;
                indexCon++;
                level++;

            }
            }
    fclose(input11);

    FILE *output;
    output=fopen("output.txt","w");


    FILE *input2;
    input2=fopen(param2,"r");
    char value3;
    int value4;
    while (!feof(input2)){
        control=0;
        kacinci=0;
        fscanf(input2,"%c",&value3);
        fscanf(input2,"%d ",&value4);

        if(value3=='d'){


            search(root,value4,&control,&temp1,&temp2,&kacinci);
            if(temp2!=NULL){
                deleting(temp1,temp2,kacinci,&root);
                temp2=NULL;

            }
        }
        else if(value3=='l'){
            search(root,value4,&control,&temp1,&temp2,&kacinci); //// listede yoksa geç
            if(temp2!=NULL){
                if(temp2->cocuksayisi!=0){
                    printPre(temp2);
                    int y;
                    for(y=0;y<outputSize;y++){

                        fprintf(output,"%d,",outputArray[y]);

                    }
                    fprintf(output,"%d",outputArray[outputSize]);

                    fprintf(output,"\n");

                    temp2=NULL;
                    outputSize=0;

                }
                else{
                    fprintf(output,"%d\n",temp2->data);
                    temp2=NULL;
                    outputSize=0;
                }
            }

        }

    }

    fclose(input2);
    fclose(output);
    return 0;
}

