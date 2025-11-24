# FPGA 7-Segment Counter with Nios II Processor
--- 

https://github.com/user-attachments/assets/7a04b07b-4dd3-4a0b-983b-5d1f7763a604

---



## 📖 Project Overview

This project implements a **4-digit 7-segment counter** on an FPGA using a **Nios II soft processor**. The counter increments continuously from 0000 to 9999, displaying the values on four 7-segment displays. The system demonstrates a complete **System-on-Programmable-Chip (SoPC)** design using Intel's Qsys/Platform Designer.

## 🎯 Features

- **4-digit 7-segment display** counter (0000 to 9999)
- **Nios II soft processor** implementation
- **Qsys/Platform Designer** system integration
- **Custom C application** running on embedded processor
- **Auto-reset** after reaching 9999
- **Configurable display speed**

## 🛠 Hardware Architecture

### Block Diagram
```
[CLOCK_50] → [Nios II Processor] → [4x PIO Controllers] → [7-Segment Displays]
[RESET_N]  → [On-Chip Memory]   → [JTAG UART]           → [Debug Interface]
```

### Qsys System Components
- **Nios II/f processor** (32-bit RISC)
- **On-Chip Memory** (64KB for instructions/data)
- **4x PIO Cores** (Parallel Input/Output for displays)
- **JTAG UART** (Debug communication)
- **System ID** (Peripheral identification)
<img width="1222" height="703" alt="image" src="https://github.com/user-attachments/assets/47c3ddf1-eb87-4905-bf6c-6a6e581a19be" />

## 📁 Project Structure



## 🔧 Hardware Implementation

### Top-Level VHDL Interface

```vhdl
entity TopLevel is
    port (
        CLOCK_50 : in  std_logic;                    -- 50MHz clock input
        RESET_N  : in  std_logic;                    -- Active-low reset
        
        -- 7-segment display outputs (Common Anode)
        HEX0 : out std_logic_vector(6 downto 0);     -- Rightmost digit
        HEX1 : out std_logic_vector(6 downto 0);     -- Second digit
        HEX2 : out std_logic_vector(6 downto 0);     -- Third digit
        HEX3 : out std_logic_vector(6 downto 0)      -- Leftmost digit
    );
end entity TopLevel;
```

### Pin Assignments (DE10-Lite Example)

| Signal    | FPGA Pin | Description           |
|-----------|----------|-----------------------|
| CLOCK_50  | PIN_P11  | 50MHz Clock           |
| RESET_N   | PIN_A7   | Reset Button          |
| HEX0[6:0] | PIN_A13-C13| 7-segment Display 0  |
| HEX1[6:0] | PIN_D13-E13| 7-segment Display 1  |
| HEX2[6:0] | PIN_F13-B16| 7-segment Display 2  |
| HEX3[6:0] | PIN_A14-A16| 7-segment Display 3  |

## 💻 Software Implementation

### Main Application Logic

```c
#include "system.h"
#include "io.h"

// 7-segment encoding for COMMON ANODE displays (active-low)
const unsigned char seg_code[10] = {
    0xC0, // 0 - segments: a,b,c,d,e,f
    0xF9, // 1 - segments: b,c
    0xA4, // 2 - segments: a,b,d,e,g
    0xB0, // 3 - segments: a,b,c,d,g
    0x99, // 4 - segments: b,c,f,g
    0x92, // 5 - segments: a,c,d,f,g
    0x82, // 6 - segments: a,c,d,e,f,g
    0xF8, // 7 - segments: a,b,c
    0x80, // 8 - all segments
    0x90  // 9 - segments: a,b,c,d,f,g
};
```

### Key Functions

1. **Digit Extraction**
   ```c
   int d0 = (counter % 10);        // Units
   int d1 = (counter / 10) % 10;   // Tens
   int d2 = (counter / 100) % 10;  // Hundreds
   int d3 = (counter / 1000) % 10; // Thousands
   ```

