#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void merge(int * arr, int first, int middle, int end)
{
    int * lower, * upper;
    lower = malloc(sizeof(int) * (middle - first + 1));
    upper = malloc(sizeof(int) * (end - middle));
    int j, k;
    int n = first;
    for(int j = 0; j < (middle - first + 1); j++){
        lower[j] = arr[n];
        n++;
    }
    for(int k = 0; k < end - middle; k++){
        upper[k] = arr[n];
        n++;
    }
    n = first;
    j = 0;
    k = 0;
    while(j < (middle - first + 1) && k < (end - middle)){
        if (lower[j] < upper[k]){
            arr[n] = lower[j];
            j++;
        } else {
            arr[n] = upper[k];
            k++;
        }
        n++;
    }
    while(j < middle - first + 1){
        arr[n] = lower[j];
        n++;
        j++;
    }
    while(k < end - middle){
        arr[n] = upper[k];
        n++;
        k++;
    }
}




void mergeSort(int * arr, int first, int end){

    if(first<end){
        int middle=(first+end)/2;


        mergeSort(arr, first, middle);
        mergeSort(arr, middle + 1, end);
        merge(arr, first, middle, end);
    }

}

void mergeSort3(void * arg,int * arr, int first, int end){

    if(first<end){
        int middle=(first+end)/2;


        mergeSort(arr, first, middle);
        mergeSort(arr, middle + 1, end);
        merge(arr, first, middle, end);
    }

}


void mergeSort2(int * arr, int first, int end){
        pthread_t threads[4];
        int mid1=end/4;
        int mid2=mid1*2;
        int mid3=mid1*3;

    if(first<end){
        for(int i=1;i<=4;i++){
            if(i=1){
                pthread_create(&threads[i],NULL,mergeSort3(arr,first,mid1),NULL);
                pthread_join(threads,NULL);
            }
            if(i=2){
                pthread_create(&threads[i],NULL,mergeSort3(arr,mid1+1,mid2),NULL);
                pthread_join(threads,NULL);
            }
            if(i=3){
                pthread_create(&threads[i],NULL,mergeSort3(arr,mid2+1,mid3),NULL);
                pthread_join(threads,NULL);
            }
            if(i=4){
                pthread_create(&threads[i],NULL,mergeSort3(arr,mid3+1,end),NULL);
                pthread_join(threads,NULL);
            }
        }
        //int middle=(first+end)/2;
        //merge(arr,first,middle,end);
    }
}

void printArray(int * arr, int size)
{
    char * output;
    output=malloc(size * 4+1);
    for(int i=0;i<size;i++){
        char strInt[3];
        sprintf(strInt,"%d",arr[i]);
        if(arr[i>9]){
            output[i*4]=strInt[0];
            output[i*4+1]=strInt[1];
        }
        else{
            output[i*4]=' ';
            output[i*4+1]=strInt[0];
        }
        output[i*4+2]=',';
        output[i*4+3]=' ';
    }
    output[4*size]='\0';
    printf("%s\n",output);
    free(output);
}

int main(){


    int arr[8]={1,2,3,5,4,7,8.8};
    
    int length=sizeof(arr)/sizeof(arr[0]);
    int middle=length/2;

    mergeSort(arr, 0, length - 1);

    printArray(arr,length);

    time_t t;
    srand((unsigned)time(&t));
    int arr2[100];
    for(int i=0;i<100;i++){
        arr2[i]=rand()%50;
    }
    printf("The Original Array is: \n");
    printArray(arr2,100);
    mergeSort2(arr2,0,100);
    printf("The Sorted Array is: \n");
    printArray(arr2,100);

    return 0;
}