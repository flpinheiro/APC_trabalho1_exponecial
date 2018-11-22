/* Algoritmos e programaçao de computadores - 1/2018
 * File:   projeto1.c
 * Aluno: felipe luís pinheiro
 * matricula: 18/0052667
 * Turma: b
 * descrição: Este programa calcula uma aproximaçao em ordem n da função exponencial e compara com a função exponencial calculada pela biblioteca do sistema retornando o erro associado
 * Created on 16 de Maio de 2018, 09:42
 */

#include <stdio.h>
#include <math.h>

/**
 * funçao absoluto. retorna o valor absoluto do valor x
 * @param x: @double
 * @return x: @double
 */
double absoluto(double x) {
    /*verifica se o numero eh negativo, se for retorna o valor com o sinal trocado*/
    if (x < 0) {
        return -x;
    }

    return x;
}

/**
 * Função fatorial, recebe um inteiro como parametro e calcula o fatorial dele, retornando um numeral inteiro
 * @param n : @int
 * @return fatorial : @int
 */
int fatorial(int n) {

    /*declaração de variaveis*/
    int fat = 1, cont;

    /*verificação de erro da funçao fatorial*/
    if (n < 0) {
        printf("ERRO: Função fatorial indefinida\n");
        return -1;
    }

    /*"callcula" e retorna o fatorial de 0 e de 1*/
    if (n < 2) {
        return 1;
    }

    /*calcula e retorna o fatorial de numeros maiores e iguais a 2*/
    for (cont = 2; cont <= n; cont++) {
        fat *= cont;
    }
    return fat;

}

/**
 * funçao potencial, calcula a potencia inteira de um numero double. recebe um double e um inteiro e retorna um double
 * @param x: @double
 * @param n: @int
 * @return pot: @double
 */
double potencia(double x, int n) {

    /*declaração de variaveis*/
    int cont;
    double pot = 1;

    /*verifica se a potencia é positiva ou negativa*/
    if (n > 0) {
        /*se for positiva calcula aqui o valor da potencia*/
        for (cont = 1; cont <= n; cont++) {
            pot *= x;
        }
    } else {
        /*se negativa calcula aqui o valor da potencia,zero incluso*/
        for (cont = 0; cont > n; cont--) {
            pot /= x;
        }
    }

    /*retorna o valor da potencia calculado*/
    return pot;

}

/**
 * função exponencial. calcula a aproximação exponencial de ordem n para um número real x
 * @param x: @double
 * @param n: @int
 * @return exp: @double
 */
double exponencial(double x, int n) {

    /*declaracao de variaveis*/
    double exp = 0;
    int cont;

    /*calcula o valor da funcao exponencial*/
    for (cont = 0; cont <= n; cont++) {
        exp += (double) potencia(x, cont) / (double) fatorial(cont);
    }

    /*retorna o valor da funcao exponencial*/
    return exp;

}

/**
 * funçao lerN: le o numero n da potencia do exponencial e do fatorial e retorna possiveis mensagens de erro.
 * teste dessa funcao eh feito manualmente devido ao fato de ser valores de entrada do usuario.
 * @return n: @int
 */
int lerN(void) {

    /*declaracao de variaveis*/
    int n;

    do {
        /*pede para o usuario entrar com o numero manualmente*/
        printf("Digite N, entre 0 e 10: ");
        scanf("%d", &n);

        /*verifica se o numero digitado eh um numero viavel. numeros negativos sao proibidos e numeros muito grandes causam instabilidade do sistema e erros de aproximacao.*/
        if (n < 0) {
            printf("ERRO: N digitado eh inconsistente, impossivel solucao com numeros negativos\n");
        }

        if (n > 10) {
            printf("ERRO: numero digitado eh muito grande.");
        }

        /*executa enquanto o usuario insistir em entrar um numero "impossivel"*/
    } while (n < 0 || n > 10);

    /*retorna o valor digitado para o operacao principal*/
    return n;

}

