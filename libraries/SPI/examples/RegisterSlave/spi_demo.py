"""
To access SPI bus 1 you need to 
Edit the /boot/firmware/config.txt
Add  the following lines to enable SPI1:
dtoverlay=spi1-1cs,cs0_pin=22
"""
import spidev
import time
import sys


def write_register(register_address, data):
    """Writes 16 bits  to a specified register."""
    # The first byte sent contains the register address and a write bit
    command_byte = register_address & 0x7F  # Clear MSB for write
    
    # Send command byte and data bytes (MSB first)
    spi.xfer2([command_byte, (data >> 8) & 0xff, data & 0xff])


def read_register(register_address):
    """Reads a 16-bit word from a register."""
    # The first byte sent contains the register address and a read bit
    command_byte = register_address | 0x80  # Set MSB for read
    
    # Send command byte and dummy bytes for reading
    # The received data will be in the response list
    response = spi.xfer2([command_byte] + [0x00] * 2) 
    
    # Return the relevant data from the response (excluding the command byte)
    return response[1] << 8 | response[2]


spi_speed = 50000
if (len(sys.argv) > 1):
  spi_speed = int(sys.argv[1]) 

bus = 1
device = 0
# Enable SPI
spi = spidev.SpiDev()

# Open a connection to a specific bus and device (chip select pin)
spi.open(bus, device)

# Set SPI speed and mode
print("Set SPI bus speed to %d kHz\n" % (spi_speed/1000))
spi.max_speed_hz = spi_speed
spi.mode = 0

while(1):
  test = 0xA55A
  write_register(11, test) 
  time.sleep(.05) 
  val = read_register(11);
  print("Wrote 0x%x in reg 11, read back 0x%x" % (test, val))

  val = read_register(0);
  print("reg 0 millis = %d" % val)

  val = read_register(1);
  print("User button = %d" % val)

  test = 0x0F0F
  write_register(11, test) 
  time.sleep(.05) 
  val = read_register(11);
  print("Wrote 0x%x in reg 11, read back 0x%x" % (test, val))


  time.sleep(.5) 
  print("\n")
  


