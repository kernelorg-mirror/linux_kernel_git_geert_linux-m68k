/*
 *  Dummy Ariadne network driver
 *
 *  Copyright 2011 Geert Uytterhoeven
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>


static int ariadne_net_probe(struct platform_device *pdev)
{
	dev_info(&pdev->dev, "%s %p\n", __func__, pdev);
	return 0;
}

static void ariadne_net_remove(struct platform_device *pdev)
{
	dev_info(&pdev->dev, "%s %p\n", __func__, pdev);
}

static struct platform_driver ariadne_net_driver = {
	.driver = {
		.name	= "ariadne-net",
		.owner	= THIS_MODULE,
	},
	.probe	= ariadne_net_probe,
	.remove	= ariadne_net_remove,
};

static int __init ariadne_net_init(void)
{
	return platform_driver_register(&ariadne_net_driver);
}

static void __exit ariadne_net_exit(void)
{
	platform_driver_unregister(&ariadne_net_driver);
}

module_init(ariadne_net_init);
module_exit(ariadne_net_exit);

MODULE_DESCRIPTION("Dummy Ariadne network driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:ariadne-net");