/**
 * funcao lerX: serve para fazer a leitura do valor x digitado pelo usuario, e impedir que o usuario coloque valores muito grandes de x, o que pode causar instabilidade do sistema.
 * @return x: @double 
 */
double lerX(void) {

    /*delcaracao de variaveis*/
    double x;

    do {
        /*pede para o usuario entrar com o valor de x*/
        printf("Digite X: ");
        scanf("%lf", &x);

        /*verifica se o valor digitado não eh muito grande, se for pede para digitar outro valor*/
        if (x > 50 || x < -50) {
            printf("ERRO: o valor digitado para X é muuto grando o que pode causer instabilidade no funcionamento do sistema\n");
        }
    } while (x > 50 || x < -50);

    /*retorna o valor de x digitado pelo usuario*/
    return x;
}

/**
 * funçao de test, verifica as funcoes de entrada manual, feitas pelo usuario
 */
void test(void) {

    /*declaraçao de variaveis*/
    int n;

    /**
     * teste da função lerN.
     * é feito manualmente, essa função ler dados inseridos pelo usuario. 
     */
    printf("\nTest funcao lerN\n");
    for (n = 1; n <= 10; n++) {
        printf("teste numero : %d\n\n", n);
        lerN();
    }

    /**
     *  teste da função lerX.
     * feito manualmente devido ao fato de ser uma função que exige a entrada dde dados pelo usuario. 
     */
    printf("\nTest funcao lerX\n");
    for (n = 1; n <= 10; n++) {
        printf("teste numero : %d\n\n", n);
        lerX();
    }

}

/**
 * textExp. Testa a funcao exponencial, potencia e fatorial
 */
void testExp(void) {

    int n;
    double x;

    printf("\nTest funcao exponencial\n\n");
    for (x = 0; x <= 2; x += .5) {
        printf("%.2lf ", x);
        for (n = 0; n <= 10; n++) {
            printf(" %.2lf %c", (exponencial(x, n) - exp(x)) / exp(x) * 100, 37);
        }
        printf("\n");
    }

    /**
     * teste da funcao fatorial
     * é feito entre numeros negativos e positivos, para verificar a funcionalidade em todo o espectro possivel, mesmo que o programa impessa que o usuario use um numero negativo.
     */
    printf("\nTest de fatorial\n");
    for (n = -3; n <= 10; n++) {
        printf("%d! = %d\n", n, fatorial(n));
    }

    /**
     * Teste da função potencia
     * é testado com potencias positivas e negativas, pois a função foi construida com essa funcionalidade.
     */
    printf("\nTest de potencia positiva\n");
    for (n = -3; n <= 10; n++) {
        printf("2^%d = %lf\n", n, potencia(2, n));
    }

    /**
     * também é testado uma potencia de numeros negativos
     */
    printf("\nTest de potencia negativa\n");
    for (n = -3; n <= 10; n++) {
        printf("2^%d = %lf\n", n, potencia(-2, n));
    }

}

/**
 * função main
 */
int main(void) {

    /*test();*/
    /*testExp();*/

    /*delcaracao de variaveis*/
    int n;
    double x, expL, expF, erro;

    /*exp;ica suncintamente a funcionalidade do programa*/
    printf("Esse programa calcula a aproximacao da funcao exponecial para um determinado falor x e uma quantidade de termos n.\n");

    /*leitura dos dados entrado pelo usuario*/
    x = lerX();
    n = lerN();

    /*calculo dos valores,  sendo expL-> exp', resultado da funcao exponencial deste programa, e expF-> exp(), resultado da funcao exponencial da biblioteca math.h*/
    expL = exponencial(x, n);
    expF = exp(x);

    /*calculo do erro*/
    erro = absoluto(expL - expF);

    /*imprime o resultado final*/
    printf("o resultado de exp para x = %lf e n = %d eh %lf com um erro %lf", x, n, expL, erro);

    return 0;
}
