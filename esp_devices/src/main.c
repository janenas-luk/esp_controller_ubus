#include <stdio.h>
#include <stdlib.h>
#include <libubox/blobmsg_json.h>
#include <libubus.h>
#include "esp_devices.h"
#include "ubus_methods.h"

int main(int argc, char **argv)
{
	init_ubus();
	return 0;
}
