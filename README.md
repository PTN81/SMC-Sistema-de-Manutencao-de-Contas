# SMC - Sistema de-Manutenção de Contas

Este é um sistema de gerenciamento de contas bancárias em miniatura desenvolvido em **Linguagem C**. O projeto foi criado com o objetivo de estudar e aplicar conceitos avançados de manipulação de arquivos, estruturas de dados (`struct`) e persistência de dados em arquivos binários (`.dat`).

O grande diferencial deste sistema é a eficiência: ele utiliza **acesso aleatório**, o que permite ler, gravar ou atualizar qualquer registro diretamente no disco sem a necessidade de carregar o arquivo inteiro na memória RAM ou varrer o arquivo sequencialmente desde o início.

## 🚀 Funcionalidades

O programa conta com um menu interativo que permite realizar as seguintes operações:
1. **Cadastrar Cliente:** Salva um novo cliente em uma posição (índice físico) específica determinada pelo usuário.
2. **Consultar por Conta:** Busca sequencial no arquivo para exibir os dados de um cliente específico.
3. **Atualizar Saldo:** Altera apenas o campo de saldo de um registro, sem afetar o restante do arquivo.
4. **Encerrar Conta:** Aplica o conceito de **exclusão lógica** (*soft delete*), marcando o registro como inativo (ID `0`) para que o espaço possa ser reaproveitado futuramente.
5. **Listar Clientes:** Exibe na tela todas as contas que estão atualmente ativas no sistema.
6. **Demonstração de `rewind()`:** Restaura o ponteiro de leitura do arquivo para o início de forma explícita.

## 🛠️ Conceitos Técnicos Aplicados

* **Persistência Binária:** Uso dos modos `rb` e `r+b` com as funções `fread()` e `fwrite()`.
* **Acesso Aleatório (`fseek` e `SEEK_SET`):** Movimentação precisa do ponteiro do arquivo calculando o deslocamento em bytes (`posição * sizeof(Cliente)`).
* **Rastreamento de Posição (`ftell`):** Utilizado para memorizar o local exato de um registro antes de sobrescrevê-lo em operações de atualização.
* **Tratamento de Buffer:** Uso de máscaras como `%*c` e `strcspn()` para limpar o buffer do teclado e tratar strings vindas do `fgets()`.


   
