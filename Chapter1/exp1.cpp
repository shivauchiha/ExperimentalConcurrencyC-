#include <iostream>
#include <thread>

/*
   Just experimenting with starting a thread and running it 
*/

void functionA();
void functionB();
void test();


void functionA()
{
    std::cout<<"Hello from function A "<<std::this_thread::get_id()<<std::endl;
    std::thread threadC(test);
    threadC.join();
}

void functionB()
{
    std::cout<<"Hello from function B "<<std::this_thread::get_id()<<std::endl;
}

void test()
{
    std::cout<<"Hello from test function "<<std::this_thread::get_id()<<std::endl;
}


int main()
{
    std::thread threadA(functionA);
    std::thread threadB(functionB);
    threadA.join();
    threadB.join();
    
}