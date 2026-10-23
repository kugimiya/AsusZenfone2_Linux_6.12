#include <linux/module.h>
#include <linux/kprobes.h>
#include <linux/printk.h>
#include <linux/firmware/qcom/qcom_scm.h>

static int pre(struct kprobe *p, struct pt_regs *regs)
{
	int ret;

	if (regs->regs[0] != 6)
		return 0;

	ret = qcom_scm_pas_mem_setup(6, 0x86800000, 0x600000);
	pr_info("wcnss-pas: mem_setup(0x86800000) = %d\n", ret);
	return 0;
}

static struct kprobe kp = {
	.symbol_name = "qcom_scm_pas_init_image",
	.pre_handler = pre,
};

static int __init wcnss_pas_init(void)
{
	return register_kprobe(&kp);
}

static void __exit wcnss_pas_exit(void)
{
	unregister_kprobe(&kp);
}

module_init(wcnss_pas_init);
module_exit(wcnss_pas_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Assign the WCNSS PIL region before image authentication");
