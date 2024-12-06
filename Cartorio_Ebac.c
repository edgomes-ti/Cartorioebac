#include <stdio.h>   // Biblioteca padrão para entrada e saída (ex.: printf, scanf, fopen)
#include <stdlib.h>  // Biblioteca para funções auxiliares (ex.: system(), exit())
#include <locale.h>  // Biblioteca para configurações regionais (ex.: idioma e formatação)
#include <string.h>  // Biblioteca para manipulação de strings (ex.: strcmp, strstr)

// Função para registrar um usuário em um único arquivo
int registro() {
    setlocale(LC_ALL, "Portuguese");  // Define o idioma e a formatação regional (suporte a acentuação)

    // Declaração de variáveis para armazenar os dados do usuário
    char cpf[40];    // CPF do usuário
    char nome[100];  // Nome completo do usuário
    char cargo[100]; // Cargo do usuário
    FILE *file;      // Ponteiro para o arquivo onde os dados serão armazenados

    // Solicita o CPF do usuário
    printf("Digite o CPF a ser cadastrado: ");
    scanf("%s", cpf);  // Lê o CPF digitado (sem espaços)

    getchar();  // Limpa o caractere de nova linha deixado pelo scanf()

    // Solicita o nome completo do usuário
    printf("Digite o nome completo a ser cadastrado: ");
    fgets(nome, sizeof(nome), stdin);  // Lê o nome completo, incluindo espaços
    nome[strcspn(nome, "\n")] = '\0';  // Remove o caractere de nova linha do final da string

    // Solicita o cargo do usuário
    printf("Digite o cargo do usuário: ");
    fgets(cargo, sizeof(cargo), stdin);  // Lê o cargo completo, incluindo espaços
    cargo[strcspn(cargo, "\n")] = '\0';  // Remove o caractere de nova linha do final da string

    // Abre o arquivo "usuarios.txt" no modo de adição (append)
    file = fopen("usuarios.txt", "a");
    if (file == NULL) {  // Verifica se o arquivo foi aberto com sucesso
        printf("Erro ao abrir o arquivo!\n");
        return 1;  // Retorna 1 em caso de erro
    }

    // Escreve os dados do usuário no arquivo
    fprintf(file, "CPF: %s\n", cpf);    // Grava o CPF no arquivo
    fprintf(file, "Nome: %s\n", nome);  // Grava o nome no arquivo
    fprintf(file, "Cargo: %s\n", cargo); // Grava o cargo no arquivo
    fprintf(file, "-------------------------\n\n");  // Adiciona uma linha separadora

    fclose(file);  // Fecha o arquivo após gravar os dados

    printf("Usuário registrado com sucesso!\n");  // Confirmação de sucesso
    system("pause");  // Pausa a tela para o usuário visualizar a mensagem
    return 0;  // Retorna 0 indicando sucesso
}

// Função para consultar um usuário no arquivo
int consulta() {
    setlocale(LC_ALL, "Portuguese");  // Define o idioma e a formatação regional

    char cpf[40];     // CPF do usuário a ser consultado
    char linha[200];  // Buffer para armazenar cada linha lida do arquivo
    FILE *file;       // Ponteiro para o arquivo de dados

    // Solicita o CPF a ser consultado
    printf("Digite o CPF a ser consultado: ");
    scanf("%s", cpf);  // Lê o CPF digitado

    // Abre o arquivo "usuarios.txt" no modo de leitura
    file = fopen("usuarios.txt", "r");
    if (file == NULL) {  // Verifica se o arquivo foi aberto com sucesso
        printf("Erro ao abrir o arquivo!\n");
        return 1;  // Retorna 1 em caso de erro
    }

    // Lê o arquivo linha por linha e verifica se o CPF está presente
    while (fgets(linha, sizeof(linha), file)) {
        if (strstr(linha, cpf) != NULL) {  // Verifica se a linha contém o CPF
            printf("\nInformações do Usuário:\n");
            printf("%s", linha);           // Exibe o CPF
            fgets(linha, sizeof(linha), file);
            printf("%s", linha);           // Exibe o Nome
            fgets(linha, sizeof(linha), file);
            printf("%s", linha);           // Exibe o Cargo
            break;  // Interrompe a leitura após encontrar o CPF
        }
    }

    if (feof(file)) {  // Se chegou ao final do arquivo sem encontrar o CPF
        printf("Usuário não encontrado!\n");
    }

    fclose(file);  // Fecha o arquivo após a leitura
    system("pause");  // Pausa a tela para o usuário visualizar a mensagem
    return 0;  // Retorna 0 indicando sucesso
}

