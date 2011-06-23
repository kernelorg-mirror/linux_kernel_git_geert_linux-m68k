/*
 *  Dummy Catweasel floppy driver
 *
 *  Copyright 2012 Geert Uytterhoeven
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>


static int catweasel_floppy_probe(struct platform_device *pdev)
{
	dev_info(&pdev->dev, "%s %p\n", __func__, pdev);
	return 0;
}

static void catweasel_floppy_remove(struct platform_device *pdev)
{
	dev_info(&pdev->dev, "%s %p\n", __func__, pdev);
}

static struct platform_driver catweasel_floppy_driver = {
	.driver = {
		.name	= "catweasel-floppy",
		.owner	= THIS_MODULE,
	},
	.probe	= catweasel_floppy_probe,
	.remove	= catweasel_floppy_remove,
};

static int __init catweasel_floppy_init(void)
{
	return platform_driver_register(&catweasel_floppy_driver);
}

static void __exit catweasel_floppy_exit(void)
{
	platform_driver_unregister(&catweasel_floppy_driver);
}

module_init(catweasel_floppy_init);
module_exit(catweasel_floppy_exit);

MODULE_DESCRIPTION("Dummy Catweasel floppy driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:catweasel-floppy");
