# Hello, World!

Simple "Hello World" example for
[**Infineon XMC2Go**](hhttps://www.keil.arm.com/boards/infineon-xmc-2go-v1-d3962c0/projects/) development board.
This example is configured to print `Hello World` and a counter value via semihosting to the Telnet console.

Other [serial I/O message options](https://github.com/Arm-Examples/.github/blob/main/profile/Serial.md) can be
configured as well (refer to [Going Further](#going-further)).

## Quick Start

1. Install [Keil Studio for VS Code](https://marketplace.visualstudio.com/items?itemName=Arm.keil-studio-pack) from the
   VS Code marketplace.
2. Clone this Git repository into a VS Code workspace.
3. The related tools and software packs are downloaded and installed. Review progress with
   *View - Output - CMSIS Solution*.
4. In the CMSIS view, use the
   [Action buttons](https://github.com/ARM-software/vscode-cmsis-csolution?tab=readme-ov-file#action-buttons) to build,
   load and debug the example on the hardware.
5. In the [VS Code Panel](https://code.visualstudio.com/api/ux-guidelines/panel), click on **SERIAL MONITOR**. Select
   the **Monitor Mode** "TCP" and set **Host** to `localhost` and **Port** to `4444`. Observe the output:

   ```txt
   SEGGER J-Link GDB Server V9.10 - Terminal output channel
   Hello, World! 0
   Hello, World! 1
   Hello, World! 2
   Hello, World! 3
   Hello, World! 4
   ...
   ```

## Going Further

While semihosting requires not hardware configuration and can be easily used for quick debugging, it is not recommended
for production systems (due to intrusive and slow communication). A viable option is to use a UART (serial port)
instead.