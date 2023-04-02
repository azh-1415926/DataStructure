# DataStructure
一些自制的简单数据类型，为了方便使用以及后续的迭代，特此写一个说明文档，以便查阅。


### 顺序存储
> 一些顺序存储的数据结构，如 seqList、seqStack、seqQueue。

### **seqList**
这是一个顺序表，应该用得不多，只作为参考。
```c
typedef struct seqList {		
	void** pList;
	int capacity;
	int length;
}*seqList;
```
用 `seqList` 表示顺序表，即该结构体的指针。

使用时，我们用 seqList 定义一个顺序表，即该结构体指针，然后调用函数初始化，最后记得调用函数释放它。

**函数介绍**
1. 初始化顺序表 | `seqListInitalize`
    
    `void seqListInitalize(seqList* ppList,int capacity);`
    * 需要传入顺序表的指针、顺序表的容量，用指针操控顺序表，让顺序表指向一片动态分配的空间。
    * 无返回值。
2. 释放顺序表 | `seqListFree`

    `void seqListFree(seqList* list);`
    * 需要传入顺序表的指针，用指针操控顺序表，释放顺序表。
    * 无返回值。
3. 插入数据 | `seqListInsert`

    `void seqListInsert(seqList list,void* const data,int pos);`
    * 需要传入顺序表、数据指针、位置下标（从 0 开始），将节点插入到指定位置，数据域存放数据指针。
    * 无返回值。
4. 删除数据 | `seqListErase`
    
    `void* seqListErase(seqList list,int pos);`
    * 传入顺序表、位置下标（从 0 开始），删除指定位置的节点。
    * 返回数据域中存放的数据指针，否则返回 NULL。
5. 根据下标查找数据 | `seqListIndexSearch`

    `void* seqListIndexSearch(seqList const list,int pos);`
    * 需要传入一个顺序表、位置下标（从 0 开始），查找指定位置的节点。
    * 返回找到节点的数据域，找不到返回 NULL。

6. 根据数据查找下标 | `seqListDataSearch`

    `int seqListDataSearch(seqList const list,void* const data);`
    * 需要传入一个顺序表、位置下标（从 0 开始），查找指定位置的节点。
    * 返回找到节点的数据域，找不到返回 NULL。
7. 合并顺序表 | `seqListCombine`

    `seqList seqListCombine(seqList firstList,seqList const endList);`
    * 需要传入两个顺序表，生成一个长度为二者相加的顺序表，将所有数据拷贝。
    * 返回顺序表。
8. 合并顺序表（无重复数据） | `seqListCombineNoRepeat`

    `seqList seqListCombineNoRepeat(seqList firstList,seqList const endList,bool(*compare)(void*,void* const));`
    * 需要传入两个顺序表，它会调用上面那个函数生成一个长度为二者相加的顺序表，将所有数据拷贝，然后用给定的函数去重。
    * 返回顺序表。
### **seqStack**
这是一个顺序栈。
```c
typedef struct seqStack {
    int top;
    void** bottom;
    int capacity;
}*seqStack;
```
用 `seqStack` 表示顺序表，即该结构体的指针。

使用时我们用 seqStack 定义一个顺序栈，并用函数初始化它，最后记得释放它。

**函数介绍**

1. 初始化顺序栈 | `seqStackInitalize`

    `void seqStackInitalize(seqStack* ppStack,int capacity);`
    * 需要传入一个顺序栈的指针，然后会用这个指针操控顺序栈动态分配空间。
    * 无返回值。

2. 释放顺序栈 | `seqStackFree`

    `void seqStackFree(seqStack* stack);`
    * 需要传入一个顺序栈的指针，然后会用这个指针操控顺序栈释放。
    * 无返回值。
3. 判断顺序栈是否为空 | `seqStackIsEmpty`
    `bool seqStackIsEmpty(seqStack const stack);`
    * 需要传入一个顺序栈，判断顺序栈是否为空。
    * 为空返回 true，不为空返回 false。
4. 判断顺序栈是否已满 | `seqStackIsFull`
    
    `bool seqStackIsFull(seqStack const stack);`
    * 需要传入一个顺序栈，判断顺序栈是否已满。
    * 已满返回 true，未满返回 false。
