/*
 *  Ariadne II Multifunction driver
 *
 *  Copyright 2012 Geert Uytterhoeven
 *
 *  The Ariadne is a Zorro-II board made by Village Tronic.
 *  It contains a Realtek RTL8019AS Ethernet Controller.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/zorro.h>
#include <linux/mfd/core.h>


static const struct mfd_cell ariadne2_mfd_cells[] = {
	{
		.name		= "zorro8390",
//		.platform_data	= xxx,
//		.pdata_size	= xxx,
		.num_resources	= 1,
		.resources	= (const struct resource []) {
			{
				.start	= 0x600,
				.end	= 0x67f,
				.name	= "RTL8019AS"
			}
		}
	}
};


static int ariadne2_mfd_probe(struct zorro_dev *z,
			      const struct zorro_device_id *ent)
{
	unsigned long base = z->resource.start;
	int error;

	dev_info(&z->dev, "Ariadne II at 0x%08lx\n", base);

	/*
	 * Function 1: Realtek RTL8019AS Ethernet
	 *
	 *   1.1. RTL8019AS at offset 0x600
	 *   1.2. 16 KiB of boot ROM at offset 0x4000
	 *   1.3. 32 KiB of RAM at offset 0x8000
	 */

	error = mfd_add_devices(&z->dev, z->dev.id, ariadne2_mfd_cells,
				ARRAY_SIZE(ariadne2_mfd_cells), &z->resource,
				0, NULL);
	if (error) {
		dev_err(&z->dev, "mfd_add_devices() failed %d\n", error);
		return error;
	}
	return 0;
}

static void ariadne2_mfd_remove(struct zorro_dev *z)
{
	mfd_remove_devices(&z->dev);
}

static struct zorro_device_id ariadne2_mfd_ids[] = {
	{ ZORRO_PROD_VILLAGE_TRONIC_ARIADNE2 },
	{ 0 }
};
MODULE_DEVICE_TABLE(zorro, ariadne2_mfd_ids);

static struct zorro_driver ariadne2_mfd_driver = {
	.name		= "ariadne2-mfd",
	.id_table	= ariadne2_mfd_ids,
	.probe		= ariadne2_mfd_probe,
	.remove		= ariadne2_mfd_remove,
};

static int __init ariadne2_mfd_init(void)
{
	return zorro_register_driver(&ariadne2_mfd_driver);
}

static void __exit ariadne2_mfd_exit(void)
{
	zorro_unregister_driver(&ariadne2_mfd_driver);
}

module_init(ariadne2_mfd_init);
module_exit(ariadne2_mfd_exit);

MODULE_DESCRIPTION("Ariadne II Multifunction driver");
MODULE_LICENSE("GPL");
