section .text
_strlen:
  xor rcx, rcx
  mov rax, -1
_strlen_loop:
  inc rax
  mov cl, byte[rdi + rax]
  cmp cl, 0
  jnz _strlen_loop
  ret
global _add_whole_same_length
_add_whole_same_length:
  push r12
  call _strlen
  lea rcx, [rax - 1]
  xor r11, r11
  xor r10b, r10b
_add_whole_same_length_loop_1:
  mov r12b, byte[rdi + rcx]
  add r12b, byte[rsi + rcx]
  sub r12b, 48
  test r10b, r10b
  jz _after_add_whole_same_length_if_1
  xor r10b, r10b
  inc r12b
_after_add_whole_same_length_if_1:
  cmp r12b, 57
  jle _after_add_whole_same_length_if_2
  mov r10b, 1
  sub r12b, 10
_after_add_whole_same_length_if_2:
  mov byte[rdx + r11], r12b
  inc r11
  mov r8, rcx
  dec rcx
  cmp r8, 0
  jg _add_whole_same_length_loop_1
  test r10b, r10b
  jz _after_add_whole_same_length_if_3
  mov byte[rdx + r11], 49
  inc rax
_after_add_whole_same_length_if_3:
  xor r11, r11
  mov rcx, rax
  shr rcx, 1
_add_whole_same_length_loop_2:
  mov r8b, byte[rdx + r11]
  mov r12, rax
  sub r12, r11
  lea r12, [r12 + rdx - 1]
  mov r9b, byte[r12]
  mov byte[rdx + r11], r9b
  mov byte[r12], r8b
  inc r11
  cmp r11, rcx
  js _add_whole_same_length_loop_2
  mov byte[rdx + rax], 0
  pop r12
  ret
global _add_whole
_add_whole:
  push r12
  push r13
  push r14
  call _strlen
  push rax
  push rdi
  mov rdi, rsi
  call _strlen
  mov r8, rax
  pop rdi
  pop rax
  mov r9, r8
  cmp rax, r8
  jle _after_add_whole_if_1
  mov r9, rax
_after_add_whole_if_1:
  xor r10b, r10b
  xor rcx, rcx
_add_whole_loop_1:
  lea r13, [rcx + 1]
  mov r11b, 48
  mov r12b, r11b
  cmp rax, r13
  js _after_add_whole_if_2
  lea r14, [rdi + rax]
  sub r14, rcx
  dec r14
  mov r11b, byte[r14]
_after_add_whole_if_2:
  cmp r8, r13
  js _after_add_whole_if_3
  lea r14, [rsi + r8]
  sub r14, rcx
  dec r14
  mov r12b, byte[r14]
_after_add_whole_if_3:
  mov r13b, r11b
  add r13b, r12b
  sub r13b, 48
  test r10b, r10b
  jz _after_add_whole_if_4
  xor r10b, r10b
  inc r13b
_after_add_whole_if_4:
  cmp r13b, 57
  jle _after_add_whole_if_5
  sub r13b, 10
  mov r10b, 1
_after_add_whole_if_5:
  mov byte[rdx + rcx], r13b
  inc rcx
  cmp rcx, r9
  js _add_whole_loop_1
  test r10b, r10b
  jz _after_add_whole_if_6
  mov byte[rdx + rcx], 49
  inc r9
_after_add_whole_if_6:
  xor rcx, rcx
  mov r11, r9
  shr r11, 1
_add_whole_loop_2:
  lea r12, [rdx + r9]
  sub r12, rcx
  dec r12
  mov r8b, byte[rdx + rcx]
  mov r10b, byte[r12]
  mov byte[rdx + rcx], r10b
  mov byte[r12], r8b
  inc rcx
  cmp rcx, r11
  js _add_whole_loop_2
  mov byte[rdx + r9], 0
  pop r14
  pop r13
  pop r12
  ret