/*
 *  X-Surf Multifunction driver
 *
 *  Copyright 2012 Geert Uytterhoeven
 *
 *  The X-Surf is a Zorro-II board made by Individual Computers.
 *  It contains a Realtek RTL8019AS Ethernet Controller and 2 IDE interfaces.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/zorro.h>
#include <linux/mfd/core.h>


static const struct mfd_cell xsurf_mfd_cells[] = {
	{
		.name		= "zorro8390",
//		.platform_data	= xxx,
//		.pdata_size	= xxx,
		.num_resources	= 1,
		.resources	= (const struct resource []) {
			{
				.start	= 0x8600,
				.end	= 0x867f,
				.name	= "RTL8019AS"
			}
		}
	}, {
		.name		= "buddha-ide",
		.id		= 0,
//		.platform_data	= xxx,
//		.pdata_size	= xxx,
		.num_resources	= 2,
		.resources	= (const struct resource []) {
			{
				.start	= 0x800,
				.end	= 0x9ff,
				.name	= "IDE"
			}, {
				.start	= 0xf00,
				.end	= 0xf00,
				.name	= "IRQ"
			}
		}
	}, {
		.name		= "buddha-ide",
		.id		= 1,
//		.platform_data	= xxx,
//		.pdata_size	= xxx,
		.num_resources	= 2,
		.resources	= (const struct resource []) {
			{
				.start	= 0xa00,
				.end	= 0xbff,
				.name	= "IDE"
			}, {
				.start	= 0xf40,
				.end	= 0xf40,
				.name	= "IRQ"
			}
		}
	}
};


static int xsurf_mfd_probe(struct zorro_dev *z,
			   const struct zorro_device_id *ent)
{
	unsigned long base = z->resource.start;
	int error;

	dev_info(&z->dev, "X-Surf at 0x%08lx\n", base);

	/* Catweasel has 3 buddha-ide cells, hence enumeration id times 3 */
	error = mfd_add_devices(&z->dev, z->dev.id * 3, xsurf_mfd_cells,
				ARRAY_SIZE(xsurf_mfd_cells), &z->resource,
				0, NULL);
	if (error) {
		dev_err(&z->dev, "mfd_add_devices() failed %d\n", error);
		return error;
	}
	return 0;
}

static void xsurf_mfd_remove(struct zorro_dev *z)
{
	mfd_remove_devices(&z->dev);
}

static struct zorro_device_id xsurf_mfd_ids[] = {
	{ ZORRO_PROD_INDIVIDUAL_COMPUTERS_X_SURF },
	{ 0 }
};
MODULE_DEVICE_TABLE(zorro, xsurf_mfd_ids);

static struct zorro_driver xsurf_mfd_driver = {
	.name		= "xsurf-mfd",
	.id_table	= xsurf_mfd_ids,
	.probe		= xsurf_mfd_probe,
	.remove		= xsurf_mfd_remove,
};

static int __init xsurf_mfd_init(void)
{
	return zorro_register_driver(&xsurf_mfd_driver);
}

static void __exit xsurf_mfd_exit(void)
{
	zorro_unregister_driver(&xsurf_mfd_driver);
}

module_init(xsurf_mfd_init);
module_exit(xsurf_mfd_exit);

MODULE_DESCRIPTION("X-Surf Multifunction driver");
MODULE_LICENSE("GPL");
