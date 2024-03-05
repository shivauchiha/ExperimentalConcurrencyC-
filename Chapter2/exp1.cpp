/*Thread safe stack implementation using stl library */ 

#include <iostream>
#include <stack>
#include <mutex>

template<typename T>
class ThreadSafeStack {
private:
    std::stack<T> data_stack;
    mutable std::mutex mutex_;

public:
    // Push operation
    void push(const T& item) {
        std::lock_guard<std::mutex> lock(mutex_);
        data_stack.push(item);
    }

    // Pop operation
    bool pop(T& item) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (data_stack.empty()) {
            return false; // Stack is empty
        }
        item = data_stack.top();
        data_stack.pop();
        return true;
    }

    // Check if stack is empty
    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return data_stack.empty();
    }

    // Get size of stack
    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return data_stack.size();
    }
};


int main()
{
  ThreadSafeStack<float> st;
  st.push(5);
  st.push(10);
  st.push(12);
  st.push(7);
  float item = 0;
  st.pop(item);
  std::cout<<item<<std::endl;
}