
/*Karen Munyan and Candice Murray
 * CS 106B Spring 2015
 * Problem Set 5
 * Sources: Lecture notes on Heap Priority Queues, lecture notes in general
 *
 *
 * This file is the .h file for the HeapPriorityQueue, which creates
 * a priority queue with an array as the base structure. With
 * this priority queue implementation, data is enqueued by adding
 * it to the end of the array and "bubbling it up" to its proper
 * sorted location. Data is dequeued by removing the first data set
 * in the queue, then moving the last item in the queue to the front
 * and "bubbling it down" until it is in its proper sorted location.
 */

#ifndef _heappriorityqueue_h
#define _heappriorityqueue_h

#include <iostream>
#include <string>
#include "PQEntry.h"
using namespace std;

/*
 * For documentation of each member, see ArrayPriorityQueue.h.
 */
class HeapPriorityQueue {
public:
    HeapPriorityQueue();
    ~HeapPriorityQueue();
    void changePriority(string value, int newPriority);
    void clear();
    string dequeue();
    void enqueue(string value, int priority);
    bool isEmpty() const;
    string peek() const;
    int peekPriority() const;
    int size() const;
    friend ostream& operator <<(ostream& out, const HeapPriorityQueue& queue);

private:
    //variables
    int mySize;
    int myCapacity;
    PQEntry* elements;
    //methods
    void checkResize();
    void swap(int index1, int index2);

};

#endif
