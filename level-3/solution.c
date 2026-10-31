#include <stdio.h>

typedef unsigned int uint;
typedef unsigned char byte;
typedef unsigned long long ulonglong;
typedef unsigned short ushort;

uint rotate_left(unsigned int num_to_rotate, unsigned char places_to_shift)

{
  return num_to_rotate << (places_to_shift & 0x1f) | num_to_rotate >> 0x20 - (places_to_shift & 0x1f);
}

uint mix_chars_to_num(char *username_buffer)

{
  byte *cursor;
  uint mixed_num;

  mixed_num = 0x1505;
  for (cursor = (byte *)username_buffer; *cursor != 0; cursor = cursor + 1)
  {
    mixed_num = (uint)*cursor ^ mixed_num * 0x21;
  }
  return mixed_num;
}

uint mix_num_with_seed(uint num, byte seed)

{
  uint uVar1;

  uVar1 = rotate_left(num ^ seed, 7);
  return uVar1 + 0x9e3779b9 ^ uVar1 + 0x9e3779b9 >> 0xd;
}

void gen_password(byte *username_buffer, byte *password_seed, char *password_buffer_start)

{
  int i;
  uint gen_password;

  gen_password = mix_chars_to_num(username_buffer);
  for (i = 0; i < 8; i = i + 1)
  {
    gen_password = mix_num_with_seed(gen_password, password_seed[i]);
  }
  uint rotated_num = rotate_left(gen_password ^ 0xdec0ded1, 0xb);
  snprintf(password_buffer_start, 17, "%08X%08X", gen_password, rotated_num);
  return;
}

void gen_password_seed(char *text_key, int chars_text_key_used, byte *bytes_to_scramble, int bytes_to_scramble_count)

{
  byte abStack_118[258];
  byte local_16;
  byte local_15;
  int local_14;
  uint local_10;
  uint local_c;

  local_10 = 0;
  for (local_c = 0; (int)local_c < 0x100; local_c = local_c + 1)
  {
    abStack_118[(int)local_c] = (byte)local_c;
  }
  for (local_c = 0; (int)local_c < 0x100; local_c = local_c + 1)
  {
    local_10 = (uint)(byte)text_key[(int)local_c % chars_text_key_used] + abStack_118[(int)local_c] + local_10 & 0xff;
    local_16 = abStack_118[(int)local_c];
    abStack_118[(int)local_c] = abStack_118[(int)local_10];
    abStack_118[(int)local_10] = local_16;
  }
  local_10 = 0;
  local_c = 0;
  for (local_14 = 0; local_14 < bytes_to_scramble_count; local_14 = local_14 + 1)
  {
    local_c = local_c + 1 & 0xff;
    local_10 = local_10 + abStack_118[(int)local_c] & 0xff;
    local_15 = abStack_118[(int)local_c];
    abStack_118[(int)local_c] = abStack_118[(int)local_10];
    abStack_118[(int)local_10] = local_15;
    *(byte *)(bytes_to_scramble + local_14) = *(byte *)(bytes_to_scramble + local_14) ^ abStack_118[(int)(uint)(byte)(abStack_118[(int)local_10] + abStack_118[(int)local_c])];
  }
  return;
}

int main(int argc, char *argv[])

{
  if (argc < 2)
  {
    printf("Wrong usage. Missing parameter \"username\". E.g., `./solution eliel`\n");
    return 1;
  }
  char *username = argv[1];
  char *text_key = "RE-WIN!!";
  int chars_text_key_used = 8;
  byte password_seed[8] = {0x4a, 0x8d, 0x50, 0x3c, 0x60, 0x4c, 0x04, 0x5c};
  int bytes_to_scramble_count = 8;
  gen_password_seed(text_key, chars_text_key_used, password_seed, bytes_to_scramble_count);
  char generated_password[17];
  gen_password(username, password_seed, generated_password);
  printf("Password computed from %s: %s\n", username, generated_password);
  return 0;
}
