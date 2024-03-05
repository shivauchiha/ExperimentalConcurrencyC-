#include<iostream>
#include<thread>
#include<vector>
#include<numeric>
#include<random>
#include<chrono>
#include<functional>
#include<algorithm>
//implement parallel accumulate
// threading offers advantage of speed when operating in large dataset
template<typename it, typename T >
void accumulator (it start, it end, T& psum)
{
   
     psum = (std::accumulate(start,end,0.0f));

}


void generate_data(std::vector<float> & ret)
{
    
    ret.reserve(10000000);
    std::default_random_engine gen;
    std::uniform_real_distribution<double> distribution(0.0,1000.0);
    for(int i =0; i<1000000; i++)
    {
        ret.emplace_back(distribution(gen));
    }
}


int main()
{
    std::vector<float> data;
    generate_data(data);
    float result = 0;
    
    auto start = std::chrono::high_resolution_clock::now();
    result = std::accumulate(data.begin(), data.end(), 0.0);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout <<"value :"<<result<<" Time:"<< duration.count() << std::endl;

    //Threaded execution
    start = std::chrono::high_resolution_clock::now();
    int hardware_threads = std::thread::hardware_concurrency();
    std::vector<float> partial_sums;
    partial_sums.reserve(hardware_threads);
    int block_size = (data.size()+hardware_threads-1)/hardware_threads;
    std::vector<std::thread> thread_list;
    auto startit = data.begin(); 
    auto endit = data.end();
    std::cout<<"spawning threads :"<<hardware_threads<<std::endl;

    for(int i =0 ; i< hardware_threads-1; i++)
    {  
        
        endit = startit;
        std::advance(endit,block_size);
        thread_list.emplace_back([startit,endit,&partial_sums](){partial_sums.emplace_back(std::accumulate(startit,endit, 0.0)); std::cout<<"started thread"<<std::this_thread::get_id()<<std::endl;});
        startit=endit;
        
    }
    endit = data.end();
    thread_list.emplace_back([startit,endit,&partial_sums](){partial_sums.emplace_back(std::accumulate(startit,endit, 0.0));std::cout<<"started thread"<<std::this_thread::get_id()<<std::endl;});
    for (auto&t : thread_list)
    {
        t.join();
    }
   
    float TotalSum = std::accumulate(partial_sums.begin(), partial_sums.end(), 0.0);
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout<<"Partial sum vector size: "<< TotalSum<< "Time: "<< duration.count()<<std::endl;

    
}