#include <iostream>
#include <fstream>
#include <unistd.h>
#include <random>
#include <ctime>
#include <cmath>
#include <chrono>
#include <thread>
#include <semaphore.h>
#include <queue>

#define FILE_NAME "output.txt"

using namespace std;

// Enums for efficient case switches in if else
enum fstate
{
    COMMUNITY,
    HUNGRY,
    EATS,
    EXITS
};

enum vstate
{
    SLEEP,
    EMPTY
};

// Semaphores
sem_t icesem;
sem_t qsem;
sem_t esem;
sem_t rsem;

// Queue for extra credit :)
queue<int> q;

// Average Time Calculation
size_t total_wait_eat = 0;

size_t total_refill_time = 0;
size_t total_refill = 0;

// Global variables for number of Threads,critical section count
size_t kcount, mcount, ncount;
double mean1, mean2, mean, mean3, mean4;

// Global variable to denote that execution is done
bool done = 0;

// Generate exponential distribution
size_t ran_expo(double lambda)
{
    double ran = rand() / (RAND_MAX + 1.0);
    double waittime = -log(1 - ran) / lambda;
    return (size_t)waittime;
}

// Pop the queue
int qpop()
{
    sem_wait(&qsem);
    int No = q.front();
    q.pop();
    sem_post(&qsem);
    return No;
}

// Push to queue
void qpush(int No)
{
    sem_wait(&qsem);
    q.push(No);
    sem_post(&qsem);
}

// Add waiting time to eat
void addeattime(size_t time)
{
    sem_wait(&esem);
    total_wait_eat += time;
    sem_post(&esem);
}

// Add waiting time to refill
void addrefilltime(size_t time)
{
    sem_wait(&rsem);
    total_refill += 1;
    total_refill_time += time;
    sem_post(&rsem);
}

// Returns time since epoch
size_t us()
{
    size_t t = std::chrono::duration_cast<std::chrono::milliseconds>(
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

// Prints to output file/log file
void printfile(string file, string toprint)
{
    ofstream output(file, ios_base::app);
    output << toprint;
    output.close();
}

// Function for sleep
void csleep(double mean)
{
    std::chrono::duration<int, std::milli> timespan(ran_expo(1 / mean));
    std::this_thread::sleep_for(timespan);
}

// Print Statement for family
string psf(int number, fstate t)
{
    string mid;
    if (t == HUNGRY)
        mid = " is hungry";
    else if (t == EATS)
        mid = " is eating";
    else if (t == COMMUNITY)
        mid = " is in community service";
    else if (t == EXITS)
        mid = " exits";

    return ("[ " + getSysTime() + " ]: Family " + to_string(number) + mid + +"\n");
}

// Print Statement for Vendor
string psv(vstate t)
{
    string mid = "";
    if (t == SLEEP)
        mid = " sleeps";
    else if (t == EMPTY)
        mid = " is refilling";
    return ("[ " + getSysTime() + " ]: Vendor" + mid + "\n");
}

// Sleep till refill is needed
void refillsleep()
{
    size_t start = us();
    int temp = 1;
    while (!done && temp > 0)
        sem_getvalue(&icesem, &temp);
    size_t end = us();
    addrefilltime(end - start);
}

// Put Ice Cream into Pot
void putTraysInPot()
{
    if (!done)
    {
        printfile(FILE_NAME, psv(EMPTY));
        csleep(mean3);
        for (int i = 0; i < mcount; i++)
            sem_post(&icesem);
    }
    printfile(FILE_NAME, psv(SLEEP));
    csleep(mean4);
}

// vendor Thread Function
void vendor()
{
    while (!done)
    {
        refillsleep();
        putTraysInPot();
    }
}

// Wait for Ice Cream
void getIceCreamFromPot(int threadNo)
{
    size_t start = us();
    qpush(threadNo);
    printfile(FILE_NAME, psf(threadNo, HUNGRY));

    while (q.front() != threadNo)
        ;
    sem_wait(&icesem);
    qpop();
    size_t end = us();
    addeattime(end - start);
}

// Eat Sleep
void eat(int threadNo)
{
    printfile(FILE_NAME, psf(threadNo, EATS));
    csleep(mean1);
}

// Community Service Sleep
void communityservice(int threadNo)
{
    printfile(FILE_NAME, psf(threadNo, COMMUNITY));
    csleep(mean2);
}

// family Thread Function
void family(int threadNo)
{
    for (int i = 0; i < ncount; i++)
    {
        getIceCreamFromPot(threadNo);
        eat(threadNo);
        communityservice(threadNo);
    }
    printfile(FILE_NAME, psf(threadNo, EXITS));
}

// Main function
int main()
{
    ifstream input("input.txt");
    input >> kcount >> mcount >> ncount >> mean1 >> mean2 >> mean3 >> mean4;
    remove(FILE_NAME);
    input.close();

    sem_init(&icesem, 1, mcount);
    sem_init(&qsem, 1, 1);
    sem_init(&esem, 1, 1);
    sem_init(&rsem, 1, 1);

    thread vendorId;
    thread famId[kcount];

    vendorId = thread(vendor);
    for (int i = 0; i < kcount; i++)
        famId[i] = thread(family, i + 1);

    for (auto &th : famId) // Wait for family threads to finish
        th.join();
    done = 1;
    vendorId.join();

    double avg_wait_eat = (double)total_wait_eat / (kcount * ncount);
    double avg_wait_refill = (double)total_refill_time / (total_refill);

    printfile(FILE_NAME, "\nAverage waiting time to eat: " + to_string(avg_wait_eat) + " ms");
    printfile(FILE_NAME, "\nAverage waiting time to refill: " + to_string(avg_wait_refill) + " ms");
    return 0;
}