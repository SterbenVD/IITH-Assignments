#include <iostream>
#include <fstream>
#include <unistd.h>
#include <random>
#include <ctime>
#include <cmath>
#include <chrono>
#include <thread>
#include <atomic>

#define FILE_NAME "cas.txt"
using namespace std;

// Global variables for number of Threads,critical section count
size_t numThread;
size_t cric_count;
double mean1, mean2;

// Lock
atomic_bool lock = ATOMIC_FLAG_INIT;
bool newval = true;

// Generate exponential distribution
size_t ran_expo(double lambda)
{
    double ran = rand() / (RAND_MAX + 1.0);
    double waittime = -log(1 - ran) / lambda;
    return (size_t)waittime;
}

// Returns time since epoch
size_t us()
{
    size_t t = std::chrono::duration_cast<std::chrono::microseconds>(
                   std::chrono::high_resolution_clock::now().time_since_epoch())
                   .count();
    return t;
}
// Returns current time in a string
string getSysTime()
{
    time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
    tm *ltm = localtime(&now);
    size_t t = us();
    string hr = to_string(ltm->tm_hour);
    string min = to_string(ltm->tm_min);
    string sec = to_string(ltm->tm_sec);
    string mil = to_string(t / 1000 % 1000);
    string mic = to_string(t % 1000);
    string s = hr + ":" + min + ":" + sec + ":" + mil + ":" + mic;
    return s;
}

// Returns number with ordinal suffix
string ordinal_suffix(int n)
{
    string suffixes[4] = {"th", "st", "nd", "rd"};
    int ord = n % 100;
    ord = (ord / 10 == 1) ? 0 : (ord % 10 > 3) ? 0
                                               : ord % 10;
    string num = to_string(n) + suffixes[ord];
    return num;
}

// Prints to output file(or log)
void printfile(int iteration, string id, string oper)
{
    string toprint = "[" + getSysTime() + "]: " + ordinal_suffix(iteration) + " CS " + oper + " by thread " + id + "\n";
    ofstream output(FILE_NAME, ios_base::app);
    output << toprint;
    output.close();
}

void printlog(int iteration, string id, string oper)
{
    string toprint = to_string(us()) + "," + id + "," + to_string(iteration) + "," + oper + "\n";
    ofstream output(FILE_NAME, ios_base::app);
    output << toprint;
    output.close();
}

// Function for sleep
void csleep(double mean)
{
    std::chrono::duration<int, std::milli> timespan(ran_expo(1 / mean));
    std::this_thread::sleep_for(timespan);
}

// Thread Function
void testCS(int threadNo)
{
    srand(threadNo);
    string id = to_string(threadNo);
    for (int i = 1; i <= cric_count; i++)
    {
        bool expect = false;
        printfile(i, id, "Request");
        while (lock.compare_exchange_weak(expect, newval, std::memory_order_relaxed) != true)
            expect = false;
        // Entry Section

        printfile(i, id, "Entry");
        csleep(mean1); // Simulation of critical - section
        printfile(i, id, "Exit");
        lock.store(false);
        // Exit Section
        csleep(mean2); // Simulation of Reminder Section
    }
}

// Main function
int main()
{
    // Read thread count, number of critical sections and values of mean 1 and mean 2
    ifstream input("inp-params.txt");
    input >> numThread >> cric_count >> mean1 >> mean2;
    remove(FILE_NAME);
    input.close();
    thread threadId[numThread];
    for (int i = 0; i < numThread; i++)
        threadId[i] = thread(testCS, i + 1);

    for (auto &th : threadId) // Wait for each thread to finish
        th.join();

    return 0;
}