/*************************************************************************
 * Processor-specific object file.  Contains SFR definitions.
 *Updated for Neuron Robotics Bootloader
 *************************************************************************/
INPUT("processor.o")

OPTIONAL("libmchp_peripheral.a")
OPTIONAL("libmchp_peripheral_32MX440F128H.a")


/*************************************************************************
 * For interrupt vector handling
 *************************************************************************/
PROVIDE(_vector_spacing = 0x00000001);
_ebase_address  = 0x9D00A000;

/*************************************************************************
 * Memory Address Equates
 *************************************************************************/
_RESET_ADDR              = 0x9D00B000;
_BEV_EXCPT_ADDR          = 0x9D00B380;
_DBG_EXCPT_ADDR          = 0x9D00B480;
_DBG_CODE_ADDR           = 0xBFC02000;
_GEN_EXCPT_ADDR          = _ebase_address + 0x180;

/*************************************************************************
 * Memory Regions
 *
 * Memory regions without attributes cannot be used for orphaned sections.
 * Only sections specifically assigned to these regions can be allocated
 * into these regions.
 *************************************************************************/
MEMORY
{
  kseg0_program_mem    (rx)  : ORIGIN = 0x9D00BA00, LENGTH = 0x13600
  kseg0_boot_mem             : ORIGIN = 0x9D00B490, LENGTH = 0x970
  kseg1_boot_mem             : ORIGIN = 0x9D00B000, LENGTH = 0x490
  exception_mem              : ORIGIN = 0x9D00A000, LENGTH = 0x1000
  
  debug_exec_mem             : ORIGIN = 0xBFC02000, LENGTH = 0xFF0
  config3                    : ORIGIN = 0xBFC02FF0, LENGTH = 0x4
  config2                    : ORIGIN = 0xBFC02FF4, LENGTH = 0x4
  config1                    : ORIGIN = 0xBFC02FF8, LENGTH = 0x4
  config0                    : ORIGIN = 0xBFC02FFC, LENGTH = 0x4
  

  boot_software_key          : ORIGIN = 0xA0000000, LENGTH = 0x4
  mac_address1		         : ORIGIN = 0xA0000004, LENGTH = 0x4
  mac_address2		         : ORIGIN = 0xA0000008, LENGTH = 0x4
  kseg1_data_mem       (w!x) : ORIGIN = 0xA000000c, LENGTH = 0x7FF4
  
  sfrs                       : ORIGIN = 0xBF800000, LENGTH = 0x100000
}
SECTIONS
{

  .boot_software_key_sec : {
    *(.boot_software_key_sec)
  } > boot_software_key
  .mac_address1_sec : {
    *(.mac_address1_sec)
  } > mac_address1
  
    .mac_address2_sec : {
    *(.mac_address2_sec)
  } > mac_address2
  
  .config_BFC02FF0 : {
    KEEP(*(.config_BFC02FF0))
  } > config3
  .config_BFC02FF4 : {
    KEEP(*(.config_BFC02FF4))
  } > config2
  .config_BFC02FF8 : {
    KEEP(*(.config_BFC02FF8))
  } > config1
  .config_BFC02FFC : {
    KEEP(*(.config_BFC02FFC))
  } > config0
}
