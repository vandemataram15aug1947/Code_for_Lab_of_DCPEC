# Code_for_Lab_of_DCPEC

# Code_for_Lab_of_DCPEC

This repository contains embedded C source code and project configuration files for various lab experiments conducted at **DCPEC (Department of Electrical Engineering)**. The code is designed for the **Texas Instruments TMS320F28379D (C2000 Delfino)** microcontroller, using **Code Composer Studio (CCS)** as the development environment.

## 📁 Project Structure

├── .launches/ # CCS launch configuration
├── .settings/ # Workspace-specific settings
├── CPU1_FLASH/ # Build config for Flash
├── CPU1_RAM/ # Build config for RAM
├── device/ # Device support files (TMS320F28379D)
├── targetConfigs/ # Target configuration XML files
├── .ccsproject # CCS project descriptor
├── .cproject # Eclipse project descriptor
├── .project # Eclipse project file
├── 2837xD_FLASH_lnk_cpu1.cmd # Linker command file for Flash
├── 2837xD_RAM_lnk_cpu1.cmd # Linker command file for RAM
├── F2837xD_CodeStartBranch.asm
├── F2837xD_usDelay.asm
├── F2837xD_GlobalVariableDefs.c
├── F2837xD_DefaultISR.c
├── F2837xD_PieCtrl.c
├── F2837xD_PieVect.c
├── F2837xD_SysCtrl.c
├── F2837xD_CpuTimers.c
├── F2837xD_Gpio.c
├── F2837xD_Headers_nonBIOS_cpu1.cmd
├── ADC.c # ADC initialization and ISR code
├── SPWM.c # Sinusoidal PWM logic
├── Genereate_Class_ePWM.c # ePWM generation for experiments
├── LED_for_DCPEC.c # Basic LED test using GPIO
├── LED_for_DCPEC_Timer_0.c # Timer-based LED toggling
├── LED_for_DCPEC_Timer_2.c # Another Timer-based LED control
├── LAB_Exp_a.c # Lab-specific experiment code
├── Add.c, SUB.c, MUL.c # Basic arithmetic operation modules


## 🔧 Requirements

- **Code Composer Studio (CCS)**
- **TMS320F28379D LaunchPad or custom board**
- **C2000ware / driverlib support**
- Oscilloscope/DSO for waveform observation (if applicable)

## 🧪 Lab Experiments Overview

| File                         | Description                              |
|------------------------------|------------------------------------------|
| `LED_for_DCPEC.c`           | Basic GPIO LED toggle                    |
| `ADC.c`                     | ADC initialization and ISR              |
| `SPWM.c`                    | Implementation of Sinusoidal PWM        |
| `Genereate_Class_ePWM.c`    | ePWM configuration for lab experiments  |
| `LAB_Exp_a.c`               | Custom experiment logic                 |
| `Add.c`, `SUB.c`, `MUL.c`   | Demonstrations of math operations       |

## ⚙️ How to Build and Run

1. Open Code Composer Studio.
2. Import this project: `Project -> Import CCS Projects -> Browse to this repo`
3. Choose either **CPU1_RAM** or **CPU1_FLASH** build configuration.
4. Build the project.
5. Connect your F28379D board via USB.
6. Load and run the code.

## 📌 Notes

- All experiments are meant for real-time embedded control systems.
- Interrupt vector table, GPIO muxing, and system initialization are handled by TI driver files in the `device/` folder.
- This repository is structured to support fast deployment and modular testing of various lab modules.

## 📜 License

This repository is for **educational purposes** and meant to be used within the scope of DCPEC lab experiments. For broader use or redistribution, please consult with the repository author.

---


