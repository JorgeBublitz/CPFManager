### Funcionalidades

- **Create (Criar)**: Inserir um novo registro de dados pessoais com CPF único.
- **Read (Ler)**: Buscar um registro específico pelo CPF.
- **Update (Atualizar)**: Atualizar informações de um registro existente.
- **Delete (Deletar)**: Remover um registro com base no CPF.
- **Listagem**: Exibir todos os registros em ordem crescente de CPF.
- **Exportação**: Exportar registros para um arquivo de texto.

### Estrutura de Dados

O sistema utiliza uma Árvore AVL, onde cada nó contém um registro com os seguintes dados:
- **CPF** (chave única)
- **Nome completo**
- **Data de nascimento**
- **Endereço**
- **Número de telefone**

A árvore é balanceada automaticamente para garantir que as operações de busca, inserção, remoção e atualização ocorram em tempo O(log n).

### Requisitos Técnicos

- **Tipo de dados para CPF**: `unsigned long long` para garantir a precisão e a eficiência nas comparações.
- **Validação de CPF**: O sistema valida o CPF antes de permitir inserção ou atualização, garantindo unicidade e formato correto.
- **Interface de linha de comando (CLI)**: O sistema oferece uma interface simples para interação com o usuário.
