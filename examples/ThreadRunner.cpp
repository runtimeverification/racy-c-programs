// Copyright (c) 2015 RV-Predict Team. All Rights Reserved.

#include <thread>

using namespace std;

void thread1();
void thread2();

void thread1() {
    thread t(thread1);
    t.join();
}

void thread2() {
    thread t(thread2);
    t.join();
}

int main() {
    thread t1(thread1);
    thread t2(thread2);

    t1.join();
    t2.join();

    return 0;
}
