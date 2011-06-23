/*
 *  Ariadne Multifunction driver
 *
 *  Copyright 2011 Geert Uytterhoeven
 *
 *  The Ariadne is a Zorro-II board made by Village Tronic. It contains:
 *
 *	- an Am79C960 PCnet-ISA Single-Chip Ethernet Controller with both
 *	  10BASE-2 (thin coax) and 10BASE-T (UTP) connectors
 *
 *	- an MC68230 Parallel Interface/Timer configured as 2 parallel ports
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/zorro.h>
#include <linux/mfd/core.h>

#include <asm/byteorder.h>


static const struct mfd_cell ariadne_mfd_cells[] = {
	{
		.name		= "ariadne-net",
//		.platform_data	= xxx,
//		.pdata_size	= xxx,
		.num_resources	= 3,
		.resources	= (const struct resource []) {
			{
				.start	= 0x360,
				.end	= 0x377,
				.name	= "Am79C960"
			}, {
				.start	= 0x4000,
				.end	= 0x7fff,
				.name	= "Boot ROM"
			}, {
				.start	= 0x8000,
				.end	= 0xffff,
				.name	= "RAM"
			}
		}
	}, {
		.name		= "ariadne-par",
//		.platform_data	= xxx,
//		.pdata_size	= xxx,
		.num_resources	= 2,
		.resources	= (const struct resource []) {
			{
				.start	= 0x1000,
				.end	= 0x103f,
				.name	= "MC68230"
			}
		}
	}
};


static int ariadne_mfd_probe(struct zorro_dev *z,
			     const struct zorro_device_id *ent)
{
	unsigned long base = z->resource.start;
	char mac[6] = { 0x00, 0x60, 0x30, };
	u32 serial;
	int error;

	dev_info(&z->dev, "Ariadne at 0x%08lx\n", base);

	/*
	 * Function 1: Am79C960 PCnet-ISA Ethernet
	 *
	 *   1.1. struct Am79C960 (24 bytes) at offset 0x360
	 *   1.2. 16 KiB of boot ROM at offset 0x4000
	 *   1.3. 32 KiB of RAM at offset 0x8000
	 *
	 * MAC address 00:60:30:xx:yy:zz
	 */

	serial = be32_to_cpu(z->rom.er_SerialNumber);
	mac[3] = (serial >> 16) & 0xff;
	mac[4] = (serial >> 8) & 0xff;
	mac[5] = serial & 0xff;

	dev_info(&z->dev, "    Ethernet Address %pM\n", mac);

	/*
	 * Function 2: MC68230 Parallel Interface/Timer
	 *
	 *   2.1. 64 bytes of struct MC68230 at offset 0x1000
	 */

	error = mfd_add_devices(&z->dev, z->dev.id, ariadne_mfd_cells,
				ARRAY_SIZE(ariadne_mfd_cells), &z->resource,
				0, NULL);
	if (error) {
		dev_err(&z->dev, "mfd_add_devices() failed %d\n", error);
		return error;
	}
	return 0;
}

static void ariadne_mfd_remove(struct zorro_dev *z)
{
	mfd_remove_devices(&z->dev);
}

static struct zorro_device_id ariadne_mfd_ids[] = {
	{ ZORRO_PROD_VILLAGE_TRONIC_ARIADNE },
	{ 0 }
};
MODULE_DEVICE_TABLE(zorro, ariadne_mfd_ids);

static struct zorro_driver ariadne_mfd_driver = {
	.name		= "ariadne-mfd",
	.id_table	= ariadne_mfd_ids,
	.probe		= ariadne_mfd_probe,
	.remove		= ariadne_mfd_remove,
};

static int __init ariadne_mfd_init(void)
{
	return zorro_register_driver(&ariadne_mfd_driver);
}

static void __exit ariadne_mfd_exit(void)
{
	zorro_unregister_driver(&ariadne_mfd_driver);
}

module_init(ariadne_mfd_init);
module_exit(ariadne_mfd_exit);

MODULE_DESCRIPTION("Ariadne Multifunction driver");
MODULE_LICENSE("GPL");
