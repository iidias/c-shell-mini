# 🐚 Mini Shell em C (sh-lite)

Um interpretador de comandos minimalista desenvolvido em C puro para explorar chamadas de sistema Unix.

## 🧠 O que este projeto demonstra?
* **Gerenciamento de Processos:** Uso de `fork()` para criar processos filhos e `wait()` para sincronização.
* **Execução de Programas:** Uso da família `exec()` para substituir a imagem do processo.
* **Parsing de Strings:** Manipulação de ponteiros e tokenização (`strtok`) para quebrar comandos e argumentos.
* **Sistemas Operacionais:** Entendimento prático de como o kernel gerencia chamadas do usuário.

## 🚀 Funcionalidades
* Executa comandos básicos do sistema (`ls`, `ps`, `pwd`, `date`, etc.).
* Suporta múltiplos argumentos (ex: `ls -l -a`).
* Implementação nativa do comando `cd` (Built-in), já que `exec` não altera o diretório do processo pai.
* Comando `exit` para encerrar o shell.

## 🛠️ Como Compilar e Rodar

1. Compile o código:
   ```bash
   gcc main.c -o shell```
2. Execute:
    ```bash
   ./shell```
