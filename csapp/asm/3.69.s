# void test(long i, b_struct *bp)
# i in %rdi, bp in %rsi
test:
  mov 0x120(%rsi), %ecx         # bp+0x120 fetch bp->last
  add (%rsi), %ecx              # bp->first + bp->last

  lea (%rdi,%rdi,4), %rax       # i*5
  lea (%rsi,%rax,8), %rax       # rax = bp+i*40

  # ap = &bp->a[i] = bp+i*40+8, +8 means skip int first
  # so a_struct is aligned by 8, size is 40
  # check last instrction, 
  # so in a_struct, idx is first element
  # rdx store the value of ap->idx
  mov 0x8(%rax), %rdx

  movslq %ecx, %rcx        # convert to long

  #  (0x10) is 16
  # save n to address: 
  # bp + i*40 + 0x8 + 0x8 + 8*(ap->idx) 
  # bp + i*40 + 0x8 means ap
  # ap + 0x8 means &(ap->x)
  # &(ap->x) + 8*(ap->idx) means &(ap-x[ap->idx])
  # second element of a_struct is x, 
  # x is an array of long
  # 8*(ap->idx) means idx is also long type
  mov %rcx, 0x10(%rax,%rdx,8)

  # size of a_struct is 40 and aligned by 8
  # so array x has 4 long elements
  # finally, a_struct is
  #   typedef struct {
  #     long idx,
  #     long x[4]
  #   } a_struct
  retq
