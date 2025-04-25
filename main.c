#include <stdio.h>
#include <stdlib.h>

char *nomes = NULL;
int tamanho = 0;

void adicionar() {
    char nome[100];
    int i, j;

    printf("Digite o nome a ser adicionado: ");
    scanf(" %[^\n]", nome);

    for (i = 0; nome[i] != '\0'; i++);
    int novotamanho = tamanho + i + (tamanho > 0 ? 1 : 0) + 1;
    nomes = realloc(nomes, novotamanho);

    if (tamanho > 0) {
        nomes[tamanho] = ','; //separar os nomes por uma virgula
        tamanho++;
    }

    for (j = 0; nome[j] != '\0'; j++, tamanho++) {
        nomes[tamanho] = nome[j];
    }
   nomes[tamanho] = '\0';
}

/*void remover() {
    if (!nomes) {
        printf("Nenhum nome armazenado pra ser removido.\n");
        return;
    }
    char nome[100];
    int i = 0, j = 0, k, achou = 0;

    printf("Digite o nome a remover: ");
    scanf(" %[^\n]", nome);

        }
*/
void lista() {
if (!nomes) {
        printf("Nenhum nome pra listar.\n");
        return;
    } else {
        printf("Nomes: %s\n", nomes);
    }
}

int main() {
    int opcao;

    do {
        printf("\n Menu:\n");
        printf("1- Adicionar nome\n");
      //  printf("2- Remover nome\n");
        printf("3- Listar\n");
        printf("4- Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: adicionar(); break;
           // case 2: remover(); break;
            case 3: lista(); break;
            case 4: printf("\n Saindo do Programa..."); break;
        }
    } while (opcao != 4);

    return 0;
}
