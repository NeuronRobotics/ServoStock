typedef union __attribute__((__packed__)) _AS5055CommandPacket
		{
			UINT16	uint0_15;
                        struct
			{
                            UINT8   ubyte0_7;
                            UINT8   ubyte8_15;
                        } bytes;
			struct
			{
				unsigned int PAR:1;
				unsigned int Address:14;
				unsigned int RWn:1;
			} regs;
		} AS5055CommandPacket;

typedef union __attribute__((__packed__)) _AS5055ReadPacket
		{
			UINT16	uint0_15;
                        struct
			{
                            UINT8   ubyte0_7;
                            UINT8   ubyte8_15;
                        } bytes;
			struct
			{
				unsigned int PAR:1;
                                unsigned int EF:1;
				unsigned int Data:14;
			} regs;
		} AS5055ReadPacket;

typedef union __attribute__((__packed__)) _AS5055WritePacket
		{
			UINT16	uint0_15;
                        struct
			{
                            UINT8   ubyte0_7;
                            UINT8   ubyte8_15;
                        } bytes;
			struct
			{
				unsigned int PAR:1;
                                unsigned int unassigned1:1;
				unsigned int Data:14;
			} regs;
		} AS5055WritePacket;

// See 7.2.4 in AS5055 Datasheet
        #define     AS5055REG_PowerOnReset              0x3f22
        #define     AS5055REG_SoftwareReset             0x3c00
        #define     AS5055REG_ClearErrorFlagReset       0x3380
        #define     AS5055REG_NoOperation               0x0000
        #define     AS5055REG_AutomaticGainControl      0x3ff8
        #define     AS5055REG_AngularData               0x3fff
        #define     AS5055REG_SystemConfig1             0x3f20

UINT8   AS5055CalculateParity(UINT16 data);