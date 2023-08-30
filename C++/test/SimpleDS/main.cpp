#include <simpleDS/linkQueue.hpp>
#include <iostream>

int main(){
    linkQueue<int> queue;
    queue.enqueue(0);
    queue.enqueue(1);
    queue.enqueue(2);
    return 0;
}