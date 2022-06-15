# HeapPriorityQueue

 * This is an implementation of HeapPriorityQueue, which creates
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
