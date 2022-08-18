/***************************************************************************
 * ARM Stack Unwinder, Michael.McTernan.2001@cs.bris.ac.uk
 * Updated, adapted and several bug fixes on 2018 by Eduardo José Tagle
 *
 * This program is PUBLIC DOMAIN.
 * This means that there is no copyright and anyone is able to take a copy
 * for free and use it as they wish, with or without modifications, and in
 * any context, commercially or otherwise. The only limitation is that I
 * don't guarantee that the software is fit for any purpose or accept any
 * liability for its use or misuse - this software is without warranty.
 ***************************************************************************
 * File Description: Utility functions to access memory
 **************************************************************************/

#if defined(__arm__) || defined(__thumb__)

#include "unwmemaccess.h"
#include "../../../inc/MarlinConfig.h"

/* Validate address */

#ifdef ARDUINO_ARCH_SAM

  // For DUE, valid address ranges are
  //  SRAM  (0x20070000 - 0x20088000) (96kb)
  //  FLASH (0x00080000 - 0x00100000) (512kb)
  //
  #define START_SRAM_ADDR   0x20070000
  #define END_SRAM_ADDR     0x20088000
  #define START_FLASH_ADDR  0x00080000
  #define END_FLASH_ADDR    0x00100000

#elif defined(TARGET_LPC1768)

  // For LPC1769:
  //  SRAM  (0x10000000 - 0x10008000) (32kb)
  //  FLASH (0x00000000 - 0x00080000) (512kb)
  //
  #define START_SRAM_ADDR   0x10000000
  #define END_SRAM_ADDR     0x10008000
  #define START_FLASH_ADDR  0x00000000
  #define END_FLASH_ADDR    0x00080000

#elif 0

  // For STM32F103CBT6
  //  SRAM  (0x20000000 - 0x20005000) (20kb)
  //  FLASH (0x00000000 - 0x00020000) (128kb)
  //
  #define START_SRAM_ADDR   0x20000000
  #define END_SRAM_ADDR     0x20005000
  #define START_FLASH_ADDR  0x00000000
  #define END_FLASH_ADDR    0x00020000

#elif defined(__STM32F1__) || defined(STM32F1xx) || defined(STM32F0xx)

  // For STM32F103ZET6/STM32F103VET6/STM32F0xx
  //  SRAM  (0x20000000 - 0x20010000) (64kb)
  //  FLASH (0x00000000 - 0x00080000) (512kb)
  //
  #define START_SRAM_ADDR   0x20000000
  #define END_SRAM_ADDR     0x20010000
  #define START_FLASH_ADDR  0x00000000
  #define END_FLASH_ADDR    0x00080000

#elif defined(STM32F4) || defined(STM32F4xx)

  // For STM32F407VET
  //  SRAM  (0x20000000 - 0x20030000) (192kb)
  //  FLASH (0x08000000 - 0x08080000) (512kb)
  //
  #define START_SRAM_ADDR   0x20000000
  #define END_SRAM_ADDR     0x20030000
  #define START_FLASH_ADDR  0x08000000
  #define END_FLASH_ADDR    0x08080000

#elif MB(REMRAM_V1, NUCLEO_F767ZI)

  // For STM32F765VI in RemRam v1
  //  SRAM  (0x20000000 - 0x20080000) (512kb)
  //  FLASH (0x08000000 - 0x08200000) (2048kb)
  //
  #define START_SRAM_ADDR   0x20000000
  #define END_SRAM_ADDR     0x20080000
  #define START_FLASH_ADDR  0x08000000
  #define END_FLASH_ADDR    0x08200000

#elif defined(__MK20DX256__)

  // For MK20DX256 in TEENSY 3.1 or TEENSY 3.2
  //  SRAM  (0x1FFF8000 - 0x20008000) (64kb)
  //  FLASH (0x00000000 - 0x00040000) (256kb)
  //
  #define START_SRAM_ADDR   0x1FFF8000
  #define END_SRAM_ADDR     0x20008000
  #define START_FLASH_ADDR  0x00000000
  #define END_FLASH_ADDR    0x00040000

#elif defined(__MK64FX512__)

  // For MK64FX512 in TEENSY 3.5
  //  SRAM  (0x1FFF0000 - 0x20020000) (192kb)
  //  FLASH (0x00000000 - 0x00080000) (512kb)
  //
  #define START_SRAM_ADDR   0x1FFF0000
  #define END_SRAM_ADDR     0x20020000
  #define START_FLASH_ADDR  0x00000000
  #define END_FLASH_ADDR    0x00080000

#elif defined(__MK66FX1M0__)

  // For MK66FX1M0 in TEENSY 3.6
  //  SRAM  (0x1FFF0000 - 0x20030000) (256kb)
  //  FLASH (0x00000000 - 0x00140000) (1.25Mb)
  //
  #define START_SRAM_ADDR   0x1FFF0000
  #define END_SRAM_ADDR     0x20030000
  #define START_FLASH_ADDR  0x00000000
  #define END_FLASH_ADDR    0x00140000

#elif defined(__IMXRT1062__)

  // For IMXRT1062 in TEENSY 4.0/4/1
  //  ITCM (rwx):  ORIGIN = 0x00000000, LENGTH = 512K
  //  DTCM (rwx):  ORIGIN = 0x20000000, LENGTH = 512K
  //  RAM (rwx):   ORIGIN = 0x20200000, LENGTH = 512K
  //  FLASH (rwx): ORIGIN = 0x60000000, LENGTH = 1984K
  //
  #define START_SRAM_ADDR   0x00000000
  #define END_SRAM_ADDR     0x20280000
  #define START_FLASH_ADDR  0x60000000
  #define END_FLASH_ADDR    0x601F0000

#elif defined(__SAMD51P20A__)

  // For SAMD51x20, valid address ranges are
  //  SRAM  (0x20000000 - 0x20040000) (256kb)
  //  FLASH (0x00000000 - 0x00100000) (1024kb)
  //
  #define START_SRAM_ADDR   0x20000000
  #define END_SRAM_ADDR     0x20040000
  #define START_FLASH_ADDR  0x00000000
  #define END_FLASH_ADDR    0x00100000

#endif

static bool validate_addr(uint32_t addr) {

  // Address must be in SRAM range
  if (addr >= START_SRAM_ADDR && addr < END_SRAM_ADDR)
    return true;

  // Or in FLASH range
  if (addr >= START_FLASH_ADDR && addr < END_FLASH_ADDR)
    return true;

  return false;
}

bool UnwReadW(const uint32_t a, uint32_t *v) {
  if (!validate_addr(a))
    return false;

  *v = *(uint32_t *)a;
  return true;
}

bool UnwReadH(const uint32_t a, uint16_t *v) {
  if (!validate_addr(a))
    return false;

  *v = *(uint16_t *)a;
  return true;
}

bool UnwReadB(const uint32_t a, uint8_t *v) {
  if (!validate_addr(a))
    return false;

  *v = *(uint8_t *)a;
  return true;
}

#endif // __arm__ || __thumb__
