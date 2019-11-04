void *check_malloc(long size);
void perror_exit(char *str);
pthread_t *make_thread(void *entry(void *), void *arg);
void join_thread(pthread_t *tid);
void exit_thread();

typedef pthread_mutex_t Mutex;
Mutex * make_mutex();
void mutex_lock(Mutex *mutex);
void mutex_unlock(Mutex *mutex);

typedef pthread_cond_t Cond;
Cond *make_cond();
void cond_wait(Cond *cond, Mutex *mutex);
void cond_signal(Cond *cond);

typedef struct {
    int counter;
    Mutex *counter_mutex;
    Cond *cond;
} Sem;

Sem *make_semaphore(int counter);

void semaphore_wait(Sem *sem);

void semaphore_signal(Sem *sem);
