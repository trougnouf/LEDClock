#include <stdio.h>
#include <stdlib.h>

unsigned char reverse(unsigned char);

int main()
{

  printf("{%u, %u, %u, %u, %u, %u, %u, %u, %u, %u},{%u, %u, %u, %u, %u, %u, %u, %u, %u, %u},{%u, %u, %u, %u, %u, %u, %u, %u, %u, %u},{%u, %u, %u, %u, %u, %u, %u, %u, %u, %u},{%u, %u, %u, %u, %u, %u, %u, %u, %u, %u},{%u, %u, %u, %u, %u, %u, %u, %u, %u, %u},{%u, %u, %u, %u, %u, %u, %u, %u, %u, %u},{%u, %u, %u, %u, %u, %u, %u, %u, %u, %u},{%u, %u, %u, %u, %u, %u, %u, %u, %u, %u},{%u, %u, %u, %u, %u, %u, %u, %u, %u, %u}}", reverse(0x7e), reverse(0xff), reverse(0xff), reverse(0xe7), reverse(0xc3), reverse(0xc3), reverse(0xe7), reverse(0xff), reverse(0xff), reverse(0x7e),reverse(0x3e), reverse(0x3e), reverse(0x3c), reverse(0x3c), reverse(0x3c), reverse(0x3c), reverse(0x3c), reverse(0x3c), reverse(0x7e), reverse(0x7e),reverse(0x3c), reverse(0x7e), reverse(0xe7), reverse(0xe3), reverse(0x71), reverse(0x38), reverse(0x1c), reverse(0x0e), reverse(0xff), reverse(0xff),reverse(0x7f), reverse(0xff), reverse(0xe0), reverse(0xc0), reverse(0xfe), reverse(0xfe), reverse(0xc0), reverse(0xe0), reverse(0xff), reverse(0x7f),reverse(0x06), reverse(0x07), reverse(0x67), reverse(0x67), reverse(0x67), reverse(0xff), reverse(0xff), reverse(0xff), reverse(0x60), reverse(0x60),reverse(0xff), reverse(0xff), reverse(0x07), reverse(0x3f), reverse(0x7f), reverse(0xf0), reverse(0xe0), reverse(0xf3), reverse(0xff), reverse(0x7e),reverse(0x7e), reverse(0xff), reverse(0xc7), reverse(0x07), reverse(0x7f), reverse(0xff), reverse(0xe7), reverse(0xe7), reverse(0xff), reverse(0x7e),reverse(0xff), reverse(0xff), reverse(0xff), reverse(0xe0), reverse(0xf0), reverse(0x78), reverse(0x3c), reverse(0x1e), reverse(0x0f), reverse(0x07),reverse(0x7e), reverse(0xff), reverse(0xe7), reverse(0xe7), reverse(0x7e), reverse(0xff), reverse(0xe7), reverse(0xe7), reverse(0xff), reverse(0x7e),reverse(0x7e), reverse(0xff), reverse(0xe7), reverse(0xe7), reverse(0xff), reverse(0xfe), reverse(0xc0), reverse(0xe3), reverse(0xff), reverse(0x7e));

}

// sth@stackoverflow
unsigned char reverse(unsigned char b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}