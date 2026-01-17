#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <process.h>
    #include <windows.h>
    #include <direct.h>
    #define limpar_tela() system("cls")
#else
    #include <unistd.h>
    #include <sys/wait.h>
    #define limpar_tela() system("clear")
#endif

#define TAM_MAX_CMD 1024
#define TAM_MAX_ARGS 64
#define DELIMITADORES " \t\r\n\a"

void exibir_ajuda() {
    printf("\n");
    printf("==================================================\n");
    printf("            MINI SHELL C (Win-Shell)              \n");
    printf("==================================================\n");
    printf("COMMANDOS INTERNOS (Built-in):\n");
    printf("  > cd [dir]   : Muda o diretorio atual\n");
    printf("  > cls        : Limpa a tela do terminal\n");
    printf("  > help       : Mostra esta lista de comandos\n");
    printf("  > exit       : Encerra o shell\n");
    printf("\n");
    printf("COMMANDOS EXTERNOS & LOTES:\n");
    printf("  > Execute programas do sistema (ex: notepad, calc)\n");
    printf("  > Execute comandos DOS (ex: dir, ipconfig, echo)\n");
    printf("==================================================\n\n");
}

char *ler_linha(void) {
    char *linha = malloc(TAM_MAX_CMD * sizeof(char));
    if (!linha) {
        fprintf(stderr, "Erro de alocacao\n");
        exit(EXIT_FAILURE);
    }

    int c;
    int posicao = 0;
    while (1) {
        c = getchar();
        if (c == EOF || c == '\n') {
            linha[posicao] = '\0';
            return linha;
        } else {
            linha[posicao] = c;
        }
        posicao++;
    }
}

char **parse_argumentos(char *linha) {
    int pos = 0;
    char **tokens = malloc(TAM_MAX_ARGS * sizeof(char*));
    char *token;

    if (!tokens) {
        fprintf(stderr, "Erro de alocacao\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(linha, DELIMITADORES);
    while (token != NULL) {
        tokens[pos] = token;
        pos++;
        if (pos >= TAM_MAX_ARGS) break;
        token = strtok(NULL, DELIMITADORES);
    }
    tokens[pos] = NULL;
    return tokens;
}

int executar_comando(char **args) {
    if (args[0] == NULL) {
        return 1;
    }

    if (strcmp(args[0], "help") == 0) {
        exibir_ajuda();
        return 1;
    }

    if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "Erro: argumento esperado para \"cd\"\n");
        } else {
            if (_chdir(args[1]) != 0) {
                perror("win-shell");
            }
        }
        return 1;
    }

    if (strcmp(args[0], "exit") == 0) {
        return 0;
    }

    if (strcmp(args[0], "cls") == 0 || strcmp(args[0], "clear") == 0) {
        limpar_tela();
        return 1;
    }

    int status = _spawnvp(_P_WAIT, args[0], (const char * const *)args);

    if (status != -1) {
        return 1;
    }

    char comando_completo[TAM_MAX_CMD] = "";
    int i = 0;
    while(args[i] != NULL) {
        strcat(comando_completo, args[i]);
        strcat(comando_completo, " ");
        i++;
    }

    int ret = system(comando_completo);
    if (ret != 0) {
         printf("Erro: Comando '%s' nao reconhecido.\n", args[0]);
    }

    return 1;
}

int main(int argc, char **argv) {
    char *linha;
    char **args;
    int status = 1;

    system("chcp 65001 > nul");
    limpar_tela();

    exibir_ajuda();

    while (status) {
        printf("win-shell> ");
        linha = ler_linha();
        args = parse_argumentos(linha);
        status = executar_comando(args);

        free(linha);
        free(args);
    }

    return 0;
}
