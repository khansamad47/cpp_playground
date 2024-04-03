#include <iostream>
#include <map>
#include <shared_mutex>
#include <experimental/random>
#include <thread>
#include <chrono>

template<typename Key, typename Value>
class DataStore {
  public:
    DataStore() {}
    Value read(Key key)
    {
        // This is a shared lock which means that multiple threads can acquire
        // this at the same time
        std::shared_lock<std::shared_mutex> lk(d_sharedMutex);
        return d_store.at(key);
    }
    void write(Key key, Value value)
    {
        // This is an exclusive lock only one thread can aquire this at any
        // given time
        std::lock_guard<std::shared_mutex> lk(d_sharedMutex);
        d_store[key] = value;
    }
  private:
    std::map<Key,Value> d_store;
    std::shared_mutex d_sharedMutex;
};


void readerJob(DataStore<int,std::string>& store, std::mutex& logMutex)
{
    while (1)
    {
        int random_number = std::experimental::randint(0, 50);
        std::string val = "MISSING";
        try {
            val = store.read(random_number);
        }
        catch(...) { }
        {
            std::lock_guard<std::mutex> lk(logMutex);
            std::cout << "Read key = " << random_number 
                << " value = " << val << '\n';
        }
        std::chrono::duration<int> sleepTime = std::chrono::seconds(1);
        std::this_thread::sleep_for(sleepTime);
    }
}

void writerJob(DataStore<int,std::string>& store, std::mutex& logMutex)
{
    while (1)
    {
        int random_number = std::experimental::randint(0, 50);
        store.write(random_number, std::to_string(random_number));
        {
            std::lock_guard<std::mutex> lk(logMutex);
            std::cout << "Write key = " << random_number 
                << " value = " << random_number << '\n';
        }
        std::chrono::duration<double> sleepTime = std::chrono::milliseconds(100);
        std::this_thread::sleep_for(sleepTime);
    }
}

int main() 
{
    std::mutex logMutex;
    DataStore<int,std::string> myStore;
    std::thread readerA(readerJob, std::ref(myStore), std::ref(logMutex));
    std::thread readerB(readerJob, std::ref(myStore), std::ref(logMutex));
    std::thread readerC(readerJob, std::ref(myStore), std::ref(logMutex));
    std::thread writerA(writerJob, std::ref(myStore), std::ref(logMutex));

    readerA.join();
    readerB.join();
    readerC.join();
    writerA.join();
    return 0;
}
