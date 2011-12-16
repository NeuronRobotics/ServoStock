'''
Created on Jun 22, 2010

@author: hephaestus
'''
from time import gmtime, strftime
import commands
class FirmwarePublishDriver():
    def __init__(self):
        rev = self.getRevision()
        out = self.getFiles(rev,'release','644p')
        filename = "dyio-firmware-"+rev+".xml"
        print "Making ",filename
        f=open("../../Release/"+filename, 'w')
        f.write(out)
        
        rev = self.getRevision()
        out = self.getFiles(rev,'release','324p')
        filename = "dyio-firmware-"+rev+"_legacy.xml"
        print "Making ",filename
        f=open("../../Release/legacy/"+filename, 'w')
        f.write(out)
        
        commands.getstatusoutput("rm ../../Dev/*")#delete stale dev firmware
        
        rev = self.getRevision()
        out = self.getFiles(rev,'release','644p')
        filename = "dyio-firmware-"+rev+"_dev_"+strftime("%b_%d_%Y", gmtime())+".xml"
        print "Making ",filename
        f=open("../../Dev/"+filename, 'w')
        f.write(out)
    
        out = self.getFiles(rev,'debug','debug')
        filename = "DyIO_Firmware_"+rev+"_debug_"+strftime("%b_%d_%Y", gmtime())+".xml"
        print "Making ",filename
        f=open("../../Dev/"+filename, 'w')
        f.write(out)
        
        out = self.getFiles(rev,'debug','644p')
        filename = "DyIO_Firmware_"+rev+"_PIC_debug_"+strftime("%b_%d_%Y", gmtime())+".xml"
        print "Making ",filename
        f=open("../../Dev/"+filename, 'w')
        f.write(out)

        out = self.getFiles(rev,'debug','324p')
        filename = "DyIO_Firmware_"+rev+"_PIC_debug_legacy_"+strftime("%b_%d_%Y", gmtime())+".xml"
        print "Making ",filename
        f=open("../../Dev/"+filename, 'w')
        f.write(out)
        
        out = self.getFiles(rev,'release','debug')
        filename = "DyIO_Firmware_"+rev+"_AVR_debug_"+strftime("%b_%d_%Y", gmtime())+".xml"
        print "Making ",filename
        f=open("../../Dev/"+filename, 'w')
        f.write(out)
        print "OK"
    def getRevision(self):
        f = open('../../../common/include/DyIO/DyIO_def.h', 'r')
        contents=f.read()
        lines=contents.split('\n')
        MAJOR_REV=0
        MINOR_REV=0
        FIRMWARE_VERSION=0
        for l in lines:
            
            if l.find("MAJOR_REV")>=0:
                parts = l.split("MAJOR_REV")
                MAJOR_REV = int(parts[1].strip())
            if l.find("MINOR_REV")>=0:
                parts = l.split("MINOR_REV")
                MINOR_REV= int(parts[1].strip())
            if l.find("FIRMWARE_VERSION")>=0:
                parts = l.split("FIRMWARE_VERSION")
                FIRMWARE_VERSION = int(parts[1].strip())
        f.close()
        return str(MAJOR_REV)+"."+str(MINOR_REV)+"."+str(FIRMWARE_VERSION)
    def getFiles(self,rev,Prelease,Arelease):
        top="""<root>
<revision>"""+rev+"""</revision>
    <core>
        <index>0</index>
        <type>pic32mx440f128h</type>
        <wordSize>4</wordSize>
        <hex>"""
        middle = """</hex>
    </core>
    <core>
        <index>1</index>
        <type>avr_atmegaXX4p</type>
        <wordSize>2</wordSize>
        <hex>"""
        bottom="""</hex>
    </core>
</root>"""
        Afile='../../../avr/output/'+Arelease+'/output.hex'
        f = open(Afile, 'r')
        avr=f.read()
        Pfile = '../../../pic/output/'+Prelease+'/output.hex'
        f = open(Pfile, 'r')
        pic=f.read()
        #print "Using :",Afile," ",Pfile
        return top+pic+middle+avr+bottom
        
if __name__ == '__main__':
    print "Starting main"
    FirmwarePublishDriver()
        
