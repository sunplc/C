void *check_malloc(long size);
void perror_exit(char *str);
pthread_t *make_thread(void *entry(void *), void *arg);
void join_thread(pthread_t *tid);
void exit_thread();
