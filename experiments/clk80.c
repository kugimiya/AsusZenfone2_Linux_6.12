#include <linux/clk.h>
#include <linux/module.h>
#include <linux/of.h>

static int __init clk80_init(void)
{
	struct device_node *np;
	struct clk *core;
	unsigned long before, after;
	int ret;

	np = of_find_compatible_node(NULL, NULL, "qcom,scm-msm8916");
	if (!np)
		return -ENODEV;

	core = of_clk_get(np, 0);
	of_node_put(np);
	if (IS_ERR(core))
		return PTR_ERR(core);

	before = clk_get_rate(core);
	ret = clk_set_rate(core, 80000000);
	after = clk_get_rate(core);
	pr_info("scm core clk before %lu set80 %d after %lu\n", before, ret, after);
	clk_put(core);
	return 0;
}

static void __exit clk80_exit(void)
{
}

module_init(clk80_init);
module_exit(clk80_exit);
MODULE_LICENSE("GPL");
