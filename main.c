/*-----------------------------------------------------------------------------
 * Copyright (c) 2023-2026 Arm Limited (or its affiliates).
 * All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *---------------------------------------------------------------------------*/

#include "RTE_Components.h"
#include CMSIS_device_header

#include <stdio.h>

/*-----------------------------------------------------------------------------
 * Minimal “Hello World” example.
 *
 * Notes for embedded targets:
 * - This uses `printf`, so your toolchain/project must provide a backend for
 *   stdout (e.g., UART retargeting, SWO/ITM, semihosting, or a debug-probe
 *   console). If stdout is not routed anywhere, the code will still run but you
 *   won't see output.
 * - For production firmware, `printf` can be expensive (flash/RAM/time). It is
 *   kept here for clarity and bring-up verification.
 *---------------------------------------------------------------------------*/

int main() {
    /*-------------------------------------------------------------------------
     * Print a few lines so you can quickly verify that:
     * - startup code runs correctly,
     * - clocks/stack/heap are sane,
     * - and stdout routing is configured as expected.
     *-----------------------------------------------------------------------*/
    for (int count = 0; count < 10; count++) {
        /* CRLF for terminals that expect \r\n line endings. */
        printf("Hello, World! %d\r\n", count);
    }

    /*-------------------------------------------------------------------------
     * Many bare-metal projects keep running forever (e.g., while (1) { ... }).
     * This example simply returns from `main` after printing.
     *-----------------------------------------------------------------------*/
}
