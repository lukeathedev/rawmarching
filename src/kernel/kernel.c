void some_func() {
  return;
}

void print(int colour, const char *string, int* x, int* y)
{
    volatile char* video = (volatile char* ) 0xB8000;
    video +=  ((*y) * 160) + (*x);

    while (*string != 0)
    {
        *video++ = *string++;
        *video++ = colour;
    }
}

void main() {
  int x = 0;
  int y = 5;

  print(0b00101111, "[INFO]  Kernel called at 0x1000", &x, &y);
  y++;
  print(0b00000111, "[INFO]  Switching to VGA 640x480 16-color", &x, &y);
}
