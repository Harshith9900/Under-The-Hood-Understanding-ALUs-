# Under the Hood: Understanding ALUs
A software simulation of a 32-bit CPU Arithmetic Logic Unit (ALU) using pure C++ bitwise operations.

## 32-Bit ALU Simulator (C++)
This project is a software simulation of a physical CPU's Arithmetic Logic Unit (ALU). Instead of relying on standard C++ arithmetic operators (`+`, `-`, `*`, `/`), this simulator manually calculates operations using pure bitwise logic and shift operators, mimicking the actual physical hardware pathways of a processor.

## Features
* **Bitwise Arithmetic:** Custom functions for addition, two's complement subtraction, and Shift-and-Add multiplication.
* **Binary Converters:** Includes custom string-to-binary and integer-to-binary converters with hardware sign extension to handle negative 32-bit integers perfectly.
* **Hardware Status Flags:** Calculates and outputs standard processor flags based on mathematical results:
  * **Z (Zero Flag):** Triggers if the math result is exactly 0. This flag is used when we do stuff like `if (a == b)` where under the hood it just does `a - b` then checks the Z flag. 
  * **S (Sign Flag):** Triggers if the math result is negative.
  * **O (Overflow Flag):** Triggers if memory limits are breached (e.g., Positive + Positive = Negative).

## How It Works
The core of the simulator relies on a simulated half-adder circuit using `AND` (`&`) and `XOR` (`^`) gates to calculate sums and carries, combined with bitwise shifting (`<<`, `>>`) to move data through the virtual registers.

