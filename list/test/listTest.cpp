#include "list.h"
#include "gtest/gtest.h"

struct listTest:testing::Test
{
     virtual void SetUp()
     {
         head = list_create();
         ASSERT_TRUE(head != NULL);
     }

     virtual void TearDown()
     {
         list_destroy(head);
     }
protected:
     node *head;
};

TEST_F(listTest,should_create_list_succ)
{
    ASSERT_TRUE(list_isempty(head) == 1);
    ASSERT_TRUE(list_size(head) == 0);
}

TEST_F(listTest,should_insert_at_succ)
{
    for(int i = 0;i<6;++i)
    {
        ASSERT_TRUE(list_insert_at(head,0, &i) == 0);
    }
    list_display(head);
    ASSERT_TRUE(list_isempty(head) == 0);
    ASSERT_TRUE(list_size(head) == 6);
}

TEST_F(listTest,should_insert_push_back_data_succ)
{
    for(int i = 0;i<6;++i)
    {
        ASSERT_TRUE(list_push_back(head, &i) == 0);
    }
    list_display(head);
}

TEST_F(listTest,should_insert_at_failed)
{
    datatype data = 1;
    ASSERT_TRUE(list_insert_at(head,1, &data) == -3);
    list_display(head);
    ASSERT_TRUE(list_isempty(head) == 1);
}

TEST_F(listTest,should_find_exist_data_succ)
{
    datatype data = 1;
    ASSERT_TRUE(list_insert_at(head,0, &data) == 0);
    ASSERT_TRUE(list_find(head,&data) == 1);
}


