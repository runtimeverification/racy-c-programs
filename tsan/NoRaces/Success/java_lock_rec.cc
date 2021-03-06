// RUN: %clangxx_tsan -O1 %s -o %t && %run %t 2>&1 | FileCheck %s
#include "java.h"

jptr varaddr;
jptr lockaddr;

void *Thread(void *p) {
  __tsan_java_mutex_lock(lockaddr);
  __tsan_java_mutex_lock(lockaddr);
  *(int*)varaddr = 42;
  int rec = __tsan_java_mutex_unlock_rec(lockaddr);
  if (rec != 2) {
    printf("FAILED 0 rec=%d\n", rec);
    exit(1);
  }
  barrier_wait(&barrier);
  barrier_wait(&barrier);
  __tsan_java_mutex_lock_rec(lockaddr, rec);
  if (*(int*)varaddr != 43) {
    printf("FAILED 3 var=%d\n", *(int*)varaddr);
    exit(1);
  }
  __tsan_java_mutex_unlock(lockaddr);
  __tsan_java_mutex_unlock(lockaddr);
  return 0;
}

int main() {
  barrier_init(&barrier, 2);
  int const kHeapSize = 1024 * 1024;
  jptr jheap = (jptr)malloc(kHeapSize + 8) + 8;
  __tsan_java_init(jheap, kHeapSize);
  const int kBlockSize = 16;
  __tsan_java_alloc(jheap, kBlockSize);
  varaddr = jheap;
  *(int*)varaddr = 0;
  lockaddr = jheap + 8;
  pthread_t th;
  pthread_create(&th, 0, Thread, 0);
  barrier_wait(&barrier);
  __tsan_java_mutex_lock(lockaddr);
  if (*(int*)varaddr != 42) {
    printf("FAILED 1 var=%d\n", *(int*)varaddr);
    exit(1);
  }
  *(int*)varaddr = 43;
  __tsan_java_mutex_unlock(lockaddr);
  barrier_wait(&barrier);
  pthread_join(th, 0);
  __tsan_java_free(jheap, kBlockSize);
  printf("DONE\n");
  return __tsan_java_fini();
}

// CHECK-NOT: WARNING: ThreadSanitizer: data race
// CHECK-NOT: FAILED
// CHECK: DONE
