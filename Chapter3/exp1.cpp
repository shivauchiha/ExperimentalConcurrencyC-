#include <iostream>
#include <stack>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>
#include <random>
//events trigger using conditional variables
/* basically there are 2 threads: Producer and Consumers
   The producer to produce data and notify consumer to consume data.
   The consumer will consume data and notify producer to produce data.
   Producer produces random float value using random engine*/






class exp_data
{
    private:
    float data;
    
    public:
    std::atomic<bool> isSet;
    exp_data():data(0){isSet.store(false);};
    float get_data()
    {
        isSet.store(false);
        return data;
        
    }

    void set_data(const float& input)
    {
       data = input;
       isSet.store(true);
    }
};

static exp_data message;
static std::condition_variable cv;
static std::mutex key;
static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
static std::default_random_engine generator(seed);
static std::uniform_real_distribution<float> distribution(20.0f, 100000.0f);   

void producer()
{
    while(true)
    {
        std::unique_lock<std::mutex> lock(key);
        cv.wait(lock,[]{return !(message.isSet.load());});

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        float data = distribution(generator);
        message.set_data(data);
        std::cout<<"Publishing data :"<<data<<std::endl;
        cv.notify_one();

    }
    
  

}


void consumer()
{
    while(true)
    {
        std::unique_lock<std::mutex> lock(key);
        cv.wait(lock,[]{return message.isSet.load();});
        std::cout <<"consumed data :"<<message.get_data()<<std::endl;
        cv.notify_one();

    }
    
}



int main()
{
    std::thread T1(producer);
    std::thread T2(consumer);
    

    T1.join();
    T2.join();
    
}