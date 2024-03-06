// Name: Vishal Vijay Devadiga
// Roll No: CS21BTECH11061

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include <mutex>
#include <random>
#include <ctime>
#include <cmath>
#include <string>
#include <map>
#include <vector>
#include <unistd.h>

// ZEROMQ
#include <zmq.hpp>

using namespace std;

#define INPUT_FILE "inp-params.txt"
#define LOGS_FILE "logs.txt"
#define DATA_FILE "data.txt"

double lamb;
int numEvents;
int numProcesses;
double ratio_proc;

int total_entries = 0;
int total_msg_size = 0;
// Mutex for data
mutex data_mtx;

// Receive Address of the process
string recv_addr(int processId)
{
    int port = 5555 + processId;
    string s = "tcp://127.0.0.1:" + to_string(port);
    return s;
}

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
    // Ensure that the time is in the format HH:MM:SS:MS:MIC
    string hr = to_string(ltm->tm_hour);
    if (hr.size() == 1)
        hr = "0" + hr;
    string min = to_string(ltm->tm_min);
    if (min.size() == 1)
        min = "0" + min;
    string sec = to_string(ltm->tm_sec);
    if (sec.size() == 1)
        sec = "0" + sec;
    string mil = to_string(t / 1000 % 1000);
    if (mil.size() == 1)
        mil = "00" + mil;
    else if (mil.size() == 2)
        mil = "0" + mil;
    string mic = to_string(t % 1000);
    if (mic.size() == 1)
        mic = "00" + mic;
    else if (mic.size() == 2)
        mic = "0" + mic;
    string s = hr + ":" + min + ":" + sec + ":" + mil + ":" + mic;
    return s;
}

// Enum for event type
enum EventType
{
    INTERNAL,
    SEND,
    RECEIVE,
    MARKER_SEND,
    MARKER_RECV,
    FINISH
};

// Generate whether internal or send
EventType generateEvent()
{
    // Generate a random number between 0 and 1
    double ran = (double)rand() / RAND_MAX;

    // Ratio of internal events to send events is ratio_proc
    ran *= ratio_proc;
    // If the random number is less than 0.5, return SEND
    if (ran > 0.5)
    {
        return INTERNAL;
    }
    // Else return send
    else
    {
        return SEND;
    }
}

// Input File
ifstream input(INPUT_FILE);
ofstream main_func(LOGS_FILE);

// Implementing Vector Clocks
class VC
{
private:
    // vectorClocks[i] stores the value of the clock of process i
    vector<int> vectorClocks;
    // processId is the id of the process
    int processId;
    // numProcesses is the number of processes
    int numProcesses;
    // Event number of the process
    int eventNo;
    // Mutex for the vector clocks
    mutex mtx;

    // File name for the logs
    string log_name;

    enum ActionType
    {
        INCREMENT_VC,
        UPDATE_VC,
        SEND_VC,
        RECEIVE_VC,
        PRINT_VC,
    };

public:
public:
    VC()
    {
    }
    // Constructor to initialize the vectorClocks
    VC(int processId, int numProcesses, string file_name)
    {
        this->processId = processId;
        this->numProcesses = numProcesses;
        vectorClocks.resize(numProcesses, 0);
        this->eventNo = 0;
        this->log_name = file_name;
        // Do not Clear the file
        // ofstream output(file_name);
        // output.close();
        eventNo = 0;
    }

    // Function to print to the file
    void print(string toprint)
    {
        ofstream output(log_name, ios_base::app);
        output << toprint;
        output.close();
    }

    // Function to increment the clock of the process
    void increment()
    {
        vectorClocks[processId]++;
    }

    void clock_increment()
    {
        mtx.lock();
        increment();
        mtx.unlock();
    }

    // Function to update the clock of the process when it receives a message
    void update(vector<int> newVectorClocks)
    {
        for (int i = 0; i < numProcesses; i++)
        {
            vectorClocks[i] = max(vectorClocks[i], newVectorClocks[i]);
        }
    }

    // Function to send the clock of the process
    string send()
    {
        string s = "";
        for (int i = 0; i < numProcesses; i++)
        {
            s += to_string(vectorClocks[i]) + ",";
        }
        s.pop_back();
        return s;
    }

    string clock_send()
    {
        mtx.lock();
        string s = send();
        mtx.unlock();
        data_mtx.lock();
        total_entries += (int)vectorClocks.size();
        total_msg_size += s.size();
        data_mtx.unlock();
        return s;
    }

    // Function to receive the clock of the process
    void receive(string s)
    {
        vector<int> newVectorClocks;
        int i = 0;
        while (i < s.size())
        {
            string num = "";
            while (s[i] != ',' && i != s.size())
            {
                num += s[i];
                i++;
            }
            newVectorClocks.push_back(stoi(num));
            num = "";
            i++;
        }
        mtx.lock();
        increment();
        update(newVectorClocks);
        mtx.unlock();
    }

    // Function to log the events
    void main_func(EventType type, int pairId = -1, string msg = "")
    {
        mtx.lock();
        if (type != FINISH && type != SEND && type != RECEIVE)
            increment();
        int eventno = vectorClocks[processId];
        string systime = getSysTime();
        string clock = send();
        mtx.unlock();
        string s = "P" + to_string(processId) + "E" + to_string(eventno) + " :[" + systime + "]: (" + clock + ") ;";
        if (type == INTERNAL)
            s += " Internal Event in Process " + to_string(processId);
        else if (type == SEND)
            s += " Send Event in Process " + to_string(processId) + " to Process " + to_string(pairId);
        else if (type == RECEIVE)
            s += " Receive Event in Process " + to_string(processId) + " from Process " + to_string(pairId);
        else if (type == MARKER_SEND)
            s += " Marker Sent in Process " + to_string(processId) + " to Process " + to_string(pairId);
        else if (type == MARKER_RECV)
            s += " Marker Received in Process " + to_string(processId) + " from Process " + to_string(pairId);
        else if (type == FINISH)
            s += " Finished Events in Process " + to_string(processId);
        s += "\n";
        // Print to the file
        print(s);
    }
};

