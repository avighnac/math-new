section .text
global _assembly_strlen
_assembly_strlen:
  ; Input:
  ;   - char *str -> rdi

  ; Registers used:
  ;   - rcx

  xor    rcx, rcx
  mov    rax, -1
_assembly_strlen_loop:
  inc    rax
  mov    cl, byte[rdi + rax]
  test   cl, cl
  jnz    _assembly_strlen_loop
  ret