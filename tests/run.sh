
set -e

gcc -o spidev spidev.cpp
gcc -o gpio gpio.cpp
sudo ./spidev
# sudo ./gpio
