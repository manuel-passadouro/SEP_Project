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
- [ ] Timer interrupt
- [ ] SPI initial config
- [ ] Timer based interrupt
- [ ] Remove MCC files
- [ ] Organize Code file structure
- [ ] Sensor Node schematic
<!-- TODO ENDS HERE -->

<!-- NEW LOG ENTRY STARTS HERE -->

## 26/09/2024

### Notes:
- ADC temperature readout inconsistent, using external references
  or 12-bit does not improve results, seem related to Vdd/Vss connections;
- I2C implementation is showing progress. Can read fro and write to slaves registers;
- Now we can begin exploring sensor configurations and starting testing its capabilities.

<!-- NEW LOG ENTRY ENDS HERE -->

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



