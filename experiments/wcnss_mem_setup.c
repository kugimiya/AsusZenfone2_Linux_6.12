// SPDX-License-Identifier: GPL-2.0
#include <linux/firmware/qcom/qcom_scm.h>
#include <linux/kernel.h>
#include <linux/kprobes.h>
#include <linux/module.h>

#define WCNSS_PAS_ID	6U
#define WCNSS_PHYS	0x8b600000ULL
#define WCNSS_SIZE	0x600000ULL

static int pre_handler(struct kprobe *p, struct pt_regs *regs)
{
	u32 pas_id = (u32)regs->regs[0];
	int ret;

	if (pas_id != WCNSS_PAS_ID)
		return 0;

	ret = qcom_scm_pas_mem_setup(WCNSS_PAS_ID, WCNSS_PHYS, WCNSS_SIZE);
	pr_info("wcnss_mem_setup: qcom_scm_pas_mem_setup(6, 0x8b600000, 0x600000) = %d\n",
		ret);
	return 0;
}

static struct kprobe kp = {
	.symbol_name = "qcom_scm_pas_init_image",
	.pre_handler = pre_handler,
};

static int __init wcnss_mem_setup_init(void)
{
	int ret;

	ret = register_kprobe(&kp);
	if (ret < 0) {
		pr_err("wcnss_mem_setup: register_kprobe failed: %d\n", ret);
		return ret;
	}

	pr_info("wcnss_mem_setup: kprobe installed at %pS\n", kp.addr);
	return 0;
}

static void __exit wcnss_mem_setup_exit(void)
{
	unregister_kprobe(&kp);
	pr_info("wcnss_mem_setup: kprobe removed\n");
}

module_init(wcnss_mem_setup_init);
module_exit(wcnss_mem_setup_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("PAS mem_setup before WCNSS pas_init_image");
