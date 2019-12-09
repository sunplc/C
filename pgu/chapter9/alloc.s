# PURPOSE: Program to manage memory usage - allocates
# and deallocates memory as requested
#
# NOTES: The programs using these routines will ask
# for a certain size of memory. We actually
# use more than that size, but we put it
# at the beginning, before the pointer
# we hand back. We add a size field and
# an AVAILABLE/UNAVAILABLE marker. So, the
# memory looks like this
#
# #########################################################
# # Available Marker # Size of memory # Actual memory locations #
# #########################################################
# ^--Returned pointer
# points here
# The pointer we return only points to the actual
# locations requested to make it easier for the
# calling program. It also allows us to change our
# structure without the calling program having to
# change at all.

.section .data
#######GLOBAL VARIABLES########
# This points to the beginning of the memory we are managing
heap_begin:
    .quad 0
# This points to one location past the memory we are managing
current_break:
    .quad 0
    debug:
    .ascii "rs:%d\n\0"

######STRUCTURE INFORMATION####
# size of space for memory region header
    .equ HEADER_SIZE, 16
# Location of the "available" flag in the header
    .equ HDR_AVAIL_OFFSET, 0
# Location of the size field in the header
    .equ HDR_SIZE_OFFSET, 8

########### CONSTANTS ###########
    .equ UNAVAILABLE, 0 # This is the number we will use to mark
# space that has been given out
    .equ AVAILABLE, 1 # This is the number we will use to mark
                        # space that has been returned, and is
                        # available for giving
    .equ SYS_BRK, 12 # system call number for the break

.section .text

########## FUNCTIONS ############
## allocate_init ##
# PURPOSE: call this function to initialize the
# functions (specifically, this sets heap_begin and
# current_break). This has no parameters and no
# return value.
.globl allocate_init
.type allocate_init, @function
allocate_init:

    # If the brk system call is called with 0 in %rdi, it
    # returns the last valid usable address
    movq $SYS_BRK, %rax # find out where the break is
    movq $0, %rdi
    syscall

    incq %rax   # %rax now has the last valid
                # address, and we want the
                # memory location after that

    movq %rax, current_break # store the current break
    movq %rax, heap_begin   # store the current break as our
                            # first address. This will cause
                            # the allocate function to get
                            # more memory from Linux the
                            # first time it is run
    # exit the function
    ret
##### END OF FUNCTION #######

## allocate ##
# PURPOSE: This function is used to grab a section of
# memory. It checks to see if there are any
# free blocks, and, if not, it asks Linux
# for a new one.
#
# PARAMETERS: This function has one parameter - the size
# of the memory block we want to allocate
#
# RETURN VALUE:
# This function returns the address of the
# allocated memory in %rax. If there is no
# memory available, it will return 0 in %rax
#
###### PROCESSING ########
# Variables used:
#
# %rdi - hold the size of the requested memory
#       (first/only parameter)
# %rsi - current memory region being examined
# %rdx - current break position
# %rcx - size of current memory region
#
# We scan through each memory region starting with
# heap_begin. We look at the size of each one, and if
# it has been allocated. If it’s big enough for the
# requested size, and its available, it grabs that one.
# If it does not find a region large enough, it asks
# Linux for more memory. In that case, it moves
# current_break up

.globl allocate
.type allocate, @function

allocate:
    pushq %rbp # standard function stuff
    movq %rsp, %rbp

    # check if allocate_init have been called
    cmpq $0, current_break
    jne skip_allocate_init

    # Cause %rdi holds the value we need, so we save
    # it in stack
    pushq %rdi
    call allocate_init
    popq %rdi

skip_allocate_init:

    movq heap_begin, %rsi # %rsi will hold the current
                            # search location
    movq current_break, %rdx # %rdx will hold the current
                            # break

alloc_loop_begin: # here we iterate through each
                    # memory region

    cmpq %rsi, %rdx # need more memory if these are equal
    jle move_break

    # grab the size of this memory region
    movq HDR_SIZE_OFFSET(%rsi), %rcx
    # If the space is unavailable, go to the next one
    cmpq $UNAVAILABLE, HDR_AVAIL_OFFSET(%rsi)
    je next_location

    cmpq %rcx, %rdi     # If the space is available, compare
    jle allocate_here   # the size to the needed size. If its
                        # big enough, go to allocate_here

