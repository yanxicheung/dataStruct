#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct llist_node_st
{
//    void *data;
    struct llist_node_st *prev;
    struct llist_node_st *next;
    /*
     * 变长结构体 柔性数组 作为占位符号;
     * C99才支持 ;
     * 写成char data[1]比较保险;
     * */
    char data[0];
};

struct llist_head_st
{
    int size;
    struct llist_node_st head;
};


static struct llist_node_st*find_(struct llist_head_st *list, const void* key, llist_cmp* cmp)
{
    struct llist_node_st *cur;
    for(cur = list->head.next;cur != &list->head;cur = cur->next)
    {
        if(cmp(key,cur->data) == 0) break;
    }
    return cur;  // if not find return &list->head;
}

static int llist_fetch_(struct llist_head_st *list, const void* key, llist_cmp* cmp, void* data)
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
    free(node);
    return 0;
}

LLIST* llist_create(int size)
{
    struct llist_head_st *head;
    head = (struct llist_head_st *)malloc(sizeof(*head));

    if(head == NULL) return NULL;

    head->size = size;
    head->head.next = &head->head;
    head->head.prev = &head->head;
    return head;
}

int llist_insert(LLIST* l, const void* data, int mode)
{
    struct llist_node_st *newnode;
    struct llist_head_st *list = (struct llist_head_st *)l;
    newnode = (struct llist_node_st *)malloc(sizeof(*newnode) + list->size);

    if(newnode == NULL) return -1;

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

void llist_travel(LLIST* l,llist_op* callback)
{
    struct llist_node_st *cur;
    struct llist_head_st *list = (struct llist_head_st *)l;
    for(cur = list->head.next;cur != &list->head;cur = cur->next)
    {
        callback(cur->data);
    }
}

void llist_destroy(LLIST* l)
{
    struct llist_node_st *cur,*next;
    struct llist_head_st *list = (struct llist_head_st *)l;
    for(cur = list->head.next;cur != &list->head;cur = cur->next)
    {
        next = cur->next;
        free(cur);
    }
    free(list);
}

void* llist_find(LLIST* l, const void* key, llist_cmp* cmp)
{
    struct llist_node_st *node;
    struct llist_head_st *list = (struct llist_head_st *)l;
    node = find_(list,key,cmp);
    if(node == &list->head)
        return NULL;
    return node->data;
}

int llist_delete(LLIST* list, const void* key, llist_cmp* cmp)
{
    return llist_fetch_((struct llist_head_st *)list, key, cmp, NULL);
}

int llist_fetch(LLIST* list, const void* key, llist_cmp* cmp, void* data)
{
    return llist_fetch_((struct llist_head_st *)list, key, cmp, data);
}
