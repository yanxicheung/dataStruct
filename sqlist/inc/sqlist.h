#ifndef SQLIST_H_
#define SQLIST_H_

#define DATASIZE  20

#ifdef __cplusplus // 告诉编译器，这部分代码按C语言的格式进行编译，而不是C++的
extern "C"
{
#endif

    typedef int datatype;

    typedef struct node_st
    {
        datatype data[DATASIZE];
        int last;
    } sqlist;

    void sqlist_create(sqlist **);
    int sqlist_insert(sqlist *, int, datatype *);
    int sqlist_delete(sqlist *, int);
    int sqlist_find(sqlist *, datatype *);
    int sqlist_isempty(sqlist *);
    int sqlist_setempty(sqlist *);
    int sqlist_getnum(sqlist *);
    int sqlist_destroy(sqlist *);
    int sqlist_merge(sqlist *, sqlist *); // 取并集
    void sqlist_display(sqlist *);

#ifdef __cplusplus
}
#endif

#endif
