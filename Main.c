#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

#define THREAD_NUM 8 //Si no mal estoy, son o datos char o datos void, o si no entonces sería int

//#define SHARED 1

sem_t semEmpty;
sem_t semFull;

pthread_mutex_t mutexBuffer; //evitar las rece condition

void *Producer(); // Make Declaration of Producer
void *Consumer(); // Make Declaration of Consumer
/*sem_t empty, full; //Declare semaphores to be used
int data;*/ // data variable

int buffer[10];
int count = 0; //variables globales

int main(int argc, char* argv[])
{
    char commandBuf[64];

    /*
    pthread_t ptid, ctid;
    printf("\nMain Started");
    sem_init(&empty, SHARED, 1);
    sem_init(&full, SHARED, 0);
    sem_init(&amp;sm, SHARED, 1);
    pthread_create(&ptid,NULL,Producer,NULL);

    printf("Ingrese 'paciente' en la consola para agregar un paciente\n");

    while (fgets(commandBuf, sizeof(commandBuf), stdin) != NULL){
        
        pthread_join(ptid,NULL);

        if (strncmp(commandBuf, "paciente", strlen("paciente")) == 0){
            pthread_create(&ctid,NULL,Consumer,NULL); 
            
            pthread_join(ctid,NULL); 
            printf("\nMain done\n");
        }
        else if (strncmp(commandBuf, "salir", strlen("salir")) == 0)
        {
            break;
        }
    }*/
    /*
    srand(time(NULL));
    pthread_t th[THREAD_NUM];
    pthread_mutex_init(&mutexBuffer, NULL);
    sem_init(&semEmpty, 0, 10);
    sem_init(&semFull, 0, 0);
    int i;
    for (i = 0; i < THREAD_NUM; i++) {
        if (i > 0) {
            if (pthread_create(&th[i], NULL, &producer, NULL) != 0) {
                perror("Failed to create thread");
            }
        } else {
            if (pthread_create(&th[i], NULL, &consumer, NULL) != 0) {
                perror("Failed to create thread");
            }
        }
    }
    for (i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    sem_destroy(&semEmpty);
    sem_destroy(&semFull);
    pthread_mutex_destroy(&mutexBuffer);
    return 0;*/

    srand(time(NULL));
    pthread_t ptid;
    pthread_t ctid[THREAD_NUM];
    printf("\nMain Started");
    sem_init(&semEmpty, 0, 10);
    sem_init(&semFull, 0, 0);
    pthread_create(&ptid, NULL, &Producer, NULL);

    printf("Ingrese 'paciente' en la consola para agregar a un paciente\n");
    printf("Ingrese 'salir' en la consola para terminar el programa\n");

    while (fgets(commandBuf, sizeof(commandBuf), stdin) != NULL){
        if (strncmp(commandBuf, "paciente", strlen("paciente")) == 0){
            for (int i = 0; i < THREAD_NUM; i++){
                pthread_create(ctid + i, NULL, &Consumer, NULL); 
                
                pthread_join(ptid, NULL);
                pthread_join(ctid[i], NULL);
            }
            printf("\nMain done\n");
        }
        else if (strncmp(commandBuf, "salir", strlen("salir")) == 0)
        {
            break;
        }
    }

    sem_destroy(&semEmpty);
    sem_destroy(&semFull);
    pthread_mutex_destroy(&mutexBuffer);

    return 0;
}

void *Producer()
{
    //ITEM PRODUCED...
    //int produced;
    printf("\nProducer created");
    printf("\nProducer id is %ld\n",pthread_self()); //print thread id

    
    while(1){

        int x = rand() % 10;
        sleep(1);

        sem_wait(&semEmpty);

        pthread_mutex_lock(&mutexBuffer);
        
        //add to the buffer
        if(count < 10){
            buffer[count] = x;
            count++;
        }
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semFull);
    }
/*
    for(produced=0;produced<10;produced++)
    {
        sem_wait(&empty);
        // LOCK-starts
            sem_wait(&sm);
                //CRITICAL SECTION STARTS
                        data=produced;
                //CRITICAL SECTION ENDS
            sem_post(&sm);
        //LOCK-ends
        sem_post(&full);
        printf("\nProducer: %d",data);
    }*/
}

void *Consumer(/*int citas*/)
{
    //int consumed, total=0;

    while (1) {
        int y;

        // Remove from the buffer
        sem_wait(&semFull);
        pthread_mutex_lock(&mutexBuffer);
        y = buffer[count - 1];
        count--;
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semEmpty);

        // Consume
        printf("Got %d\n", y);
        sleep(1);
    }

/*
    //int c_necs = citas;

    printf("\nConsumer created\n");
    printf("\nConsumer id is %ld\n",pthread_self());
    for(consumed=0;consumed<10;consumed++)
    {
        sem_wait(&full); //Hacer que el semáforo 
        //LOCK-starts   
            sem_wait(&sm);
                    //CRITICAL SECTION STARTS
                            total=total+data;
                    //CRITICAL SECTION ENDS
            sem_post(&sm);
        //LOCK-ends
        sem_post(&empty);
        printf("\nConsumed: %d",data);
    }
    printf("\nThe total of 100 iterations is %d\n",total);*/
}