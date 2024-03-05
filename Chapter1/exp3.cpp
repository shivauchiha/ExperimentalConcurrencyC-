#include<iostream>
#include<thread>

// just trying out thread id and number of threads available function
//checking out sleep and yield function as well

void thread1 ()
{
    int i = 0;
    std::cout<<"starting thread 1! "<<std::this_thread::get_id()<<std::endl;
    while(i<1000)
    {
        std::cout<<"thread 1 going to sleep !"<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout<<"ping from thread 1"<<std::endl;
        i++;
    }
    std::cout<<"ending thread 1! "<<std::endl;
}

void thread2()
{
    int i = 0;
    std::cout<<"starting thread 2! "<<std::this_thread::get_id()<<std::endl;
    while(i<1000)
    {
        if(i%2==0)
        {
            std::cout<<"Thread2 yielded !"<<std::endl;
            std::this_thread::yield();
            std::cout<<"ping from thread 2"<<std::endl;
        } 
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        i++;
    }
    std::cout<<"ending thread 2! "<<std::endl;
}



int main()
{
    std::cout<<"The number of hardware threads available is "<<std::thread::hardware_concurrency()<<std::endl;
    std::thread t1(thread1);
    std::thread t2(thread2);
    t1.join();
    t2.join();
}