# RELATÓRIO DE TESTES DO SISTEMA DE REGISTRO DE USUÁRIOS (Cartorio_Ebac)

## 1. INFORMAÇÕES GERAIS

**Nome do Sistema**: Cartório da EBAC

**Data do Teste**: 05/12/2024

**Responsável pelo Teste**: Ednilson Gonçalves Gomes (Estudante da Ebac e Graduando em Engenharia de Software)

**Versão do Sistema Testado**: 1.0

---

## 2. CENÁRIOS DE TESTE E RESULTADOS

---

## 3. CONCLUSÃO

Todos os cenários de teste foram executados com sucesso, e o sistema se comportou conforme o esperado. O sistema está aprovado para as funcionalidades testadas.

## Cenários de Teste e Resultados

| ID  | CENÁRIO TESTADO                     | PASSOS REALIZADOS                                               | RESULTADO ESPERADO                                        | RESULTADO OBTIDO                                         | STATUS    |
| ----| ----------------------------------- | -------------------------------------------------------------- | -------------------------------------------------------- | ------------------------------------------------------- | --------- |
| 1   | Login com senha correta            | Inserir a senha: ‘admin’ na tela de login.                     | Acesso concedido e exibição do menu principal.           | Acesso concedido e menu exibido corretamente.           | Aprovado  |
| 2   | Login com senha incorreta          | Inserir uma senha inválida (ex.: 1234) na tela de login.       | Exibir mensagem "Senha incorreta. Tente novamente."      | Mensagem exibida corretamente e programa encerrado.     | Aprovado  |
| 3   | Registro de usuário (nome com espaços) | Inserir CPF 12345678900, Nome completo João Silva Santos, Cargo Gerente. | Dados registrados no arquivo usuarios.txt em formato legível. | Dados registrados corretamente, incluindo espaços e caracteres especiais. | Aprovado  |
| 4   | Registro de usuário com caracteres brasileiros | Inserir CPF 98765432100, Nome completo José Gonçalves de Sá, Cargo Engenheiro. | Dados registrados corretamente no arquivo com suporte a acentuação (ex.: ç, ã, é). | Dados exibidos e registrados corretamente com acentuação. | Aprovado  |
| 5   | Consulta de usuário existente       | Consultar o CPF 12345678900.                                   | Exibir dados completos do usuário registrado.            | Dados exibidos corretamente, com nome completo e cargo. | Aprovado  |
| 6   | Consulta de usuário inexistente     | Consultar um CPF não registrado (ex.: 11111111111).            | Exibir mensagem "Usuário não encontrado!".               | Mensagem exibida corretamente.                          | Aprovado  |
| 7   | Exclusão de usuário existente       | Excluir o CPF 12345678900.                                     | Usuário removido do arquivo e exibição de mensagem.      | Usuário removido corretamente e mensagem exibida.       | Aprovado  |
| 8   | Exclusão de usuário inexistente     | Tentar excluir um CPF não registrado (ex.: 22222222222).       | Exibir mensagem "Usuário não encontrado!".               | Mensagem exibida corretamente.                          | Aprovado  |
| 9   | Encerramento do programa            | Selecionar a opção 4 - Sair do sistema no menu principal.      | Exibir uma mensagem de agradecimento e encerrar o programa. | Mensagem exibida corretamente e programa encerrado.     | Aprovado  |


## 4. SUGESTÕES PARA MELHORIA (QA)

- **Validação dos dados**: Verificar se o CPF tem 11 números e se o nome/cargo contém apenas letras e espaços.
- **Mensagens de erro claras**: Informar o motivo exato do erro, como "Arquivo não encontrado, registre um usuário primeiro".
- **Interface de texto melhorada**: Usar separadores e destaques no menu e nos resultados para facilitar a leitura.
- **Evitar CPFs duplicados**: Verificar antes do registro se o CPF já existe no sistema e impedir duplicatas.
- **Listar todos os usuários**: Criar uma opção no menu para exibir todos os usuários cadastrados.
- **Sistema de login com múltiplos operadores**: Permitir que cada operador tenha login e senha únicos para acessar o sistema.
- **Uso de banco de dados SQL**: Substituir o arquivo de texto por um banco de dados SQL simples, como SQLite, para facilitar a organização, consulta e integridade dos dados.
