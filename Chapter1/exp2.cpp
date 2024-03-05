
#include<iostream>
#include<thread>
#include<functional>
#include<atomic>

// just a udemy exercise for thinking in concurrency 
/*
 -> cleaning crew can take any number of tasks from captain (Main thread)
 -> Engine crew can take only one task at a time and captain has to wait till engine crew finishes their previous task
 -> enum command defines the inputs available which user needs to give in runtime terminal
*/

enum class command { clean = 1 , fullspeed = 2  , halt = 3, stopPrg = 100};


class thread_guard
{
    private:
    std::thread & t1;
    thread_guard(const thread_guard & ) = delete;
    thread_guard& operator=(const thread_guard& ) = delete;

    public:
    explicit thread_guard(std::thread & inputThread):t1(inputThread){};
    
    ~thread_guard()
    {
        if(t1.joinable())
        {
            t1.join();
        }
    } 
};


class CleaningCrew
{
    public:
    void operator()()
    {
        std::cout<<"started cleaning !" <<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        std::cout<<"finished cleaning !"<<std::endl;
    }

};

class EngineCrew
{
    private:
    std::atomic<bool> isThreadBusy{false} ;
    public:
    void fullspeed ()
    {
      isThreadBusy = true;
      std::cout<<"Fullspeed Ahead !"<<std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(20000));
      std::cout<<"Reached Maximum speed !"<<std::endl;
      isThreadBusy = false;
    }
    void halt ()
    {
        isThreadBusy = true;
        std::cout<<"Decelerating !"<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(8000));
        std::cout<<"Ship Halted !"<<std::endl;
        isThreadBusy = false;
    }

    bool is_busy()
    {
        if(isThreadBusy == false)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

};


int main()
{
    //captain 
    CleaningCrew C1;
    EngineCrew E1;
    int userInput = 0;
    char run = 0x01;
     
    std::thread cleaner;
    std::thread Enginectr;
    thread_guard G1(Enginectr);

    while(run == 0x01)
    {
      std::cout<<"what to do ?" << std::endl;
      std::cin>>userInput;
      command cmd = static_cast<command>(userInput);
      switch(cmd)
      {
        case command::fullspeed:
           if(E1.is_busy() == true)
           {
            std::cout<<"Sorry Engine Crew is busy !"<<std::endl;
           }
           else
           {
            if(Enginectr.joinable())
            {Enginectr.join();}
             Enginectr = std::thread(std::bind(&EngineCrew::fullspeed,std::ref(E1)));
           }
           
           break;
        
        case command::halt:
           if(E1.is_busy() == true)
           {
            std::cout<<"Sorry Engine Crew is busy !"<<std::endl;
           }
           else
           {
            if(Enginectr.joinable())
            {Enginectr.join();}
             Enginectr = std::thread(std::bind(&EngineCrew::halt,std::ref(E1)));
           }
           
           break;


        case command::clean:
           cleaner = std::thread(C1);
           cleaner.detach();
           break;        
             
        case command::stopPrg:
           run = 0x02;
           break;

        default:
           std::cout<<"Invalid Input"<<std::endl;
           break;
           
      }  
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    
    


}