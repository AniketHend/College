#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
    key_t key = ftok("shmfile", 65);// ftok to generate unique key
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);// shmget returns an identifier in shmid
    char *str = (char *)shmat(shmid, (void *)0, 0);// shmat to attach to shared memory
    printf("Data read from memory: %s", str);// detach from shared memory
    shmdt(str);// destroy the shared memory
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