// Function to create a zmq::message_t from the string and the type
zmq::message_t create_message(EventType type, string s = "", int processId = -1)
{
    string msg = "";
    if (type == MARKER_RECV || type == MARKER_SEND)
        msg = "M";
    else
        msg = "V";
    msg += to_string(processId) + " ";
    msg += s;
    zmq::message_t message(msg.size());
    memcpy(message.data(), msg.c_str(), msg.size());
    return message;
}

// Function for sleep
void csleep(double mean)
{
    std::chrono::duration<int, std::milli> timespan(ran_expo(1 / mean));
    std::this_thread::sleep_for(timespan);
}

// ZEROMQ Functions

void process_recv(int processId, VC &vc, vector<vector<int>> &adjMat)
{
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_PULL);
    socket.bind(recv_addr(processId));
    // Number of connections
    int ac = 0;
    for (int i = 0; i < numProcesses; i++)
    {
        if (adjMat[i][processId] == 1 && (i != processId))
        {
            ac++;
        }
    }
    // Receive the messages
    while (ac != 0)
    {
        zmq::message_t message;
        socket.recv(&message);
        string s = string(static_cast<char *>(message.data()), message.size());
        // If the message is a marker message
        if (s[0] == 'M')
        {
            string receiveId = s.substr(1, s.size() - 2);
            int rId = stoi(receiveId);
            vc.main_func(MARKER_RECV, rId);
            ac--;
        }
        // If the message is a vector clock message
        else
        {
            // Find the process id from the message
            // It is till first space
            int i = 1;
            while (s[i] != ' ')
            {
                i++;
            }
            string receiveId = s.substr(1, i - 1);
            int rId = stoi(receiveId);
            // Update the vector clock of the process
            string clock = s.substr(i + 1, s.size() - i - 1);
            vc.receive(clock);
            vc.main_func(RECEIVE, rId);
        }
    }
    socket.close();
    zmq_ctx_destroy(&context);
}

void process_send(int processId, VC &vc, vector<vector<int>> &adjMat)
{
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_PUSH);
    int msg_count = 0;
    // Find the number of connections
    vector<int> sendIds;
    for (int i = 0; i < numProcesses; i++)
    {
        if (adjMat[processId][i] == 1 && (i != processId))
        {
            sendIds.push_back(i);
        }
    }

    while (msg_count < numEvents)
    {
        // Generate the event type
        EventType type = generateEvent();
        // If the event is internal
        if (type == INTERNAL)
        {
            vc.main_func(INTERNAL);
        }
        // If the event is send
        else
        {
            // Select a random process to send the message to
            int sendId = sendIds[rand() % sendIds.size()];
            // Send the message
            string addr = recv_addr(sendId);
            socket.connect(addr);
            vc.clock_increment();
            zmq::message_t message = create_message(SEND, vc.clock_send(), processId);
            socket.send(message);
            // Disconnect the socket
            socket.disconnect(addr);
            vc.main_func(SEND, sendId);
            msg_count++;
        }
        csleep(lamb);
    }
    // Send the marker messages
    for (int i = 0; i < sendIds.size(); i++)
    {
        string addr = recv_addr(sendIds[i]);
        socket.connect(addr);
        zmq::message_t message = create_message(MARKER_SEND, "", processId);
        socket.send(message);
        // Disconnect the socket
        socket.disconnect(addr);
        vc.main_func(MARKER_SEND, sendIds[i]);
    }
    socket.close();
    zmq_ctx_destroy(&context);
}

// Thread function for each process
void process_main(int processId, vector<vector<int>> &adjMat)
{
    string PLOG_FILE = "logs.txt";
    // Create a vector clock for the process and a log file
    VC vc(processId, numProcesses, PLOG_FILE);
    // Create a thread for receiving messages
    thread recv_thread(process_recv, processId, ref(vc), ref(adjMat));
    // Create a thread for sending messages
    thread send_thread(process_send, processId, ref(vc), ref(adjMat));
    // Join the threads
    send_thread.join();
    recv_thread.join();
    vc.main_func(FINISH);
}

// Main function

int main()
{
    // Read from input
    input >> numProcesses;
    input >> lamb;
    input >> ratio_proc;
    input >> numEvents;

    // Read the adjacency matrix
    vector<vector<int>> adjMat(numProcesses, vector<int>(numProcesses, 0));
    string s;
    getline(input, s);
    // Getline then, suppose 1 2 3, then 1 is connected to 2 and 3
    while (getline(input, s))
    {
        // Read integers from the string
        stringstream ss;
        ss << s;
        int x;
        int i;
        ss >> i;
        while (ss >> x)
        {
            adjMat[i - 1][x - 1] = 1;
        }
    }

    // Remove output file
    ofstream output(LOGS_FILE);
    output.close();

    // // Create Threads for each process
    vector<thread> threads(numProcesses);
    for (int i = 0; i < numProcesses; i++)
    {
        threads[i] = thread(process_main, i, ref(adjMat));
    }

    // Join all threads
    for (int i = 0; i < numProcesses; i++)
    {
        threads[i].join();
    }

    // Print the total number of entries
    output = ofstream(DATA_FILE);
    // output << "Total number of entries: " << total_entries << endl;
    // output << "Total message size: " << total_msg_size << endl;
    output << total_entries << "," << total_msg_size << endl;
    output.close();

    return 0;
}