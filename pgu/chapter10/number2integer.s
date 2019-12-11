# Conversion a string of number to integer
#
# Parameters:
# %rdi - Pointer to string buffer which need to be transfer

.globl number2integer
.type number2integer, @function
number2integer:

movq $0, %rdx # the integer value
movq $0, %rsi # index of buffer

conversion_loop:

    # Fetch each char of buffer
    movb (%rdi, %rsi, 1), %al

begin_check_character:

    cmpb $0, %al
    jle conversion_end

    # Check to see if each char is valid
    cmpb $'0', %al
    jge L1
    jmp L2

L1:
    cmpb $'9', %al
    jle handle_decimal

L2:
    cmpb $'a', %al
    jge L3
    jmp conversion_end

L3:
    cmpb $'f', %al
    jle handle_hexdecimal
    jmp conversion_end

# Swtich each char to integer
handle_decimal:
    subb $'0', %al
    jmp match_character

handle_hexdecimal:
    subb $'a', %al
    addb $10, %al

match_character:
    # add each integer to sum
    imulq $10, %rdx
    movq $0, %rcx
    movq %rax, %rcx
    addq %rcx, %rdx

    addq $1, %rsi
    jmp conversion_loop

conversion_end:
    movq %rdx, %rax
    ret

