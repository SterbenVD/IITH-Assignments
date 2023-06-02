#include <iostream>
#include <fstream>
#include <pthread.h>
#include <chrono>

using namespace std;

// Global variables for n and k
size_t numThread;
size_t numbers;

// Returns current time in microseconds
size_t us()
{
    size_t t = std::chrono::duration_cast<std::chrono::microseconds>(
                   std::chrono::high_resolution_clock::now().time_since_epoch())
                   .count();
    return t;
}

// Function for the child thread. Generates the numbers, operates on it and prints it to the log files
void *threadsolve(void *parentdata)
{
    size_t threadNo = *(size_t *)parentdata;
    string circname = "circ" + to_string(threadNo) + ".log";
    string notcircname = "notcirc" + to_string(threadNo) + ".log";

    // Creating Log FILE
    ofstream circfile(circname);
    ofstream notcircfile(notcircname);
    size_t *arr = (size_t *)malloc(3 * sizeof(size_t));
    arr[0] = threadNo;
    arr[1] = 0;
    arr[2] = 0;
    unsigned int seed = us() + threadNo;

    for (size_t i = threadNo + 1; i <= numbers; i += numThread) // Generate points and check if it lies in circle
    {
        double x = 1 - (((double)rand_r(&seed)) / RAND_MAX) * 2;
        double y = 1 - (((double)rand_r(&seed)) / RAND_MAX) * 2;
        double dis = x * x + y * y;
        arr[1]++;
        if (dis <= 1)
        {
            circfile << "(" << x << ", " << y << ")\n";
            arr[2]++;
        }
        else
            notcircfile << "(" << x << ", " << y << ")\n";
    }
    circfile.close();
    notcircfile.close();
    pthread_exit(arr); // Return pointer of the array
}

// Main function
int main()
{
    // Read n and k
    ifstream input("input.txt");
    input >> numbers >> numThread;
    remove("output.txt");
    remove("log.txt");
    input.close();
    size_t thread = 0;
    pthread_t threadId[numThread];
    size_t threadComm[numThread]; // Which threadNo is the thread
    for (size_t i = 0; i < numThread; i++)
        threadComm[i] = i;

    // Time taken
    size_t start = us();
    do // Making k threads
    {
        pthread_create(&threadId[thread], NULL, threadsolve, &threadComm[thread]);
        thread++;
    } while (thread < numThread);

    size_t circpoints = 0, totpoints = 0;
    for (size_t i = 0; i < thread; i++) // Wait for each thread, and do the required work
    {
        size_t *ptr;
        pthread_join(threadId[i], (void **)&ptr);
        size_t num = ptr[0], size = ptr[0];

        // Print the respective log files into the main log file
        string circname = "circ" + to_string(i) + ".log";
        string notcircname = "notcirc" + to_string(i) + ".log";
        ifstream input1(circname);
        ifstream input2(notcircname);
        ofstream logput("Log.log", ios_base::app);
        logput << "T" << i + 1 << ": ";
        logput << ptr[1] << " points checked, " << ptr[2] << " points in circle.";
        string line;
        logput << "\nPoints in circle: ";
        while (getline(input1, line))
            logput << line << ";";
        logput << "\nPoints not in circle: ";
        while (getline(input2, line))
            logput << line << ";";
        circpoints += ptr[2];
        totpoints += ptr[1];
        logput << "\n\n";
        logput.close();

        // Remove thread's log files
        const char *c1 = circname.c_str();
        const char *c2 = notcircname.c_str();
        input1.close();
        input2.close();
        remove(c1);
        remove(c2);
        free(ptr);
    }
    double pi = 4 * ((double)circpoints) / totpoints;
    size_t end = us();
    // Print to output file
    ofstream output("output.txt");
    output
        << "Time taken: " << end - start << " microseconds\n" // in us
        << "Value of pi calculated: " << pi << "\n";
    output.close();
    return 0;
}
