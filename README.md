# Hello, World!

Simple "Hello World" example for
**[Infineon XMC2Go](https://www.keil.arm.com/boards/infineon-xmc-2go-v1-d3962c0/projects/)** development board.
This example is configured to print `Hello World` once a second via semihosting to the Telnet console.

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
   Hello, World!
   Hello, World!
   Hello, World!
   ...
   ```

## Going Further

While semihosting requires not hardware configuration and can be easily used for quick debugging, it is not recommended
for production systems (due to intrusive and slow communication). A viable option is to use a UART (serial port)
instead. The following explains how to use the on-chip UART which is available through the Segger J-Link debug adapter
for `printf` output.

### Adding Software Components

To be able to redirect the output to the UART, you need the following software components. The
[Keil Studio User's Guide](https://mdk-packs.github.io/vscode-cmsis-solution-docs/create_app.html#software-components)
explains how to add them.

- CMSIS-Compiler:CORE
- CMSIS-Compiler:STDOUT:Custom
- CMSIS Driver:USART
- Device:RTE_Device

> [!NOTE]
> Check the validation output for further components that may be required.

### Adding User Code

In the **CMSIS** view, click on the **+** sign next to **Application** and select **Add From Component Code Template**:

![Add code template](./images/add-user-code-template.png)

Then, select **CMSIS-Compiler:STDOUT:Custom** which adds a `stdout_user.c` file to the **Application** group. Add this
code in the file:

```c
#include "retarget_stdout.h"
#include "Driver_USART.h"

#include <stdint.h>

extern ARM_DRIVER_USART Driver_USART0;

static ARM_DRIVER_USART * const stdout_usart = &Driver_USART0;
static uint8_t stdout_usart_initialized;

#ifndef STDOUT_USART_BAUDRATE
#define STDOUT_USART_BAUDRATE 115200U
#endif

static int stdout_usart_ensure_initialized (void) {
  int32_t status;

  if (stdout_usart_initialized != 0U) {
    return 0;
  }

  status = stdout_usart->Initialize(NULL);
  if (status != ARM_DRIVER_OK) {
    return -1;
  }

  status = stdout_usart->PowerControl(ARM_POWER_FULL);
  if (status != ARM_DRIVER_OK) {
    return -1;
  }

  status = stdout_usart->Control(
    ARM_USART_MODE_ASYNCHRONOUS |
    ARM_USART_DATA_BITS_8       |
    ARM_USART_PARITY_NONE       |
    ARM_USART_STOP_BITS_1       |
    ARM_USART_FLOW_CONTROL_NONE,
    STDOUT_USART_BAUDRATE
  );
  if (status != ARM_DRIVER_OK) {
    return -1;
  }

  status = stdout_usart->Control(ARM_USART_CONTROL_TX, 1U);
  if (status != ARM_DRIVER_OK) {
    return -1;
  }

  stdout_usart_initialized = 1U;
  return 0;
}

/**
  Put a character to the stdout

  \param[in]   ch  Character to output
  \return          The character written, or -1 on write error.
*/
int stdout_putchar (int ch) {
  uint8_t c;

  if (stdout_usart_ensure_initialized() != 0) {
    return -1;
  }

  /* If caller prints bare '\n', emit CRLF on the wire. */
  if ((uint8_t)ch == (uint8_t)'\n') {
    (void)stdout_putchar('\r');
  }

  /* Serialize by waiting for any previous send to complete. */
  while (stdout_usart->GetStatus().tx_busy != 0U) {
  }

  c = (uint8_t)ch;
  if (stdout_usart->Send(&c, 1U) != ARM_DRIVER_OK) {
    return -1;
  }

  while (stdout_usart->GetStatus().tx_busy != 0U) {
  }

  return ch;
}
```

### Device Configuration

The UART that is connected to the Segger J-Link uses the the ports **P2.1** and **P2.2** on the device. You need to
configure this in the `RTE_Device.h` file.

- In the **CMSIS** view, expand **Device_RTE_Device** and click on the `RTE_Device.h` file. This file is annotated for
  **Configuration Wizard view** which can be enabled by pressing the
  ![Open configuration wozard view](./images/open-conf-wiz-view.png) button at the top right corner.
- In this view, enable `UART0` and set the `UART0_TX_Pin` to `P2_1` and the `UART0_RX_Pin` to `P2_2`.
- Save the file.

### Build and Run

If you now build the application and run it on the target, you need to change the **SERIAL MONITOR** to the following:

- **Monitor Mode**: Serial
- **Port**: the Segger J-Link
- **Baud rate**: 115200

Press **Start Monitoring** to view the `printf` massages.

## More Examples

Similar examples which are pre-configured for the UART output are available on GitHub:

- [Hello_B-U585I-IOT02A](https://github.com/Arm-Examples/Hello_B-U585I-IOT02A)
- [Hello_NUCLEO-G474RE](https://github.com/Arm-Examples/Hello_NUCLEO-G474RE)
- [Hello_NUCLEO-F756ZG](https://github.com/Arm-Examples/Hello_NUCLEO-F756ZG)
- [Hello_LPCXpresso55S69](https://github.com/orgs/Arm-Examples/repositories?q=hello#:~:text=Hello_LPCXpresso55S69)
- [Hello_FRDM-K32L3A6](https://github.com/Arm-Examples/Hello_FRDM-K32L3A6)
