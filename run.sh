. $HOME/esp/esp-idf/export.sh
idf.py build
idf.py -p /dev/tty.SLAB_USBtoUART flash
# idf.py -p /dev/tty.usbserial-0001 flash
screen /dev/tty.SLAB_USBtoUART 115200