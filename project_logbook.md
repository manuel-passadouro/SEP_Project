# SEP Project Logbook
<!-- TODO STARTS HERE -->
## To-Do (1st Delivery by 04/10):

- [x] GIT repo
- [x] Google Drive Folder
- [x] Project logbook
- [ ] Top-level flowchart and diagram
- [ ] List of features/requirements
- [x] PIC setup on breadboard
- [x] LED test
- [x] Temp sensor ADC readout
- [x] APDS 9960 I2C config
- [x] Timer interrupt
- [x] SPI initial config
- [x] Remove MCC files
- [x] Organize Code file structure
- [ ] Sensor Node schematic
<!-- TODO ENDS HERE -->

<!-- NEW LOG ENTRY STARTS HERE -->

## 09/10/2024

### Notes:
- SPI working with interrupts, now we can control the flow of
  messages;
- Needed to configure Rx Buffer interrupt, instead of just spi1interrupt
  as we thought at first. Many options to trigger spi interrupts;
- Can read from sensor periodically and send data to bridge;
- ADC still not sending out reliable read outs;
- Must test with sleep mode when not aquiring data;
- Adjusted bridge display to printf 2 digits of hex data,
  must remove irrelevant code from bridge;
- For 1st Demo:
  - Aquire sensor data periodically, LED On when done;
  - Send data to bridge when requested
   (button on bridge triggers spi master send), LED Off when done;
  - Button selects what data is sent;
  - Sleep while not aquiring sensor data nor sending to bridge.

<!-- NEW LOG ENTRY ENDS HERE -->

## 03/10/2024

### Notes:
- Added timer and timer interrupt, working fine;
- Clock source for timers must be chosen carefully
  due to sleep mode and overflow;
- Watchdog timer needs to be better understood before implmentation;
- SPI is working well after properly configuring PPS, next
  step is to implement interrupts;
- No registers for SPI prescaller, what baudrate to use? ;
- FOSC had to be defined in sys_config, delays now working
  in expected way, actual FCY is 4MHz (FOSC/2);
- Sleep mode appers to be working and interrupts trigger wake-up,
  but control register does not inidicate sleep? ;
- Development is going at a good pace, can start to
  draw out software flowchart.

## 01/10/2024

### Notes:
- Organized code in .c/.h files, excluded MCC generated code
  from project;
- Started SPI implementation on Devboard, need to test master config and
  view output on oscilloscope;
- Need to implement timer interrupt and idle/sleep mode;
- Must write proper I2C drivers for 1st delivery;
- Idea: test WDT by making a function that gets randomly stuck.

## 27/09/2024

### Notes:
- Started work on gesture detection, need to better understand sensor behaviour
  interms of timings and when reading can/should be performed;
- Priority is to implement a timer interrupt for enter/exit in idle mode;
- Begin to clean-up the code before it gets out of hand, split the code
  in .c/.h combinations (ADC, I2C, APPD9960, SPI, etc...).

## 26/09/2024

### Notes:
- ADC temperature readout inconsistent, using external references
  or 12-bit does not improve results, seem related to Vdd/Vss connections;
- I2C implementation is showing progress. Can read fro and write to slaves registers;
- Now we can begin exploring sensor configurations and starting testing its capabilities.

## 24/09/2024

### Notes:

- Color Sensor was placed on the breadboard, with 2.2KOhm pull-ups;
- I2C master init and byte send function were tested,
  results on the oscilloscope were ok;
- Slave address must be concatenated for read and write (so 0x39 becomes 0x73 for read, 0x72 for write);
- Workflow for reading the sensor data:
  - Send start condition;
  - Send slave write address;
  - wait for ACK;
  - Send data register address;
  - wait for ACK;
  - Send Stop condition (?);
  - read byte from slave;
- Must implement and test voltage divider for ADC Vref;
- Merge ADC and I2C code then reorganize project library before 1st delivery. 

## 22/09/2024

### Notes:

- Temp sensor was placed in reverse, now gives expected output voltage;
- ADC readout is fine but fluctuates a lot, Vref should be lower since max temp of sensor comes at around 0.4V
- Use external Vref for ADC
- Next step is to connect APDS9960 breakout board to PIC and start working on I2C.

## 19/09/2024

### Notes:

- Temp sensor gives 0V at output, need to test independently with 5V;
- Ask Prof for new temp sensor;
- ADC sample code divides by 4, when it should divide by 2 (the # of samples);
- ADC appears to by working fine, produces the expected 10 bit result for VDD reference;
- APDS 9960 has arrived, i2c implementation can begin;
- Will probably have to write APDS functions, library is arduino only.



