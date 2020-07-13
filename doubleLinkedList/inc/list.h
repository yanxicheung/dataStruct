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

typedef void LLIST;

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
