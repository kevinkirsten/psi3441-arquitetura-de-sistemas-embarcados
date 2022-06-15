#include "mbed.h"

Timer t;
Serial serial(USBTX, USBRX);
AnalogIn ain(PTB0);

float calculate_timer_diff(float timer_start, float timer_end) {
    float diff = timer_end - timer_start;
    return diff;
}

void printf_line(int lines_amount) {
    for (int i = 0; i < lines_amount; i++) {
        printf("\n ");
    }
}

int main() {
    float timer_start, timer_end, timer_diff;
    t.start();
    printf("------------------ Inicio Ex 01 ------------------\n");
    
    // Tarefa 1 ----------------------------------------------------------
    timer_start = t.read_us();
    float temp = ain;
    timer_end = t.read_us();  
    timer_diff = calculate_timer_diff(timer_start, timer_end);
    printf("\n1) Tempo para realizar uma aquisicao analogica:\n");
    printf("        > %f ms\n", timer_diff);
    
    // Tarefa 2 ----------------------------------------------------------
    int x = 1;
    int y;
    int max = 0;
    int i = 0;
    
    // sem loop
    timer_start = t.read_us();
    x = x * 3;
    x = x * 4;
    y = x + max;
    x = y - i;
    x = x << 4;
    timer_end = t.read_us();  
    timer_diff = calculate_timer_diff(timer_start, timer_end);
    printf("\n2) Tempo para realizar o calculo matematico (sem loop):\n");
    printf("        > %f ms\n", timer_diff);
    
    // com loop
    x = 1;
    max = 0;
    float diff_sum = 0;
    int threshold = 10000;
    for(int i = 0; i < threshold; i++)
    {
        timer_start = t.read_us();
        x = x * 3;
        x = x * 4;
        y = x + max;
        x = y - i;
        x = x << 4;
        timer_end = t.read_us();
        timer_diff = calculate_timer_diff(timer_start, timer_end);
        diff_sum += timer_diff;
    }
    timer_diff = diff_sum/threshold;
    printf("\n   Tempo para realizar o calculo matematico (media com loop %dx):\n", threshold);
    printf("        > %f ms\n", timer_diff);
    
    // Tarefa 3 ----------------------------------------------------------
    printf("\n3) Tempo para realizar operacoes matematicas:\n");
    
    // a. Adição Int
    int a_int = 1;
    int b_int = 2;
    int r_int;
    diff_sum = 0.0;
    for(int i = 0; i < threshold; i++)
    {
        timer_start = t.read_us();
        r_int = a_int * b_int;
        timer_end = t.read_us();
        timer_diff = calculate_timer_diff(timer_start, timer_end);
        diff_sum += timer_diff;
    }
    timer_diff = diff_sum/threshold;
    printf("    a) Adicao de int:\n");
    printf("        > %f ms\n", timer_diff);
    
    // a. Adição Float
    float a_float = 1.0;
    float b_float = 2.0;
    float r_float;
    diff_sum = 0.0;
    for(int i = 0; i < threshold; i++)
    {
        timer_start = t.read_us();
        r_float = a_float * b_float;
        timer_end = t.read_us();
        timer_diff = calculate_timer_diff(timer_start, timer_end);
        diff_sum += timer_diff;
    }
    timer_diff = diff_sum/threshold;
    printf("       Adicao de float:\n");
    printf("        > %f ms\n", timer_diff);
    
    // b. Subtração Int
    a_int = 3;
    b_int = 2;
    diff_sum = 0.0;
    for(int i = 0; i < threshold; i++)
    {
        timer_start = t.read_us();
        r_int = a_int + b_int;
        timer_end = t.read_us();
        timer_diff = calculate_timer_diff(timer_start, timer_end);
        diff_sum += timer_diff;
    }
    timer_diff = diff_sum/threshold;
    printf("\n    b) Subtracao de int:\n");
    printf("        > %f ms\n", timer_diff);
    
    // b. Subtração Float
    a_float = 3.0;
    b_float = 2.0;
    diff_sum = 0.0;
    for(int i = 0; i < threshold; i++)
    {
        timer_start = t.read_us();
        r_float = a_float * b_float;
        timer_end = t.read_us();
        timer_diff = calculate_timer_diff(timer_start, timer_end);
        diff_sum += timer_diff;
    }
    timer_diff = diff_sum/threshold;
    printf("       Subtracao de float:\n");
    printf("        > %f ms\n", timer_diff);
    
    // c. Multiplicação Int
    a_int = 3;
    b_int = 2;
    diff_sum = 0.0;
    for(int i = 0; i < threshold; i++)
    {
        timer_start = t.read_us();
        r_int = a_int * b_int;
        timer_end = t.read_us();
        timer_diff = calculate_timer_diff(timer_start, timer_end);
        diff_sum += timer_diff;
    }
    timer_diff = diff_sum/threshold;
    printf("\n    c) Multiplicao de int:\n");
    printf("        > %f ms\n", timer_diff);
    
    // c. Multiplicação Float
    a_float = 3.0;
    b_float = 2.0;
    diff_sum = 0.0;
    for(int i = 0; i < threshold; i++)
    {
        timer_start = t.read_us();
        r_float = a_float * b_float;
        timer_end = t.read_us();
        timer_diff = calculate_timer_diff(timer_start, timer_end);
        diff_sum += timer_diff;
    }
    timer_diff = diff_sum/threshold;
    printf("\n       Multiplicao de float:\n");
    printf("        > %f ms\n", timer_diff);
    
    // d. Divisão Int
    a_int = 6;
    b_int = 2;
    diff_sum = 0.0;
    for(int i = 0; i < threshold; i++)
    {
        timer_start = t.read_us();
        r_int = a_int / b_int;
        timer_end = t.read_us();
        timer_diff = calculate_timer_diff(timer_start, timer_end);
        diff_sum += timer_diff;
    }
    timer_diff = diff_sum/threshold;
    printf("\n    d) Divisao de int:\n");
    printf("        > %f ms\n", timer_diff);
    
    // d. Divisão Float
    a_float = 6.0;
    b_float = 2.0;
    diff_sum = 0.0;
        for(int i = 0; i < threshold; i++)
    {
        timer_start = t.read_us();
        r_float = a_float / b_float;
        timer_end = t.read_us();
        timer_diff = calculate_timer_diff(timer_start, timer_end);
        diff_sum += timer_diff;
    }
    timer_diff = diff_sum/threshold;
    printf("       Divisao de float:\n");
    printf("        > %f ms\n", timer_diff);
    
    // Tarefa 4 ----------------------------------------------------------
    printf("\n4) Qual o valor da soma de 2.147.483.647 + 1?\n");
    a_int = 2147483647;
    b_int = 1;
    r_int = a_int + b_int;
    printf("        > Soma: %d\n", r_int);
    printf_line(10);
}
