## 📘 LED7SEG & 74HC595 Shift Register

### 🔦 1. LED7SEG (Common Cathode)

- **Forward voltage per segment**: ~2V
- **Max forward current**: ~20mA/segment
- **Segment ON logic**: HIGH (LED turns ON), LOW (OFF)

| Segment | Description  |
|---------|-------|
| A–G     | Display segments |
| DP      | Decimal point |
| COM     | GND pin |

---

### 🔢 7-Segment Encoding Table

| Character | F | A | E | D | DP | B | G | C | HEX Code |
|-----------|---|---|---|---|----|---|---|---|-------------|
| 0         | 1 | 1 | 1 | 1 | 0  | 1 | 0 | 1 | 0xF5  |
| 1         | 0 | 0 | 0 | 0 | 0  | 1 | 0 | 1 | 0x05  |
| 2         | 0 | 1 | 1 | 1 | 0  | 1 | 1 | 0 | 0x76  |
| 3         | 0 | 1 | 0 | 1 | 0  | 1 | 1 | 1 | 0x57  |
| 4         | 1 | 0 | 0 | 0 | 0  | 1 | 1 | 1 | 0x87  |
| 5         | 1 | 1 | 0 | 1 | 0  | 0 | 1 | 1 | 0xD3  |
| 6         | 1 | 1 | 1 | 1 | 0  | 0 | 1 | 1 | 0xF3  |
| 7         | 0 | 1 | 0 | 0 | 0  | 1 | 0 | 1 | 0x45  |
| 8         | 1 | 1 | 1 | 1 | 0  | 1 | 1 | 1 | 0xF7  |
| 9         | 1 | 1 | 0 | 1 | 0  | 1 | 1 | 1 | 0xD7  |
| A         | 1 | 1 | 1 | 0 | 0  | 1 | 1 | 1 | 0xE7  |
| b         | 1 | 0 | 1 | 1 | 0  | 0 | 1 | 1 | 0xF7  |
| C         | 1 | 1 | 1 | 1 | 0  | 0 | 0 | 0 | 0xF0  |
| d         | 0 | 1 | 1 | 1 | 0  | 1 | 1 | 1 | 0xF5  |
| E         | 1 | 1 | 1 | 1 | 0  | 0 | 1 | 0 | 0xF2  |
| F         | 1 | 1 | 1 | 0 | 0  | 0 | 1 | 0 | 0xE2  |
| H         | 1 | 0 | 1 | 0 | 0  | 1 | 1 | 1 | 0xA7  |
| I         | 0 | 0 | 0 | 0 | 0  | 1 | 1 | 1 | 0x05  |
| J         | 0 | 1 | 0 | 1 | 0  | 0 | 0 | 1 | 0x35  |
| L         | 1 | 0 | 1 | 1 | 0  | 0 | 0 | 0 | 0xB0  |
| n         | 0 | 0 | 1 | 0 | 0  | 0 | 1 | 1 | 0xE5  |
| O         | 1 | 1 | 1 | 1 | 0  | 1 | 0 | 1 | 0xF5  |
| P         | 1 | 1 | 1 | 0 | 0  | 1 | 1 | 0 | 0xE6  |
| S         | 1 | 1 | 0 | 1 | 0  | 0 | 1 | 1 | 0xD3  |
| U         | 1 | 1 | 1 | 1 | 0  | 1 | 0 | 1 | 0xB5  |
| (blank)   | 0 | 0 | 0 | 0 | 0  | 0 | 0 | 0 | 0x00  |


---

