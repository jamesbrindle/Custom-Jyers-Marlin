/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#ifdef TARGET_LPC1768

#include "../../inc/MarlinConfigPre.h"
#include "MarlinSerial.h"

#if ANY_SERIAL_IS(0)
  MSerialT MSerial(true, LPC_UART0);
  extern "C" void UART0_IRQHandler() { MSerial.IRQHandler(); }
#endif
#if ANY_SERIAL_IS(1)
  MSerialT MSerial1(true, (LPC_UART_TypeDef *) LPC_UART1);
  extern "C" void UART1_IRQHandler() { MSerial1.IRQHandler(); }
#endif
#if ANY_SERIAL_IS(2)
  MSerialT MSerial2(true, LPC_UART2);
  extern "C" void UART2_IRQHandler() { MSerial2.IRQHandler(); }
#endif
#if ANY_SERIAL_IS(3)
  MSerialT MSerial3(true, LPC_UART3);
  extern "C" void UART3_IRQHandler() { MSerial3.IRQHandler(); }
#endif

#endif // TARGET_LPC1768
