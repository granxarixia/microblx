/*
 * An interaction block that hexdumps the data to stdout.
 */

#undef DEBUG

#include <stdio.h>
#include <stdlib.h>

#include "ubx.h"

char hexdumpmeta[] =
	"{ doc='hexdump interaction',"
	"  realtime=false,"
	"}";

/* hexdump a buffer */
void hexdump(unsigned char *buf, unsigned long index, unsigned long width)
{
	unsigned long i, fill;

	/* dump data */
	for (i = 0; i < index; i++)
		printf("%02x ", buf[i]);

	for (fill = index; fill < width; fill++)
		printf(" ");  /* pad on right */

	printf(": ");

	/* add ascii repesentation */
	for (i = 0; i < index; i++) {
		if (buf[i] < 32)
			printf(".");
		else
			printf("%c", buf[i]);
	}
	printf("\n");
}

void hexdump_write(ubx_block_t *i, const ubx_data_t *data)
{
	const char *typename = get_typename(data);

	printf("%s (%s): ", i->name, (typename != NULL) ? typename : "unknown");
	hexdump(data->data, data_size(data), 16);
}

/* put everything together */
ubx_proto_block_t hexdump_comp = {
	.name = "ubx/hexdump",
	.type = BLOCK_TYPE_INTERACTION,
	.meta_data = hexdumpmeta,

	/* ops */
	.write = hexdump_write,
};

int hexdump_mod_init(ubx_node_t *nd)
{
	return ubx_block_register(nd, &hexdump_comp);
}

void hexdump_mod_cleanup(ubx_node_t *nd)
{
	ubx_block_unregister(nd, "ubx/hexdump");
}

UBX_MODULE_INIT(hexdump_mod_init)
UBX_MODULE_CLEANUP(hexdump_mod_cleanup)
UBX_MODULE_LICENSE_SPDX(BSD-3-Clause)
