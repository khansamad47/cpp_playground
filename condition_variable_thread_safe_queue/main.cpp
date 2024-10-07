#include <queue>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <experimental/random>
#include <thread>

template<typename T>
class ThreadSafeQueue {
    private:
        std::queue<T> d_storage;
        std::mutex d_mutex;
        std::condition_variable d_cv;
    public:
        ThreadSafeQueue() {};
        bool empty() const {
            std::lock_guard lk(d_mutex);
            return d_storage.empty();
        }
        size_t size() const {
            std::lock_guard lk(d_mutex);
            return d_storage.size();
        }
        void push(T item) {
            {
                std::lock_guard lk(d_mutex);
                d_storage.push(item);
            }
            // We un-lock before we notify because the waiting
            // thread will have to acquire the lock and will block
            // again
            d_cv.notify_one();
        }
        void wait_and_pop(T& result){
            std::unique_lock<std::mutex> lk(d_mutex);
            d_cv.wait(lk, [this](){ return !d_storage.empty(); });
            result = d_storage.front();
            d_storage.pop();
        }
        std::shared_ptr<T> wait_and_pop()
        {
            std::unique_lock lk(d_mutex);
            d_cv.wait(lk, [this](){ return !d_storage.empty(); });
            std::shared_ptr<T> result = std::make_shared<T>(d_storage.front());
            d_storage.pop();
            return result;
        }
        bool try_pop(T& result)
        {
            std::lock_guard lk(d_mutex);
            if (d_storage.empty())
                return false;
            result = d_storage.front();
            d_storage.pop();
            return true;
        }
        std::shared_ptr<T> try_pop()
        {
            std::shared_ptr<T> result;
            std::lock_guard lk(d_mutex);
            if (!d_storage.empty())
            {
                result = std::make_shared<T>(d_storage.front());
                d_storage.pop();
            }
            return result;
        }
};

void writerJob(ThreadSafeQueue<int>& q)
{
    while (1)
    {
        int num = std::experimental::randint(0, 50);
        auto id = std::this_thread::get_id();
        std::cout << "thread = "<< id
            << " Pushing item = " << num << std::endl;
        q.push(num);
        std::chrono::duration<int> sleepTime = 
            std::chrono::seconds(1);
        std::this_thread::sleep_for(sleepTime);
    }
}

void readerJob(ThreadSafeQueue<int>& q)
{
    while (1)
    {
        int num;
        q.wait_and_pop(num);
        auto id = std::this_thread::get_id();
        std::cout << "thread = "<< id
            << " Consuming item = " << num << std::endl;
        std::chrono::duration<int> sleepTime = 
            std::chrono::seconds(1);
        std::this_thread::sleep_for(sleepTime);
    }
}

int main()
{
    ThreadSafeQueue<int> queue;
    std::thread readerThreadA(readerJob, std::ref(queue));
    std::thread readerThreadB(readerJob, std::ref(queue));
    std::thread writerThreadA(writerJob, std::ref(queue));

    readerThreadA.join();
    readerThreadB.join();
    writerThreadA.join();
    
}
