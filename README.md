# Cartório da EBAC

Este é um projeto de sistema de cadastro simples desenvolvido em C que permite o registro, consulta e exclusão de usuários em um arquivo. O programa simula um sistema de cartório, armazenando dados como CPF, nome, sobrenome e cargo em um arquivo de texto (`usuarios.txt`).

## Funcionalidades

O sistema possui três funcionalidades principais:

1. **Registro de Usuário**: Permite registrar um novo usuário, solicitando CPF, nome, sobrenome e cargo, e armazena essas informações no arquivo `usuarios.txt`.
2. **Consulta de Usuário**: Permite consultar um usuário pelo CPF, exibindo as informações cadastradas do usuário correspondente.
3. **Exclusão de Usuário**: Permite deletar um usuário registrado, removendo todos os dados relacionados a esse usuário do arquivo `usuarios.txt`.

## Pré-requisitos

- Para compilar e rodar este programa, você precisa de um compilador C. Algumas opções recomendadas:
  - GCC (GNU Compiler Collection)
  - MinGW (para usuários Windows)

## Como Usar

1. **Clonar o repositório**

   ```
   bashCopiar códigogit clone https://github.com/edgomes-ti/cartorio-ebac.git
   cd cartorio-ebac
   ```

2. **Compilar o código** No terminal, execute o seguinte comando:

   ```
   bash
   
   
   Copiar código
   gcc main.c -o cartorio
   ```

3. **Executar o programa** Após compilar, rode o executável:

   ```
   bash
   
   
   Copiar código
   ./cartorio
   ```

4. **Navegar pelo menu**

   - Escolha a opção desejada no menu principal:
     - `1` para registrar um usuário
     - `2` para consultar um usuário
     - `3` para deletar um usuário

## Arquivo de Dados

- O sistema utiliza o arquivo `usuarios.txt` para armazenar as informações dos usuários. O arquivo será criado automaticamente no diretório do projeto na primeira execução do programa.

## Estrutura do Projeto

- `main.c`: Código fonte principal que contém as funções de registro, consulta e deletar.
- `usuarios.txt`: Arquivo de dados onde os registros são armazenados.

## Observações

Este projeto é ideal para iniciantes que desejam entender o básico de manipulação de arquivos em C e como construir um menu interativo em um programa de linha de comando.

## Contribuição

Contribuições são bem-vindas! Se você quiser melhorar este projeto, fique à vontade para abrir uma *issue* ou enviar um *pull request*.
