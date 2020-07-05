#include "gtest/gtest.h"
#include "sqlist.h"

struct sqlistTest:testing::Test
{
     virtual void SetUp()
     {
        sqlist_create(&list);
        ASSERT_TRUE(list != NULL);
     }

     virtual void TearDown()
     {
         ASSERT_TRUE(sqlist_destroy(list) == 0);
     }
protected:
     void initTestList()
     {
         datatype arr[] = {1,6,3,5};
         for(int i = 0;i<sizeof(arr)/sizeof(arr[0]);++i)
         {
             ASSERT_TRUE(0 == sqlist_insert(list,0,&arr[i]));
         }

         ASSERT_TRUE(sqlist_isempty(list) == 0);
         ASSERT_TRUE(sqlist_getnum(list) == 4);
         sqlist_display(list);
     }
protected:
     sqlist *list;
};

TEST_F(sqlistTest,should_insert_succ)
{
    initTestList();
}

TEST_F(sqlistTest,should_delete_succ)
{
    initTestList();
    ASSERT_TRUE(0 == sqlist_delete(list,2));
    datatype data = -6;
    ASSERT_TRUE(-1 == sqlist_find(list, &data));
}

TEST_F(sqlistTest,should_num_equal_to_zero_when_set_to_empty)
{
  datatype data = 1;
  ASSERT_TRUE(0 == sqlist_insert(list,0,&data));
  ASSERT_TRUE(sqlist_getnum(list) == 1);

  sqlist_display(list);

  ASSERT_TRUE(0 == sqlist_setempty(list));
  ASSERT_TRUE(sqlist_getnum(list) == 0);
  sqlist_display(list);
}

TEST_F(sqlistTest,should_return_index_when_find_data)
{
    initTestList();
    datatype data = 5;
    ASSERT_TRUE(0 == sqlist_find(list, &data));
}

TEST_F(sqlistTest,should_return_invalid_index_when_not_find_data)
{
    initTestList();
    datatype data = -4;
    ASSERT_TRUE(-1 == sqlist_find(list, &data));
}
