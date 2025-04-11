# Atividade 2
This project reads the temperature on the RP2040 board and display on terminal every 1000 millisseconds

# Explanation
The RP2040 have a special diode connected to the ADC 4 that enables a temperature reading based on the voltage across
this diode, we trigger the measurement and convert the value to Celsius based on the following equation:
temperature_celsius = 27 - (voltage - 0.706) / 0.001721
