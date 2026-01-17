# 🐚 Mini Shell em C (Cross-Platform)

Um interpretador de comandos minimalista desenvolvido em C puro. Este projeto explora os fundamentos de Sistemas Operacionais, demonstrando na prática como um shell gerencia memória, interpreta strings e interage com o Kernel para criar e gerenciar processos, **adaptando-se automaticamente para Windows ou Linux**.

## 🧠 O que este projeto demonstra?
* **Portabilidade de Código (Cross-Platform):** Uso de diretivas de pré-processador (`#ifdef _WIN32`) para compilar o código corretamente em diferentes sistemas operacionais sem alterações manuais.
* **Gerenciamento de Processos:**
    * **Windows:** Uso da syscall `_spawnvp()` e `process.h`.
    * **Linux/Unix:** Uso do modelo clássico `fork()` / `exec()` (abstraído na arquitetura).
* **Parsing de Strings:** Manipulação de ponteiros e tokenização (`strtok`) para quebrar a linha de comando.
* **Fallback de Execução:** Lógica robusta que tenta executar binários nativos e, em caso de falha, recorre ao interpretador do sistema (`cmd.exe` ou `bash`).

## ⚙️ Arquitetura de Execução

O shell implementa uma estratégia híbrida para garantir compatibilidade:

1.  **Internal Commands (Built-ins):** Comandos como `cd`, `cls/clear` e `exit` são executados diretamente na memória do processo pai para alterar o estado do shell.
2.  **External Binaries:**
    * No **Windows**, carrega executáveis (`.exe`) em novos processos isolados.
    * No **Linux**, executa binários padrão do sistema (como `ls`, `grep`).
3.  **System Fallback:** Caso o binário não seja encontrado, o shell utiliza `system()` para delegar o comando ao terminal nativo, permitindo rodar scripts (`.bat`, `.sh`) e comandos de ambiente.

## 🚀 Funcionalidades

* **Interface Interativa:** Prompt de comando customizado (`win-shell> ` ou `linux-shell> `) e sistema de ajuda.
* **Adaptação de Comandos:**
    * Limpar tela: Reconhece tanto `cls` (Windows) quanto `clear` (Linux).
    * Mudar diretório: Usa `_chdir` no Windows e `chdir` no Linux.
* **Comandos Nativos:**
    * `cd [dir]`: Navegação entre diretórios.
    * `help`: Lista de comandos disponíveis.
    * `exit`: Encerramento seguro da aplicação.

## 🛠️ Como Compilar e Rodar

### Windows (MinGW)
1. Abra o terminal na pasta do projeto.
2. Compile:
   ```bash
   gcc main.c -o shell.exe```
3. Execute:
    ```bash
   ./shell```

### Linux (GCC)
1. Abra o terminal na pasta do projeto.
2. Compile:
   ```bash
   gcc main.c -o shell```
3. Execute:
    ```bash
   ./shell```

## 🎮 Exemplo de Uso
 ```Plaintext
   > help
   (Mostra a lista de comandos adaptada)
   
   > cls
   (Limpa a tela - funciona com 'clear' também)
   
   > notepad (Windows) / gedit (Linux)
   (Abre o editor de texto e aguarda o fechamento)
   
   > cd ..
   (Volta um diretório)
```

Desenvolvido para fins educacionais em Sistemas Operacionais.
