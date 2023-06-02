#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <omp.h>
#include <cmath>

using namespace std;

// Global variables for number of Threads, size of sudoku, array(2-d) for sudoku, and whether it is valid or not.
size_t numThread;
size_t sizeofmatrix;
vector<vector<int>> matrix;
bool validsud = 1;

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

size_t us()
{
    size_t t = std::chrono::duration_cast<std::chrono::microseconds>(
                   std::chrono::high_resolution_clock::now().time_since_epoch())
                   .count();
    return t;
}

// Main function
int main(int argc, char **argv)
{
    // Read thread count and sudoku
    ifstream input("input.txt");
    input >> numThread >> sizeofmatrix;

    // Set thread count
    omp_set_num_threads(numThread);
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
    numThread = (numThread > 3 * sizeofmatrix) ? 3 * sizeofmatrix : numThread;
    size_t th_id, execute = 1;

    size_t tstart = us();

    // Start threads
#pragma omp parallel private(th_id) shared(execute)
    {
        th_id = omp_get_thread_num();
        vector<bool> arr;
        for (int i = th_id; i < 3 * sizeofmatrix; i += numThread)
        {
            if (execute == 1)
            {
                if (check(i) == false)
                {
                    string toprint = printer(th_id, i, false);
                    // A single thread prints to file at a given time
                    if (execute == 1)
                    {
                        execute = 0;
                        printfile(toprint);
                    }
                }
                // A single thread prints to file at a given time
                else
                {
                    string toprint = printer(th_id, i, true);
                    if (execute == 1)
                        printfile(toprint);
                }
            }
            else
                break;
        }
        // Wait for all threads
#pragma omp barrier
    }
    size_t tend = us();
    // Print end statements
    ofstream output("output.txt", ios_base::app);
    if (execute == 1)
        output << "Sudoku is Valid";
    else
        output << "Sudoku is not Valid";
    output << "\nTime Taken: " << (tend - tstart) << " microseconds";
    output.close();
    return 0;
}