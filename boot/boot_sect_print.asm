
print:
    pusha

start:
    mov al,[bx]
    cmp al, 0
    je done

    mov ah, 0x0e
    int 10h

    add bx, 1
    jmp start

done:
    popa
    ret


print_nl:
    pusha
    
    mov ah, 0x0e
    mov al, 0x0a
    int 10h
    mov al, 0x0d
    int 10h

    popa
    ret