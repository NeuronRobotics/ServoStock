void initBackplaneHardware(void);
void initBackplanePowerMgmnt(void);
UINT16 Get5vRailVoltage(void);
UINT16 Get12vRailVoltage(void);
UINT16 Get48vRailVoltage(void);
void initBackplaneVoltageSenseRelays(void);

// This is a hack to deal with board E SPI short issue.
//#define swapEandF


// IO Mappigns for Relay Controll
#define Engaged             1
#define Disengaged          0

#define Relay5v             _RG14
#define Relay12v            _RA6
#define Relay48v            _RG14

#define Relay5_GPIO_TRIS    _TRISG14
#define Relay12_GPIO_TRIS   _TRISA6
#define Relay48_GPIO_TRIS   _RA7

//IO Mappings for Boards A-H

// Configure TRIS on all IO to the corrrect type
#define ConfigureCardIO()   {\
(BoardA_IRQ_TRIS)       =   INPUT;\
(BoardA_CS_TRIS)        =   OUTPUT;\
(BoardB_IRQ_TRIS)       =   INPUT;\
(BoardB_CS_TRIS)        =   OUTPUT;\
(BoardC_IRQ_TRIS)       =   INPUT;\
(BoardC_CS_TRIS)        =   OUTPUT;\
(BoardD_IRQ_TRIS)       =   INPUT;\
(BoardD_CS_TRIS)        =   OUTPUT;\
(BoardE_IRQ_TRIS)       =   INPUT;\
(BoardE_CS_TRIS)        =   OUTPUT;\
(BoardF_IRQ_TRIS)       =   INPUT;\
(BoardF_CS_TRIS)        =   OUTPUT;\
(BoardG_IRQ_TRIS)       =   INPUT;\
(BoardG_CS_TRIS)        =   OUTPUT;\
(BoardH_IRQ_TRIS)       =   INPUT;\
(BoardH_CS_TRIS)        =   OUTPUT;\
(BoardA_Detect_TRIS)    =   INPUT;\
(BoardB_Detect_TRIS)    =   INPUT;\
(BoardC_Detect_TRIS)    =   INPUT;\
(BoardD_Detect_TRIS)    =   INPUT;\
(BoardE_Detect_TRIS)    =   INPUT;\
(BoardF_Detect_TRIS)    =   INPUT;\
(BoardG_Detect_TRIS)    =   INPUT;\
(BoardH_Detect_TRIS)    =   INPUT;\
}  

// De-Select all cards
#define CardCSSelectNone(){\
(BoardA_CS) =   NOT_ASSERTED;\
(BoardB_CS) =   NOT_ASSERTED;\
(BoardC_CS) =   NOT_ASSERTED;\
(BoardD_CS) =   NOT_ASSERTED;\
(BoardE_CS) =   NOT_ASSERTED;\
(BoardF_CS) =   NOT_ASSERTED;\
(BoardG_CS) =   NOT_ASSERTED;\
(BoardH_CS) =   NOT_ASSERTED;\
}




// GPIO Mappings
#define BoardA_CS_TRIS      _TRISE7
#define BoardA_IRQ_TRIS       _TRISG13
#define BoardA_CS           _RE7
#define BoardA_IRQ          _RG13

#define BoardB_CS_TRIS      _TRISE6
#define BoardB_IRQ_TRIS       _TRISG0
#define BoardB_CS           _RE6
#define BoardB_IRQ          _RG0

#define BoardC_CS_TRIS      _TRISE5
#define BoardC_IRQ_TRIS       _TRISG1
#define BoardC_CS           _RE5
#define BoardC_IRQ          _RG1

#define BoardD_CS_TRIS      _TRISE4
#define BoardD_IRQ_TRIS     _TRISF1
#define BoardD_CS           _RE4
#define BoardD_IRQ          _RF1


#ifdef swapEandF
    #define BoardF_CS_TRIS      _TRISE3
    #define BoardF_IRQ_TRIS     _TRISF0
    #define BoardF_CS           _RE3
    #define BoardF_IRQ          _RF0

    #define BoardE_CS_TRIS      _TRISE2
    #define BoardE_IRQ_TRIS      _TRISD2
    #define BoardE_CS           _RE2
    #define BoardE_IRQ          _RD2
#else
    #define BoardE_CS_TRIS      _TRISE3
    #define BoardE_IRQ_TRIS     _TRISF0
    #define BoardE_CS           _RE3
    #define BoardE_IRQ          _RF0

    #define BoardF_CS_TRIS      _TRISE2
    #define BoardF_IRQ_TRIS      _TRISD2
    #define BoardF_CS           _RE2
    #define BoardF_IRQ          _RD2
#endif

#define BoardG_CS_TRIS      _TRISE1
#define BoardG_IRQ_TRIS     _TRISD13
#define BoardG_CS           _RE1
#define BoardG_IRQ          _RD13

#define BoardH_CS_TRIS      _TRISE0
#define BoardH_IRQ_TRIS      _TRISD6
#define BoardH_CS           _RE0
#define BoardH_IRQ          _RD6

// Card Detect
#define BoardA_Detect_TRIS  _TRISC2
#define BoardA_Detect       _RC2
#define BoardB_Detect_TRIS  _TRISC1
#define BoardB_Detect       _RC1
#define BoardC_Detect_TRIS  _TRISG7
#define BoardC_Detect       _RG7
#define BoardD_Detect_TRIS  _TRISG6
#define BoardD_Detect       _RG6

#ifdef swapEandF
    #define BoardF_Detect_TRIS  _TRISC4
    #define BoardF_Detect       _RC4
    #define BoardE_Detect_TRIS  _TRISC3
    #define BoardE_Detect       _RC3
#else
    #define BoardE_Detect_TRIS  _TRISC4
    #define BoardE_Detect       _RC4
    #define BoardF_Detect_TRIS  _TRISC3
    #define BoardF_Detect       _RC3
#endif
#define BoardG_Detect_TRIS  _TRISF5
#define BoardG_Detect       _RF5
#define BoardH_Detect_TRIS  _TRISF4
#define BoardH_Detect       _RF4