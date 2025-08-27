#include "test.h"

namespace ThreadTest{
    TEST_F(ThreadPoolTest, TestCase_1)
    {
        // 1. Test default ThreadPool
        ThreadPool myPool0;
        std::future<int>res = myPool0.PushTask(Func,2);
        //std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        //EXPECT_EQ(res.get(), 4);
        std::future<int>res3 = myPool0.PushTask(Func,3);
        std::future<int>res4 = myPool0.PushTask(Func,4);
        std::future<int>res5 = myPool0.PushTask(Func,5);
        std::future<int>res6 = myPool0.PushTask(Func,6);
        std::future<int>res7 = myPool0.PushTask(Func,7);
        std::future<int>res8 = myPool0.PushTask(Func,8);
        std::future<int>res9 = myPool0.PushTask(Func,9);

        // Excess tasks on queue
        std::future<int>res10 = myPool0.PushTask(Func,10);
        std::future<int>res11 = myPool0.PushTask(Func,11);
        std::future<int>res12 = myPool0.PushTask(Func,12);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        //std::cout << "Remaining items on queue now: " << myPool0.QueueItems() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(20000));
    }

    TEST_F(ThreadPoolTest, TestCase_2)
    {
        // 2. Test ThreadPool with specific size
        ThreadPool myPool1(16);
        std::future<int>res2 = myPool1.PushTask([](const int& a){
                //std::cout<<"This is from Lambda Function \n";
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                return a*a;
            }, 6);
        EXPECT_EQ(res2.get(), 36);
    }
} // Namespace