/*
static void memswap(void *one, void *other, size_t width){
	char tmp[width];
	memcpy(tmp, one, width);
	memcpy(one, other, width);
	memcpy(other, tmp, width);
}
*/
	.text


# rdi = one, rsi = other, rdx = width
memswap:
	push %rbx	# rbx = one
	push %rbp   # rbp = other
	push %r12	# r12 = width
	mov %rdi, %rbx
	mov %rsi, %rbp
	mov %rdx, %r12
	sub %r12, %rsp # char tmp[width]

	mov %rsp, %rdi
	mov %rbx, %rsi
	mov %r12, %rdx
	call memcpy  	# memcpy(tmp,one,width)

	mov %rbx, %rdi
	mov %rbp, %rsi
	mov %r12, %rdx
	call memcpy		# memcpy(one,other,width)

	mov %rbp, %rdi
	mov %rsp, %rsi
	mov %r12, %rdx
	call memcpy		# memcpy(other, tmp, width)


	add %r12, %rsp
	pop %r12
	pop %rbp
	pop %rbx
	ret
/*
void bubble_sort(void *base, size_t nelements, size_t width,
			int (*compare)(const void *, const void *)) {
	int swap_flg = 0;
	if (nelements <= 1)
		return;
	char *limit = (char *)base + (nelements - 1) * width;
	for (char *ptr = base; ptr < limit; ptr += width)
		if (compare(ptr, ptr + width) > 0) {
			memswap(ptr, ptr + width, width);
			swap_flg = 1;
		}
	if (swap_flg == 0)
		return;
	bubble_sort(base, nelements - 1, width, compare);
} 
*/


	.text
	.global	bubble_sort

# rdi = base, rsi = nelements, rdx = width, rcx = *compare
bubble_sort:	
	push %rbx # rbx = swap_flg
	push %rbp # rbp = limit
	push %r12 # r12 = ptr
	push %r13 # r13 = width
	push %r14 # r14 = *compare
	push %r15 # r15 = nelements
	mov %rdx, %r13
	mov %rcx, %r14
	mov %rsi, %r15
	cmp $1, %r15
	jbe L0_bubble_sort # if (nelements <= 1) return
	mov $0, %rbx	# swap_flg = 0
	dec %r15		# nelements - 1
	mov %r13, %rax	
	mul %r15		# width * (nelements - 1)
	add %rdi, %rax 	# base + width * (nelements - 1)
	mov %rax, %rbp 	# limit = base + (nelements - 1) * width 
	mov %rdi, %r12	# ptr = base
	sub %r13, %r12	# initialize ptr by ptr - width before loop
	push %rdi		# save base value
	jmp L1_bubble_sort
L2_bubble_sort:
	mov %r12, %rdi # rdi = ptr
	mov %r13, %rsi 
	add %r12, %rsi # rsi = ptr + width 
	call *%r14	   # compare(ptr, ptr + width)
	cmp $0, %eax	# if (compare(ptr, ptr + width) > 0)
	jle L1_bubble_sort
	mov $1, %rbx	# swap_flg = 1
	mov %r12, %rdi	# rdi = ptr
	mov %r12, %rsi	
	add %r13, %rsi	# rsi = ptr + width
	mov %r13, %rdx	# rdx = width
	call memswap	# memswap(ptr, ptr + width, width)
L1_bubble_sort:
	add %r13, %r12	# ptr += width
	cmp %rbp, %r12		
	jb L2_bubble_sort	# ptr < width
	pop %rdi # restore base value
	test %rbx, %rbx
	jz L0_bubble_sort  # if (swap_flg == 0) return
	mov %r15, %rsi
	mov %r13, %rdx
	mov %r14, %rcx
	call bubble_sort # bubble_sort(base, nelements - 1, width, compare);
L0_bubble_sort:
	pop %r15
	pop %r14
	pop %r13
	pop %r12
	pop %rbp
	pop %rbx
	ret

	.section .note.GNU-stack
