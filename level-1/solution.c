#include <stdio.h>
#include <string.h>

typedef unsigned int uint;
typedef unsigned char byte;
typedef unsigned long long ulonglong;

uint rotate_left(unsigned int num_to_rotate, unsigned char places_to_shift)

{
  return num_to_rotate << (places_to_shift & 0x1f) | num_to_rotate >> 0x20 - (places_to_shift & 0x1f);
}

uint compute_serial(char *entered_username)

{
  size_t entered_username_len;
  ulonglong i;
  uint char_aggregated_sum;

  char_aggregated_sum = 0;
  entered_username_len = strlen(entered_username);
  for (i = 0; i < entered_username_len; i = i + 1)
  {
    char_aggregated_sum = char_aggregated_sum + (uint)(byte)entered_username[i] * ((int)i + 1);
  }
  return rotate_left(char_aggregated_sum ^ 0xc001c0de, 5);
}

int main(int argc, char *argv[])

{
  if (argc < 2)
  {
    printf("Wrong usage. Missing parameter \"username\". E.g., `./solution eliel`\n");
    return 1;
  }
  char *username = argv[1];
  uint computed_user_serial = compute_serial(username);
  printf("Serial (8 hex digits) computed from %s: %08X\n", username, computed_user_serial);
  return 0;
}