2. **Display Control**
   ```c
   IOWR_8DIRECT(DISPLAY7SEGMENT1_BASE, 0, seg_code[d0]);
   IOWR_8DIRECT(DISPLAY7SEGMENT2_BASE, 0, seg_code[d1]);
   IOWR_8DIRECT(DISPLAY7SEGMENT3_BASE, 0, seg_code[d2]);
   IOWR_8DIRECT(DISPLAY7SEGMENT4_BASE, 0, seg_code[d3]);
   ```

3. **Software Delay**
   ```c
   void delay_ms(int ms) {
       volatile int i, j;
       for(i = 0; i < ms; i++)
           for(j = 0; j < 5000; j++);
   }
   ```

## 🚀 Installation & Usage

### Prerequisites
- **Intel Quartus Prime** (v18.1 or later)
- **Nios II Software Build Tools for Eclipse**
- **FPGA Development Board** (DE10-Lite, DE0-CV, etc.)
- **USB-Blaster** JTAG programmer

### Hardware Setup

1. **Open Qsys System**
   ```bash
   quartus
   Tools → Platform Designer → Open → Processeur2.qsys
   ```

2. **Generate HDL**
   - Generate HDL in Qsys
   - Update component in TopLevel.vhd if needed

3. **Compile Project**
   ```bash
   Processing → Start Compilation
   ```

4. **Program FPGA**
   ```bash
   Tools → Programmer → Add File → TopLevel.sof → Start
   ```

### Software Setup

1. **Create Nios II Application**
   ```bash
   File → New → Nios II Application
   Select "Blank Project"
   Set BSP to Processeur2_bsp
   ```

2. **Build and Run**
   ```bash
   Project → Build All
   Run → Run As → Nios II Hardware
   ```

## ⚙️ Configuration

### Customization Options

1. **Change Counter Speed**
   ```c
   delay_ms(50); // Adjust this value (ms)
   ```

2. **Modify Display Range**
   ```c
   if(counter > 9999) // Change maximum value
   ```

3. **Different 7-Segment Patterns**
   - Update `seg_code` array for different display types
   - Common Cathode: Use inverted values

## 🔍 Technical Details

### Memory Map
| Peripheral           | Base Address     | Function            |
|----------------------|------------------|---------------------|
| DISPLAY7SEGMENT1     | 0x00001000       | Rightmost digit     |
| DISPLAY7SEGMENT2     | 0x00001010       | Second digit        |
| DISPLAY7SEGMENT3     | 0x00001020       | Third digit         |
| DISPLAY7SEGMENT4     | 0x00001030       | Leftmost digit      |
| JTAG_UART            | 0x00002000       | Debug interface     |

### Timing Analysis
- **Clock Frequency**: 50 MHz
- **Counter Update**: Every 50ms
- **Full Cycle Time**: 500 seconds (0000-9999)

## 🐛 Troubleshooting

### Common Issues

1. **Displays Show Wrong Digits**
   - Check `seg_code` array matches your display type (Common Anode/Cathode)
   - Verify PIO bit order in Qsys

2. **Program Doesn't Run**
   - Verify FPGA programming succeeded
   - Check Nios II .elf file is loaded correctly
   - Confirm reset signal is properly connected

3. **Compilation Errors**
   - Ensure all Qsys components are generated
   - Verify system.h matches your Qsys configuration

### Debugging Tips

- Use **JTAG UART** for printf debugging
- Verify each display individually by writing fixed values
- Check signal timing with SignalTap Logic Analyzer

## 🎓 Learning Outcomes

This project demonstrates:
- **SoPC design** with Nios II processor
- **Qsys/Platform Designer** integration
- **Hardware/Software co-design**
- **Memory-mapped I/O** operations
- **Embedded C programming** for FPGAs
- **VHDL top-level** system integration

## 📝 License

This project is open source and available under the [MIT License](LICENSE).

## 🤝 Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues for improvements.

## 📧 Contact

For questions or support regarding this project, please open an issue in the GitHub repository.

