#include <stdio.h>   // Biblioteca padrão de entrada e saída em C
#include <stdlib.h>  // Biblioteca para funções auxiliares, como system() e exit()
#include <locale.h>  // Biblioteca para configurações de localização, como idioma e formatação
#include <string.h>  // Biblioteca para manipulação de strings

// Função para registrar um usuário em um único arquivo
int registro() {
    char cpf[40];         // Variável para armazenar o CPF do usuário
    char nome[40];        // Variável para armazenar o nome do usuário
    char sobrenome[40];   // Variável para armazenar o sobrenome do usuário
    char cargo[40];       // Variável para armazenar o cargo do usuário
    FILE *file;           // Ponteiro para o arquivo onde serão armazenados os dados

    // Coleta de dados do usuário
    printf("Digite o CPF a ser cadastrado: ");
    scanf("%s", cpf);

    printf("Digite o nome a ser cadastrado: ");
    scanf("%s", nome);

    printf("Digite o sobrenome: ");
    scanf("%s", sobrenome);

    printf("Digite o cargo: ");
    scanf("%s", cargo);

    // Abre o arquivo "usuarios.txt" no modo de adição (append), criando-o se ele não existir
    file = fopen("usuarios.txt", "a");
    if (file == NULL) {  // Verifica se o arquivo foi aberto corretamente
        printf("Erro ao abrir o arquivo!\n");
        return 1;  // Retorna 1 caso haja um erro
    }

    // Salva os dados do usuário no arquivo em um formato organizado
    fprintf(file, "CPF: %s\n", cpf);
    fprintf(file, "Nome: %s\n", nome);
    fprintf(file, "Sobrenome: %s\n", sobrenome);
    fprintf(file, "Cargo: %s\n", cargo);
    fprintf(file, "-------------------------\n\n");  // Adiciona um separador visual entre registros

    fclose(file);  // Fecha o arquivo após escrever os dados

    printf("Usuário registrado com sucesso!\n");
    system("pause");  // Pausa a tela para o usuário ler a mensagem
    return 0;  // Retorna 0, indicando que a função foi concluída com sucesso
}

// Função para consultar um usuário
int consulta() {
    setlocale(LC_ALL, "Portuguese");  // Define a linguagem e localização
    char cpf[40];     // Variável para armazenar o CPF de busca
    char linha[200];  // Variável para armazenar linhas lidas do arquivo
    FILE *file;       // Ponteiro para o arquivo de dados

    printf("Digite o CPF a ser consultado: ");
    scanf("%s", cpf);

    file = fopen("usuarios.txt", "r");  // Abre o arquivo em modo de leitura
    if (file == NULL) {  // Verifica se o arquivo foi aberto corretamente
        printf("Erro ao abrir o arquivo!\n");
        return 1;  // Retorna 1 caso haja um erro
    }

    // Lê o arquivo linha por linha e procura o CPF informado pelo usuário
    while (fgets(linha, sizeof(linha), file)) {
        // Verifica se a linha atual contém o CPF procurado
        if (strstr(linha, cpf) != NULL) {
            // Exibe os dados do usuário encontrado
            printf("\nInformações do Usuário:\n");
            printf("%s", linha);  // Exibe o CPF
            fgets(linha, sizeof(linha), file);  // Lê e exibe o Nome
            printf("%s", linha);
            fgets(linha, sizeof(linha), file);  // Lê e exibe o Sobrenome
            printf("%s", linha);
            fgets(linha, sizeof(linha), file);  // Lê e exibe o Cargo
            printf("%s", linha);
            break;  // Para a leitura após encontrar o CPF
        }
    }

    // Verifica se o fim do arquivo foi alcançado e se o CPF não foi encontrado
    if (feof(file)) {
        printf("Usuário não encontrado!\n");
    }

    fclose(file);  // Fecha o arquivo após a leitura
    system("pause");  // Pausa a tela para o usuário ler a mensagem
    return 0;  // Retorna 0 para indicar sucesso
}

