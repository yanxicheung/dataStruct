#include <stdio.h>
#include "sqlist.h"
#include <stdlib.h>

void sqlist_create(sqlist **self)
{
    *self = (sqlist*) malloc(sizeof(sqlist));
    if (*self == NULL)
        return;
    (*self)->last = -1;
    return;
}

int sqlist_insert(sqlist *self, int pos, datatype *data)
{
    if (self->last == DATASIZE - 1)
        return -1;
    if (pos < 0 || pos > self->last + 1)
        return -2;

    int cursor = self->last + 1;
    while (cursor > pos)
    {
        self->data[cursor] = self->data[cursor - 1];
        cursor--;
    }
    self->data[cursor] = *data;
    self->last++;
    return 0;
}

int sqlist_delete(sqlist *self, int pos)
{
    int i = 0;
    if(pos < 0 || pos > self->last)
        return -1;
    for(i = pos+1;i<=self->last;++i)
        self->data[i - 1] = self->data[i];
    self->last--;
    return 0;
}

int sqlist_merge(sqlist *lhs, sqlist *rhs)
{
    int i = 0;
    for(i = 0;i< sqlist_getnum(rhs);++i)
    {
        if(sqlist_find(lhs,&rhs->data[i]) == -1)
        {
            sqlist_insert(lhs,0,&rhs->data[i]);
        }
    }
    return 0;
}

int sqlist_find(sqlist *self, datatype *data)
{
    int i = 0;
    for (i = 0; i < sqlist_getnum(self); ++i)
    {
        if (*data == self->data[i])
            return i;
    }
    return -1;
}

int sqlist_isempty(sqlist *self)
{
    if (sqlist_getnum(self) <= 0)
        return 1;
    return 0;
}

int sqlist_setempty(sqlist *self)
{
    if (!sqlist_isempty(self))
    {
        self->last = -1;
    }
    return 0;
}

int sqlist_getnum(sqlist *self)
{
    if (self == NULL)
        return -1;
    return self->last + 1;
}

int sqlist_destroy(sqlist *self)
{
    free(self);
    return 0;
}

void sqlist_display(sqlist *self)
{
    int i = 0;
    for (i = 0; i < sqlist_getnum(self); ++i)
    {
        printf("data [%d] = %d\n", i, self->data[i]);
    }
}
