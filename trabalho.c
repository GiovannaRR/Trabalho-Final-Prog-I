//Igor Henrique Koga Vigato e Giovanna Beatriz Ramos.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cadastrocliente {
    int codigo;
    char npet[15];
    char ndono[30];
    char especie[30];
    int idade;
    char sintoma[75];
    char diagnostico[150];
} cadastro;

void funcadastro() {
    FILE *pontfile = fopen("usuario.txt","a");
    if (pontfile == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    printf("Digite o codigo do seu bichinho: ");
    setbuf(stdin, NULL);
    scanf("%d", &cadastro.codigo);
    fprintf(pontfile,"%d\n", cadastro.codigo);

    printf("Digite o nome do seu bichinho: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]%*c", cadastro.npet);
    fprintf(pontfile,"%s\n", cadastro.npet);

    printf("Digite o nome do(a) dono(a) do bichinho: ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]%*c", cadastro.ndono);
    fprintf(pontfile, "%s\n", cadastro.ndono);

    printf("De qual especie ele(a) e? ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]%*c", cadastro.especie);
    fprintf(pontfile, "%s\n", cadastro.especie);

    printf("Quantos anos seu bichinho tem? ");
    setbuf(stdin, NULL);
    scanf("%d", &cadastro.idade);
    fprintf(pontfile, "%d\n", cadastro.idade);

    printf("Qual o sintoma dele(a)? ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]%*c", cadastro.sintoma);
    fprintf(pontfile, "%s\n", cadastro.sintoma);

    printf("Diagnostico do bichinho? ");
    setbuf(stdin, NULL);
    scanf(" %[^\n]%*c", cadastro.diagnostico);
    fprintf(pontfile, "%s\n", cadastro.diagnostico);

    fclose(pontfile);
}

void consulta(int codigo) {
    FILE *pontfile;
    pontfile = fopen("usuario.txt", "r");

    if (pontfile == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

while (!feof(pontfile)) {
            fscanf(pontfile, "%d\n", &cadastro.codigo);
            fscanf(pontfile, "%s\n", cadastro.npet);
            fscanf(pontfile, "%s\n", cadastro.ndono);
            fscanf(pontfile, "%s\n", cadastro.especie);
            fscanf(pontfile, "%d\n", &cadastro.idade);
            fscanf(pontfile, "%s\n", cadastro.sintoma);
            fscanf(pontfile, "%s\n", cadastro.diagnostico);
        if (cadastro.codigo == codigo) {

            printf("\nNome do pet: %s\n", cadastro.npet);
            printf("Nome do dono(a): %s\n", cadastro.ndono);
            printf("Especie: %s\n", cadastro.especie);
            printf("Idade: %d\n", cadastro.idade);
            printf("Sintomas: %s\n", cadastro.sintoma);
            printf("Diagnostico: %s\n", cadastro.sintoma);
            break;
        }
    }
}

void alteraregistro(int codigo) {
    FILE *pontfile;
    pontfile = fopen("usuario.txt", "r");
    FILE *filetemp;
    filetemp = fopen("usuariotemp.txt", "w");
    if (pontfile == NULL || filetemp == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    int codigo_lido;

    int encontrado = 0;
    while (fscanf(pontfile, "%d", &codigo_lido) == 1) {
        if (codigo_lido == codigo) {
            encontrado = 1;
            printf("Digite os novos dados do registro\n");
            printf("Nome do Pet: ");
            setbuf(stdin, NULL);
            fgets(cadastro.npet, sizeof(cadastro.npet), stdin);
            printf("\nNome do Dono: ");
            setbuf(stdin, NULL);
            fgets(cadastro.ndono, sizeof(cadastro.ndono), stdin);
            printf("Especie do bichinho: ");
            setbuf(stdin, NULL);
            fgets(cadastro.especie, sizeof(cadastro.especie), stdin);
            printf("Idade do Pet: ");
            scanf("%d", &cadastro.idade);
            setbuf(stdin, NULL);
            printf("Sintoma: ");
            setbuf(stdin, NULL);
            fgets(cadastro.sintoma, sizeof(cadastro.sintoma), stdin);
            setbuf(stdin, NULL);
            printf("Diagnostico: ");
            setbuf(stdin, NULL);
            fgets(cadastro.diagnostico, sizeof(cadastro.diagnostico), stdin);

            fscanf(filetemp, "%d\n", cadastro.codigo);
            fscanf(filetemp, "%s", cadastro.npet);
            fscanf(filetemp, "%s", cadastro.ndono);
            fscanf(filetemp, "%s", cadastro.especie);
            fscanf(filetemp, "%d\n", cadastro.idade);
            fscanf(filetemp, "%s", cadastro.sintoma);
            fscanf(filetemp, "%s\n", cadastro.diagnostico);
            
            printf("Registro alterado com sucesso!\n");
            break;
        }

    }
    fclose(filetemp);
    fclose(pontfile);
    remove("usuario.txt");
    rename("usuariotemp.txt", "usuario.txt");
    if (!encontrado) {
        printf("Registro nao encontrado.\n");
    }
    
}

void remover_registro(int codigo) {
    FILE *pontfile = fopen("usuario.txt", "r");
    FILE *filetemp = fopen("usuariotemp.txt", "w");
    char linha[150];
    char codestring[150];
    sprintf(codestring, "%d", codigo);

    if (pontfile == NULL || filetemp == NULL) {
        printf("Erro ao abrir os arquivos!\n");
        exit(1);
    } else {
        while(fscanf(pontfile, "%d\n", &cadastro.codigo) == 1){
            fscanf(pontfile, "%s\n", cadastro.npet);
            fscanf(pontfile, "%s\n", cadastro.ndono);
            fscanf(pontfile, "%s\n", cadastro.especie);
            fscanf(pontfile, "%d\n", &cadastro.idade);
            fscanf(pontfile, "%s\n", cadastro.sintoma);
            fscanf(pontfile, "%s\n", cadastro.diagnostico);
            if(cadastro.codigo != codigo){
                fprintf(filetemp, "%d\n", cadastro.codigo);
                fprintf(filetemp, "%s\n", cadastro.npet);
                fprintf(filetemp, "%s\n", cadastro.ndono);
                fprintf(filetemp, "%s\n", cadastro.especie);
                fprintf(filetemp, "%d\n", cadastro.idade);
                fprintf(filetemp, "%s\n", cadastro.sintoma);
                fprintf(filetemp, "%s\n", cadastro.diagnostico);
            }
        }
    }
    fclose(pontfile);
    fclose(filetemp);
    remove("usuario.txt");
    rename("usuariotemp.txt", "usuario.txt");
}

void exibir_registro() {
    FILE *pontfile = fopen("usuario.txt", "r");
    char linha[150];

    if (pontfile == NULL) {
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    } else {
        while (fgets(linha, sizeof(linha), pontfile) != NULL) {
            linha[strcspn(linha, "\n")] = '\0'; // Remover o caractere de nova linha da linha lida
            printf("Codigo: %s \n", linha);

            fgets(linha, sizeof(linha), pontfile); // Nome do Pet
            linha[strcspn(linha, "\n")] = 0;
            printf("Nome do Pet: %s \n", linha);

            fgets(linha, sizeof(linha), pontfile); // Nome do(a) Dono(a)
            linha[strcspn(linha, "\n")] = 0;
            printf("Nome do(a) Dono(a): %s \n", linha);

            fgets(linha, sizeof(linha), pontfile); // Especie
            linha[strcspn(linha, "\n")] = '\0';
            printf("Especie: %s \n", linha);

            fgets(linha, sizeof(linha), pontfile); // Idade
            linha[strcspn(linha, "\n")] = '\0';
            printf("Idade: %s \n", linha);

            fgets(linha, sizeof(linha), pontfile); // Sintomas
            linha[strcspn(linha, "\n")] = '\0';
            printf("Sintomas: %s \n", linha);

            fgets(linha, sizeof(linha), pontfile); // Diagnostico
            linha[strcspn(linha, "\n")] = '\0';
            printf("Diagnostico: %s \n", linha);

            fgets(linha, sizeof(linha), pontfile); // Avançar para a próxima linha vazia
            printf("\n");
        }
    }
    fclose(pontfile);
}

int main() {
    char variavel;
    int codigo;
    int varloop = 1;

    while (varloop == 1) {
        printf("\n=========================================\n");
        printf("          ||Menu de interacao||\n");
        printf("=========================================\n");
        printf("Digite 1 para: Cadastro do seu bichinho. \n");
        printf("Digite 2 para: Consultar o registro.\n");
        printf("Digite 3 para: Alterar algum registro.\n");
        printf("Digite 4 para: Remover algum registro.\n");
        printf("Digite 5 para: Exibir registros.\n");
        printf("_________________________________________\n");
        printf("        Qual opcao voce deseja? ");
        scanf(" %c", &variavel);

        switch (variavel) {
            case '1':
                funcadastro();
                break;
            case '2':
                printf("Digite o codigo: ");
                scanf("%d", &codigo);
                setbuf(stdin, NULL);
                consulta(codigo);
                break;
            case '3':
                printf("Digite o codigo:");
                scanf("%d", &codigo);
                setbuf(stdin, NULL);
                alteraregistro(codigo);
                break;
            case '4':
                printf("Digite o codigo para remocao: ");
                scanf("%d", &codigo);
                setbuf(stdin, NULL);
                remover_registro(codigo);
                break;
            case '5':
                exibir_registro();
                break;
            default:
                printf("Obrigado por usar o Programa!\n");
                varloop = 0;
                break;
        }
    }

    return 0;
}