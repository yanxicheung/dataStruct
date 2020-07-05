#include "gtest/gtest.h"
#include "sqlist.h"

struct sqlistMergeTest:testing::Test
{
     virtual void SetUp()
     {
        sqlist_create(&list1);
        ASSERT_TRUE(list1 != NULL);

        sqlist_create(&list2);
        ASSERT_TRUE(list2 != NULL);
     }

     virtual void TearDown()
     {
         ASSERT_TRUE(sqlist_destroy(list1) == 0);
         ASSERT_TRUE(sqlist_destroy(list2) == 0);
     }

protected:
     void initTestList(sqlist *list,datatype *arr,int size)
     {
        ASSERT_TRUE(list != NULL);
        for(int i = 0;i<size;++i)
        {
            ASSERT_TRUE(0 == sqlist_insert(list,0,&arr[i]));
        }

        ASSERT_TRUE(sqlist_isempty(list) == 0);
        ASSERT_TRUE(sqlist_getnum(list) == size);
        sqlist_display(list);
        printf("\n");
     }
protected:
     sqlist *list1;
     sqlist *list2;
};

TEST_F(sqlistMergeTest,should_union_two_list_succ)
{

    datatype arr1[] = {1,6,3,5};
    initTestList(list1,arr1,sizeof(arr1)/sizeof(arr1[0]));

    datatype arr2[] = {1,2,3,5};
    initTestList(list2,arr2,sizeof(arr2)/sizeof(arr2[0]));
    sqlist_merge(list1, list2);
    sqlist_display(list1);
}


