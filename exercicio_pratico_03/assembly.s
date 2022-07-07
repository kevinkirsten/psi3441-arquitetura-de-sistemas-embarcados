@ t_start = SysTick_PDD_ReadCurrentValueReg(SysTick_DEVICE);
ldr r3,[pc, #28] @ r3 carregado com o endereço de program counter + offset de 28
ldr r3,[r3,  #8] @ r3 carregado com o valor de r3 + offset de 8
str r3,[r7, #12] @ r3 armazenado no endereço de r7 + offset de 12
@ c = a + b;
ldr  r2,[r7,#20] @ r2 carregado com o valor de r7 + offset de 20
ldr  r3,[r7,#16] @ r3 carregado com o valor de r7 + offset de 16
adds r3, r2, r3  @ r3 = r2 + r3 e armazena o resultado em r3
str  r3,[r7, #8] @ r3 armazenado no endereço de r7 + offset de 8
@ t_stop = SysTick_PDD_ReadCurrentValueReg(SysTick_DEVICE);
ldr  r3,[pc,#12] @ r3 carregado com o endereço de program counter + offset de 12
ldr  r3,[r3, #8] @ r3 carregado com o valor de r3 + offset de 8
str  r3,[r7, #4] @ r3 armazenado no endereço de r7 + offset de 4
@ delta_t = t_start - t_stop;
ldr  r2,[r7,#12] @ r2 carregado com o valor de r7 + offset de 12
ldr  r3,[r7, #4] @ r3 carregado com o valor de r7 + offset de 4
subs r3, r2, r3  @ r3 = r2 - r3 e armazena o resultado em r3
str  r3,[r7, #0] @ r3 armazenado no endereço de r7 + offset de 0