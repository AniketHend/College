#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
    key_t key = ftok("shmfile", 65);// ftok to generate unique key
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);// shmget returns an identifier in shmid
    char *str = (char *)shmat(shmid, (void *)0, 0);// shmat to attach to shared memory
    printf("Write Data : ");
    fgets(str, 1024, stdin);
    printf("Data Written in memory: %s", str);// detach from shared memory
    shmdt(str);
    return 0;
}
