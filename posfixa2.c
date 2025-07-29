#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 100

// Estrutura para a pilha, usada para armazenar operandos durante o cálculo da expressão pós-fixa
typedef struct {
    double data[MAX_SIZE]; // Vetor que armazena os valores (operandos)
    int top;               // Índice do topo da pilha
} Stack;

// Inicializa a pilha, definindo o topo como -1 (pilha vazia)
void initialize(Stack *s) {
    s->top = -1;
}

// Verifica se a pilha está vazia
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Verifica se a pilha está cheia
int isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

// Insere um valor no topo da pilha
void push(Stack *s, double valor) {
    if (isFull(s)) {
        printf("Erro: Pilha cheia!\n");
        exit(EXIT_FAILURE);
    }
    s->data[++(s->top)] = valor
;
}

// Remove e retorna o valor do topo da pilha
double pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Erro: Pilha vazia!\n");
        exit(EXIT_FAILURE);
    }
    return s->data[(s->top)--];
}

// Função que avalia uma expressão matemática na notação pós-fixa (polonesa reversa)
// Utiliza uma pilha para armazenar operandos e processar operadores
double evaluatePostfix(char *expressao) {
    Stack s;
    initialize(&s);
    char *token;
    double operand1, operand2;

    // Divide a expressão em tokens usando espaço como delimitador
    token = strtok(expressao, " ");

    // Processa cada token da expressão
    while (token != NULL) {
        // Se o token for um número (positivo ou negativo), converte e empilha
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(&s, atof(token));
        } else {
            // Se não for número, deve ser operador: desempilha dois operandos
            if (isEmpty(&s) || s.top < 1) {
                printf("Erro: Expressão inválida (muitos operadores ou falta de operandos)!\n");
                exit(EXIT_FAILURE);
            }
            operand2 = pop(&s);
            operand1 = pop(&s);

            // Executa a operação correspondente e empilha o resultado
            switch (token[0]) {
                case '+':
                    push(&s, operand1 + operand2);
                    break;
                case '-':
                    push(&s, operand1 - operand2);
                    break;
                case '*':
                    push(&s, operand1 * operand2);
                    break;
                case '/':
                    if (operand2 == 0) {
                        printf("Erro: Divisão por zero!\n");
                        exit(EXIT_FAILURE);
                    }
                    push(&s, operand1 / operand2);
                    break;
                case '^':
                    push(&s, pow(operand1, operand2));
                    break;
                default:
                    printf("Erro: Operador inválido: %s\n", token);
                    exit(EXIT_FAILURE);
            }
        }
        // Avança para o próximo token
        token = strtok(NULL, " ");
    }

    // Ao final, deve restar apenas um valor na pilha: o resultado da expressão
    if (isEmpty(&s) || s.top != 0) {
        printf("Erro: Expressão inválida (faltam operadores ou operandos)!\n");
        exit(EXIT_FAILURE);
    }
    return pop(&s); // Retorna o resultado final
}

int main() {
    char expressao[MAX_SIZE];

    // Solicita ao usuário a expressão pós-fixa, separando elementos por espaço
    printf("Digite a expressao na notacao polonesa reversa (pos-fixa), separando os elementos por espacos: ");
    fgets(expressao, MAX_SIZE, stdin);

    // Remove o caractere de nova linha '\n' adicionado pelo fgets
    expressao[strcspn(expressao, "\n")] = 0;

    // Avalia a expressão e imprime o resultado com duas casas decimais
    double result = evaluatePostfix(expressao);
    printf("Resultado: %.2f\n", result);

    return 0;
}