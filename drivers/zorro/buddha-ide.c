/*
 *  Dummy Buddha IDE driver
 *
 *  Copyright 2012 Geert Uytterhoeven
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>


static int buddha_ide_probe(struct platform_device *pdev)
{
	dev_info(&pdev->dev, "%s %p\n", __func__, pdev);
	return 0;
}

static void buddha_ide_remove(struct platform_device *pdev)
{
	dev_info(&pdev->dev, "%s %p\n", __func__, pdev);
}

static struct platform_driver buddha_ide_driver = {
	.driver = {
		.name	= "buddha-ide",
		.owner	= THIS_MODULE,
	},
	.probe	= buddha_ide_probe,
	.remove	= buddha_ide_remove,
};

static int __init buddha_ide_init(void)
{
	return platform_driver_register(&buddha_ide_driver);
}

static void __exit buddha_ide_exit(void)
{
	platform_driver_unregister(&buddha_ide_driver);
}

module_init(buddha_ide_init);
module_exit(buddha_ide_exit);

MODULE_DESCRIPTION("Dummy Buddha IDE driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:buddha-ide");
