#include <stdio.h>
#include <string.h>

void indice() {
    printf("================================\n");
    printf("   Controle de Estoque\n");
    printf("================================\n");
    printf("Selecione uma opção:\n");
    printf("1. Adicionar Item\n2. Remover Item\n3. Listar Estoque\n4. Sair\n");
    printf("Opção: ");
}

struct Estoque {
    char nome[50];
    int quantidade;
};

void indiceEstoque(){
    printf("=============================\n");
    printf("        Estoque Atual\n");
    printf("=============================\n");
}
void listarEstoque() {
    struct Estoque item;
    FILE *file = fopen("estoque.txt", "r");
    if (file == NULL) {
        printf("Nenhum item no estoque.\n");
        return;
    }
    while (fscanf(file, "%s %d", item.nome, &item.quantidade) != EOF) {
        printf("Nome: %s\nQuantidade: %d\n\n", item.nome, item.quantidade);
    }
    fclose(file);
}

int main() {
    int opcao, quantidade, itemRemovido = 0;
    char nome[50], nomeParaRemover[50];
    char repetir = 's';

    do {
        indice();
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Digite o nome do item: ");
                fgets(nome, 50, stdin);
                nome[strcspn(nome, "\n")] = 0;

                printf("Digite a quantidade: ");
                scanf("%d", &quantidade);
                getchar();

                FILE *file = fopen("estoque.txt", "a");
                if (file != NULL) {
                    fprintf(file, "%s\n%d\n", nome, quantidade);
                    fclose(file);
                    printf("Item adicionado com sucesso!\n");
                } else {
                    printf("Erro ao adicionar item.\n");
                }
        
                break;
            case 2:
                printf("Digite o nome do item: ");
                fgets(nomeParaRemover, 50, stdin);
                nomeParaRemover[strcspn(nomeParaRemover, "\n")] = 0;
                printf("Digite a quantidade a ser removida: ");
                scanf("%d", &quantidade);
                getchar();

                file = fopen("estoque.txt", "r");
                itemRemovido = 0;
                FILE *tempFILE = fopen("temp.txt", "w");
                int removidoCompletamente = 0;

                struct Estoque item;
                while (fscanf(file, "%s %d", item.nome, &item.quantidade) != EOF) {
                    if (strcmp(item.nome, nomeParaRemover) == 0) {
                        if (item.quantidade > quantidade) {
                            item.quantidade -= quantidade;
                            fprintf(tempFILE, "%s\n%d\n", item.nome, item.quantidade);
                            itemRemovido = 1;
                        } else if (item.quantidade == quantidade) {
                            printf("Item removido do estoque!\n");
                            removidoCompletamente = 1;
                            itemRemovido = 1;
                        } else {
                            fprintf(tempFILE, "%s\n%d\n", item.nome, item.quantidade);
                            printf("Quantidade insuficiente. Quantidade disponível: %d\n", item.quantidade);
                        } 
                    } else {
                        fprintf(tempFILE, "%s\n%d\n", item.nome, item.quantidade);
                    }
                }
                if (itemRemovido && !removidoCompletamente) {
                    printf("Quantidade atualizada com sucesso!\n");    
                } else {
                    printf("Item não encontrado\n");
                }

                fclose(file);
                fclose(tempFILE);

                remove("estoque.txt");
                rename("temp.txt", "estoque.txt");
                
                break;
            case 3:
                indiceEstoque();
                listarEstoque();
                break;
            case 4:
                printf("Obrigado por usar o Controle de Estoques! Até a próxima.\n");
                return 0;

            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }

        printf("Deseja realizar outra operação? (s/n)\n");
        scanf("%c", &repetir);
        getchar();
    
    } while (repetir == 's' || repetir == 'S');

    return 0;
}