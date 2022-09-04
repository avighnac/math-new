extern _assembly_strlen

global _subtract_whole_same_length
_subtract_whole_same_length:
  call   _assembly_strlen
  xor    cl, cl
  lea    r8, [rax - 1]
_subtract_whole_same_length_loop_1:
  mov    r9b, byte [rdi + r8]
  sub    r9b, cl
  cmp    r9b, byte [rsi + r8]
  js     _subtract_whole_same_length_else_1
  mov    byte [rdx + r8], r9b
  mov    r10b, byte [rsi + r8]
  sub    byte [rdx + r8], r10b
  add    byte [rdx + r8], 48
  jmp    _after_subtract_whole_same_length_else_1
_subtract_whole_same_length_else_1:
  mov    byte [rdx + r8], 58
  add    byte [rdx + r8], r9b
  mov    r10b, byte [rsi + r8]
  sub    byte [rdx + r8], r10b
_after_subtract_whole_same_length_else_1:
  xor    cl, cl
  cmp    r9b, byte [rsi + r8]
  setl   cl
  dec    r8
  lea    r9, [r8 + 1]
  cmp    r9, 0
  jg     _subtract_whole_same_length_loop_1
  mov    byte [rdx + rax], 0
  cmp    byte [rdx], 48
  jge    _after_subtract_whole_same_length_if_2
  mov    r8, 1
_subtract_whole_same_length_loop_2:
  mov    r9b, byte [rdx + r8]
  mov    byte [rdx + r8 - 1], r9b
  inc    r8
  cmp    r8, rax
  js     _subtract_whole_same_length_loop_2
  mov    byte [rdx + rax - 1], 0
  mov    cl, 1
_after_subtract_whole_same_length_if_2:
  push   rdi
  push   rcx
  mov    rdi, rdx
  call   _assembly_strlen
  pop    rcx
  pop    rdi
  test   cl, cl
  jz     _subtract_whole_same_length_return
  mov    byte [rdx + rax + 1], 0
  mov    r10b, 106
  sub    r10b, byte [rdx + rax - 1]
  mov    byte [rdx + rax], r10b
  lea    r8, [rax - 2]
_subtract_whole_same_length_loop_3:
  mov    r10b, 105
  sub    r10b, byte [rdx + r8]
  mov    byte [rdx + r8 + 1], r10b
  dec    r8
  lea    r9, [r8 + 1]
  cmp    r9, 0
  jg     _subtract_whole_same_length_loop_3
  mov    byte [rdx], 2DH
_subtract_whole_same_length_return: ret