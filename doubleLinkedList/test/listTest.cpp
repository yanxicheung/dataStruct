#include "list.h"
#include "gtest/gtest.h"

#define NAMESIZE 32

 struct score_st
 {
     int id;
     char name[NAMESIZE];
     int math;
     int chinese;
 };

 void print(const void *arg)
 {
     struct score_st*score = (struct score_st*)arg;
     printf("id = %d,name = %s,math = %d,chinese = %d\n",score->id,score->name,score->math,score->chinese);
 }

 int id_cmp(const void *key,const void *data)
 {
     const int *id  = (const int *)key;
     const struct score_st *r = (const struct score_st *)data;
     return (*id - r->id);
 }

struct llistTest:testing::Test
{
     virtual void SetUp()
     {
         handler = llist_create(sizeof(struct score_st));
         ASSERT_TRUE(handler != NULL);
     }

     virtual void TearDown()
     {
         llist_destroy(handler);
     }
protected:
     LLIST *handler;
};

TEST_F(llistTest,should_create_list_succ)
{
    struct score_st tmp;

    for(int i = 0;i<7;++i)
    {
        tmp.id = i;
        snprintf(tmp.name,NAMESIZE,"std%d",i);
        tmp.math = rand()%100;
        tmp.chinese = rand()%100;
        llist_insert(handler,&tmp,BACKWARD);
    }
    llist_travel(handler,print);

    int id = 3;
    struct score_st *data =  (struct score_st *)llist_find(handler,&id,id_cmp);
    if(data != NULL)
    {
        printf("find:\n");
        print(data);
    }
    else
    {
        printf("can not find\n");
    }
}



