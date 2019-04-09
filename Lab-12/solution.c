#include<stdio.h>
#include <stdlib.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex, writeblock;
int VAR = 0, reader_count = 0;
const int MAXM = 15;

void *reader(void *arg)
{
    int f = ((int)arg);
    while(1) {
        sem_wait(&mutex);

        // update reader count
        reader_count = reader_count + 1;
        if(reader_count==1)
        {
            printf("First Reader Enters!\n");
            sem_wait(&writeblock);
        }
        sem_post(&mutex);

        // open file for reading.
        FILE *fp = fopen("buffer.txt", "r");
        char result[25];
        fgets(result, 25, fp);
        printf("Reader %lu reads value %s\n", pthread_self(), result);
        sleep(1);
        
        // update reader count.
        sem_wait(&mutex);
        reader_count = reader_count - 1;
        if(reader_count==0)
        {
            printf("Last Reader Leaves !\n");
            sem_post(&writeblock);
        }
        sem_post(&mutex);

        // check if we have reached the termination condition.
        int rv = atoi(result);
        if(rv >= MAXM) break;
        sleep(1);
    }
    pthread_exit(0);
}

void *writer()
{
    while(1) {
        sem_wait(&writeblock);
        printf("Writer(%lu) enters\n", pthread_self());
        VAR++; // increment variable.

        FILE *f = fopen("buffer.txt", "w");
        char result[50]; 
        sprintf(result, "%d", VAR);  // convert int to string. 
        fputs(result, f); // save to the file.
        printf("Writer(%lu) writes the value %d\n", pthread_self(), VAR);
        fclose(f); // close the file.
        
        printf("Writer(%lu) leaves\n", pthread_self());
        sem_post(&writeblock);
        if(VAR >= MAXM) break;
        sleep(1);
    }
    pthread_exit(0);
}

int main()
{
    // useful variable initialisations.
    int i,b; 
    pthread_t rtid[2];
    sem_init(&mutex,0,1);
    sem_init(&writeblock,0,1);
    
    // creation of initial file.
    FILE *sharedFile = fopen("buffer.txt", "w");
    if(sharedFile == NULL) {
        printf("There was a problem in creating the file!\n");
        return 1;
    }
    fputs("0", sharedFile);
    fclose(sharedFile);
    printf("File created, VAR is 0\n");

    // creating threads.
    pthread_create(&rtid[0],NULL,reader,(void *)0);
    pthread_create(&rtid[1],NULL,reader,(void *)1);    
    writer();

    // waiting for the child threads to exit.
    pthread_join(rtid[0], NULL);
    pthread_join(rtid[1], NULL);
    return 0;
}
