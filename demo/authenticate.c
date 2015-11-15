// Copyright (c) 2015 Runtime Verification Inc. (RV-Predict Team). All Rights Reserved.

#include <pthread.h>
#include <stdio.h>
pthread_mutex_t lock;
int x=0, y=0;
int z=0;//assume z is a shared resource

void *MyThread(void* v) {
  int r1,r2;
  pthread_mutex_lock(&lock);
  r1 = y;
  pthread_mutex_unlock(&lock);
  r2 = x;//race here, x is not protected

  if (r1 + r2 > 0) {
    z=1;//authenticate z here if x or y is positive
  }
  return v;
}

int main() {
  pthread_t t;
  pthread_create(&t, NULL, MyThread, NULL);
  pthread_mutex_lock(&lock);
  y = 1;
  x = 1;
  pthread_mutex_unlock(&lock);
  pthread_join(t, NULL);
  //use z
  //may throw divide by zero exception 
  printf("Safe: %d", 1 / z);
  return 0;
}
