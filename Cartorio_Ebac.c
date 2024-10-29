#include <stdio.h>   // Biblioteca padr�o de entrada e sa�da em C
#include <stdlib.h>  // Biblioteca para fun��es auxiliares, como system() e exit()
#include <locale.h>  // Biblioteca para configura��es de localiza��o, como idioma e formata��o
#include <string.h>  // Biblioteca para manipula��o de strings

// Fun��o para registrar um usu�rio em um �nico arquivo
int registro() {
    char cpf[40];         // Vari�vel para armazenar o CPF do usu�rio
    char nome[40];        // Vari�vel para armazenar o nome do usu�rio
    char sobrenome[40];   // Vari�vel para armazenar o sobrenome do usu�rio
    char cargo[40];       // Vari�vel para armazenar o cargo do usu�rio
    FILE *file;           // Ponteiro para o arquivo onde ser�o armazenados os dados

    // Coleta de dados do usu�rio
    printf("Digite o CPF a ser cadastrado: ");
    scanf("%s", cpf);

    printf("Digite o nome a ser cadastrado: ");
    scanf("%s", nome);

    printf("Digite o sobrenome: ");
    scanf("%s", sobrenome);

    printf("Digite o cargo: ");
    scanf("%s", cargo);

    // Abre o arquivo "usuarios.txt" no modo de adi��o (append), criando-o se ele n�o existir
    file = fopen("usuarios.txt", "a");
    if (file == NULL) {  // Verifica se o arquivo foi aberto corretamente
        printf("Erro ao abrir o arquivo!\n");
        return 1;  // Retorna 1 caso haja um erro
    }

    // Salva os dados do usu�rio no arquivo em um formato organizado
    fprintf(file, "CPF: %s\n", cpf);
    fprintf(file, "Nome: %s\n", nome);
    fprintf(file, "Sobrenome: %s\n", sobrenome);
    fprintf(file, "Cargo: %s\n", cargo);
    fprintf(file, "-------------------------\n\n");  // Adiciona um separador visual entre registros

    fclose(file);  // Fecha o arquivo ap�s escrever os dados

    printf("Usu�rio registrado com sucesso!\n");
    system("pause");  // Pausa a tela para o usu�rio ler a mensagem
    return 0;  // Retorna 0, indicando que a fun��o foi conclu�da com sucesso
}

// Fun��o para consultar um usu�rio
int consulta() {
    setlocale(LC_ALL, "Portuguese");  // Define a linguagem e localiza��o
    char cpf[40];     // Vari�vel para armazenar o CPF de busca
    char linha[200];  // Vari�vel para armazenar linhas lidas do arquivo
    FILE *file;       // Ponteiro para o arquivo de dados

    printf("Digite o CPF a ser consultado: ");
    scanf("%s", cpf);

    file = fopen("usuarios.txt", "r");  // Abre o arquivo em modo de leitura
    if (file == NULL) {  // Verifica se o arquivo foi aberto corretamente
        printf("Erro ao abrir o arquivo!\n");
        return 1;  // Retorna 1 caso haja um erro
    }

    // L� o arquivo linha por linha e procura o CPF informado pelo usu�rio
    while (fgets(linha, sizeof(linha), file)) {
        // Verifica se a linha atual cont�m o CPF procurado
        if (strstr(linha, cpf) != NULL) {
            // Exibe os dados do usu�rio encontrado
            printf("\nInforma��es do Usu�rio:\n");
            printf("%s", linha);  // Exibe o CPF
            fgets(linha, sizeof(linha), file);  // L� e exibe o Nome
            printf("%s", linha);
            fgets(linha, sizeof(linha), file);  // L� e exibe o Sobrenome
            printf("%s", linha);
            fgets(linha, sizeof(linha), file);  // L� e exibe o Cargo
            printf("%s", linha);
            break;  // Para a leitura ap�s encontrar o CPF
        }
    }

    // Verifica se o fim do arquivo foi alcan�ado e se o CPF n�o foi encontrado
    if (feof(file)) {
        printf("Usu�rio n�o encontrado!\n");
    }

    fclose(file);  // Fecha o arquivo ap�s a leitura
    system("pause");  // Pausa a tela para o usu�rio ler a mensagem
    return 0;  // Retorna 0 para indicar sucesso
}

