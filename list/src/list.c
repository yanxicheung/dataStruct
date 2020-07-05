#include "list.h"
#include <stdio.h>
#include <stdlib.h>

static void list_travle(node* self, void *arg ,void(*visit)(node *,void *))
{
    if(list_isempty(self) == 1)
        return;
    node *cursor = self->next;
    while(cursor)
    {
        visit(cursor,arg);
        cursor = cursor->next;
    }
}

static void print(node *p,void *arg)
{
    printf("%d\n",p->data);
}

static void accumulateSize(node *p,void *arg)
{
    int *size = (int *)arg;
    (*size)++;
}

node* list_create()
{
    // 带头节点的单链表;头节点不使用;
    node *head = (node *)malloc(sizeof(node));
    if(head != NULL)
    {
        head->next = NULL;
    }
    return head;
}

int list_insert_at(node* self, int pos, datatype* data)
{
    if(self == NULL)
        return -1;

    node*p = self;
    int cursor = 0;
    // find previous
    while(p != NULL && cursor < pos)
    {
        p = p->next;
        cursor++;
    }

    if(p != NULL)
    {
        node *insert_node = (node*)malloc(sizeof(node));
        if(insert_node == NULL)
            return -2;
        insert_node->data = *data;
        insert_node->next = p->next;
        p->next = insert_node;
        return 0;
    }
    else
        return -3;
}

int list_push_back(node* self, datatype* data)
{
    if(self == NULL)
        return -1;
    node*p = self;

    while(p->next)
    {
        p = p->next;
    }
    node *insert_node = (node*)malloc(sizeof(node));
    if(insert_node == NULL)
        return -2;
    insert_node->data = *data;
    insert_node->next = NULL;
    p->next = insert_node;
    return 0;
}

int list_delete_at(node* self, int pos)
{

}

int list_delete(node* self, datatype* data)
{

}

int list_find(node* self, datatype* data)
{
    int find = 0;

    if(list_isempty(self) == 1)
        return 0;
    node *cursor = self->next;
    while(cursor)
    {
        if(cursor->data == *data)
        {
            find = 1;
            break;
        }
        cursor = cursor->next;
    }

    return find;
}

int list_isempty(node* self)
{
    if(self == NULL || self->next == NULL)
        return 1;
    return 0;
}

void list_destroy(node* self)
{
    node *p = NULL,*next = NULL;
    for(p = self->next;p != NULL;p = next)
    {
        next = p->next;
        free(p);
    }
    free(self);
}

void list_display(node* self)
{
    list_travle(self,NULL,print);
}

int list_size(node* self)
{
    int size = 0;
    list_travle(self,&size,accumulateSize);
    return size;
}
