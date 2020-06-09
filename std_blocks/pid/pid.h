/*
 * pid microblx function block (autogenerated, don't edit)
 */

#include <ubx.h>

UBX_MODULE_LICENSE_SPDX(BSD-3-Clause)

/* block meta information */
char pid_meta[] =
	" { doc='',"
	"   realtime=true,"
	"}";

/* declaration of block configuration */
ubx_proto_config_t pid_config[] = {
	{ .name="Kp", .type_name = "double", .doc="P-gain (def: 0)" },
	{ .name="Ki", .type_name = "double", .doc="I-gain (def: 0)" },
	{ .name="Kd", .type_name = "double", .doc="D-gain (def: 0)" },
	{ .name="data_len", .type_name = "long", .doc="length of signal array (def: 1)" },
	{ 0 },
};

/* declaration port block ports */
ubx_proto_port_t pid_ports[] = {
	{ .name="msr", .in_type_name="double", .in_data_len=1, .doc="measured input signal"  },
	{ .name="des", .in_type_name="double", .in_data_len=1, .doc="desired input signal"  },
	{ .name="out", .out_type_name="double", .out_data_len=1, .doc="controller output"  },
	{ 0 },
};

/* declare a struct port_cache */
struct pid_port_cache {
	ubx_port_t* msr;
	ubx_port_t* des;
	ubx_port_t* out;
};

/* declare a helper function to update the port cache this is necessary
 * because the port ptrs can change if ports are dynamically added or
 * removed. This function should hence be called after all
 * initialization is done, i.e. typically in 'start'
 */
static void update_port_cache(ubx_block_t *b, struct pid_port_cache *pc)
{
	pc->msr = ubx_port_get(b, "msr");
	pc->des = ubx_port_get(b, "des");
	pc->out = ubx_port_get(b, "out");
}


/* block operation forward declarations */
int pid_init(ubx_block_t *b);
void pid_cleanup(ubx_block_t *b);
void pid_step(ubx_block_t *b);


/* put everything together */
ubx_proto_block_t pid_block = {
	.name = "pid",
	.type = BLOCK_TYPE_COMPUTATION,
	.meta_data = pid_meta,
	.configs = pid_config,
	.ports = pid_ports,

	/* ops */
	.init = pid_init,
	.cleanup = pid_cleanup,
	.step = pid_step,
};


/* pid module init and cleanup functions */
int pid_mod_init(ubx_node_info_t* ni)
{
	if(ubx_block_register(ni, &pid_block) != 0)
		return -1;

	return 0;
}

void pid_mod_cleanup(ubx_node_info_t *ni)
{
	ubx_block_unregister(ni, "pid");
}

/* declare module init and cleanup functions, so that the ubx core can
 * find these when the module is loaded/unloaded */
UBX_MODULE_INIT(pid_mod_init)
UBX_MODULE_CLEANUP(pid_mod_cleanup)
