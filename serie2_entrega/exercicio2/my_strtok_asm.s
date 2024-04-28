/*
char *my_strtok(char *str, const char *sep)
{
	static char *p = NULL;
	if (str != NULL)
		p = str;
	if (p == NULL || *p == 0)
		return NULL;
	while (strchr(sep, *p) != NULL)
		++p;
	if (*p == 0)
		return NULL;
	char *q = p;
	while (*p != 0 && strchr(sep, *p) == NULL)
		++p;
	*p++ = 0;
	return q;
}
*/
	.bss
	
	p: .space 8

	.text
	.global my_strtok


my_strtok:			
	push %rbx	# rbx = sep
	push %rbp	# rbp = q
	mov %rsi, %rbx 		
	test %rdi, %rdi 
	jz L0_my_strtok	# if (str != NULL) p = str
	mov %rdi, p
L0_my_strtok:
	xor %rax, %rax		
	mov p, %rdx
	cmp $0, %rdx
	jz L1_my_strtok	# if (p == NULL) return NULL	
	mov (%rdx), %dl
	cmp $0, %dl
	jz L1_my_strtok	# if (*p == 0) return NULL
	jmp L2_my_strtok
L3_my_strtok:
	incq p			# ++p
L2_my_strtok:
	mov %rbx, %rdi	# rdi = sep
	mov p, %rsi		
	mov (%rsi), %sil # sil = *p	
	call strchr
	test %al, %al		
	jnz L3_my_strtok  # strchr(sep,*p) != NULL	
	xor %rax, %rax
	mov p, %rdx			
	mov (%rdx), %dl
	cmp $0, %dl		
	jz L1_my_strtok	# if (*p == 0) return NULL
	mov p, %rbp
	jmp	L4_my_strtok
L5_my_strtok:
	incq p		# ++p
L4_my_strtok:
	mov %rbx, %rdi
	mov p, %rsi
	mov (%rsi), %sil
	cmp $0, %sil	
	jz L6_my_strtok	# *p == 0, end cycle
	call strchr
	test %al, %al
	jz L5_my_strtok	# if (*p != 0 && strchr(sep, *p) == NULL) continue loop
L6_my_strtok: 
	mov p, %rsi      
	movb $0, (%rsi)    # *p = 0
	incq p	   # p++
	mov %rbp, %rax	   # return q
L1_my_strtok:
	pop %rbp
	pop %rbx
	ret

	.section .note.GNU-stack
