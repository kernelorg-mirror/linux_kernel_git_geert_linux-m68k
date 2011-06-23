/*
 *  Dummy 8390 cell driver
 *
 *  Copyright 2012 Geert Uytterhoeven
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>


static int ns8390_cell_probe(struct platform_device *pdev)
{
	dev_info(&pdev->dev, "%s %p\n", __func__, pdev);
	return 0;
}

static void ns8390_cell_remove(struct platform_device *pdev)
{
	dev_info(&pdev->dev, "%s %p\n", __func__, pdev);
}

static struct platform_driver ns8390_cell_driver = {
	.driver = {
		.name	= "8390-cell",
		.owner	= THIS_MODULE,
	},
	.probe	= ns8390_cell_probe,
	.remove	= ns8390_cell_remove,
};

static int __init ns8390_cell_init(void)
{
	return platform_driver_register(&ns8390_cell_driver);
}

static void __exit ns8390_cell_exit(void)
{
	platform_driver_unregister(&ns8390_cell_driver);
}

module_init(ns8390_cell_init);
module_exit(ns8390_cell_exit);

MODULE_DESCRIPTION("Dummy 8390 cell driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:8390-cell");
