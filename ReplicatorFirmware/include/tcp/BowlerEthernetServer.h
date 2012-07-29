#include <TCPIP-BSD/tcpip_bsd.h>
#include "system_services.h"
#include "EthernetController.h"
PRIVATE BOOL _AcceptConnection(void);
PRIVATE void _CloseConnection(SOCKET socket);
PRIVATE int _GetTCPRecv(SOCKET socket, BYTE *data, int *data_len);
//PRIVATE BYTE _ParseFTPString(BYTE *ftp_str, BYTE **arg, BYTE max_arg);
//PRIVATE FTP_COMMAND _GetFTPCommand(BYTE *cmd_str);
//PRIVATE BOOL _ExecuteFTPCommand(FTP_COMMAND cmd, BYTE **arg);
//PRIVATE BOOL _FTPQuit(void);
//PRIVATE BOOL _FTPPutFile(BYTE *filename);
PRIVATE int _SendData(SOCKET socket, BYTE *buf, int len);
//PRIVATE BOOL _FTPGetFile(BYTE *filename);

void InitializeBowlerEthernetServer(int port);

BOOL checkBowlerEthernetServer(BowlerPacket * Packet);

