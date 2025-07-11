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

| Step | DS  | SHCP ↑ | STCP ↑ | Internal Register         | Output (Q0–Q7) |
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
| **74HC595 #1**   | Q0–Q7 → Segments a–g (shared across all digits) |
| **74HC595 #2**   | Q0–Qn → Common cathode/anode of each digit      |
| SHCP & STCP      | Shared between both ICs                         |
| DS               | Daisy-chained: IC2 → IC1 (for 16-bit shift)     |
| **Q7' (Serial Out) of IC1** | Connected to **DS of IC2 (Digit Selector)** |

Use **Q7'** (also called **Q7s** or serial out) from the first 74HC595 to **cascade** to the second 595.
> This allows shifting **16 bits** (8 bits per chip) using only one data line (DS), one clock (SHCP), and one latch (STCP).
> 
> In this configuration:
> - The first 8 bits go into **IC2 (Digit Selector)**
> - The next 8 bits go into **IC1 (Segment Control)**

---
