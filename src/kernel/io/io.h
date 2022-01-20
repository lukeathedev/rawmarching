#ifndef IO_H
#define IO_H

#include <stdint.h>

// TODO: make inline
uint8_t inb(uint16_t port);
// static inline uint16_t inw(uint16_t port);

void outb(uint16_t port, uint8_t val);
// static inline void outw(uint16_t port, uint16_t val);

#endif
