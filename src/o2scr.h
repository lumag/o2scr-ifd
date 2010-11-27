#ifndef O2SCR_H
#define O2SCR_H

#define O2SCR_ATR_SIZE	0x40

#define O2SCR_RESET	_IO('o', 0x01)
#define O2SCR_STATUS	_IOW('o', 0x02, unsigned short)
#define O2SCR_PON	_IO('o', 0x03)
#define O2SCR_POFF	_IO('o', 0x04)
#define O2SCR_GET_ATR	_IOW('o', 0x05, unsigned char[O2SCR_ATR_SIZE])

/* STATUS_EXCH */
#define BAD_TS          0x8000
#define BAD_PB          0x4000
#define ERR_PAR         0x2000
#define ERR_EXE         0x1000
#define TOC             0x0800
#define TOB             0x0400
#define TOR             0x0200
#define CRD_INS         0x0080
#define CRD_ON          0x0040
#define FIFO_FULL       0x0002
#define FIFO_EMPTY      0x0001


#ifdef __KERNEL__

#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/irqreturn.h>

struct o2scr_info {
	struct pcmcia_device	*p_dev;
	struct device		dev;
	struct cdev		char_dev;
	int			id;
	unsigned long		flags;
	void __iomem		*io;
	void __iomem		*mem;

	unsigned char		atr[O2SCR_ATR_SIZE];
	int			atr_len;
};

enum {
	O2SCR_DEV_BUSY,
};

irqreturn_t o2scr_interrupt(int irq, void *dev_id);

int o2scr_dev_add(struct o2scr_info *info, struct device *parent);
void o2scr_dev_remove(struct o2scr_info *info);

int o2scr_dev_init(void);
void o2scr_dev_exit(void);

#endif

#endif