### 🧠 2. 74HC595 - 8 bit Shift Register
- [74HC595 Timing Diagram – Nexperia](https://assets.nexperia.com/documents/data-sheet/74HC_HCT595.pdf)
**74HC595** is an 8-bit serial-in, parallel-out shift register with a storage register and tri-state outputs. It allows expanding output pins using only **3 GPIOs**.

| Pin | Name    | Mô tả |
|------|--------|------|
| DS   | Data   | Data input |
| SHCP | Shift  | Shifts data on rising edge |
| STCP | Latch  | Transfers data to outputs on rising edge |
| Q0–Q7| Output | Connected to display segments |
| OE   | Output Enable | Active LOW  |
| MR   | Master Reset  | Active LOW  |

---

### ⚙️ 3. Wiring: 74HC595 to 7-Segment Display

| 74HC595 Pin | 7-Segment Segment |
|-------------|-------------------|
| Q0          | F                 |
| Q1          | A                 |
| Q2          | E                 |
| Q3          | D                 |
| Q4          | DP                |
| Q5          | B                 |
| Q6          | G                 |
| Q7          | C                 |

## 🧭 Timing Diagram & Working Principle of 74HC595

The **74HC595** shift register receives data serially and outputs it in parallel. It uses three main control signals:

- `DS` (Serial Data Input)
- `SHCP` (Shift Clock): triggers a shift on rising edge
- `STCP` (Latch Clock): updates output on rising edge
### ⚙️ Working Steps

1. **Shift Phase** (SHCP ↑)
   - On every rising edge of `SHCP`, the bit on `DS` is shifted into the register.
   - Bits move one step right (serially), older bits shift toward MSB.

2. **Latch Phase** (STCP ↑)
   - After sending all 8 bits, a rising edge on `STCP` transfers the internal register content to outputs Q0–Q7.

3. **Output Enable (OE)**
   - Must be LOW to enable outputs. If HIGH, Q0–Q7 are tri-stated (disabled).

### 💡 Example Operation (Display `2` = 0x76 = `0b01110110`)

1. Send each bit of `0b01110110` to `DS`, toggling `SHCP` after each bit.
2. After 8 bits, toggle `STCP` to latch the data.
3. The output pins Q0–Q7 now reflect the segment states as defined in the 7-Segment Encoding Table.

---

### 📷 Visual Reference

You can visualize the timing as follows:

| Step | DS  | SHCP ↑ | STCP ↑ | Internal Register          | Output (Q0–Q7)  |
|------|-----|--------|--------|----------------------------|----------------|
| 1    | 0   | ↑      |        | 00000000                   | —              |
| 2    | 1   | ↑      |        | 00000001                   | —              |
| 3    | 1   | ↑      |        | 00000011                   | —              |
| ...  | ... | ...    | ...    | ...                        | —              |
| 8    | 1   | ↑      | ↑      | 01110110 (0x76)            | 01110110       |

## 🔁 Expanding with 2x 74HC595 Using LED Scanning Method

When using multiple 7-segment displays (e.g., 2 digits or more), it's inefficient to assign a separate 74HC595 for each one. Instead, we can **use two 74HC595 chips** together with the **LED scanning method**.

---

### 🧱 Hardware Architecture

- **IC1 (Segment Register)**: Drives segment lines `A–G` (shared across all displays)
- **IC2 (Digit Selector)**: Controls common cathodes (or anodes) of each digit
- Only **one digit is active at a time**, but switching rapidly (100–500Hz) creates the illusion that all digits are lit simultaneously.

---
### ⚡ Wiring Overview

| Component        | Connection                                       |
|------------------|--------------------------------------------------|
| **74HC595 #1**   | Q0–Q7 → Segments a–g (shared across all digits)  |
| **74HC595 #2**   | Q0–Qn → Common cathode/anode of each digit       |
| SHCP & STCP      | Shared between both ICs                          |
| DS               | Daisy-chained: IC2 → IC1 (for 16-bit shift)      |
| **Q7' (Serial Out) of IC1** | Connected to **DS of IC2 (Digit Selector)** |

Use **Q7'** (also called **Q7s** or serial out) from the first 74HC595 to **cascade** to the second 595.
> This allows shifting **16 bits** (8 bits per chip) using only one data line (DS), one clock (SHCP), and one latch (STCP).
> 
> In this configuration:
> - The first 8 bits go into **IC2 (Digit Selector)**
> - The next 8 bits go into **IC1 (Segment Control)**

---
## 📚 myLED Library (Custom Driver for 7-Segment with 74HC595)

This library provides functions to control a 7-segment display using one or two 74HC595 shift registers. It supports displaying single digits, multiple digits (via LED scanning), and full strings up to 5 characters.

---

### 📁 Files

- `myLED.h` – Header file containing function prototypes and macros.
- `myLED.c` – Source file implementing the functions.

---

### 🧰 Available Functions

#### 🔹 `void Data8_put(uint8_t d8)`
Sends a single byte (8 bits) to one 74HC595 shift register.

- **d8**: The data byte.
- **Bit Mapping**:
  - `QH` (bit 7) = MSB
  - `QA` (bit 0) = LSB

> Useful when controlling a single digit or segment pattern.

---

#### 🔹 `void Data16_put(uint16_t d16)`
Sends a 16-bit value across **two daisy-chained 74HC595 chips**.

- The first 8 bits are shifted into the second register (e.g., digit select),
- The remaining 8 bits go into the first register (e.g., segment control).

- **Bit Mapping**:
  - `QH` of second 595 = MSB of `d16` (bit 15)
  - `QA` of first 595 = LSB of `d16` (bit 0)

> Used for scanning LED displays with multiplexing (LED scanning method).

---

#### 🔹 `void LED_data(uint8_t n)`
Displays a digit `n` (0–9, or valid letters) by shifting the corresponding segment code to the LED.

> Internally uses a lookup table to map `n` to segment patterns.

Example:
```c
LED_data(3); // Displays digit 3
```
---

#### 🔹 `void LED_put(uint8_t n, uint8_t p)`
Displays digit or character `n` on the selected LED position `p`.

- `n`: The digit (0–9) or supported character (e.g., A–F, H, L, etc.)
- `p`: A bitmask that selects which LED positions to activate (see below)

#### 🧭 LED Position Mapping (`p` values):

| p Value | Active LED Position(s)  | Binary     |
|---------|-------------------------|------------|
| 0       | **All LEDs OFF**        | `00000000` |
| 1       | k1                      | `00000001` |
| 2       | k2                      | `00000010` |
| 4       | k3                      | `00000100` |
| 8       | k4                      | `00001000` |
| 16      | k5                      | `00010000` |
| 3       | k1 + k2                 | `00000011` |
| 7       | k1 + k2 + k3            | `00000111` |
> Setting `p = 0` disables all digits. This is useful for clearing the display or as part of a scanning routine where each digit is refreshed one at a time.

---

#### 🔹 `void LED_putstring(uint8_t *s)`
Displays a character string on the 7-segment display (up to 5 characters).

#### ⚙️ Behavior:

- Only the **first 5 characters** of the input string `s` will be displayed (k1 → k5).
- For each character:
  - If it's **supported** (e.g., `0–9`, `A–F`, `H`, `L`, `P`, etc.), the corresponding segment pattern is displayed.
  - If it's **not found** in the character lookup table, that position will be **blank (OFF)**.

#### Example:
```c
LED_putstring("123Ab"); // Shows 1 2 3 A b (if all are in encoding table)
LED_putstring("7$9X!"); // Shows 7 (blank) 9 X (blank)
```
---

#### 🔹 `void display_LED(int num, uint8_t start, uint8_t stop)`
Displays a multi-digit integer (`num`) on the 7-segment display, within digit range from `start` to `stop`.

- `num`: Integer number to be displayed (positive only)
- `start`: Start position (e.g., 1 = leftmost digit)
- `stop`: End position (e.g., 5 = rightmost digit)

#### Example:
```c
display_LED(123, 1, 3); // Displays digits '1', '2', '3' from positions 1 to 3
```
---

#### 🔹 `void blink_LED(int num, long long *last_blink, uint8_t start, uint8_t stop)`
Displays a multi-digit number `num` on the 7-segment display, with a **blinking effect** applied to digits in the range `[start, stop]`.

#### 🧩 Parameters:
- `num`: The integer number to be displayed (e.g., 0–99999)
- `last_blink`: Pointer to a timestamp (e.g., using `HAL_GetTick()`) to keep track of blinking state
- `start`: Index of the first digit to blink (1 = leftmost digit)
- `stop`: Index of the last digit to blink (5 = rightmost digit)

#### 🔁 Behavior:
- The digits in the range `[start, stop]` will toggle between **visible** and **blank** every ~500 milliseconds.
- Digits **outside the range** are always shown.

#### 🧠 How it works:
Internally uses a software timer (based on `HAL_GetTick()`) to toggle a visibility flag. Only the digits within the blinking range are hidden/shown periodically.

#### 📘 Example:
```c
long long last_blink_time = 0;

blink_LED(345, &last_blink_time, 2, 4); 
// → Digits 3, 4, 5 will blink (positions 2, 3, 4)
```
---

#### 🔹 `void display_mm_ss(int mm, int ss, long long *last_blink, int mode_blink)`
Displays the time in `MM–SS` (minutes–seconds) format using **five 7-segment LEDs**. Supports blinking modes for user time-setting interaction.

---

#### 🧩 Parameters:

- `mm`: Minutes value (0–99)
- `ss`: Seconds value (0–59)
- `last_blink`: Pointer to a timer variable (e.g., from `HAL_GetTick()`) used to track blinking state
- `mode_blink`: Blink mode for indicating current adjustment state

---

### 🧭 Supported Blink Modes

| Mode Constant | Description                      | Blinking Behavior                         |
|---------------|----------------------------------|-------------------------------------------|
| `MODE_SS`     | **Second-setting mode**          | The **seconds digits** (LED 4 and 5) blink every 0.5s |
| `MODE_MM`     | **Minute-setting mode**          | The **minutes digits** (LED 1 and 2) blink every 0.5s |
| `NO_MODE`     | **Normal display mode**          | All LEDs are constantly shown (no blinking) |

---

### 🖥️ LED Layout: `MM–SS` on 5 Digits

The time is displayed on **5 separate 7-segment LEDs** as follows:

| LED Position | Content          | Description              |
|--------------|------------------|--------------------------|
| k1 (LED 1)   | `M₁`             | Tens of minutes          |
| k2 (LED 2)   | `M₂`             | Units of minutes         |
| k3 (LED 3)   | `-`              | Dash or blank separator  |
| k4 (LED 4)   | `S₁`             | Tens of seconds          |
| k5 (LED 5)   | `S₂`             | Units of seconds         |

> The center LED (`k3`) shows a dash `–` as a **visual separator** between minutes and seconds.

---

### 🧠 Blinking Behavior

- Blinking is handled via non-blocking timing using `HAL_GetTick()` or an equivalent.
- The specified digit range will **toggle visibility ON/OFF every ~500 ms** depending on `mode_blink`.

---

### 📘 Examples

```c
long long last_blink_time = 0;

display_mm_ss(12, 45, &last_blink_time, MODE_SS);  // Show "12-45", blink 4th and 5th LEDs (seconds)
display_mm_ss(08, 30, &last_blink_time, MODE_MM);  // Show "08-30", blink 1st and 2nd LEDs (minutes)
display_mm_ss(23, 59, &last_blink_time, NO_MODE);  // Show "23-59", no blinking
```
---

## 🔌 Wiring Overview

### 📟 7-Segment LED Display via 74HC595 Shift Register

To control the 7-segment LEDs, we use **one or two 74HC595 shift registers**, connected to STM32 as follows:

| STM32 Pin  | 74HC595 Pin   | Description                   |
|------------|---------------|-------------------------------|
| `PA4`      | DS,`MOSI`     | Serial Data Input             |
| `PA3`      | SHCP,`SCK`    | Shift Register Clock Input    |
| `PA6`      | STCP,`RCK`    | Storage Register Clock (Latch)|
| `PA5`      | GND,`RCL`     | Output Enable (Active LOW)    |
| 5V         | Vcc           | Master Reset (Active LOW)     |

> 🧠 For dual shift registers: Connect **Q7S** of the first 74HC595 to **DS** of the second. This allows you to shift 16 bits (2 bytes) for **5-digit multiplexing control + segment data**.

---

### 🔘 Button Interface (P1–P4)

Four **active-low push buttons** (normally open) are used for user interaction. Each button should be connected with a **pull-up resistor** or internal pull-up via STM32.

| Button | Functionality         | Connected To STM32 Pin | Circuit Note              |
|--------|-----------------------|-------------------------|----------------------------|
| `P1`   | Count-up / Increment  | e.g., `PB4`             | Pull-up resistor required  |
| `P2`   | Count-down / Decrement| e.g., `PB5`             | Pull-up resistor required  |
| `P3`   | Mode switch           | e.g., `PB8`             | Pull-up resistor required  |
| `P4`   | Confirm / Value ++    | e.g., `PB9`             | Pull-up resistor required  |
---

## 📂 How to Setting `GPIO` in STM32CubeMX Project

1. Open **STM32CubeMx** project.
2. Follow the steps in the picture.

---
## 🧪 Application Examples

---

### 🟢 3.4. Application 2: Manual Number Control with Buttons

This program uses the 7-segment display and `74HC595` shift register to display and control a 5-digit number. The system responds to 4 push buttons (`P1` → `P4`) with the following behavior:

#### 🔧 Behavior:

- **At startup**: The display shows the default number `12345`.
- **P1 pressed**: The number increases by 1  
  → e.g. `12345` → `12346`
- **P2 pressed**: The number decreases by 1  
  → e.g. `12345` → `12344`
- **P3 pressed**: The number resets to the default `12345`
- **P4 pressed**: The number begins **auto-incrementing** by 1 every second  
  → Counting continues until `99999`, then stops automatically.

#### 🔁 Notes:
- Each button press should be **debounced** to avoid repeated triggers.
- Use `HAL_GetTick()` or a hardware timer to implement the 1-second interval for P4.

---

### 🟢 3.5. Application 3: Digital Clock MM–SS Mode with Adjustment

This application implements a **digital clock (minute-second)** using a **5-digit 7-segment display**, with full support for **count-up, count-down, and manual adjustment** using 4 buttons.

#### 🔧 Initial Display:

- At startup, the display shows `12–00` → 12 minutes, 00 seconds

---

### 🔘 Button Functions:

| Button | Functionality                                                                 |
|--------|--------------------------------------------------------------------------------|
| **P1** | Toggle **count-up mode** (increases seconds by 1 every second)                |
| **P2** | Toggle **count-down mode** (decreases seconds by 1 every second)              |
| **P3** | Cycle through **adjustment modes**:<br>1. Adjust Seconds (2 right LEDs blink)<br>2. Adjust Minutes (2 left LEDs blink)<br>3. Exit Adjustment (no blinking) |
| **P4** | Increment the current value depending on mode:<br>- In **second adjust mode**: +1 second<br>- In **minute adjust mode**: +1 minute<br>- In **no mode**: No effect |

---

### 🧭 Adjustment Modes (cycled by P3):

| Mode Name   | LED Behavior             | Affected by P4 |
|-------------|--------------------------|----------------|
| `MODE_SS`   | Seconds digits blink     | Add 1 second   |
| `MODE_MM`   | Minutes digits blink     | Add 1 minute   |
| `NO_MODE`   | No blinking (normal)     | P4 has no effect |

---

### 🔁 Time Behavior:

- **Counting Up**:
  - `MM–SS` increases every second.
  - When seconds reach `59`, reset to `00` and minutes increase by 1.
- **Counting Down**:
  - `MM–SS` decreases every second.
  - When seconds reach `00`, reset to `59` and minutes decrease by 1.
  - Stops when both minutes and seconds are `00`.

---

### 💡 Adjustment Notes:

- When adjusting minutes or seconds:
  - Values wrap around after 59 → 00.
  - Increasing seconds from `59` → `00` **does NOT affect minutes**.
- Ensure only one mode (count-up or count-down) is active at a time to avoid conflicts.

---

### 📘 Example Usage:

```c
// Initial display
display_mm_ss(12, 0, &last_blink_time, NO_MODE);

// User presses P1: Start auto count-up
// User presses P3 twice: Enter minute adjustment mode
// User presses P4 repeatedly: Increase minutes
// User presses P2: Start count-down
```
---

## 📂 How to Add `myLED` Library in Keil C Project

To use the `myLED.c` and `myLED.h` library in your STM32 project (Keil µVision), follow these steps:

---
### ➕ 2. Add `myLED.c` to Project Source Group

1. Open **Keil µVision** project.
2. In **Project Explorer**, right-click on **Application/User/Core**.
3. Click **Add Existing Files to Group...**
4. Navigate to `myLED.c` and select it → Click **Add** → then **Close**

✅ Now Keil will compile `myLED.c` with your project.

<img width="576" height="424" alt="Image" src="https://github.com/user-attachments/assets/f2182b36-b510-45ad-8682-4c38580aec35" />
---

### 📌 How to Add a `.h` Header File to Your Keil Project

Header files (`.h`) contain **function prototypes**, **macros**, and **global variables** used across multiple `.c` files.

To use `myLED.h` or any custom header:

---
1. Open **Keil µVision** project.
2. In **Project Explorer**, follow the steps in the picture.
<img width="1322" height="537" alt="Image" src="https://github.com/user-attachments/assets/e42710b0-e5dc-46b1-be87-b49be8034ed5" />

### 🧩 Step 5: Place the Header File

Make sure `myLED.h` is placed in an accessible folder within your project directory.

<img width="833" height="458" alt="Image" src="https://github.com/user-attachments/assets/2d1718f7-e776-4bdc-8bfa-1345d987d18a" />
