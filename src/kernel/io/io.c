#include <stdint.h>

#include "io.h"

uint8_t inb(uint16_t port) {
  uint8_t ret;
  asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
  return ret;
}

// static inline uint16_t inw(uint16_t port);

void outb(uint16_t port, uint8_t val) {
  asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}
