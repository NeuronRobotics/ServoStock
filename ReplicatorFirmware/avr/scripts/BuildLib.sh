#!/bin/bash
echo building DDK
START=$PWD
rm -rf $START/dyiolib/build
mkdir $START/dyiolib/build
mkdir $START/dyiolib/build/lib

mkdir $START/dyiolib/build/include
mkdir $START/dyiolib/build/include/arch


cp -r ../include/* 			$START/dyiolib/build/include/
cp -r ../../DyIO_Common/include/* 	$START/dyiolib/build/include/
cp -r ../../NRLIB/include/Bowler 	$START/dyiolib/build/include/
cp -r ../../NRLIB/include/arch/AVR 	$START/dyiolib/build/include/arch/

mkdir $START/dyiolib/build/lib/o

cp -r ../../DyIO_Common/Release/avr/libDyIOCommon.a 	$START/dyiolib/build/lib/o
cp -r ../../NRLIB/lib/AVR/atmega324p/* 			$START/dyiolib/build/lib/o

cd $START/dyiolib/build/lib/o
cp $START/dyiolib/*.o .
avr-ar x libDyIOCommon.a
avr-ar x libNRLIB.a
find .|grep ".o"|xargs avr-ar rcs ../libDyIOLibrary.a

rm *.o
cp $START/dyiolib/*.o .
avr-ar x libDyIOCommon.a
avr-ar x libNRLIB_debug.a
find .|grep ".o"|xargs avr-ar rcs ../libDyIOLibrary_debug.a


rm -rf $START/dyiolib/build/lib/o
cd $START/dyiolib/
rm $START/NeuronRoboticsDDK_*.tar
tar cf $START/NeuronRoboticsDDK_3.7.4.tar build --exclude-vcs --exclude=.DS_Store --exclude=__MACOSX
rm -rf $START/dyiolib/build
echo DDK OK
