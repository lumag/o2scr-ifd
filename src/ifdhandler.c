#include <ifdhandler.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <string.h>

#include "o2scr.h"

static int reader_fd = -1;

RESPONSECODE IFDHCreateChannelByName(DWORD Lun, LPSTR DeviceName)
{
	reader_fd = open(DeviceName, O_RDWR);
	if (reader_fd < 0) {
		struct stat st;
		if (stat(DeviceName, &st))
			return IFD_NO_SUCH_DEVICE;
		else
			return IFD_COMMUNICATION_ERROR;
	}

	if (ioctl(reader_fd, O2SCR_RESET, NULL))
		return IFD_COMMUNICATION_ERROR;

	return IFD_SUCCESS;
}

RESPONSECODE IFDHCreateChannel(DWORD Lun, DWORD Channel)
{
	char buf[40];
	snprintf(buf, sizeof(buf), "/dev/o2scr%d", Channel);
	return IFDHCreateChannelByName(Lun, buf);
}

RESPONSECODE IFDHCloseChannel(DWORD Lun)
{
	if (close(reader_fd))
		return IFD_COMMUNICATION_ERROR;
	else
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
	int ret;
	char atr[O2SCR_ATR_SIZE];
	switch (Action) {
	case IFD_POWER_DOWN:
		ret = ioctl(reader_fd, O2SCR_POFF, NULL);
		if (AtrLength)
			*AtrLength = 0;
		if (ret)
			return IFD_ERROR_POWER_ACTION;
		else
			return IFD_SUCCESS;
		break;
	case IFD_POWER_UP:
		ret = ioctl(reader_fd, O2SCR_PON, NULL);
		if (ret < 0) {
			*AtrLength = 0;
			return IFD_ERROR_POWER_ACTION;
		}
		ret = ioctl(reader_fd, O2SCR_GET_ATR, atr);
		if (ret < 0) {
			*AtrLength = 0;
			return IFD_COMMUNICATION_ERROR;
		}
		if (ret < *AtrLength)
			*AtrLength = ret;
		memcpy(Atr, atr, *AtrLength);
		return IFD_SUCCESS;
	case IFD_RESET:
		ret = ioctl(reader_fd, O2SCR_WARM_RST, NULL);
		if (ret < 0) {
			*AtrLength = 0;
			return IFD_ERROR_POWER_ACTION;
		}
		ret = ioctl(reader_fd, O2SCR_GET_ATR, atr);
		if (ret < 0) {
			*AtrLength = 0;
			return IFD_COMMUNICATION_ERROR;
		}
		if (ret < *AtrLength)
			*AtrLength = ret;
		memcpy(Atr, atr, *AtrLength);
		return IFD_SUCCESS;
	default:
		return IFD_NOT_SUPPORTED;
	}
}

RESPONSECODE IFDHTransmitToICC (DWORD Lun, SCARD_IO_HEADER SendPci, PUCHAR TxBuffer, DWORD TxLength, PUCHAR RxBuffer, PDWORD RxLength, PSCARD_IO_HEADER RecvPci)
{
	return IFD_NOT_SUPPORTED;
}

RESPONSECODE IFDHICCPresence (DWORD Lun)
{
	int ret;
	unsigned short st;

	ret = ioctl(reader_fd, O2SCR_STATUS, &st);
	if (ret < 0)
		return IFD_COMMUNICATION_ERROR;

	if (st & CRD_INS)
		return IFD_SUCCESS;
	else
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
