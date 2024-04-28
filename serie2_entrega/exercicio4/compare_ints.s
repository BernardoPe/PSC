/*
static int compare_ints(const void *a, const void *b) {
	if (*(int *)a > *(int *)b)
		return +1;
	else if (*(int *)a < *(int *)b)
		return -1;
	return 0;
}
*/
	.text
	.global	compare_ints
compare_ints:
	mov	(%rdi), %eax
	mov	(%rsi), %ecx
	cmp	%eax, %ecx
	jl	return_positive
	jg	return_negative
	mov	$0, %eax
	jmp	return
return_positive:
	mov	$+1, %eax
	jmp	return
return_negative:
	mov	$-1, %eax
return:
	mov	$-1, %rdi
	mov	$-1, %rsi
	mov	$-1, %rdx
	mov	$-1, %rcx
	mov	$-1, %r8
	mov	$-1, %r9
	mov	$-1, %r10
	mov	$-1, %r11
	ret

	.section .note.GNU-stack
