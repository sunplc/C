# PURPOSE: Count the characters until a null byte is reached.
#
# INPUT: The address of the character string
#
# OUTPUT: Returns the count in %eax
# PROCESS:

# Parameters:
#   %rdi - current character address

# Register used:
#   %rsi - character count
#   %al - current character

.globl count_chars
.type count_chars, @function

count_chars:
    #Counter starts at zero
    movq $0, %rsi

count_loop_begin:
    #Grab the current character
    movb (%rdi), %al
    #Is it null?
    cmpb $0, %al
    #If yes, we’re done
    je count_loop_end
    #Otherwise, increment the counter and the pointer
    incq %rsi
    incq %rdi
    #Go back to the beginning of the loop
    jmp count_loop_begin

count_loop_end:
    #We’re done. Move the count into %eax
    #and return.
    movq %rsi, %rax
    ret

