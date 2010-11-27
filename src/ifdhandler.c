#include <ifdhandler.h>

#include <stdio.h>

RESPONSECODE IFDHCreateChannelByName(DWORD Lun, LPSTR DeviceName)
{
	return IFD_NO_SUCH_DEVICE;
}

RESPONSECODE IFDHCreateChannel(DWORD Lun, DWORD Channel)
{
	char buf[40];
	snprintf(buf, sizeof(buf), "/dev/o2scr%d", Channel);
	return IFDHCreateChannelByName(Lun, buf);
}

RESPONSECODE IFDHCloseChannel(DWORD Lun)
{
	return IFD_SUCCESS;
}

RESPONSECODE IFDHGetCapabilities (DWORD Lun, DWORD Tag, PDWORD Length, PUCHAR Value)
{
	// FIXME
	(*Length) = 0;
	return IFD_ERROR_TAG;
}

RESPONSECODE IFDHSetCapabilities (DWORD Lun, DWORD Tag, DWORD Length, PUCHAR Value)
{
	return IFD_NOT_SUPPORTED;
}

RESPONSECODE IFDHPowerICC (DWORD Lun, DWORD Action, PUCHAR Atr, PDWORD AtrLength)
{
	return IFD_NOT_SUPPORTED;
}

RESPONSECODE IFDHTransmitToICC (DWORD Lun, SCARD_IO_HEADER SendPci, PUCHAR TxBuffer, DWORD TxLength, PUCHAR RxBuffer, PDWORD RxLength, PSCARD_IO_HEADER RecvPci)
{
	return IFD_NOT_SUPPORTED;
}

RESPONSECODE IFDHICCPresence (DWORD Lun)
{
	return IFD_ICC_NOT_PRESENT;
}

RESPONSECODE IFDHControl (DWORD Lun, DWORD dwControlCode, PUCHAR TxBuffer, DWORD TxLength, PUCHAR RxBuffer, DWORD RxLength, LPDWORD pdwBytesReturned)
{
	return IFD_NOT_SUPPORTED;
}

RESPONSECODE IFDHSetProtocolParameters (DWORD Lun, DWORD Protocol, UCHAR Flags, UCHAR PTS1, UCHAR PTS2, UCHAR PTS3)
{
	return IFD_NOT_SUPPORTED;
}
