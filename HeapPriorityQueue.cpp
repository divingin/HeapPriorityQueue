
/*Karen Munyan and Candice Murray
 * CS 106B Spring 2015
 * Problem Set 5
 * Sources: Lecture notes on Heap Priority Queues, lecture notes in general
 *
 *
 * This file is the cpp file for the HeapPriorityQueue, which creates
 * a priority queue with an array as the base structure. With
 * this priority queue implementation, data is enqueued by adding
 * it to the end of the array and "bubbling it up" to its proper
 * sorted location. Data is dequeued by removing the first data set
 * in the queue, then moving the last item in the queue to the front
 * and "bubbling it down" until it is in its proper sorted location.
 * This means that a HeapPriorityQueue is efficient at enqueueing data
 * because it only has to go through part of the array (only takes logN time).
 * It is also efficient for dequeueing elements, because after removing the
 * element at the first index, it only has to go through part of the queue
 * to "bubble down" (only takes logN time). It is also very efficient for
 * peeking at the elements with the highest priority, because they are
 * sorted at the beginning of the queue.
 */

#include "HeapPriorityQueue.h"
#include "string.h"

//Constructor: constructs a HeapPriorityQueue
HeapPriorityQueue::HeapPriorityQueue() {
    myCapacity = 10;
    mySize = 0;
    elements = new PQEntry[myCapacity]();
}

//Destructor: destructs a HeapPriorityQueue at the end of the program
HeapPriorityQueue::~HeapPriorityQueue() {
    delete[] elements;
}

// O(N)
void HeapPriorityQueue::checkResize(){  //added
    /*checks if the array needs to be made bigger.  If so, doubles the capacity of the array. */
    if (mySize == myCapacity-1){
        PQEntry* bigger = new PQEntry[2*myCapacity];
        for (int i = 1; i < myCapacity; i++){
            bigger[i] = elements[i];
        }
        delete[] elements;
        elements = bigger;
        myCapacity *= 2;
    }
}

// O(1)
void HeapPriorityQueue::swap(int index1, int index2){ //added
    /*swaps two entries in the array located at the given indexes. */
    PQEntry temp = elements[index2];
    elements[index2] = elements[index1];
    elements[index1] = temp;
}

//See ArrayPriorityQueue.h for documentation member functions.
// O(N)
void HeapPriorityQueue::changePriority(string value, int newPriority) {
    int elementIndex;
    bool found = false;
    for(int i = 1; i <= mySize; i++)
    {
        if(!found && elements[i].value == value)
        {
            elementIndex = i;
            found = true;
        }
    }
    if(!found || elements[elementIndex].priority <= newPriority)
    {
        throw "The new priority is less urgent than the old priority or the value is not in the queue.";
    }
    else
    {
        elements[elementIndex].priority = newPriority;
        while(elements[elementIndex/2].priority > newPriority)
        {
            swap(elementIndex, elementIndex/2);
            elementIndex = elementIndex/2;
        }
    }
}

//See ArrayPriorityQueue.h for documentation member functions.
// O(1)
void HeapPriorityQueue::clear() { // implemented
    mySize = 0;
}

//See ArrayPriorityQueue.h for documentation member functions.
// O(logN) (because of the shifting)
string HeapPriorityQueue::dequeue() {
    if(mySize < 1) throw "Your queue is empty.";
    PQEntry urgent = elements[1];
    elements[1] = elements[mySize]; //moves last element to front
    mySize--;
    int index = 1;
    while(index*2 < mySize && (elements[index].priority >= (elements[index*2].priority || elements[index*2+1].priority)) )
    {
        if (elements[index*2].priority == min(elements[index*2].priority, elements[index*2+1].priority) &&
                (elements[index].priority > elements[index*2].priority ||
                (elements[index].priority == elements[index*2].priority
                && elements[index].value > elements[index*2].value))){
            /*This if statement checks if the minimum of the two children is the index*2 element, then checks if the PQEntry of index*2 is
             *more urgent than the PQEntry of index, and swaps the two if it is.*/
            swap(index,index*2);
            cout << elements << endl;
            index = index*2;
        }else if (elements[index].priority > elements[index*2+1].priority ||
                  (elements[index].priority == elements[index*2+1].priority && elements[index].value > elements[index*2+1].value)){
            /*This statement assumes that the index*2+1 is the minimum of the two children, and checks to see if the index*2+1 PQEntry
             *is less urgent than the index PQEntry, and swaps if they are.*/
            swap(index,index*2+1);
            cout << elements << endl;
              index = index*2+1;
        }

    }
    return urgent.value;
}

//See ArrayPriorityQueue.h for documentation member functions.
// O(logN)
void HeapPriorityQueue::enqueue(string value, int priority) {
    checkResize();
    mySize++;
    elements[mySize].priority = priority;
    elements[mySize].value = value;
    int index = mySize;
    while (elements[index/2].priority > priority || (elements[index/2].priority == priority && elements[index/2].value > value)){
        swap(index,index/2);
        index = index/2;
    }
}

//See ArrayPriorityQueue.h for documentation member functions.
// O(1)
bool HeapPriorityQueue::isEmpty() const {
    if (mySize==0){
        return true;
    }
    return false;
}

//See ArrayPriorityQueue.h for documentation member functions.
// O(1)
string HeapPriorityQueue::peek() const {
    return elements[1].value;
}

//See ArrayPriorityQueue.h for documentation member functions.
// 0(1)
int HeapPriorityQueue::peekPriority() const {
    return elements[1].priority;
}

//See ArrayPriorityQueue.h for documentation member functions.
// O(1)
int HeapPriorityQueue::size() const {
    return mySize;
}

//See ArrayPriorityQueue.h for documentation member functions.
// O(N)
ostream& operator<<(ostream& out, const HeapPriorityQueue& queue) {
    out << "{";
    if (!queue.isEmpty()) {
        out << "\"" << queue.elements[1].value << "\": " << queue.elements[1].priority; //fencepost
        for (int i = 2; i <= queue.size(); i++) {
            out << ", \"" << queue.elements[i].value << "\": " << queue.elements[i].priority;
        }
    }
    out << "}";
    return out;
}
