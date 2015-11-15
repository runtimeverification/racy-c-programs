// Copyright (c) 2015 Runtime Verification Inc. (RV-Predict Team). All Rights Reserved.

#include <pthread.h>
#include <stdio.h>
#include <time.h>
pthread_mutex_t lock;
int x = 0;

void *MyThread(void* v) {
  nanosleep((struct timespec[]){{0, 10000}}, NULL);
  pthread_mutex_lock(&lock);
  x++;
  pthread_mutex_unlock(&lock);
  printf("%d", 1 / x);
  return v;
}

int main() {
  pthread_t t1, t2;
  pthread_create(&t1, NULL, MyThread, NULL);
  pthread_create(&t2, NULL, MyThread, NULL);
  pthread_mutex_lock(&lock);
  x++;
  pthread_mutex_unlock(&lock);
  x = 0;
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  return 0;
}
