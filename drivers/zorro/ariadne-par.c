/*
 *  Dummy Ariadne parport driver
 *
 *  Copyright 2011 Geert Uytterhoeven
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>


static int ariadne_par_probe(struct platform_device *pdev)
{
	dev_info(&pdev->dev, "%s %p\n", __func__, pdev);
	return 0;
}

static void ariadne_par_remove(struct platform_device *pdev)
{
	dev_info(&pdev->dev, "%s %p\n", __func__, pdev);
}

static struct platform_driver ariadne_par_driver = {
	.driver = {
		.name	= "ariadne-par",
		.owner	= THIS_MODULE,
	},
	.probe	= ariadne_par_probe,
	.remove	= ariadne_par_remove,
};

static int __init ariadne_par_init(void)
{
	return platform_driver_register(&ariadne_par_driver);
}

static void __exit ariadne_par_exit(void)
{
	platform_driver_unregister(&ariadne_par_driver);
}

module_init(ariadne_par_init);
module_exit(ariadne_par_exit);

MODULE_DESCRIPTION("Dummy Ariadne parport driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:ariadne-par");
