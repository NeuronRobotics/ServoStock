#http://ww1.microchip.com/downloads/mplab/X_Beta/installer.html
PICTOOLCHAIN    = /home/opt/microchip/mplabc32/v2.01/bin/
GCCP			=$(PICTOOLCHAIN)pic32-gcc  -O3 -mips16 -s
ARP				=$(PICTOOLCHAIN)pic32-ar
BIN2HEX			=$(PICTOOLCHAIN)pic32-bin2hex

#PICTOOLCHAIN    = /usr/local/bin/
#GCCP			=$(PICTOOLCHAIN)pic32mx-gcc  -O3 -mips16 -s
#ARP				=$(PICTOOLCHAIN)pic32mx-ar
#BIN2HEX			=$(PICTOOLCHAIN)pic32mx-bin2hex