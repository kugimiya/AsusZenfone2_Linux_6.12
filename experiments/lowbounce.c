#include <linux/module.h>
#include <linux/kprobes.h>
#include <linux/fs.h>
#include <linux/gfp.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/string.h>

#define LOW_LIMIT 0x86000000ULL
#define META_MAX 8192

typedef void (*clean_fn)(unsigned long start, unsigned long end);

static clean_fn dcache_clean = (clean_fn)0xffffcf567e02c89c;
static struct page *stash[512];
static int nstash;
static void *low_virt;
static phys_addr_t low_phys;
static size_t meta_len;

static int pre(struct kprobe *p, struct pt_regs *regs)
{
	phys_addr_t src;

	if (regs->regs[22] != 6 || !low_virt)
		return 0;

	src = regs->regs[23];
	regs->regs[23] = low_phys;
	pr_info("lowbounce: pas %lu phys %pap -> %pap len %zu\n",
		(unsigned long)regs->regs[22], &src, &low_phys, meta_len);
	return 0;
}

static struct kprobe kp = {
	.symbol_name = "__scm_smc_call",
	.offset = 0x144,
	.pre_handler = pre,
};

static int __init lowbounce_init(void)
{
	struct file *filp;
	loff_t pos = 0;
	ssize_t n;
	int i, ret;

	for (i = 0; i < 512 && !low_virt; i++) {
		struct page *page = alloc_page(GFP_KERNEL | __GFP_NORETRY);
		phys_addr_t phys;

		if (!page)
			break;
		phys = page_to_phys(page);
		stash[nstash++] = page;
		if (phys >= 0x80000000ULL && phys < LOW_LIMIT) {
			low_virt = page_address(page);
			low_phys = phys;
		}
	}

	if (!low_virt) {
		pr_err("lowbounce: no page below %#llx (held %d)\n",
		       LOW_LIMIT, nstash);
		return -ENOMEM;
	}

	filp = filp_open("/lib/firmware/wcnss.mdt", O_RDONLY, 0);
	if (IS_ERR(filp))
		return PTR_ERR(filp);
	n = kernel_read(filp, low_virt, META_MAX, &pos);
	filp_close(filp, NULL);
	if (n <= 0)
		return n < 0 ? n : -EIO;
	meta_len = n;
	dcache_clean((unsigned long)low_virt,
		     (unsigned long)low_virt + PAGE_SIZE);
	pr_info("lowbounce: metadata %zu bytes at %pap\n", meta_len, &low_phys);

	ret = register_kprobe(&kp);
	if (ret)
		pr_err("lowbounce: kprobe %d\n", ret);
	return ret;
}

static void __exit lowbounce_exit(void)
{
	int i;

	unregister_kprobe(&kp);
	for (i = 0; i < nstash; i++)
		__free_page(stash[i]);
}

module_init(lowbounce_init);
module_exit(lowbounce_exit);
MODULE_LICENSE("GPL");
