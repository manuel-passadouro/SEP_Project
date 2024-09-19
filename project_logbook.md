# Project Logbook

---

## Log Entry

**Date:** YYYY-MM-DD  
**Time:** HH:MM AM/PM

### Summary:
*Brief title or description of the entry.*

### Details:
- What was done: 
  - 
- Issues encountered:
  - 
- Solutions/Notes:
  - 

### Action Items / To-Do:
- [ ] Task 1
- [ ] Task 2

---

## Example Entry

**Date:** 2024-09-19  
**Time:** 10:00 AM

### Summary:
Configured I2C Communication for APDS-9960

### Details:
- What was done: 
  - Initialized I2C module on PIC24F for APDS-9960 sensor.
  - Verified the sensor address (0x39) on the I2C bus.
- Issues encountered:
  - First proximity reading was always incorrect.
- Solutions/Notes:
  - Adjusted the start condition timing in the I2C setup, which resolved the issue.

### Action Items / To-Do:
- [ ] Test the color detection feature.
- [ ] Implement data averaging for smoother sensor readings.