// Função para deletar um usuário do arquivo
int deletar() {
    setlocale(LC_ALL, "Portuguese");  // Define o idioma e a formatação regional

    char cpf[40];     // CPF do usuário a ser deletado
    char linha[200];  // Buffer para armazenar cada linha lida do arquivo
    FILE *file, *tempFile;  // Ponteiros para o arquivo original e o temporário
    int encontrado = 0;  // Indica se o CPF foi encontrado

    // Solicita o CPF a ser deletado
    printf("Digite o CPF a ser deletado: ");
    scanf("%s", cpf);  // Lê o CPF digitado

    // Abre o arquivo original no modo de leitura
    file = fopen("usuarios.txt", "r");
    if (file == NULL) {  // Verifica se o arquivo foi aberto com sucesso
        printf("Erro ao abrir o arquivo!\n");
        return 1;  // Retorna 1 em caso de erro
    }

    // Abre um arquivo temporário no modo de escrita
    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {  // Verifica se o arquivo temporário foi criado com sucesso
        printf("Erro ao criar arquivo temporário!\n");
        fclose(file);
        return 1;  // Retorna 1 em caso de erro
    }

    // Lê o arquivo original linha por linha e copia para o temporário, exceto o CPF a ser deletado
    while (fgets(linha, sizeof(linha), file)) {
        if (strstr(linha, cpf) == NULL) {  // Se a linha não contém o CPF
            fprintf(tempFile, "%s", linha);  // Copia a linha para o temporário
        } else {  // CPF encontrado
            fgets(linha, sizeof(linha), file);  // Ignora o Nome
            fgets(linha, sizeof(linha), file);  // Ignora o Cargo
            fgets(linha, sizeof(linha), file);  // Ignora a linha separadora
            encontrado = 1;  // Marca que o CPF foi encontrado
        }
    }

    fclose(file);  // Fecha o arquivo original
    fclose(tempFile);  // Fecha o arquivo temporário

    // Substitui o arquivo original pelo temporário
    if (encontrado) {
        remove("usuarios.txt");          // Exclui o arquivo original
        rename("temp.txt", "usuarios.txt");  // Renomeia o arquivo temporário
        printf("Usuário deletado com sucesso!\n");
    } else {
        printf("Usuário não encontrado!\n");
        remove("temp.txt");  // Exclui o temporário se o CPF não foi encontrado
    }

    system("pause");  // Pausa a tela para o usuário visualizar a mensagem
    return 0;  // Retorna 0 indicando sucesso
}

// Função principal
int main() {
    setlocale(LC_ALL, "Portuguese");  // Define o idioma e a formatação regional
    system("chcp 1252 > nul");       // Configura o terminal para Windows-1252

    int opcao = 0;  // Armazena a escolha do menu
    char senhadigitada[40];  // Armazena a senha digitada
    int comparacao;  // Armazena o resultado da comparação da senha

    // Solicita a senha do administrador
    printf("### Cartório da EBAC ###\n\n");
    printf("Login de administrador\n\nDigite sua senha: ");
    scanf("%s", senhadigitada);

    comparacao = strcmp(senhadigitada, "admin");  // Compara a senha digitada com "admin"

    if (comparacao == 0) {  // Se a senha estiver correta
        while (1) {  // Loop infinito para o menu principal
            system("cls");  // Limpa a tela
            printf("\n\n### Cartório da EBAC ###\n\n\n");
            printf("\t1 - Registrar nomes\n");
            printf("\t2 - Consultar nomes\n");
            printf("\t3 - Deletar nomes\n\n");
            printf("\t4 - Sair do sistema\n\n\n");
            printf("Digite a opção desejada: ");
            scanf("%d", &opcao);

            system("cls");  // Limpa a tela

            // Executa a ação correspondente à opção escolhida
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
                    printf("Opção inválida! Tente novamente.\n");
                    system("pause");
            }
        }
    } else {
        printf("Senha incorreta! Tente novamente.\n");
    }

    return 0;  // Retorna 0 indicando sucesso
}

