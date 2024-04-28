/*
static int compare_strings(const void *a, const void *b) {
	return strcmp(*(char **)a, *(char **)b);
}
*/
	.text
	.global	compare_strings
compare_strings:
	mov	(%rdi), %rdi
	mov	(%rsi), %rsi
	call	strcmp
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