// Fun��o para deletar um usu�rio
int deletar() {
    char cpf[40];        // Vari�vel para armazenar o CPF do usu�rio a ser deletado
    char linha[200];     // Vari�vel para armazenar as linhas lidas do arquivo
    FILE *file, *tempFile;  // Ponteiros para o arquivo original e um tempor�rio
    int encontrado = 0;  // Vari�vel para verificar se o CPF foi encontrado

    printf("Digite o CPF a ser deletado: ");
    scanf("%s", cpf);

    file = fopen("usuarios.txt", "r");  // Abre o arquivo original em modo de leitura
    if (file == NULL) {  // Verifica se o arquivo foi aberto corretamente
        printf("Erro ao abrir o arquivo!\n");
        return 1;  // Retorna 1 caso haja um erro
    }

    // Cria um arquivo tempor�rio para armazenar os dados ap�s a remo��o
    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {  // Verifica se o arquivo tempor�rio foi criado corretamente
        printf("Erro ao criar arquivo tempor�rio!\n");
        fclose(file);
        return 1;
    }

    // L� o arquivo linha por linha e reescreve todas as linhas, exceto a do CPF a ser deletado
    while (fgets(linha, sizeof(linha), file)) {
        if (strstr(linha, cpf) == NULL) {  // Se o CPF n�o est� na linha, reescreve no arquivo tempor�rio
            fprintf(tempFile, "%s", linha);
        } else {
            // Pula as pr�ximas tr�s linhas (Nome, Sobrenome, Cargo) e o separador
            fgets(linha, sizeof(linha), file);
            fgets(linha, sizeof(linha), file);
            fgets(linha, sizeof(linha), file);
            fgets(linha, sizeof(linha), file);  // Pula o separador
            encontrado = 1;  // Marca que o CPF foi encontrado
        }
    }

    fclose(file);        // Fecha o arquivo original
    fclose(tempFile);    // Fecha o arquivo tempor�rio

    // Verifica se o CPF foi encontrado e realiza as opera��es de exclus�o
    if (encontrado) {
        remove("usuarios.txt");          // Remove o arquivo original
        rename("temp.txt", "usuarios.txt");  // Renomeia o tempor�rio para o nome do original
        printf("Usu�rio deletado com sucesso!\n");
    } else {
        printf("Usu�rio n�o encontrado!\n");
        remove("temp.txt");  // Exclui o arquivo tempor�rio se o CPF n�o foi encontrado
    }

    system("pause");  // Pausa a tela para o usu�rio ler a mensagem
    return 0;  // Retorna 0 para indicar sucesso
}

int main() {
    int opcao = 0;    // Vari�vel para armazenar a escolha do usu�rio no menu
    int laco = 1;     // Vari�vel para manter o programa em execu��o no loop principal

    // Loop principal do programa
    while (laco == 1) {
        system("cls");  // Limpa a tela (no Windows)
        setlocale(LC_ALL, "Portuguese");  // Define a linguagem e localiza��o

        // Exibe o menu principal
        printf("### Cart�rio da EBAC ###\n\n");
        printf("Escolha a op��o desejada no Menu: \n\n");
        printf("\t1 - Registrar nomes\n");
        printf("\t2 - Consultar nomes\n");
        printf("\t3 - Deletar nomes\n\n"); 
    	printf("\t4 - Sair do sistema\n\n");
    	
        printf("Digite o n�mero correspondente � op��o desejada: ");

        scanf("%d", &opcao);  // L� a escolha do usu�rio
        system("cls");        // Limpa a tela para uma experi�ncia visual melhor

        // Seleciona a fun��o correspondente � escolha do usu�rio
        switch(opcao) {
        	
            case 1:
                registro();  // Chama a fun��o de registro
                break;
                
            case 2:
                consulta();  // Chama a fun��o de consulta
                break;
                
            case 3:
                deletar();   // Chama a fun��o de deletar
                break;
                
            case 4:
                printf ("\t Obrigado por utilizar o sistema de cart�rio EBAC!\n\n\n\n\n");   // Sair do programa
                return 0;
				break;
				
            default:
                printf("Essa op��o n�o est� dispon�vel!\n");
                system("pause");  // Pausa a tela para o usu�rio ler a mensagem de erro
                break;
        }
    }
}