5. 入栈 | `seqStackPush`

    `void seqStackPush(seqStack stack,void* const data);`
    * 需要传入一个顺序栈，将数据指针压入栈。
    * 无返回值。
6. 获取栈顶元素 | `seqStackTop`

    `void* seqStackTop(seqStack const stack);`
    * 需要传入一个顺序栈，获取栈顶数据。
    * 返回栈顶数据，栈空返回 NULL。
7. 出栈 | `seqStackPop`
    
    `void seqStackPop(seqStack stack);`
    * 需要传入一个顺序栈，弹出栈顶数据。
    * 无返回值。
### **seqQueue**
这是一个顺序队列。

**函数介绍**
```c
typedef struct seqQueue {
    int rear;
    int front;
    void** pQueue;
    int capacity;
    int flag;
}*seqQueue;
```
用 `seqQueue` 表示顺序队列，即该结构体的指针。

使用时我们用 seqQueue 定义一个顺序队列，并用函数初始化它，最后记得释放它。

1. 初始化顺序队列 | `seqQueueInitalize`

    `void seqQueueInitalize(seqQueue* ppQueue,int capacity);`
    * 需要传入一个顺序栈指针，操纵顺序栈动态分配空间。
    * 无返回值。
2. 释放顺序队列 | `seqQueueFree`

    `void seqQueueFree(seqQueue* queue);`
    * 需要传入一个顺序栈指针，操纵顺序栈释放。
    * 无返回值。
3. 判断队空
    `bool seqQueueIsEmpty(seqQueue const queue);`
    * 需要传入一个顺序栈，判断队列是否为空。
    * 为空返回 true，不为空返回 false。
4. 判断队满

    `bool seqQueueIsFull(seqQueue const queue);`
    * 需要传入一个顺序栈，判断队列是否已满。
    * 已满返回 true，未满返回 false。   
5. 入队

    `void seqQueueEnqueue(seqQueue queue,void* const data);`
    * 需要传入一个顺序栈，将数据入队。
    * 无返回值。
6. 获取队头数据
    `void* seqQueueFront(seqQueue const queue);`
    * 需要传入一个顺序栈，获取队头数据。
    * 返回队头数据域中存放的数据指针，否则返回 NULL。
7. 出队

    `void seqQueueDequeue(seqQueue queue);`
    * 需要传入一个顺序栈，将队头数据出队。
    * 无返回值。
### 链式存储
> 一些链式存储的数据类型，如 linkList、linkStack、linkQueue。
### **linkList**
这是一个链表，用一个结构体来存储数据域和指针域。

数据域为一个空指针，以便应用在所有类型中，指针域为该结构体类型的指针。
```c
typedef struct linkNode{
	void* data;
	struct linkNode *next;
}linkNode,*linkList;
```
用 `linkNode` 表示链表节点，`linkList` 表示链表，即链表头结点的指针。
**函数介绍**
1. 初始化链表 | `linkListInitalize`

    `void linkListInitalize(linkList* ppList);`
    
    * 需要传入一个链表的指针，然后会为这个链表动态分配空间。即添加头结点，linkList 为头结点指针。
    * 无返回值。
2. 释放链表

    `void linkListFree(linkList* ppList);`

    * 需要传入一个链表的指针，然后会释放这个链表中的所有节点，并释放头结点，linkList 为头结点指针，释放完之后置为 NULL。
    * 无返回值。
3. 头插数据 | `linkListHeadInsert`

    `void linkListHeadInsert(linkList list,void* const data);`

    * 传入链表和数据的指针，头插该节点即插入到头结点后面成为新的首元结点，数据域将存放数据指针。
    * 无返回值。
4. 尾插数据 | `linkListTailInsert`

    `void linkListTailInsert(linkList list,void* const data);`

    * 传入链表和数据的指针，尾插该节点即插入到尾节点后面成为新的尾结点，数据域将存放数据指针。
    * 无返回值。
5. 插入数据 | `linkListInsert`

    `void linkListInsert(linkList list,void* const data,int pos);`

    * 传入链表、数据指针、位置下标（从 0 开始），将节点插入到指定位置，数据域将存放数据指针。
    * 无返回值。
6. 删除数据 | `linkListErase`
    
    `void* linkListErase(linkList list,int pos);`

    * 传入链表、位置下标（从 0 开始），删除指定位置的节点。
    * 返回数据域中存放的数据指针，否则返回 NULL。
