
#ifndef TASKF_H
#define TASKF_H

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <vector>
#include <numeric>
#include <thread>
#include <chrono>
#include "print.h"

using namespace std;
 
/* --------------------------------------------------
   SIMPLE BUT MEANINGFUL TASKS
   -------------------------------------------------- */

// 1️⃣ Compute expression like: "45 * 78"
void computeTask(string &s) {
    lock_guard<mutex> lk(printMutex());

    printSection("TASK EXECUTION");
    slowRefresh(150);
    printKV("Task", "Compute");
    slowRefresh(150);
    printKV("Input", s);

    int a, b;
    char op;
    stringstream ss(s);

    if (ss >> a >> op >> b) {
        int res = 0;
        if (op == '+') res = a + b;
        else if (op == '-') res = a - b;
        else if (op == '*') res = a * b;
        else if (op == '/') res = (b != 0 ? a / b : 0);

        cout << "Result = " << res << endl;
    } else {
        cout << "Invalid expression" << endl;
    }
slowRefresh(150);
    printFooter();
}

// 2️⃣ Simulate heavy processing
void processTask(string &s) {
    lock_guard<mutex> lk(printMutex());

    printSection("TASK EXECUTION");
    slowRefresh(150);
    printKV("Task", "Process");
    slowRefresh(150);
    printKV("Data", s);
    slowRefresh(150);

    cout << "Processing data";
    for (int i = 0; i < 5; i++) {
        cout << ".";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(300));
    }
    cout << "\nProcess completed successfully\n";
slowRefresh(150);
    printFooter();
}



// 5️⃣ Reverse string
void reverseTask(string &s) {
    lock_guard<mutex> lk(printMutex());

    printSection("TASK EXECUTION");
    slowRefresh(150);
    printKV("Task", "Reverse");
    slowRefresh(150);
    printKV("Input", s);

    reverse(s.begin(), s.end());
    cout << "Reversed = " << s << endl;
slowRefresh(150);
    printFooter();
}

// 6️⃣ Count vowels
void vowelTask(string &s) {
    lock_guard<mutex> lk(printMutex());

    printSection("TASK EXECUTION");
    slowRefresh(150);
    printKV("Task", "VowelCount");
    slowRefresh(150);
    printKV("Input", s);
slowRefresh(150);
    int count = 0;
    for (char c : s) {
        c = tolower(c);
        if (c=='a'||c=='e'||c=='i'||c=='o'||c=='u')
            count++;
    }

    cout << "Vowels = " << count << endl;
slowRefresh(150);
    printFooter();
}

void primeTask(string &s) {
    lock_guard<mutex> lk(printMutex());

    printSection("TASK EXECUTION");
    slowRefresh(150);
    printKV("Task", "PrimeCheck");
    slowRefresh(150);
    printKV("Input", s);

    int n = stoi(s);
    bool prime = n > 1;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) prime = false;

    cout << n << (prime ? " is PRIME\n" : " is NOT PRIME\n");
    slowRefresh(150);
    printFooter();
}

void factorialTask(string &s) {
    lock_guard<mutex> lk(printMutex());

    printSection("TASK EXECUTION");
    slowRefresh(150);
    printKV("Task", "Factorial");
    slowRefresh(150);
    printKV("Input", s);

    int n = stoi(s);
    long long fact = 1;
    for (int i = 1; i <= n; i++) fact *= i;

    cout << "Factorial = " << fact << endl;
    slowRefresh(150);
    printFooter();
}

void fibonacciTask(string &s) {
    lock_guard<mutex> lk(printMutex());

    printSection("TASK EXECUTION");
    slowRefresh(150);
    printKV("Task", "Fibonacci");
    slowRefresh(150);
    printKV("Input", s);

    int n = stoi(s);
    long long a = 0, b = 1;
slowRefresh(150);
    cout << "Series: ";
    for (int i = 0; i < n; i++) {
        cout << a << " ";
        long long c = a + b;
        a = b;
        b = c;
    }
    cout << endl;
    slowRefresh(150);
    printFooter();
}


void fileTask(string &s) {
    lock_guard<mutex> lk(printMutex());

    printSection("TASK EXECUTION");
    slowRefresh(150);
    printKV("Task", "FileProcess");
    slowRefresh(150);
    printKV("Size(KB)", s);
    slowRefresh(150);

    int size = stoi(s);
    for (int i = 0; i <= size; i += size/5 + 1) {
        cout << "Processed " << i << " KB\n";
        this_thread::sleep_for(chrono::milliseconds(200));
    }

    cout << "File processing completed\n";
    slowRefresh(150);
    printFooter();
}


void palindromeTask(string &s) {
    lock_guard<mutex> lk(printMutex());

    printSection("TASK EXECUTION");
    slowRefresh(150);
    printKV("Task", "Palindrome");
    slowRefresh(150);
    printKV("Input", s);
    slowRefresh(150);

    string r = s;
    reverse(r.begin(), r.end());

    cout << (r == s ? "Palindrome\n" : "Not Palindrome\n");
    slowRefresh(150);
    printFooter();
}


void heavyCpuTask(string &s) {
    lock_guard<mutex> lk(printMutex());

    printSection("TASK EXECUTION");
    slowRefresh(150);
    printKV("Task", "HeavyCPU");
    slowRefresh(150);
    printKV("Iterations", s);
slowRefresh(150);
    long long n = stoll(s);
    volatile long long x = 0;
    for (long long i = 0; i < n; i++) x += i;

    cout << "Heavy CPU task done\n";
    slowRefresh(150);
    printFooter();
}



/* --------------------------------------------------
   TASK MAP (ONLY REAL WORK)
   -------------------------------------------------- */

inline unordered_map<string, function<void(string&)>> taskMap = {
    {"Compute",  computeTask},
    {"Process",  processTask},
    {"Reverse",  reverseTask},
    {"Vowel",    vowelTask},
    {"Prime",      primeTask},
{"Factorial",  factorialTask},
{"Fibonacci",  fibonacciTask},
{"File",       fileTask},
{"Palindrome", palindromeTask},
{"HeavyCPU",   heavyCpuTask}
};

/* --------------------------------------------------
   GET TASK FUNCTION
   -------------------------------------------------- */

inline function<void(string&)> gett(string &topic) {
    auto it = taskMap.find(topic);
    if (it != taskMap.end())
        return it->second;

    return [](string &data){
        lock_guard<mutex> lk(printMutex());
        cout << "[Unknown Task] Payload = " << data << endl;
    };
}

#endif // TASKF_H
