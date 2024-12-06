#include <stdio.h>   // Biblioteca padr�o para entrada e sa�da (ex.: printf, scanf, fopen)
#include <stdlib.h>  // Biblioteca para fun��es auxiliares (ex.: system(), exit())
#include <locale.h>  // Biblioteca para configura��es regionais (ex.: idioma e formata��o)
#include <string.h>  // Biblioteca para manipula��o de strings (ex.: strcmp, strstr)

// Fun��o para registrar um usu�rio em um �nico arquivo
int registro() {
    setlocale(LC_ALL, "Portuguese");  // Define o idioma e a formata��o regional (suporte a acentua��o)

    // Declara��o de vari�veis para armazenar os dados do usu�rio
    char cpf[40];    // CPF do usu�rio
    char nome[100];  // Nome completo do usu�rio
    char cargo[100]; // Cargo do usu�rio
    FILE *file;      // Ponteiro para o arquivo onde os dados ser�o armazenados

    // Solicita o CPF do usu�rio
    printf("Digite o CPF a ser cadastrado: ");
    scanf("%s", cpf);  // L� o CPF digitado (sem espa�os)

    getchar();  // Limpa o caractere de nova linha deixado pelo scanf()

    // Solicita o nome completo do usu�rio
    printf("Digite o nome completo a ser cadastrado: ");
    fgets(nome, sizeof(nome), stdin);  // L� o nome completo, incluindo espa�os
    nome[strcspn(nome, "\n")] = '\0';  // Remove o caractere de nova linha do final da string

    // Solicita o cargo do usu�rio
    printf("Digite o cargo do usu�rio: ");
    fgets(cargo, sizeof(cargo), stdin);  // L� o cargo completo, incluindo espa�os
    cargo[strcspn(cargo, "\n")] = '\0';  // Remove o caractere de nova linha do final da string

    // Abre o arquivo "usuarios.txt" no modo de adi��o (append)
    file = fopen("usuarios.txt", "a");
    if (file == NULL) {  // Verifica se o arquivo foi aberto com sucesso
        printf("Erro ao abrir o arquivo!\n");
        return 1;  // Retorna 1 em caso de erro
    }

    // Escreve os dados do usu�rio no arquivo
    fprintf(file, "CPF: %s\n", cpf);    // Grava o CPF no arquivo
    fprintf(file, "Nome: %s\n", nome);  // Grava o nome no arquivo
    fprintf(file, "Cargo: %s\n", cargo); // Grava o cargo no arquivo
    fprintf(file, "-------------------------\n\n");  // Adiciona uma linha separadora

    fclose(file);  // Fecha o arquivo ap�s gravar os dados

    printf("Usu�rio registrado com sucesso!\n");  // Confirma��o de sucesso
    system("pause");  // Pausa a tela para o usu�rio visualizar a mensagem
    return 0;  // Retorna 0 indicando sucesso
}

// Fun��o para consultar um usu�rio no arquivo
int consulta() {
    setlocale(LC_ALL, "Portuguese");  // Define o idioma e a formata��o regional

    char cpf[40];     // CPF do usu�rio a ser consultado
    char linha[200];  // Buffer para armazenar cada linha lida do arquivo
    FILE *file;       // Ponteiro para o arquivo de dados

    // Solicita o CPF a ser consultado
    printf("Digite o CPF a ser consultado: ");
    scanf("%s", cpf);  // L� o CPF digitado

    // Abre o arquivo "usuarios.txt" no modo de leitura
    file = fopen("usuarios.txt", "r");
    if (file == NULL) {  // Verifica se o arquivo foi aberto com sucesso
        printf("Erro ao abrir o arquivo!\n");
        return 1;  // Retorna 1 em caso de erro
    }

    // L� o arquivo linha por linha e verifica se o CPF est� presente
    while (fgets(linha, sizeof(linha), file)) {
        if (strstr(linha, cpf) != NULL) {  // Verifica se a linha cont�m o CPF
            printf("\nInforma��es do Usu�rio:\n");
            printf("%s", linha);           // Exibe o CPF
            fgets(linha, sizeof(linha), file);
            printf("%s", linha);           // Exibe o Nome
            fgets(linha, sizeof(linha), file);
            printf("%s", linha);           // Exibe o Cargo
            break;  // Interrompe a leitura ap�s encontrar o CPF
        }
    }

    if (feof(file)) {  // Se chegou ao final do arquivo sem encontrar o CPF
        printf("Usu�rio n�o encontrado!\n");
    }

    fclose(file);  // Fecha o arquivo ap�s a leitura
    system("pause");  // Pausa a tela para o usu�rio visualizar a mensagem
    return 0;  // Retorna 0 indicando sucesso
}