7. 根据下标查找数据 | `linkListIndexSearch`

    `void* linkListIndexSearch(linkList const list,int pos);`

    * 传入链表、位置下标（从 0 开始），查找指定位置的节点。
    * 返回数据域中存放的数据指针，找不到返回 NULL。
8. 根据数据查找下标 | `linkListDataSearch`

    `int linkListDataSearch(linkList list,void* const data,bool(*compare)(void*,void* const))`

    * 传入链表、数据指针、用于数据比较的函数指针，这个函数指针返回值为布尔类型，参数为两个需要进行比较的数据指针。
    * 返回数据域中存放的数据指针，找不到返回 NULL。
8. 链表合并 | `linkListCombine`

    `linkList linkListCombine(linkList firstList,linkList const lastList);`
    * 传入两个链表，将第二个链表的所有节点拷贝并尾插到第一个链表中。
    * 返回合并后的链表，即第一个链表，否则返回 NULL。
### **linkStack**
这是一个链栈，其中的节点用一个结构体来表示，并存储数据域和指针域。
```c
typedef struct linkStackNode {
    void* data;
    struct linkStackNode *next;
//数据域为一个空指针，以便应用在所有类型中，指针域为该结构体类型的指针。
}linkStackNode;
typedef struct linkStack {
    struct linkStackNode *top;
    struct linkStackNode *bottom;
}*linkStack;
```
用 `linkStack` 表示链栈。

其中包含两个节点指针，一个指向栈顶，一个指向栈底。

**函数介绍**
1. 初始化链栈

    `void linkStackInitalize(linkStack* ppStack);`
    * 传入链栈指针，操控链栈存放动态分配的内存空间。
    * 无返回值。
2. 释放链栈

    `void linkStackFree(linkStack* ppStack);`
    * 传入链栈指针，操控链栈释放。
    * 无返回值。
3. 判断链栈是否为空

    `bool linkStackIsEmpty(linkStack const stack);`
    * 传入链栈，判断链栈是否为空。
    * 为空返回 true，不为空返回 false。
4. 入栈

    `void linkStackPush(linkStack stack,void* const data);`
    * 传入链栈、数据指针，将数据指针入栈，成为新的栈顶数据。
    * 无返回值。
5. 获取栈顶数据

    `void* linkStackTop(linkStack const stack);`
    * 传入链栈，获取栈顶数据。
    * 返回栈顶数据域存放的数据指针，否则返回 NULL。
6. 出栈

    `void linkStackPop(linkStack stack);`
    * 传入链栈，将栈顶数据指针出栈。
    * 无返回值。
### **linkQueue**
这是一个链队。
```c
typedef struct linkQueueNode {
    void* data;
    struct linkQueueNode *next;
}linkQueueNode,*linkQueue;
```
用 `linkQueue` 表示链队，即头结点指针，用 `linkQueueNode` 表示链队节点。

**函数介绍**
1. 初始化链队 | `linkQueueInitalize`

    `void linkQueueInitalize(linkQueue* ppQueue);`
    * 传入链队指针，操控链队存放动态分配的内存空间。
    * 无返回值。
2. 释放链队 | `linkQueueFree`

    `void linkQueueFree(linkQueue* ppQueue);`
    * 传入链队指针，操控链队释放。
    * 无返回值。
3. 判断链队是否为空 | `linkQueueIsEmpty`

    `bool linkQueueIsEmpty(linkQueue const queue);`
    * 传入链队，判断链队是否为空。
    * 为空返回 true，不为空返回 false。
4. 入队 | `linkQueueEnqueue`

    `void linkQueueEnqueue(linkQueue queue,void* const data);`
    * 传入链队、数据指针，将数据指针入队，成为新的队尾数据。
    * 无返回值。
5. 获取队头数据 | `linkQueueFront`

    `void* linkQueueFront(linkQueue const queue);`
    * 传入链队，获取队头数据。
    * 返回队头数据域存放的数据指针，否则返回 NULL。
6. 出队 | `linkQueueDequeue`

    `void linkQueueDequeue(linkQueue queue);`
    * 传入链队，将队头数据指针出队。
    * 无返回值。