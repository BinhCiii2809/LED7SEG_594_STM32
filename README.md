## 📘 LED7SEG & 74HC595 Shift Register

### 🔦 1. LED7SEG (Common Cathode)

**LED7SEG** là loại LED hiển thị gồm 7 thanh (a–g) và 1 dấu chấm thập phân (dp) để hiển thị số từ 0–9.

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

**74HC595** is an 8-bit serial-in, parallel-out shift register with a storage register and tri-state outputs. It allows expanding output pins using only **3 GPIOs**.

| Pin | Name    | Mô tả |
|------|--------|------|
| DS   | Data   | Data input |
| SHCP | Shift  | Shifts data on rising edge |
| STCP | Latch  | Transfers data to outputs |
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
