/*
	size_t next_pow2(size_t x)
	{
	size_t mask = 1UL << ((sizeof mask * CHAR_BIT) - 1);
	if (x == 0 || x > mask)
		return 0;
	while ((x & mask) == 0)
		mask >>= 1;
	return mask << (x != mask);
}
*/

	.text
	.global next_pow2
	
next_pow2:

	xor %rax, %rax		# if x == 0 return 0
	test %rdi, %rdi
	jz L0_next_pow2

	mov $1, %rsi	
	shl $63, %rsi		# rsi = mask
	cmp %rsi, %rdi	    # if x > mask return 0
	ja L0_next_pow2

	bsr %rdi, %rcx   	# 	while ((x & mask) == 0) mask >> = 1
    mov $1, %rax        
    shl %cl, %rax   

	cmp %rdi, %rax		# return mask << (x != mask);
	je L0_next_pow2
	shl $1, %rax

L0_next_pow2:
	ret

	.section .note.GNU-stack

