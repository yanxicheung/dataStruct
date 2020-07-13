#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct llist_node_st*find_(LLIST* list, const void* key, llist_cmp* cmp)
{
    struct llist_node_st *cur;
    for(cur = list->head.next;cur != &list->head;cur = cur->next)
    {
        if(cmp(key,cur->data) == 0) break;
    }
    return cur;  // if not find return &list->head;
}

static int llist_fetch_(LLIST* list, const void* key, llist_cmp* cmp, void* data)
{
    struct llist_node_st* node;
    node = find_(list,key,cmp);
    if(node == &list->head)
        return -1;
    node->prev->next = node->next;
    node->next->prev = node->prev;

    if(data != NULL)
    {
        memcpy(data,node->data,list->size);
    }

    free(node->data);
    free(node);
    return 0;
}

LLIST* llist_create(int size)
{
    LLIST *head;
    head = (LLIST*)malloc(sizeof(*head));

    if(head == NULL) return NULL;

    head->size = size;
    head->head.data = NULL;
    head->head.next = &head->head;
    head->head.prev = &head->head;
    return head;
}

int llist_insert(LLIST* list, const void* data, int mode)
{
    struct llist_node_st *newnode;
    newnode = (struct llist_node_st *)malloc(sizeof(*newnode));

    if(newnode == NULL) return -1;

    newnode->data = malloc(list->size);
    if(newnode->data == NULL) return -2;
    memcpy(newnode->data,data,list->size);

    if(mode == FORWARD) // 头部插入
    {
        newnode->prev = &list->head;
        newnode->next = list->head.next;
    }
    else if(mode == BACKWARD)  //尾部插入
    {
        newnode->prev = list->head.prev;
        newnode->next = &list->head;
    }
    else
    {
        return -3;
    }
    newnode->prev->next = newnode;
    newnode->next->prev = newnode;
}

void llist_travel(LLIST* list,llist_op* callback)
{
    struct llist_node_st *cur;
    for(cur = list->head.next;cur != &list->head;cur = cur->next)
    {
        callback(cur->data);
    }
}

void llist_destroy(LLIST* list)
{
    struct llist_node_st *cur,*next;
    for(cur = list->head.next;cur != &list->head;cur = cur->next)
    {
        next = cur->next;
        free(cur->data);
        free(cur);
    }
    free(list);
}

void* llist_find(LLIST* list, const void* key, llist_cmp* cmp)
{
    return find_(list,key,cmp)->data;
}

int llist_delete(LLIST* list, const void* key, llist_cmp* cmp)
{
    return llist_fetch_(list, key, cmp, NULL);
}

int llist_fetch(LLIST* list, const void* key, llist_cmp* cmp, void* data)
{
    return llist_fetch_(list, key, cmp, data);
}