// Fun��o para deletar um usu�rio do arquivo
int deletar() {
    setlocale(LC_ALL, "Portuguese");  // Define o idioma e a formata��o regional

    char cpf[40];     // CPF do usu�rio a ser deletado
    char linha[200];  // Buffer para armazenar cada linha lida do arquivo
    FILE *file, *tempFile;  // Ponteiros para o arquivo original e o tempor�rio
    int encontrado = 0;  // Indica se o CPF foi encontrado

    // Solicita o CPF a ser deletado
    printf("Digite o CPF a ser deletado: ");
    scanf("%s", cpf);  // L� o CPF digitado

    // Abre o arquivo original no modo de leitura
    file = fopen("usuarios.txt", "r");
    if (file == NULL) {  // Verifica se o arquivo foi aberto com sucesso
        printf("Erro ao abrir o arquivo!\n");
        return 1;  // Retorna 1 em caso de erro
    }

    // Abre um arquivo tempor�rio no modo de escrita
    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {  // Verifica se o arquivo tempor�rio foi criado com sucesso
        printf("Erro ao criar arquivo tempor�rio!\n");
        fclose(file);
        return 1;  // Retorna 1 em caso de erro
    }

    // L� o arquivo original linha por linha e copia para o tempor�rio, exceto o CPF a ser deletado
    while (fgets(linha, sizeof(linha), file)) {
        if (strstr(linha, cpf) == NULL) {  // Se a linha n�o cont�m o CPF
            fprintf(tempFile, "%s", linha);  // Copia a linha para o tempor�rio
        } else {  // CPF encontrado
            fgets(linha, sizeof(linha), file);  // Ignora o Nome
            fgets(linha, sizeof(linha), file);  // Ignora o Cargo
            fgets(linha, sizeof(linha), file);  // Ignora a linha separadora
            encontrado = 1;  // Marca que o CPF foi encontrado
        }
    }

    fclose(file);  // Fecha o arquivo original
    fclose(tempFile);  // Fecha o arquivo tempor�rio

    // Substitui o arquivo original pelo tempor�rio
    if (encontrado) {
        remove("usuarios.txt");          // Exclui o arquivo original
        rename("temp.txt", "usuarios.txt");  // Renomeia o arquivo tempor�rio
        printf("Usu�rio deletado com sucesso!\n");
    } else {
        printf("Usu�rio n�o encontrado!\n");
        remove("temp.txt");  // Exclui o tempor�rio se o CPF n�o foi encontrado
    }

    system("pause");  // Pausa a tela para o usu�rio visualizar a mensagem
    return 0;  // Retorna 0 indicando sucesso
}

// Fun��o principal
int main() {
    setlocale(LC_ALL, "Portuguese");  // Define o idioma e a formata��o regional
    system("chcp 1252 > nul");       // Configura o terminal para Windows-1252

    int opcao = 0;  // Armazena a escolha do menu
    char senhadigitada[40];  // Armazena a senha digitada
    int comparacao;  // Armazena o resultado da compara��o da senha

    // Solicita a senha do administrador
    printf("### Cart�rio da EBAC ###\n\n");
    printf("Login de administrador\n\nDigite sua senha: ");
    scanf("%s", senhadigitada);

    comparacao = strcmp(senhadigitada, "admin");  // Compara a senha digitada com "admin"

    if (comparacao == 0) {  // Se a senha estiver correta
        while (1) {  // Loop infinito para o menu principal
            system("cls");  // Limpa a tela
            printf("\n\n### Cart�rio da EBAC ###\n\n\n");
            printf("\t1 - Registrar nomes\n");
            printf("\t2 - Consultar nomes\n");
            printf("\t3 - Deletar nomes\n\n");
            printf("\t4 - Sair do sistema\n\n\n");
            printf("Digite a op��o desejada: ");
            scanf("%d", &opcao);

            system("cls");  // Limpa a tela

            // Executa a a��o correspondente � op��o escolhida
            switch (opcao) {
                case 1:
                    registro();
                    break;
                case 2:
                    consulta();
                    break;
                case 3:
                    deletar();
                    break;
                case 4:
                    printf("Obrigado por utilizar o sistema!\n");
                    return 0;  // Encerra o programa
                default:
                    printf("Op��o inv�lida! Tente novamente.\n");
                    system("pause");
            }
        }
    } else {
        printf("Senha incorreta! Tente novamente.\n");
    }

    return 0;  // Retorna 0 indicando sucesso
}

