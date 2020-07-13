#ifndef _LIST_H_
#define _LIST_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define FORWARD    1
#define BACKWARD   2

typedef void llist_op(const void *arg);
typedef int llist_cmp(const void *key,const void *data);

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

typedef struct
{
    int size;
    struct llist_node_st head;
}LLIST;

LLIST* llist_create(int size);  //创建包含头节点的链表

int llist_insert(LLIST* list, const void *data, int mode);

void llist_travel(LLIST* list,llist_op* callback);

void *llist_find(LLIST* list ,const void *key, llist_cmp *cmp);

int llist_delete(LLIST* list ,const void *key, llist_cmp *cmp);

int llist_fetch(LLIST* list ,const void *key, llist_cmp *cmp, void *data);

void llist_destroy(LLIST* list);

#ifdef __cplusplus
}
#endif

#endif