// Função para deletar um usuário
int deletar() {
    char cpf[40];        // Variável para armazenar o CPF do usuário a ser deletado
    char linha[200];     // Variável para armazenar as linhas lidas do arquivo
    FILE *file, *tempFile;  // Ponteiros para o arquivo original e um temporário
    int encontrado = 0;  // Variável para verificar se o CPF foi encontrado

    printf("Digite o CPF a ser deletado: ");
    scanf("%s", cpf);

    file = fopen("usuarios.txt", "r");  // Abre o arquivo original em modo de leitura
    if (file == NULL) {  // Verifica se o arquivo foi aberto corretamente
        printf("Erro ao abrir o arquivo!\n");
        return 1;  // Retorna 1 caso haja um erro
    }

    // Cria um arquivo temporário para armazenar os dados após a remoção
    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {  // Verifica se o arquivo temporário foi criado corretamente
        printf("Erro ao criar arquivo temporário!\n");
        fclose(file);
        return 1;
    }

    // Lê o arquivo linha por linha e reescreve todas as linhas, exceto a do CPF a ser deletado
    while (fgets(linha, sizeof(linha), file)) {
        if (strstr(linha, cpf) == NULL) {  // Se o CPF não está na linha, reescreve no arquivo temporário
            fprintf(tempFile, "%s", linha);
        } else {
            // Pula as próximas três linhas (Nome, Sobrenome, Cargo) e o separador
            fgets(linha, sizeof(linha), file);
            fgets(linha, sizeof(linha), file);
            fgets(linha, sizeof(linha), file);
            fgets(linha, sizeof(linha), file);  // Pula o separador
            encontrado = 1;  // Marca que o CPF foi encontrado
        }
    }

    fclose(file);        // Fecha o arquivo original
    fclose(tempFile);    // Fecha o arquivo temporário

    // Verifica se o CPF foi encontrado e realiza as operações de exclusão
    if (encontrado) {
        remove("usuarios.txt");          // Remove o arquivo original
        rename("temp.txt", "usuarios.txt");  // Renomeia o temporário para o nome do original
        printf("Usuário deletado com sucesso!\n");
    } else {
        printf("Usuário não encontrado!\n");
        remove("temp.txt");  // Exclui o arquivo temporário se o CPF não foi encontrado
    }

    system("pause");  // Pausa a tela para o usuário ler a mensagem
    return 0;  // Retorna 0 para indicar sucesso
}

int main() {
    int opcao = 0;    // Variável para armazenar a escolha do usuário no menu
    int laco = 1;     // Variável para manter o programa em execução no loop principal

    // Loop principal do programa
    while (laco == 1) {
        system("cls");  // Limpa a tela (no Windows)
        setlocale(LC_ALL, "Portuguese");  // Define a linguagem e localização

        // Exibe o menu principal
        printf("### Cartório da EBAC ###\n\n");
        printf("Escolha a opção desejada no Menu: \n\n");
        printf("\t1 - Registrar nomes\n");
        printf("\t2 - Consultar nomes\n");
        printf("\t3 - Deletar nomes\n\n"); 
    	printf("\t4 - Sair do sistema\n\n");
    	
        printf("Digite o número correspondente à opção desejada: ");

        scanf("%d", &opcao);  // Lê a escolha do usuário
        system("cls");        // Limpa a tela para uma experiência visual melhor

        // Seleciona a função correspondente à escolha do usuário
        switch(opcao) {
        	
            case 1:
                registro();  // Chama a função de registro
                break;
                
            case 2:
                consulta();  // Chama a função de consulta
                break;
                
            case 3:
                deletar();   // Chama a função de deletar
                break;
                
            case 4:
                printf ("\t Obrigado por utilizar o sistema de cartório EBAC!\n\n\n\n\n");   // Sair do programa
                return 0;
				break;
				
            default:
                printf("Essa opção não está disponível!\n");
                system("pause");  // Pausa a tela para o usuário ler a mensagem de erro
                break;
        }
    }
}

