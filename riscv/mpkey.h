// See LICENSE for license details.
#ifndef _RISCV_MPKEY_H
#define _RISCV_MPKEY_H

#include "decode.h"
#include "config.h"
#include "devices.h"
#include "trap.h"
#include <array>
#include <string>
#include <vector>
#include <map>
#include "debug_rom_defines.h"

class mpkey_t
{
public:
  mpkey_t();
  ~mpkey_t();

  reg_t get_bits();
  void set_register(reg_t value);
  reg_t get_key(size_t index);
  reg_t get_write_disable(size_t index);
  reg_t get_mode();
  void set_mode(reg_t val);
  private:
    reg_t mode;         //  1 bit
    reg_t sw;           // 19 bit
    static const size_t MAX_MPKEYS = 4;
    std::array<reg_t, MAX_MPKEYS> slot_wd; // 1 bit
    std::array<reg_t, MAX_MPKEYS> slot_mpkey; // 10 bit
};

#endif
