/**
 * @file
 * @author Nick Pelletier <nwp28@drexel.edu
 * @date 5/5/23
 * @section Description
 * 
Mergesort algorithm following the instructions given by boady.
*/
#include <cmath>
#include <stdio.h>
#include "mergesort.h"

//Sort Array A using Merge Sort. Array is sorted in place.
void mergesort(int* A, int size){
    msortSec(A, 0, size-1);
}

//Merge Sort Array values between index start and stop
void msortSec(int* A, int start, int stop){
    if(start>=stop){
        return;
    }
    int middle = start + std::floor((stop-start)/2);
    msortSec(A, start, middle);
    msortSec(A, middle+1, stop);
    merge(A, start, middle, stop);
}

//Merge two sorted sections of the array. Specifically,
//merge A[start to middle] an A[middle+1 to stop].
void merge(int* A, int start, int middle, int stop){
    int* Aux = new int[stop-start+1];
    for(int i=0; i<(stop-start+1); i++){
        Aux[i]=A[start+i];
    }
    int auxMiddle = (middle-start);
    int auxStop = (stop-start);
    int i=0;
    int j=auxMiddle+1;
    for(int k=start; k<stop+1; k++){
        if(i>auxMiddle){
            A[k] = Aux[j];
            j++;
        }
        else if(j>auxStop){
            A[k] = Aux[i];
            i++;
        }
        else if(Aux[j] > Aux[i]){
            A[k] = Aux[i];
            i++;
        }
        else{
            A[k] = Aux[j];
            j++;
        }
    }
    delete[] Aux;
}