#ifndef _LIST_H_
#define _LIST_H_

#ifdef __cplusplus
extern "C"
{
#endif


    typedef int datatype;

    typedef struct node_st
    {
        datatype data;
        struct node_st* next;
    } node;

    node * list_create();

    int list_insert_at(node *self, int pos, datatype *data); //价值不大;
    int list_push_back(node *self, datatype *data);

    int list_delete_at(node *self, int pos);
    int list_delete(node *self, datatype *data);

    int list_find(node *self, datatype *data);

    int list_isempty(node *self);

    void list_destroy(node *self);

    void list_display(node *self);

    int list_size(node *self);

#ifdef __cplusplus
}
#endif

#endif
