/*
int compare_offset(struct values *values[], int i, int j, int k, struct values *avalue) {
	return k < values[i][j].len && values[i][j].offset[k] == avalue->offset[k];
}
*/

	.text
	.global	compare_offset

	.equ VALUE_SIZE, 16
	.equ OFFSET_OFS, 8
	.equ LENMASK, 255
# value structure = 1 byte len, 1 byte padding, 2 byte base, 4 byte padding, 8 byte offset pointer
# rdi = *values[], esi = i, edx = j, ecx = k, r8 = *avalue
compare_offset:
	mov $VALUE_SIZE, %rax
	mul %rdx
    mov (%rdi, %rsi, 8), %r9  # r9 = values[i]
    mov (%r9, %rax, 1), %r10 # r10 = values[i][j] 	
	and $LENMASK, %r10	# remove base value to get .len
    cmp %r10d, %ecx                       
    jae L0_compare_offset    # k < values[i][j].len
    mov OFFSET_OFS(%r9, %rax, 1), %r9 # r9 = values[i][j].offset     
	mov (%r9, %rcx, 2), %r9	 # r9 = values[i][j].offset[k]
	mov OFFSET_OFS(%r8), %r10		 # r10 = avalue->offset
	mov (%r10, %rcx, 2), %r10	# r10 = avalue->offset[k]
	cmp %r9w, %r10w				
    jne L0_compare_offset     # values[i][j].offset[k] == avalue->offset[k];          
    mov $1, %rax                        
    ret
L0_compare_offset:
    mov $0, %rax                         
    ret

	.section .note.GNU-stack
