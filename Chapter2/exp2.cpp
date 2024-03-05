
/*unique lock
Difference between unique lock and lock_guard is that
-> lock is acquired immediately when lock_guard is constructed. whereas for unique lock can be set in away that it just acquires mutex without locking.
-> manual locking and unlocking is available for unique lock. 

*/

#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>

std::mutex m1;

void function1()
{
    int i = 0;
    std::unique_lock<std::mutex> lck1(m1,std::defer_lock); //defering lock only gaining information to mutex
    while(i<4)
    {
        
        if(lck1.try_lock())
        {
            std::cout <<"locked in function 1"<<std::endl;
        }
        else
        {
            std::cout <<"unable to lock in function1"<<std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            lck1.lock();
            
        }

        std::cout<<"Executing Function 1"<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
        lck1.unlock();//unlocking
        std::cout<<"unlocked in function 1"<<std::endl;
        i++;
    }
    


}

void function2()
{
    int i = 0;
    std::unique_lock<std::mutex> lck1(m1,std::defer_lock);
    while(i<4)
    {
        if(lck1.try_lock())
        {
            std::cout <<"locked in function 2"<<std::endl;
        }
        else
        {
            std::cout <<"unable to lock in function2"<<std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(10000));
            lck1.lock();
        }
        std::cout<<"Executing Function 2"<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        lck1.unlock();
        std::cout<<"unlocked in function 2"<<std::endl;
        i++;
    }


}




int main()
{
  std::thread t1(function1);
  std::thread t2(function2);   
  t1.join();
  t2.join();
}