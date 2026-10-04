#include <stdio.h>
#include <stdint.h>

#define STACK_SIZE 30000
#define dbg() \
    printf("Current instruction: %c, Stack: ", code[ip] == 10?'n':code[ip]); \
    printf("{"); for (i=1; i <= 10; i++) { \
        printf(" %d,", stack[i]); \
    }; printf(" }\n");

int main(int argc, char *argv[]) {
    /* Prepare variables */
    uint8_t  stack[STACK_SIZE+1];
    uint8_t  reg = 0;
    uint16_t sp = 0;
    int      ip = 0;
    int      filesize = 0;
    uint16_t sp_2 = 0;

    /* i */
    int i = 0;
    
    if (!argv[1]) {
        fprintf(stderr, "No file specified.\n");
        return 1;
    }

    /* Load file */
    FILE *fileptr = fopen(argv[1], "r");
    if (!fileptr) {
        fprintf(stderr, "File does not exist\n");
        return 1;
    }

    fseek(fileptr, 0, SEEK_END);
    filesize = ftell(fileptr);
    fseek(fileptr, 0, SEEK_SET);
    char code[filesize];
    fread(code, filesize, 1, fileptr);
    fclose(fileptr);
    
    /* Prepare jump table */
    uint32_t jump_sp = 0;
    uint32_t jump_stack[filesize];
    uint32_t jump[filesize];
    for (i = 0; i < filesize; i++) {
        if (code[i] == '[') {
            jump_stack[++jump_sp] = i;
        }
        else if (code[i] == ']') {
            jump[i] = jump_stack[jump_sp--];
            jump[jump[i]] = i;
        }
    }

    /* Main loop */
    while (ip < filesize) {
        switch (code[ip]) {
            case '>':
                if (sp+1 < STACK_SIZE)
                    stack[++sp] = 1;
                break;
            case '<':
                if (sp > 0)
                    stack[sp--] = 0;
                break;
            case '+':
                if (sp == 0) break;
                stack[sp-1] += stack[sp];
                stack[sp--] = 0;
                break;
            case '-':
                if (sp < 1) break;
                stack[sp-1] -= stack[sp];
                stack[sp--] = 0;
                break;
            case '!':
                stack[sp] = reg + stack[sp];
                reg = stack[sp] - reg;
                stack[sp] = stack[sp] - reg;
                break;
            case '?':
                if (sp < 2) break;
                sp_2 = (stack[sp-1] << 8 | stack[sp]) + 1;
                stack[sp--] = 0; stack[sp--] = 0;

                stack[sp] = stack[sp_2] + stack[sp];
                stack[sp_2] = stack[sp] - stack[sp_2];
                stack[sp] = stack[sp] - stack[sp_2];
                break;
            case '.':
                printf("%c", stack[sp]);
                fflush(stdout);
                break;
            case ',':
                if (sp+1 < STACK_SIZE) --sp;
                fprintf(stderr, "\nInput (^D for EOF): ");
                fflush(stderr);
                stack[++sp] = fgetc(stdin);
                if ((int8_t)stack[sp] == EOF) stack[sp] = 0;
                fprintf(stderr, "\n");
                break;
            case '[':
                if (!stack[sp]) {
                    ip = jump[ip];
                }
                break;
            case ']':
                if (stack[sp]) {
                    ip = jump[ip];
                }
                break;
        }
#ifdef DEBUG
        dbg();
#endif
        ip++;
    }
    puts("");
    return 0;
}

