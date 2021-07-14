#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/pci.h>
#include <linux/types.h>
#include <linux/pci_regs.h>

static int nic1g_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	int err;
	u16 vid, did;

	err = pci_enable_device_mem(pdev);
	if (err)
		return err;

	pci_set_master(pdev);

	pci_read_config_word(pdev, PCI_VENDOR_ID, &vid);
	pci_read_config_word(pdev, PCI_DEVICE_ID, &did);

	printk("vendor id: %x, device id: %x\n", vid, did);
	

	printk("nic1g_prove called\n");

	return 0;
}

static void nic1g_remove(struct pci_dev *pdev)
{
	printk("nic1g_remove called\n");

	pci_disable_device(pdev);
}

static const struct pci_device_id nic1g_pci_tbl[] = {
	{ PCI_VDEVICE(INTEL, 0x10D3) },
	{ 0, },
};
MODULE_DEVICE_TABLE(pci, nic1g_pci_tbl);

static struct pci_driver nic1g_pci_driver = {
	.name		= "nic1g",
	.id_table	= nic1g_pci_tbl,
	.probe		= nic1g_probe,
	.remove		= nic1g_remove,
};

static int __init nic1g_init_module(void)
{
	pr_info("mhkim nic driver\n");

	return pci_register_driver(&nic1g_pci_driver);
}
module_init(nic1g_init_module);

static void __exit nic1g_exit_module(void)
{
	pci_unregister_driver(&nic1g_pci_driver);
}
module_exit(nic1g_exit_module);

MODULE_AUTHOR("Minho Kim");
MODULE_DESCRIPTION("mhkim nic driver");
MODULE_LICENSE("GPL v2");

