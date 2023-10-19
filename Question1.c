#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

struct node
{
    int value;
    struct node* prev;
    struct node* next;
};

struct node *element(struct node *dll, int i) ;
struct node *add(struct node *dll, int i, int value) ;
struct node *delete(struct node *dll, int i);



void printNode (struct node *dll) {
    if (dll != NULL) {
        printf("< This: %p - %d - P : %p - N : %p >\n", dll, dll->value, dll->prev, dll->next);
    } else {
        printf("Null Pointer");
    }
}


void printLL (struct node *dll) {
    struct node* ptr = dll;
    printf("---\n");
    while (ptr != NULL) {
        printNode(ptr);
        ptr = ptr->next;
    }
    printf("---\n\n");
}

int main () {

    // Testing code! 
    struct node *dll = calloc(1, sizeof(struct node));
    dll->value = 1;
    printLL(dll);
    dll = add(dll, -1, 3);
    printLL(dll);
    dll = add(dll, -1, 4);
    printLL(dll);
    dll = add(dll, 1, 2);
    printLL(dll);
    dll = add(dll, 2, 7);
    printLL(dll);
    dll = add(dll, 9, -1);
    printLL(dll);
    dll = delete(dll, 2);
    printLL(dll);
    dll = delete(dll, 0);
    printLL(dll);
    dll = delete(dll, 4);
    printLL(dll);
    dll = delete(dll, 0);
    dll = delete(dll, 0);
    dll = delete(dll, 0);
    dll = delete(dll, 0);
    printLL(dll);
}

/* Expected Output: 

---
< This: 0x1cf8590 - 1 - P : (nil) - N : (nil) >
---

---
< This: 0x1cf8590 - 1 - P : (nil) - N : 0x1cf85b0 >
< This: 0x1cf85b0 - 3 - P : 0x1cf8590 - N : (nil) >
---

---
< This: 0x1cf8590 - 1 - P : (nil) - N : 0x1cf85b0 >
< This: 0x1cf85b0 - 3 - P : 0x1cf8590 - N : 0x1cf85d0 >
< This: 0x1cf85d0 - 4 - P : 0x1cf85b0 - N : (nil) >
---

---
< This: 0x1cf8590 - 1 - P : (nil) - N : 0x1cf85f0 >
< This: 0x1cf85f0 - 2 - P : 0x1cf8590 - N : 0x1cf85b0 >
< This: 0x1cf85b0 - 3 - P : 0x1cf85f0 - N : 0x1cf85d0 >
< This: 0x1cf85d0 - 4 - P : 0x1cf85b0 - N : (nil) >
---

---
< This: 0x1cf8590 - 1 - P : (nil) - N : 0x1cf85f0 >
< This: 0x1cf85f0 - 2 - P : 0x1cf8590 - N : 0x1cf8610 >
< This: 0x1cf8610 - 7 - P : 0x1cf85f0 - N : 0x1cf85b0 >
< This: 0x1cf85b0 - 3 - P : 0x1cf8610 - N : 0x1cf85d0 >
< This: 0x1cf85d0 - 4 - P : 0x1cf85b0 - N : (nil) >
---

---
< This: 0x1cf8590 - 1 - P : (nil) - N : 0x1cf85f0 >
< This: 0x1cf85f0 - 2 - P : 0x1cf8590 - N : 0x1cf85b0 >
< This: 0x1cf85b0 - 3 - P : 0x1cf85f0 - N : 0x1cf85d0 >
< This: 0x1cf85d0 - 4 - P : 0x1cf85b0 - N : (nil) >
---

*/ 

struct node *element(struct node *dll, int i)
{
    if(i >= 0)
    {
        for(int j = 0; j < i; j++)
        {
            if(dll == NULL)
            {
                return NULL;
            }
            dll = dll->next;
        }
    }
    else
    {
        return NULL;
    }

    return dll;
}

struct node *add(struct node *dll, int i, int value) 
{
    struct node* new_node = (struct node*)calloc(1, sizeof(struct node));
    new_node->value = value;

    if(dll != NULL)
    {
        struct node * prev_node = element(dll, i-1);
        if(prev_node == NULL)
        {
            prev_node = dll;
            while(prev_node->next != NULL)
            {
                prev_node = prev_node->next;
            }
        }

        struct node* next_node = prev_node->next;

        new_node->next = next_node;
        prev_node->next = new_node;

        new_node->prev = prev_node;
        if(next_node != NULL)
        {
            next_node->prev = new_node;
        }

        return dll;
    }
    else
    {
        return new_node;
    }
}

struct node *delete(struct node *dll, int i)
{
    struct node * delete_node = element(dll, i);
    if(delete_node == NULL)
    {
        return dll;
    }

    struct node* prev_node = delete_node->prev;
    struct node* next_node = delete_node->next;

    if(prev_node != NULL)
    {
        prev_node->next = next_node;
    }
    else
    {
        dll = next_node;
    }
    
    if(next_node != NULL)
    {
        next_node->prev = prev_node;
    }

    free(delete_node);
    delete_node = NULL;
    return dll;
}