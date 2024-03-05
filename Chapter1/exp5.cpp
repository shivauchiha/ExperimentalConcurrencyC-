#include<iostream>
#include<thread>
#include<atomic>


// experiment for thread local. thread local is used to force thread to use gobal and static variable as a local copy and dispose.

thread_local std::atomic<int> var1 {0};
std::atomic<int> var2 {0};

void thread1()
{
  
        var1++;
        var2++;
   

    std::cout<<"var1:"<<var1<<" var2:"<< var2<<std::endl;

} 

int main()
{
    std::thread t1(thread1);
    std::thread t2(thread1);
    std::thread t3(thread1);
    t1.join();
    t2.join();
    t3.join();
}