        ; Linux 32-bit assembly

SECTION .data           ;This section declares variables with values

array: dd  09h, 1Ch, 42h, 5Fh, 66h, 32h, 49h, 92h, 24h, 10h
                        ;declaring an array
array_len: equ $-array  ;set array_len to size of array
array_unit_size: equ 4  ;set array_unit_size to 4, the size of a double word

i: dd 0h                ;declare i as a dword that is equal to 0

SECTION .bss    ;This section declares variables without values. I'm not using it for this project

SECTION .text   ;This section is for running code

global _main    ;Declare that _main can be accessed outside of the program, needed to start program

_main:          ;start _main

    ;calculate half the size of the array so
    mov eax, array              ;move array to eax, testing purposes to find location in memory
    mov eax, array_len          ;move array length to eax
    mov ebx, array_unit_size    ;move the size of units to ebx
    div ebx                     ;divide eax by the ebx, get number of elements in array and store in eax
    mov ebx, 2                  ;move 2 to ebx
    div ebx                     ;divide number of elements in the array by 2 and store in eax
    mov ecx, eax                ;move the value in eax to ecx, (half the number of elements in the array to ecx)

    loop:       ;set destination for loop

    ;calculate the location in the array to move too.
    mov eax, [i]                ;move the vlaue in i to
    mov edx, array_unit_size    ;move the size of a dword to edx
    mul edx                     ;multiply the value in eax (i) by the size of a dword

    ;move edx and ebx to swap locations in array
    mov edx, eax                            ;move the value of eax to edx
    mov ebx, array_len - array_unit_size    ;move the location of the last element in the array to ebx
    sub ebx, eax                            ;subtract eax from ebx

    ;swap array locations
    mov eax, [array + edx]  ;move the value of the array (start location + edx) to eax
    xchg eax, [array + ebx] ;swap the vlaue of the array (start location + ebx) with eax
    xchg eax, [array + edx] ;swap the vlaue of the array (start location + edx) with eax

    ;increment i by 1
    mov edx, [i]    ;move the value of i to edx
    inc edx         ;increment the value in edx by 1
    mov [i], edx    ;move the value in edx to i

    ;decrement loop counter and continue
    dec ecx     ;decrement the value in ecx by 1
    jne loop    ;compare ecx to 0 and jump to loop if true continue if false

    test:       ; included for debugging read the values of array in debug mode

    ;Exit program system call.
    mov eax, 1  ;move 1 to eax
    mov ebx, 0  ;move 0 to ebx
    int 80h     ;make system call to exit cleanly
