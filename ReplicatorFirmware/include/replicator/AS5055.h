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
				unsigned PAR:1;
				unsigned Address:14;
				unsigned RWn:1;
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
				unsigned PAR:1;
                                unsigned EF:1;
				unsigned Data:14;
			} regs;
		} AS5055ReadPacket;

typedef union __attribute__((__packed__)) _AS5055AngularDataPacket
		{
			UINT16	uint0_15;
                        struct
			{
                            UINT8   ubyte0_7;
                            UINT8   ubyte8_15;
                        } bytes;
			struct
			{
				unsigned PAR:1;
                                unsigned EF:1;
				unsigned Data:12;
                                unsigned AlarmLO:1;
                                unsigned AlarmHI:1;
			} regs;
		} AS5055AngularDataPacket;
typedef union __attribute__((__packed__)) _AS5055SystemConfigPacket
		{
			UINT16	uint0_15;
                        struct
			{
                            UINT8   ubyte0_7;
                            UINT8   ubyte8_15;
                        } bytes;
			struct
			{
				unsigned PAR:1;
                                unsigned EF:1;
                                unsigned unused:2;
                                unsigned break_loop:1;
                                unsigned gain:2;
                                unsigned bw:2;
				unsigned invert:1;
                                unsigned id:3;
                                unsigned resolution:2;
			} regs;
		} AS5055SystemConfigPacket;

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
				unsigned PAR:1;
                                unsigned unassigned1:1;
				unsigned Data:14;
			} regs;
		} AS5055WritePacket;

// See 7.2.4 in AS5055 Datasheet
        #define     AS5055_READ                         1
        #define     AS5055_WRITE                        0

        #define     AS5055REG_PowerOnReset              0x3f22
        #define     AS5055REG_SoftwareReset             0x3c00
        #define     AS5055REG_ClearErrorFlagReset       0x3380
        #define     AS5055REG_NoOperation               0x0000
        #define     AS5055REG_AutomaticGainControl      0x3ff8
        #define     AS5055REG_AngularData               0x3fff
        #define     AS5055REG_SystemConfig1             0x3f20

UINT8   AS5055CalculateParity(UINT16 data);

UINT16 AS5055readAngle(BYTE index);

void initializeEncoders();

void EncoderSS(BYTE index, BYTE state);