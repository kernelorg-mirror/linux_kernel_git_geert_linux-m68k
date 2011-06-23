/*
 *  Catweasel Multifunction driver
 *
 *  Copyright 2012 Geert Uytterhoeven
 *
 *  The Catweasel is a Zorro-II board made by Individual Computers.
 *  It contains a floppy interface and 3 IDE interfaces.
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/zorro.h>
#include <linux/mfd/core.h>


static const struct mfd_cell catweasel_mfd_cells[] = {
	{
		.name		= "catweasel-floppy",
		.id		= 0,
//		.platform_data	= xxx,
//		.pdata_size	= xxx,
		.num_resources	= 1,
		.resources	= (const struct resource []) {
			{
				.start	= 0x400,
				.end	= 0x4ff,
				.name	= "floppy"
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
	}, {
		.name		= "buddha-ide",
		.id		= 2,
//		.platform_data	= xxx,
//		.pdata_size	= xxx,
		.num_resources	= 2,
		.resources	= (const struct resource []) {
			{
				.start	= 0xc00,
				.end	= 0xdff,
				.name	= "IDE"
			}, {
				.start	= 0xf80,
				.end	= 0xf80,
				.name	= "IRQ"
			}
		}
	}
};


static int catweasel_mfd_probe(struct zorro_dev *z,
			       const struct zorro_device_id *ent)
{
	unsigned long base = z->resource.start;
	int error;

	dev_info(&z->dev, "Catweasel at 0x%08lx\n", base);

	/* Catweasel has 3 buddha-ide cells, hence enumeration id times 3 */
	error = mfd_add_devices(&z->dev, z->dev.id * 3, catweasel_mfd_cells,
				ARRAY_SIZE(catweasel_mfd_cells), &z->resource,
				0, NULL);
	if (error) {
		dev_err(&z->dev, "mfd_add_devices() failed %d\n", error);
		return error;
	}
	return 0;
}

static void catweasel_mfd_remove(struct zorro_dev *z)
{
	mfd_remove_devices(&z->dev);
}

static struct zorro_device_id catweasel_mfd_ids[] = {
	{ ZORRO_PROD_INDIVIDUAL_COMPUTERS_CATWEASEL },
	{ 0 }
};
MODULE_DEVICE_TABLE(zorro, catweasel_mfd_ids);

static struct zorro_driver catweasel_mfd_driver = {
	.name		= "catweasel-mfd",
	.id_table	= catweasel_mfd_ids,
	.probe		= catweasel_mfd_probe,
	.remove		= catweasel_mfd_remove,
};

static int __init catweasel_mfd_init(void)
{
	return zorro_register_driver(&catweasel_mfd_driver);
}

static void __exit catweasel_mfd_exit(void)
{
	zorro_unregister_driver(&catweasel_mfd_driver);
}

module_init(catweasel_mfd_init);
module_exit(catweasel_mfd_exit);

MODULE_DESCRIPTION("Catweasel Multifunction driver");
MODULE_LICENSE("GPL");
