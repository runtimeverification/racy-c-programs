// Copyright (c) 2015 Runtime Verification Inc. (RV-Predict Team). All Rights Reserved.

#include <pthread.h>
#include <stdio.h>
pthread_mutex_t lock;
int Global;

void *Thread1(void* x) {
  pthread_mutex_lock(&lock);
  Global = Global + 1;
  pthread_mutex_unlock(&lock);
  printf("%d", 1 / Global);
  return x;
}

int main() {
  pthread_t t;
  pthread_create(&t, NULL, Thread1, NULL);
  pthread_mutex_lock(&lock);
  Global = 0;
  pthread_mutex_unlock(&lock);
  pthread_join(t, NULL);
  return 0;
}
