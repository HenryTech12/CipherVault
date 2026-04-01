# 🔐 The CipherVault

**An Arduino-powered Random Password Generator & Verification System**

The **CipherVault** is an interactive security-themed project that combines a random 4-digit PIN generator with a hardware-based verification interface. It uses a 16x2 LCD for real-time feedback, a 4x4 matrix keypad for input, and multi-sensory alerts (LEDs and Buzzer) to signal success or failure.

---

## 🚀 How It Works

1.  **Initialize:** Upon power-up, the LCD displays a welcome message.
2.  **Generate:** Press the **'A'** key to trigger the logic and generate a unique, random 4-digit password.
3.  **Input:** Use the numeric keypad to type the code shown on the screen.
    * Press **'*'** to clear your input if you make a mistake.
4.  **Verify:** Press **'#'** to submit your entry.
    * **Access Granted:** The **Green LED** lights up and a high-pitched "success" melody plays.
    * **Access Denied:** The **Red LED** lights up and a low-pitched "error" tone plays.

---

## 🛠️ Hardware Components

* **Microcontroller:** Arduino Uno (or compatible)
* **Display:** 16x2 LCD with I2C Interface Module
* **Input:** 4x4 Membrane Matrix Keypad
* **Indicators:** 1x Green LED, 1x Red LED
* **Sound:** 1x Passive Piezo Buzzer
* **Resistors:** 2x 220Ω (for LEDs)
* **Jumpers:** M-M and M-F jumper wires

---

## 🔌 Pin Mapping

| Component | Arduino Pin | Function |
| :--- | :--- | :--- |
| **I2C LCD SDA** | **A4** | Data Line |
| **I2C LCD SCL** | **A5** | Clock Line |
| **Keypad Rows** | **9, 8, 7, 6** | Matrix Row Scan |
| **Keypad Cols** | **5, 4, 3, 2** | Matrix Col Scan |
| **Buzzer (+)** | **10** | Audio Feedback |
| **Green LED** | **11** | Success Visual |
| **Red LED** | **12** | Failure Visual |

---

## 💻 Software Setup

This project requires the following libraries to be installed via the **Arduino Library Manager**:

1.  **Keypad** (by Mark Stanley & Alexander Brevig)
2.  **LiquidCrystal_I2C** (by Frank de Brabander)

### Installation Steps

1.  Open the Arduino IDE.
2.  Go to **Sketch** > **Include Library** > **Manage Libraries...**
3.  Search for and install the two libraries mentioned above.
4.  Copy the `CipherVault.ino` code into a new sketch.
5.  Select your board and port, then click **Upload**.

---

## 📝 Troubleshooting

* **Blank LCD:** Rotate the blue potentiometer screw on the back of the I2C module to adjust the contrast.
* **Wrong Key Mapping:** If pressing '1' gives a different character, check if your keypad connector is plugged in backwards.
* **No Sound:** Ensure the buzzer's long leg (positive) is connected to Pin 10.

---

**Built with precision and passion for secure hardware.** 🛡️
