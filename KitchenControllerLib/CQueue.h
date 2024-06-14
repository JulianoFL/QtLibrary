#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <queue>
#include <boost/thread/thread.hpp>
#include <list>
#include <map>


/// <summary>
/// Simple Threadsafe Queue using boost thread and Mutex
/// </summary>
template<typename Data>
class CQueue
{
private:
    mutable boost::mutex TMutex;
    std::queue<Data> DataQueue;
    boost::condition_variable CVariable;
public:
    void Push(Data const& Data);
    //bool empty() const;
    bool TryPop(Data& Value);
    void WaitAndPop(Data& Value);


    std::list<Data> ReturnQueueCopy();
};



template<typename Data>
void CQueue<Data>::Push(Data const& Data)
{
    boost::mutex::scoped_lock lock(TMutex);
    DataQueue.push(Data);
    lock.unlock();
    CVariable.notify_one();
}

template<typename Data>
bool CQueue<Data>::TryPop(Data& Value)
{
    boost::mutex::scoped_lock lock(TMutex);
    if (DataQueue.empty())
    {
        return false;
    }

    Value = DataQueue.front();
    DataQueue.pop();
    return true;
}

template<typename Data>
void CQueue<Data>::WaitAndPop(Data& Value)
{
    boost::mutex::scoped_lock lock(TMutex);
    while (DataQueue.empty())
    {
        CVariable.wait(lock);
    }

    Value = DataQueue.front();
    DataQueue.pop();
}

template<typename Data>
std::list<Data> CQueue<Data>::ReturnQueueCopy()
{
    boost::mutex::scoped_lock lock(TMutex);

    std::queue<Data> TempDataQueue = DataQueue;


    std::list<Data> CopyQueue;

    while (!TempDataQueue.empty()) {
        Data data = TempDataQueue.front();
        
        CopyQueue.push_back(data);

        TempDataQueue.pop();
    }

    return CopyQueue;
}


