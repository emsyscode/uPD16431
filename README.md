Arduino uPD16431 LCD Driver

Arduino Uno implementation for controlling an LCD segment display based on the NEC uPD16431 driver.

This project was created while investigating and restoring a vintage car-radio front panel. The panel contains a segmented LCD controlled by a uPD16431 display driver.

The repository contains the Arduino code used to communicate with the driver and control the individual LCD segments.

Demonstration

A complete video covering the driver, wiring, communication process and working display is available on YouTube:

https://www.youtube.com/watch?v=fTcjQisQ3Ws

Features
Controls a NEC uPD16431 using an Arduino Uno
Writes data to the LCD display memory
Supports individual segment testing
Helps map display-memory bits to physical LCD segments
Uses the driver’s default maximum-segment configuration
Can be adapted to other panels using the same controller
Provides a foundation for reading the uPD16431 key matrix
Hardware

The project was tested with:

Arduino Uno
Vintage car-radio LCD front panel
NEC uPD16431 LCD driver
Jumper wires
Suitable power supply for the display board
Common ground between the Arduino and display board
About the uPD16431

The NEC uPD16431 is an LCD segment driver designed for equipment such as automotive audio systems and other electronic control panels.

The controller can drive up to 224 LCD segments in its maximum display configuration.

Some outputs can alternatively be used as LED ports. When the LED-port functionality is enabled, fewer outputs remain available for driving LCD segments.

The controller also includes support for a key matrix with up to:

4 key-scan outputs
8 key-data inputs
32 possible keys

This project currently focuses mainly on controlling the LCD.

Communication Notes

Several details are important when communicating with the uPD16431.

Bit order

Data is transmitted most-significant bit first.

The transmitted bytes must therefore be constructed in the correct order. Another possible implementation is to reverse the bit order inside the function responsible for sending each byte.

Clock behaviour

According to the driver documentation:

Display data is written on the clock’s rising edge.
Key data is read on the clock’s falling edge.

The clocking behaviour should be considered carefully when adapting the code or implementing key-matrix reading.

Display configuration

This project uses the driver’s default maximum-segment configuration.

Although the uPD16431 supports up to 224 segments, the display panel used in this project does not necessarily use every available output.

Wiring

Connect the Arduino Uno to the corresponding communication and power connections on the uPD16431 display board.

The exact connector pinout can vary between panels, even when they use the same display driver.

Before connecting a different panel:

Identify the uPD16431 on the PCB.
Consult the uPD16431 datasheet.
Trace the connector pins to the driver.
Confirm the board’s supply voltage.
Identify the data, clock and control connections.
Connect the Arduino and display grounds together.

Important: Do not assume that the display board operates directly at 5 V. Verify the required voltage before powering the panel.
