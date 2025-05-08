#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

/* Declaração da thread */
pthread_t threads[2];

/* Função que a thread irá executar */
void * thread_function_1 (void * param) {
    int *aux = (int *)param; // Cast de void* para int*
    for (int icont = 1; icont <= 10; icont = icont + 1){
        int neoAux = icont;
        *aux = *aux + neoAux;
        printf("thread 1 - icont %d - valor do parametro %d\n\n", icont, *aux);
        //sleep(2);
        if (icont == 10){
            printf("Thread 1 finalizada na função\n\n");
        }
    }

    pthread_exit(NULL);
    
}

/* Função que a thread irá executar em paralelo */
void * thread_function_2 (void * param) {
    int *aux = (int *)param; // Cast de void* para int*

    for (int icont = 1; icont <= 10; icont = icont + 1){
        int neoAux = icont;
        *aux = *aux + neoAux;
        //sleep(5);
        printf("thread 2 - icont %d - valor do parametro %d\n\n", icont, *aux);
        if (icont == 10){
            printf("Thread 2 finalizada na função\n\n");
        }
    }
    
    pthread_exit(NULL);
}

int main(){
    setlocale(LC_ALL, "Portuguese_Brazil");
    int parametro = 0;
    int *param = &parametro;

    /* Criação da thread  
        1° parâmetro - ID da thread, acesado por endereço de memória
        2° parâmetro - Opções da thread, em geral NULL
        3° parâmetro - Ponteiro da função que será executada na thread
        4° parâmetro - parâmetro que a thread vai receber, poder ser qualquer tipo de dados, inclusive struct 
    */
    if (pthread_create(&threads[0], NULL, &thread_function_1, (void *)param) != 0){
        printf("Erro ao criar a thread!\n");
        return 1;
    }

    if (pthread_create(&threads[1], NULL, &thread_function_2, (void *)param) != 0){
        printf("Erro ao criar a thread!\n");
        return 1;
    }

    /* Aguarda a thread finalizar */
    int temp = pthread_join(threads[0], NULL);
    int temp_1 = pthread_join(threads[1], NULL);
    printf("Finalizado com temp - %d\n", temp);
    printf("Finalizado com temp_1 - %d\n", temp_1);
    printf("Thread finalizada com sucesso!\n");

    return 0;
}