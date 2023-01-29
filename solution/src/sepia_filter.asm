global sepia_fast

section .data

    f1: dd 0.393, 0.349, 0.272, 0.393
    f2: dd 0.769, 0.686, 0.543, 0.769
    f3: dd 0.189, 0.168, 0.131, 0.189




section .text


count_color:
    movdqa xmm3, [rel f1]
    movdqa xmm4, [rel f2]
    movdqa xmm5, [rel f3]
    movdqu xmm0, [rdi]
    movdqu xmm1, [rsi]
    movdqu xmm2, [rdx]
    mulps  xmm0, xmm3
    mulps  xmm1, xmm4
    mulps  xmm2, xmm5
    addps  xmm0, xmm1
    addps  xmm0, xmm2
    movdqu [rdi], xmm0
    ret

sepia_fast:
    mov rsi,  16
    add rsi, rdi
    mov rdx, 32
    add rdx, rdi
    push rdi
    push rsi
    push rdx
    call count_color
    pop rdx
    pop rsi
    pop rdi
    ret