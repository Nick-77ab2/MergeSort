/**
 @file
 @author Nick Pelletier <nwp28@drexel.edu>
 @date 5/5/23
 @section Description
 
 This file creates the threaded merge sort. Threads are used to speed up the classic merge sort.
 */
#include <cmath>
#include <thread>
#include <stdio.h>
#include "threadmerge.h"
#include "mergesort.h"

//Merge Sort array in place using maximum number of threads provided. If number of elements is smaller than number of threads, extraneous threads are not spanned.
void tmergesort(int* A, int size, int threadCount){
    if(threadCount == 1 || size<threadCount){
        mergesort(A, size); //No Gains From Threading
        return;
    }
    //correctly scale the number of threads for any given value.
    int correctedThreads;
    if(size/threadCount<4){
        correctedThreads=std::floor(size/4);
        if(correctedThreads==0){
            correctedThreads=1;
        }
    }
    else{
        correctedThreads=threadCount;
    }
    //create threads
    std::thread threads[correctedThreads];
    for(int i=0; i<correctedThreads; i++){
        int start = i * std::floor(size/correctedThreads);
        int stop = (i+1) * std::floor(size/correctedThreads)-1;
        threads[i] = std::thread(msortSec, A, start, stop);
    }
    //join threads
    for(int i=0; i<correctedThreads; i++){
        threads[i].join();
    }
    //let's re-use the threads for merging final results :)
    int mergingThreads = correctedThreads/2;
    if(mergingThreads==0){
        mergingThreads=correctedThreads;
    }
    
    //while loop to constantly re-merge
    while (mergingThreads!=1){
        for(int i=0; i<mergingThreads; i++){
            int start = (2*i) * std::floor(size / (mergingThreads*2));
            int middle = (2*i+1) * std::floor(size / (mergingThreads*2))-1;
            int stop = (2*i+2) * std::floor(size / (mergingThreads*2))-1;
            threads[i] = std::thread(merge, A, start, middle, stop);

        }
        for(int i =0;i<mergingThreads; i++){
            threads[i].join();
        }
        mergingThreads=mergingThreads/2;
    }
    //need to merge sort itself
    merge(A, 0, std::floor(size-1)/2, size-1);
}
