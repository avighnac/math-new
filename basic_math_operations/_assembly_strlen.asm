section .text
global _assembly_strlen
_assembly_strlen:
  xor    rcx, rcx
  mov    rax, -1
_assembly_strlen_loop:
  inc    rax
  mov    cl, byte[rdi + rax]
  cmp    cl, 0
  jnz    _assembly_strlen_loop
  ret