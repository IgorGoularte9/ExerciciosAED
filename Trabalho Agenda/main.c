#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_NOME 50     
#define TAMANHO_EMAIL 100
#define TAMANHO_REGISTRO_PESSOA (sizeof(int) + TAMANHO_NOME + sizeof(int) + TAMANHO_EMAIL)
#define MAX_PESSOAS 10
#define TAMANHO_BUFFER (sizeof(int) + sizeof(int) + (MAX_PESSOAS * TAMANHO_REGISTRO_PESSOA) + sizeof(int))


void *pBuffer = NULL;


void mostrar_menu();
void adicionar_pessoa();
void remover_pessoa();
void buscar_pessoa();
void listar_todos();


int main() {

    pBuffer = malloc(TAMANHO_BUFFER);
    if (pBuffer == NULL) { 
        printf("Erro ao alocar memoria para iniciar\n");
        return 1;
    }

    *(int *)pBuffer = 0; 

    
    *(int *)(pBuffer + sizeof(int)) = 1; 
    int *menu = (int *)(pBuffer + (2 * sizeof(int)) + (MAX_PESSOAS * TAMANHO_REGISTRO_PESSOA));
    *menu = 0; 


    do {
        mostrar_menu();
        printf("Escolha uma opcao: ");
        scanf("%d", menu); 
        
        while (getchar() != '\n');

        
        switch (* menu) {
            case 1:
                adicionar_pessoa();
                break;
            case 2:
                remover_pessoa();
                break;
            case 3:
                buscar_pessoa();
                break;
            case 4:
                listar_todos();
                break;
            case 5:
                printf("Saindo da agenda. Ate mais!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
        printf("\n"); 
    } while (*menu != 5);

    
    free(pBuffer);
    pBuffer = NULL; 

    return 1; 
}

void mostrar_menu() {
    printf("---      Menu  ---\n");
    printf("1- Adicionar Pessoa\n");
    printf("2- Remover Pessoa\n");
    printf("3- Buscar Pessoa\n");
    printf("4- Listar Todos\n");
    printf("5- Sair\n");
}

void adicionar_pessoa() {

    int *quantidade_pessoas = (int *)pBuffer;
    int *proximo_id = (int *)(pBuffer + sizeof(int));

    // Verifica se a agenda esta cheia antes de adicionar.
    if (*quantidade_pessoas >= MAX_PESSOAS) {
        printf("A agenda ficou cheia impossibilitando de adicionar mais pessoas\n");
        return;
    }

    void *inicio_dados_pessoas = pBuffer + (2 * sizeof(int));

    void *local_nova_pessoa = inicio_dados_pessoas + (*quantidade_pessoas * TAMANHO_REGISTRO_PESSOA);

    
    *(int *)local_nova_pessoa = *proximo_id;
    local_nova_pessoa += sizeof(int); 

    
    printf("Nome: ");
   
    fgets((char *)local_nova_pessoa, TAMANHO_NOME, stdin);
    
    ((char *)local_nova_pessoa)[strcspn((char *)local_nova_pessoa, "\n")] = 0;
    local_nova_pessoa += TAMANHO_NOME; 

    
    printf("Idade: ");
    scanf("%d", (int *)local_nova_pessoa); 
    while (getchar() != '\n'); 
    local_nova_pessoa += sizeof(int); 

 
    printf("Email: ");
    fgets((char *)local_nova_pessoa, TAMANHO_EMAIL, stdin);
    ((char *)local_nova_pessoa)[strcspn((char *)local_nova_pessoa, "\n")] = 0;

   
    (*quantidade_pessoas)++; 
    (*proximo_id)++;      
    printf("Pessoa adicionada com sucesso e seu ID é: %d\n", *proximo_id - 1); 
}


void remover_pessoa() {
    int *quantidade_pessoas = (int *)pBuffer; 
    int id_para_remover; 

    printf("Digite o ID da pessoa a remover: ");
    scanf("%d", &id_para_remover);
    while (getchar() != '\n'); 

   
    void *inicio_dados_pessoas = pBuffer + (2 * sizeof(int));
    int encontrado = 0; 
    int i; 

    
    for (i = 0; i < *quantidade_pessoas; i++) {
        
        void *registro_pessoa_atual = inicio_dados_pessoas + (i * TAMANHO_REGISTRO_PESSOA);
        
        if (*(int *)registro_pessoa_atual == id_para_remover) {
            encontrado = 1;
            if (i < *quantidade_pessoas - 1) {
                memmove(registro_pessoa_atual, registro_pessoa_atual + TAMANHO_REGISTRO_PESSOA, 
                        (*quantidade_pessoas - 1 - i) * TAMANHO_REGISTRO_PESSOA);
            }

            (*quantidade_pessoas)--; 
            printf("Pessoa com ID %d removida com sucesso.\n", id_para_remover);
            break; 
        }
    }

    if (!encontrado) {
        printf("Pessoa com ID %d nao encontrada.\n", id_para_remover);
    }
}


void buscar_pessoa() {
    int *quantidade_pessoas = (int *)pBuffer; 
    int id_para_buscar; 

    printf("Digite o ID da pessoa a buscar: ");
    scanf("%d", &id_para_buscar);
    while (getchar() != '\n'); 

    
    void *inicio_dados_pessoas = pBuffer + (2 * sizeof(int));
    int encontrado = 0; 

    
    for (int i = 0; i < *quantidade_pessoas; i++) {
        //calculo do endereco da pessoa atual no loop.
        void *registro_pessoa_atual = inicio_dados_pessoas + (i * TAMANHO_REGISTRO_PESSOA);

        int *id = (int *)registro_pessoa_atual; 
        char *nome = (char *)(registro_pessoa_atual + sizeof(int)); 
        int *idade = (int *)(registro_pessoa_atual + sizeof(int) + TAMANHO_NOME); 
        char *email = (char *)(registro_pessoa_atual + sizeof(int) + TAMANHO_NOME + sizeof(int)); 

       
        if (*id == id_para_buscar) {
            encontrado = 1; 
            
            printf("ID: %d\n", *id);
            printf("Nome: %s\n", nome);
            printf("Idade: %d\n", *idade);
            printf("Email: %s\n", email);
            break; 
        }
    }

    if (!encontrado) {
        printf("Pessoa com esse id %d nao encontrada.\n", id_para_buscar);
    }
}

void listar_todos() {
    int *quantidade_pessoas = (int *)pBuffer; 

    if (*quantidade_pessoas == 0) {
        printf("A agenda esta vazia.\n");
        return;
    }


    void *inicio_dados_pessoas = pBuffer + (2 * sizeof(int));

    printf("--- Pessoas na Agenda ---\n");
    
    for (int i = 0; i < *quantidade_pessoas; i++) {
      
        void *registro_pessoa_atual = inicio_dados_pessoas + (i * TAMANHO_REGISTRO_PESSOA);
        int *id = (int *)registro_pessoa_atual;
        char *nome = (char *)(registro_pessoa_atual + sizeof(int));
        int *idade = (int *)(registro_pessoa_atual + sizeof(int) + TAMANHO_NOME);
        char *email = (char *)(registro_pessoa_atual + sizeof(int) + TAMANHO_NOME + sizeof(int));
        // exibe os dados da pessoa
        printf("ID: %d, Nome: %s, Idade: %d, Email: %s\n", *id, nome, *idade, email);
    }
}