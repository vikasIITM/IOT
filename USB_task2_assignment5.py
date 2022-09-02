from machine import UART

uart = UART(0, 115200)                         # init with given baudrate
uart.init(115200, bits=8, parity=None, stop=1) # init with given parameters

temperature = 40

while temperature < 50:
    print (temperature)
uart.write(str(temperature))
temperature+=1