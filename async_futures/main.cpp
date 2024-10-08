#include <iostream>
#include <vector>
#include <future>
#include <thread>
#include <chrono>
#include <random>

int randomNumber(int start, int end) {
  // Simulate a delay (random between 1 to 5 seconds)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(start, end);

    return dist(gen); 
}

int fetchDataFromServer(int serverId)
{

    int delay = randomNumber(1,5);
    std::this_thread::sleep_for(std::chrono::seconds(delay));
    // Simulate the data returned by the server (random int)
    int data = randomNumber(100,999);
    std::cout << "Server " << serverId 
        << " returned data: " << data << "\n";
    return data;
}

int main()
{
    std::cout << "Number of threads = "
        << std::thread::hardware_concurrency() << std::endl;
    std::vector<std::future<int>> futures;
    for (size_t i = 0; i != 8; ++i)
    {
        futures.emplace_back(std::async(fetchDataFromServer, i));
    }
    for (auto & handle: futures)
    {
        handle.wait();
        std::cout << "future.get() = " << handle.get() << '\n';
    }
    return 0;
}
