all: main  coproc pub
	echo ok
upload:svnupdate update all commit
	if (test -d ../NR-Clib/);then cd ../NR-Clib/;make commit;	fi
	echo upload ok
update:
	echo Updating...
	if (test -d ../NR-Clib/);					then cd ../NR-Clib/;svn update;					fi
	if (test -d ../NR-Clib/);					then cd ../NR-Clib/src;make pic32MX440F128H;		fi
	if (test -d ../NR-Clib/);					then cd ../NR-Clib/src;make AVR644p;				fi
	if (test -d ../NR-Clib/);					then cd ../NR-Clib/src;make AVR324p;				fi
	if (test -d ../NR-Clib/include/); 		then rsync -raupE --exclude=.svn*					../NR-Clib/include/* 							NR-Clib/include;			fi
	if (test -d ../NR-Clib/lib/AVR); 			then rsync -raupE --exclude=.svn* --exclude=*.r*   	../NR-Clib/lib/AVR/* 							NR-Clib/lib/AVR/;				fi
	if (test -d ../NR-Clib/lib/); 			then rsync -raupE --exclude=.svn* --exclude=*.r*   	../NR-Clib/lib/PIC32/32MX440F128H/*			NR-Clib/lib/PIC32/32MX440F128H/;				fi
	if (test -d ../NR-Clib/toolchain/); 		then rsync -raupE --exclude=.svn*  					../NR-Clib/toolchain/* 						NR-Clib/toolchain;		fi
	echo Done Updating...
svnupdate:
	svn update
commit:
	svn commit -m="Building the DyIO"
	cd ../NRSDK/fw; svn commit -m="Building the DyIO"
main:
	make -C pic all	
coproc:
	make -C avr all
pub:
	if (test -e FirmwarePublish/Release/*.xml);			then rm FirmwarePublish/Release/*.xml; rm FirmwarePublish/Release/legacy/*.xml; 			fi
	if (test -e FirmwarePublish/Dev/*.xml);				then rm FirmwarePublish/Dev/*.xml; 				fi	
	cd FirmwarePublish/src/pub;python FirmwarePublish.py
	if(rm ../NRSDK/fw/*); then echo OK; fi
	cp FirmwarePublish/Dev/dyio* ../NRSDK/fw/
	cp FirmwarePublish/Release/*.xml ../NRConsole/src/com/neuronrobotics/nrconsole/plugin/bootloader/fw/