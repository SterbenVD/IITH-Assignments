#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <pthread.h>
#include <chrono>

using namespace std;
#define mp make_pair;

// Global variables for number of Threads, size of sudoku, array(2-d) for sudoku, and whether it is valid or not.
// Also, has mutex for locking the valid variable
size_t numThread;
size_t sizeofmatrix;
vector<vector<int>> matrix;
bool validsud = 1;
pthread_mutex_t valid_lock;

// Return the string to be printed
string printer(size_t th_id, int i, bool ans)
{
    string op;
    if (i < sizeofmatrix)
        op = "ROW";
    else if (i < 2 * sizeofmatrix)
        op = "COLUMN";
    else
        op = "GRID";
    string valid = (ans == true) ? "Valid" : "not Valid";
    string ret = "Thread " + to_string(th_id + 1) + " checked " + op + " " + to_string(i % sizeofmatrix + 1) + " and is " + valid + "\n";
    return ret;
}

// Prints to output file, whether row/column/grid is valid or not.
void printfile(string toprint)
{
    ofstream output("output.txt", ios_base::app);
    output << toprint;
    output.close();
}

// Function whether the given row/column/grid is valid or not
bool check(size_t task)
{
    bool pres[sizeofmatrix];
    for (int i = 0; i < sizeofmatrix; i++)
        pres[i] = 0;
    size_t step = task / sizeofmatrix;
    task -= step * sizeofmatrix;
    switch (step)
    {
    case 0:
        for (size_t i = 0; i < sizeofmatrix; i++)
        {
            if (pres[matrix[task][i] - 1] == 1)
                return false;
            else
                pres[matrix[task][i] - 1] = 1;
        }
        break;
    case 1:
        for (size_t i = 0; i < sizeofmatrix; i++)
        {
            if (pres[matrix[i][task] - 1] == 1)
                return false;
            else
                pres[matrix[i][task] - 1] = 1;
        }
        break;
    case 2:
        size_t siz = (size_t)round(sqrt(sizeofmatrix));
        for (size_t i = (task / siz) * siz; i < (task / siz) * siz + siz; i++)
        {
            for (size_t j = (task % siz) * siz; j < ((task % siz) + 1) * siz; j++)
            {
                if (pres[matrix[i][j] - 1] == 1)
                    return false;
                else
                    pres[matrix[i][j] - 1] = 1;
            }
        }
        break;
    }
    return true;
}

// Returns current time in microseconds
size_t us()
{
    size_t t = std::chrono::duration_cast<std::chrono::microseconds>(
                   std::chrono::high_resolution_clock::now().time_since_epoch())
                   .count();
    return t;
}

// Function for the child thread. Checks required rows/cloumns/grids
void *threadsolve(void *parentdata)
{
    size_t threadNo = *(size_t *)parentdata;
    for (int i = threadNo; i < 3 * sizeofmatrix; i += numThread)
    {
        if (validsud == 1)
        {
            if (check(i) == false)
            {
                string toprint = printer(threadNo, i, false);
                // A single thread prints to file at a given time
                pthread_mutex_lock(&valid_lock);
                if (validsud == 1)
                {
                    validsud = 0;
                    printfile(toprint);
                }
                pthread_mutex_unlock(&valid_lock);
            }
            else
            {
                string toprint = printer(threadNo, i, true);
                if (validsud == 1)
                    printfile(toprint);
            }
        }
        else
            pthread_exit(NULL);
    }
    pthread_exit(NULL);
}

// Main function
int main()
{
    // Read thread count and sudoku
    ifstream input("input.txt");
    input >> numThread >> sizeofmatrix;
    remove("output.txt");
    for (size_t i = 0; i < sizeofmatrix; i++)
    {
        vector<int> arr;
        for (size_t j = 0; j < sizeofmatrix; j++)
        {
            int x;
            input >> x;
            arr.push_back(x);
        }
        matrix.push_back(arr);
    }
    input.close();

    // Initialize mutex
    pthread_mutex_init(&valid_lock, NULL);

    pthread_t threadId[numThread];
    size_t threadComm[numThread]; // Which threadNo is the thread

    size_t thread = 0;
    size_t tstart = us();
    do // Making k threads
    {
        threadComm[thread] = thread;
        pthread_create(&threadId[thread], NULL, threadsolve, &threadComm[thread]);
        thread++;
    } while (thread < numThread);
    for (size_t i = 0; i < numThread; i++) // Wait for each thread to finish
        pthread_join(threadId[i], NULL);
    size_t tend = us();
    // Print end statements
    ofstream output("output.txt", ios_base::app);
    if (validsud == 1)
        output << "Sudoku is Valid";
    else
        output << "Sudoku is not Valid";
    output << "\nTime Taken: " << (tend - tstart) << " microseconds";
    output.close();
    return 0;
}
