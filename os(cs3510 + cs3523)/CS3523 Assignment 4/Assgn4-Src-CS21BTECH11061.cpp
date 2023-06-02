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
#define PLOG_NAME "logP.txt"
#define CLOG_NAME "logC.txt"
using namespace std;

enum pstate
{
    ENTER,
    REQUEST,
    INCAR,
    OUTCAR,
    EXITS
};

enum cstate
{
    WAIT,
    RIDE,
    FINISH
};

sem_t csem;
sem_t qsem;
queue<int> q;
sem_t *semcars;
// Global variables for number of Threads,critical section count
size_t pcount, ccount, cric_section;
double mean1, mean2, mean;

bool done = 0;

// Generate exponential distribution
size_t ran_expo(double lambda)
{
    double ran = rand() / (RAND_MAX + 1.0);
    double waittime = -log(1 - ran) / lambda;
    return (size_t)waittime;
}

int qpop()
{
    sem_wait(&qsem);
    int No = q.front();
    q.pop();
    sem_post(&qsem);
    return No;
}

void qpush(int No)
{
    sem_wait(&qsem);
    q.push(No);
    sem_post(&qsem);
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

string psf(int number, pstate t)
{
    string mid;
    if (t == ENTER)
        mid = " enters the museum at ";
    else if (t == REQUEST)
        mid = " made a ride request ";
    else if (t == INCAR)
        mid = " started riding ";
    else if (t == OUTCAR)
        mid = " finished riding ";
    else if (t == EXITS)
        mid = " exits the museum at ";

    return ("Passenger " + to_string(number) + mid + getSysTime() + "\n");
}

string psl(int number, pstate t)
{
    return (to_string(number) + "," + to_string(t) + "," + to_string(us()) + "\n");
}

string csf(int cno, cstate t, int pno)
{
    string mid, end = "";
    if (t == WAIT)
    {
        mid = " accepts Passenger ";
        end = "'s request";
    }
    else if (t == RIDE)
    {
        mid = " is riding Passenger ";
    }
    else if (t == FINISH)
    {
        mid = " has finished Passenger ";
        end = "'s tour";
    }
    return ("Car " + to_string(cno) + mid + to_string(pno) + end + "\n");
}

string csl(int cno, cstate t, int pno)
{
    return (to_string(cno) + "," + to_string(t) + "," + to_string(us()) + "\n");
}

void flow(int pno, int cno, int iter)
{
    printfile(FILE_NAME, csf(cno, WAIT, pno));
    printfile(FILE_NAME, psf(pno, INCAR));
    printfile(FILE_NAME, csf(cno, RIDE, pno));

    printfile(CLOG_NAME, csl(cno, RIDE, pno));
    csleep(mean);
    printfile(CLOG_NAME, csl(cno, FINISH, pno));
    printfile(FILE_NAME, csf(cno, FINISH, pno));
    printfile(FILE_NAME, psf(pno, OUTCAR));
}

// Car Thread Function
void car(int threadNo)
{
    int temp = 1;
    while (!done)
    {
        sem_post(&semcars[threadNo - 1]);
        qpush(threadNo);
        sem_post(&csem);
        temp = 1;
        while (!done && temp > 0)
            sem_getvalue(&semcars[threadNo - 1], &temp);
        if (!done)
        {
            sem_wait(&semcars[threadNo - 1]);
            csleep(mean2);
        }
    }
}

// Passenger Thread Function
void passenger(int threadNo)
{
    printfile(FILE_NAME, psf(threadNo, ENTER));
    printfile(PLOG_NAME, psl(threadNo, ENTER));
    for (int i = 0; i < cric_section; i++)
    {
        printfile(FILE_NAME, psf(threadNo, REQUEST));
        sem_wait(&csem);
        int carNo = qpop() - 1;
        sem_wait(&semcars[carNo]);
        flow(threadNo, carNo + 1, i + 1);
        sem_post(&semcars[carNo]);
        csleep(mean1);
    }
    printfile(FILE_NAME, psf(threadNo, EXITS));
    printfile(PLOG_NAME, psl(threadNo, EXITS));
}

// Main function
int main()
{
    // Read thread count, number of critical sections and values of mean 1 and mean 2
    ifstream input("inp-params.txt");
    input >> pcount >> ccount >> mean1 >> mean2 >> cric_section;
    mean = (mean1 + mean2) / 2;
    remove(FILE_NAME);
    remove(PLOG_NAME);
    remove(CLOG_NAME);

    input.close();
    sem_init(&csem, 0, 0);
    sem_init(&qsem, 0, 1);
    semcars = new sem_t[ccount];
    for (int i = 0; i < ccount; i++)
        sem_init(&(semcars[i]), 0, 0);
    thread carId[ccount];
    thread pasId[pcount];
    for (int i = 0; i < ccount; i++)
        carId[i] = thread(car, i + 1);
    for (int i = 0; i < pcount; i++)
        pasId[i] = thread(passenger, i + 1);

    for (auto &th : pasId) // Wait for passenger threads to finish
        th.join();
    done = 1;
    for (auto &th : carId) // Wait for car threads to finish
        th.join();
    return 0;
}