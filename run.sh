. $HOME/esp/esp-idf/export.sh
idf.py build
idf.py -p /dev/tty.SLAB_USBtoUART flash monitor
idf.py -p /dev/tty.usbserial-0001 flash monitor
idf.py -p /dev/cu.usbserial-A50285BI flash monitor