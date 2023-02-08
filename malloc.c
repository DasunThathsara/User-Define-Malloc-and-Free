/*------------------------------- malloc assignment --------------------------------*/
/*-------------------- 21001901 | K D T Srikantha | 2021/CS/190 --------------------*/


#include <stdio.h>
#define memSize 1000

char memory[memSize], *sPoint, * ePoint;
int currentPosition = 0;

struct memoryBlock{
    int avail;
    int lastIndex;
    int firstIndex;
    struct memoryBlock * next;
    struct memoryBlock * lastPoint;
    struct memoryBlock * firstPoint;
} * start, * ptr3, * ptr, * ptr4;

void * MyMalloc(int size){
    if(currentPosition + size + sizeof(struct memoryBlock) > memSize){
        return NULL;
    }

    struct memoryBlock * newNode;
    if(start == NULL){
        start = (void*)memory;
        newNode = start;
        sPoint = (char*) start;
        newNode->firstPoint = start;
        newNode->lastPoint = sPoint + size + sizeof(struct memoryBlock);
        start = newNode;
        newNode->avail = 0;
        newNode->firstIndex = 0;
        newNode->lastIndex = size + sizeof(struct memoryBlock);
        newNode->next = NULL;
    }
    else{
        ptr = start;
        int find = 0;
//        ptr4 = ptr->next;
        while(ptr->next != NULL){
            if(ptr->avail != 1){
                // If the free block size and required memory size is equal
                if(ptr->lastIndex - ptr->firstIndex == size + sizeof(struct memoryBlock)){
                    newNode = ptr->firstPoint;
                    newNode->avail = 0;

                    find = 1;
                }

                    // If the current block size is greater than required space
                else if(ptr->lastIndex - ptr->firstIndex > size + sizeof(struct memoryBlock)){
                    struct memoryBlock * newNode1;
                    ptr3 = ptr;
                    int f = ptr->lastIndex;
                    char * la = (char*)ptr->lastPoint;
                    char * na = (char*)ptr->next;
                    sPoint = (char*) ptr->firstPoint;

                    newNode = ptr;
                    newNode->lastPoint = sPoint + size + sizeof(struct memoryBlock);
                    newNode->lastIndex = ptr->firstIndex + size + sizeof(struct memoryBlock);
                    newNode->avail = 0;

                    newNode1 = newNode->lastPoint;
                    newNode1->next = ptr->next;

                    newNode1 = newNode->lastPoint;
                    newNode1->firstPoint = newNode->lastPoint;
                    newNode1->firstIndex = newNode->lastIndex + 1;
                    newNode1->avail = 1;
                    newNode1->lastIndex = f;
                    newNode1->lastPoint = la;
                    newNode->next = newNode1;
                    newNode1->next = na;
                    ptr3 = newNode1->next;
                    find = 1;
                }
            }
            ptr = ptr->next;
        }

        // If current block is not free, the program creates a new block and connect it into current block
        if(find == 0){
            newNode = ptr->lastPoint;
            ptr->next = newNode;
            newNode = ptr->lastPoint;
            sPoint = (char*) ptr->lastPoint;
            newNode->firstPoint = ptr->lastPoint;
            newNode->firstIndex = ptr->lastIndex + 1;
            newNode->lastIndex = size + sizeof(struct memoryBlock) + ptr->lastIndex + 1;
            ptr = ptr->lastPoint;
            newNode->lastPoint = sPoint + size + sizeof(struct memoryBlock);
            newNode->avail = 0;
            newNode->next = NULL;
        }
    }

    currentPosition = newNode->lastIndex + 1;
    return newNode;
}

void traverse(){
    ptr = start;
    while(ptr->next != NULL){
        printf("\n------ %4d   %4d   %4d", ptr->avail, ptr->firstIndex, ptr->lastIndex);
        ptr = ptr->next;
    }
}

void merge(){
    ptr = start;
    while(ptr->next != NULL){
        if(ptr->avail == 1 && ptr->next->avail == 1){
            ptr->lastPoint = ptr->next->lastPoint;
            ptr->lastIndex = ptr->next->lastIndex;
            ptr->next = ptr->next->next;
        }
        ptr = ptr->next;
    }
}

void MyFree(void * pointer){
    ptr = start;
    while(ptr->next != pointer){
        ptr = ptr->next;
    }

    ptr->next->avail = 1;
    merge();
}

int main() {
    printf("%llu\n", sizeof(struct memoryBlock));

    int *w = (int*) MyMalloc(5);
    printf("%p      %p\n", w, memory);

    int *r = (int*) MyMalloc(10);
    printf("%p      %p\n", r, memory);

    int *k = (int*) MyMalloc(5);
    printf("%p      %p\n", k, memory);

    char *g = (char*) MyMalloc(50);
    printf("%p      %p\n", g, memory);

    float *t = (float*) MyMalloc(100);
    printf("%p      %p\n", t, memory);

    double *l = (double*) MyMalloc(60);
    printf("%p      %p\n", l, memory);

    traverse();
    printf("\n");

    MyFree(g);

    traverse();
    printf("\n");

    float *f = (float*) MyMalloc(200);
    printf("%p      %p\n", f, memory);

    traverse();
    printf("\n");

    return 0;
}
