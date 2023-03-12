#include "esp_devices.h"
#include <stdio.h>
#include <string.h>
#include <libserialport.h>

void print_esp_info(struct esp_device device)
{
	printf("Vendor ID -> %#06x\n", device.vid);
	printf("Product ID -> %#06x\n", device.pid);
	printf("Port name -> %s\n", device.port_name);
	printf("Description -> %s\n", device.description);
}

int find_esp_ports(struct esp_device *esp_list)
{
	struct sp_port **port_list;
	int vid;
	int pid;
	int count	      = 0;
	enum sp_return result = sp_list_ports(&port_list);

	if (result != SP_OK) {
		return 0;
	}
	for (int i = 0; port_list[i] != NULL; i++) {
		sp_get_port_usb_vid_pid(port_list[i], &vid, &pid);
		if ((vid == CH340_VENDOR && pid == CH340_PRODUCT) ||
		    (vid == CP2102_VENDOR && pid == CP2102_PRODUCT)) {
			sprintf(esp_list[count].vid, "%x", vid);
			sprintf(esp_list[count].pid, "%x", pid);
			// esp_list[count].vid = vid;
			// esp_list[count].pid = pid;
			strncpy(esp_list[count].port_name, sp_get_port_name(port_list[i]), 254);
			strncpy(esp_list[count].description, sp_get_port_description(port_list[i]), 254);
			count++;
		}
	}
	sp_free_port_list(port_list);
	return count;
}