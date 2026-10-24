#include <stdio.h>
#include <string.h>

typedef unsigned int uint;
typedef unsigned char byte;
typedef unsigned long long ulonglong;
typedef unsigned short ushort;

uint rotate_left(ushort num_to_rotate, byte places_to_shift)

{
  return (int)(uint)num_to_rotate >> (0x10 - (places_to_shift & 0xf) & 0x1f) | (uint)num_to_rotate << (places_to_shift & 0xf);
}

ushort username_to_serial_part(char *username, ushort serial_seed)

{
  uint rotated;
  size_t username_len;
  ulonglong i;
  ushort serial;

  username_len = strlen(username);
  serial = serial_seed;
  for (i = 0; i < username_len; i = i + 1)
  {
    rotated = rotate_left((serial ^ (byte)username[i]) * -0x61c9, 3);
    serial = (ushort)rotated;
  }
  return serial;
}

void set_complete_serial(char *username, ushort computed_serial[4])

{
  computed_serial[0] = username_to_serial_part(username, 0x1234);
  computed_serial[1] = username_to_serial_part(username, 0xabcd);
  computed_serial[2] = username_to_serial_part(username, 0x7777);
  computed_serial[3] = computed_serial[0] ^ computed_serial[1] ^ computed_serial[2];
}

int main(int argc, char *argv[])

{
  if (argc < 2)
  {
    printf("Wrong usage. Missing parameter \"username\". E.g., `./solution eliel`\n");
    return 1;
  }
  char *username = argv[1];
  ushort computed_serial[4];
  set_complete_serial(username, computed_serial);
  printf("Serial (format XXXX-XXXX-XXXX-YYYY) computed from %s: %04x-%04x-%04x-%04x\n", username, computed_serial[0], computed_serial[1], computed_serial[2], computed_serial[3]);
  return 0;
}