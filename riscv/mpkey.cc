// See LICENSE for license details.

#include "mpkey.h"
#include "extension.h"
#include "common.h"
#include "config.h"
#include "simif.h"
#include "mmu.h"
#include "disasm.h"
#include <array>
#include <cinttypes>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <assert.h>
#include <limits.h>
#include <stdexcept>
#include <algorithm>

mpkey_t::mpkey_t()
  :
   mode(0),
   sw(0),
   slot_mpkey({{0}}),
   slot_wd({{0}})  {
}
mpkey_t::~mpkey_t() {}

reg_t mpkey_t::get_mode() {
  return mode;
}
void mpkey_t::set_mode(reg_t val) {
  mode = val;
}

reg_t mpkey_t::get_bits() {
  reg_t bitstring = 0;
  bitstring |= (reg_t) (mode & 0x1);
  bitstring <<= 19;
  bitstring |= (reg_t) (sw & (reg_t) 0x7FFFF);
  for (size_t i = MAX_MPKEYS; i > 0; i--) {
    bitstring <<= 1;
    bitstring |= (reg_t) (slot_wd.at(i - 1) & (reg_t) 0x1);
    bitstring <<= 10;
    bitstring |= (reg_t) (slot_mpkey.at(i - 1) & (reg_t) 0x3FF);
  }
  // printf("Returning %llx\n", bitstring);
  // printf("mode = %llx;\n sw = %llx;\n slot_wd[0] = %llx; slot_mpkey[0] = %llx;\n slot_wd[1] = %llx; slot_mpkey[1] = %llx;\n slot_wd[2] = %llx; slot_mpkey[2] = %llx;\n slot_wd[3] = %llx; slot_mpkey[3] = %llx;\n",
  //   mode, sw, slot_wd.at(0), slot_mpkey.at(0), slot_wd.at(1), slot_mpkey.at(1), slot_wd.at(2), slot_mpkey.at(2), slot_wd.at(3), slot_mpkey.at(3));
  return bitstring;
}

void mpkey_t::set_register(reg_t value) {
  for (size_t i = 0; i < MAX_MPKEYS; i++) {
    slot_mpkey.at(i) = (value & 0x3FF);
    value >>= 10;
    slot_wd.at(i) = (value & 0x1);
    value >>= 1;
  }

  //TODO this breaks if MAX_MPKEYS != 4
  sw = (value & 0x7FFFF);
  value >>= 19;

  mode = (value & 0x1);
  //value >>= 1;
  // last one without shift
}

reg_t mpkey_t::get_key(size_t index) {
  return slot_mpkey.at(index);
}
reg_t mpkey_t::get_write_disable(size_t index) {
  return slot_wd.at(index);
}
