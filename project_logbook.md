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
- [ ] APDS 9960 I2C config
- [ ] SPI initial config
- [ ] Remove MCC files
- [ ] Organize Code file structure
- [ ] Sensor Node schematic
<!-- TODO ENDS HERE -->

<!-- NEW LOG ENTRY STARTS HERE -->

## 22/09/2024

### Notes:

- Temp sensor was placed in reverse, now gives expected output voltage;
- ADC readout is fine but fluctuates a lot, Vref should be lower since max temp of sensor comes at around 0.4V
- Use external Vref for ADC
- Next step is to connect APDS9960 breakout board to PIC and start working on I2C.

<!-- NEW LOG ENTRY ENDS HERE -->

## 19/09/2024

### Notes:

- Temp sensor gives 0V at output, need to test independently with 5V;
- Ask Prof for new temp sensor;
- ADC sample code divides by 4, when it should divide by 2 (the # of samples);
- ADC appears to by working fine, produces the expected 10 bit result for VDD reference;
- APDS 9960 has arrived, i2c implementation can begin;
- Will probably have to write APDS functions, library is arduino only.



