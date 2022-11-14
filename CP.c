#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#define SHARED 1

void *Producer(); // Make Declaration of Producer
void *Consumer(); // Make Declaration of Consumer
sem_t empty, full; //Declare semaphores to be used
int data; // data variable

int main()
{
    char commandBuf[64];

    
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
    }
}

void *Producer()
{
    //ITEM PRODUCED...
    int produced;
    printf("\nProducer created");
    printf("\nProducer id is %ld\n",pthread_self()); //print thread id

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
    }
}

void Consumer(/*int citas/)
{
    int consumed, total=0;

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
    printf("\nThe total of 100 iterations is %d\n",total);
}