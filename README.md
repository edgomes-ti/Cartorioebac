# Cartório da EBAC

Este é um projeto de sistema de cadastro simples desenvolvido em C, que permite o registro, consulta e exclusão de usuários em um arquivo. O programa simula um sistema de cartório, armazenando dados como CPF, nome completo e cargo em um arquivo de texto (`usuarios.txt`).

## Funcionalidades

O sistema possui as seguintes funcionalidades:

1. **Registro de Usuário**:
   - Permite registrar um novo usuário, solicitando CPF, nome completo e cargo.
   - Os dados são armazenados no arquivo `usuarios.txt`.

2. **Consulta de Usuário**:
   - Permite consultar um usuário pelo CPF, exibindo as informações cadastradas do usuário correspondente.

3. **Exclusão de Usuário**:
   - Permite deletar um usuário registrado, removendo todos os dados relacionados a ele do arquivo `usuarios.txt`.

4. **Suporte a caracteres brasileiros**:
   - O programa agora suporta acentos e cedilhas, garantindo a correta exibição de caracteres como "ç", "á", "ê", etc.

## Melhorias Recentes

- **Nome completo**: A coleta de dados foi simplificada, substituindo os campos "Nome" e "Sobrenome" por "Nome completo", permitindo a entrada de nomes com espaços.
- **Compatibilidade com caracteres especiais**: Configurado para suportar caracteres brasileiros no terminal e no arquivo de dados.
- **Leitura aprimorada**: Uso de métodos que permitem entradas mais flexíveis, incluindo nomes e cargos com espaços.

## Pré-requisitos

Para rodar corretamente, o projeto foi desenvolvido e otimizado para uso no **Dev-C++**. É recomendado que você utilize este ambiente para evitar problemas de compatibilidade e garantir o desempenho esperado.

### Ferramentas necessárias:
- Dev-C++ (ambiente de desenvolvimento para linguagem C).

### Opcional:
- GCC (GNU Compiler Collection) ou MinGW (para outros sistemas, mas não recomendado neste projeto).

## Como Usar

1. **Clonar o repositório**
   ```bash
   git clone https://github.com/edgomes-ti/cartorio-ebac.git
   cd cartorio-ebac

2. **Abrir o projeto no Dev-C++**

   - Abra o arquivo `main.c` no Dev-C++.

3. **Compilar o código**

   - No Dev-C++, clique em `Executar -> Compilar e Executar (ou pressione F11)`.

4. **Executar o programa**

   - O programa será executado no terminal do Dev-C++.

5. **Navegar pelo menu**

   - Escolha a opção desejada no menu principal:
     - `1` para registrar um usuário.
     - `2` para consultar um usuário.
     - `3` para deletar um usuário.
     - `4` para sair do programa.

## Arquivo de Dados

- O sistema utiliza o arquivo `usuarios.txt` para armazenar as informações dos usuários.
- O arquivo será criado automaticamente no diretório do projeto na primeira execução do programa.
- Estrutura de cada registro: 
   
   CPF: 12345678900 
   Nome: João da Silva 
   Cargo: Engenheiro de Software
-------------------------

## Estrutura do Projeto

- `main.c`: Código-fonte principal que contém as funções de registro, consulta e exclusão.
- `usuarios.txt`: Arquivo de dados onde os registros são armazenados.

## Observações

- Este projeto é ideal para iniciantes que desejam entender o básico de manipulação de arquivos em C e como construir um menu interativo em um programa de linha de comando.

## Contribuição

Contribuições são bem-vindas! Se você quiser melhorar este projeto, fique à vontade para abrir uma _issue_ ou enviar um _pull request_.
