#include <mutex>
#include <exception>
#include <thread>

// We want to create a mutex class which is such that this class can only
// lock on the thread when there is not another lock held which is of lower
// value so lock can be acquired in the following sequence
// 1. 5000
// 2. 4000
// 3. 2000
//
// but not in
// 1. 4000
// 2. 5000 ====> Exception

class HiericialMutex {
  private:
    std::mutex d_mutex;
    const int d_level;
    int d_prevlevel;
    static int d_allowedLevel;
  public:
    HiericialMutex (int level): d_level(level), d_prevlevel(0)

    {

    }
    void lock() {
        if (d_level >= d_allowedLevel)
        {
            throw std::exception();
        }
        d_mutex.lock();
        d_prevlevel = d_allowedLevel;
        d_allowedLevel = d_level; // Now allowed value has reduced to this.value
    }
    void unlock() {
        d_allowedLevel = d_prevlevel;
        d_prevlevel = 0;
        d_mutex.unlock();
    }
};
int HiericialMutex::d_allowedLevel = 99999; // use MAX_INT

int main() {
    HiericialMutex mutexHigh(10); 
    HiericialMutex mutexLow (5); 

    // There is a chance of a deadlock in the code below
    // but the HiericialMutex would cause a runtime error

    std::thread threadA([&](){
        mutexHigh.lock();
        mutexLow.lock();
    });
    std::thread threadB([&](){
        mutexLow.lock();
        mutexHigh.lock();
    });
    threadA.join();
    threadB.join();
    
    return 0;
}