next_location:

    addq $HEADER_SIZE, %rsi # The total size of the memory
    addq %rcx, %rsi         # region is the sum of the size
                            # requested (currently stored
                            # in %rcx), plus another 16 bytes
                            # for the header (8 for the
                            # AVAILABLE/UNAVAILABLE flag,
                            # and 8 for the size of the
                            # region). So, adding %rcx and $16
                            # to %rsi will get the address
                            # of the next memory region

    jmp alloc_loop_begin    # go look at the next location

allocate_here:              # if we’ve made it here,
                            # that means that the
                            # region header of the region
                            # to allocate is in %rsi
                            # mark space as unavailable

    movq $UNAVAILABLE, HDR_AVAIL_OFFSET(%rsi)

    movq %rsi, %rax # save return value in %rax
    addq $HEADER_SIZE, %rax # move %rax past the header to
                            # the usable memory (since
                            # that’s what we return)
    
    # break up current region into multiple parts,
    # make the remaind part a new memory region
    subq %rdi, %rcx
    cmpq $HEADER_SIZE, %rcx

    pushq %rdi
    pushq %rsi
    pushq %rax
    pushq %rcx

    movq %rdi, %rsi
    movq $debug, %rdi
    mov $2, %al
    call printf

    popq %rcx
    popq %rax
    popq %rsi
    popq %rdi

    jle skip_save_remainder

    movq %rdi, HDR_SIZE_OFFSET(%rsi)

    addq $HEADER_SIZE, %rsi
    addq %rdi, %rsi
    subq $HEADER_SIZE, %rcx

    movq $AVAILABLE, HDR_AVAIL_OFFSET(%rsi)
    movq %rcx, HDR_SIZE_OFFSET(%rsi)

skip_save_remainder:

    movq %rbp, %rsp # return from the function
    popq %rbp
    ret

move_break: # if we’ve made it here, that
            # means that we have exhausted
            # all addressable memory, and
            # we need to ask for more.
            # %rdx holds the current
            # endpoint of the data,
            # and %rdi holds its size
            # we need to increase %rdx to
            # where we _want_ memory
            # to end, so we

    addq $HEADER_SIZE, %rdx # add space for the headers
                            # structure
    addq %rdi, %rdx # add space to the break for
                    # the data requested
                    # now its time to ask Linux
                    # for more memory

    # save needed registers
    pushq %rsi # current memory region being examined
    pushq %rdi # size of the requested memory
    pushq %rdx # current break position

    movq %rdx, %rdi
    movq $SYS_BRK, %rax # reset the break (%rax has
                        # the requested break point)
    syscall

    # under normal conditions, this should
    # return the new break in %rax, which
    # will be either 0 if it fails, or
    # it will be equal to or larger than
    # we asked for. We don’t care
    # in this program where it actually
    # sets the break, so as long as %rax
    # isn’t 0, we don’t care what it is
    cmpq $0, %rax # check for error conditions
    je error

    movq %rdx, current_break # save the new break
    
    # restore saved registers
    popq %rdx
    popq %rdi
    popq %rsi

    # set this memory as unavailable, since we’re about to
    # give it away
    movq $UNAVAILABLE, HDR_AVAIL_OFFSET(%rsi)
    # set the size of the memory
    movq %rdi, HDR_SIZE_OFFSET(%rsi)
    # move %rsi to the actual start of usable memory.
    # %rsi now holds the return value
    addq $HEADER_SIZE, %rsi
    movq %rsi, %rax

    movq %rbp, %rsp # return the function
    popq %rbp
    ret

error:
    movq $0, %rax # on error, we return zero
    movq %rbp, %rsp
    popq %rbp
    ret
######## END OF FUNCTION ########

## deallocate ##
# PURPOSE:
# The purpose of this function is to give back
# a region of memory to the pool after we’re done
# using it.
#
# PARAMETERS:
# The only parameter is the address of the memory
# we want to return to the memory pool.
#
# RETURN VALUE:
# There is no return value
#
# PROCESSING:
# If you remember, we actually hand the program the
# start of the memory that they can use, which is
# 8 storage locations after the actual start of the
# memory region. All we have to do is go back
# 8 locations and mark that memory as available,
# so that the allocate function knows it can use it.
.globl deallocate
.type deallocate, @function
deallocate:
# get the pointer to the real beginning of the memory
subq $HEADER_SIZE, %rdi
# mark it as available
movq $AVAILABLE, HDR_AVAIL_OFFSET(%rdi)
# return
ret
######## END OF FUNCTION##########

