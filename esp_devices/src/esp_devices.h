#ifndef ESP_DEVICES_H
#define ESP_DEVICES_H
#define CH340_VENDOR   0x1a86
#define CH340_PRODUCT  0x7523
#define CP2102_VENDOR  0x10c4
#define CP2102_PRODUCT 0xea60

struct esp_device {
	char vid[10];
	char pid[10];
	char port_name[255];
	char description[1024];
};

/* Returns number of found ports
*/
int find_esp_ports(struct esp_device *esp_list);
void print_esp_info(struct esp_device device);
#endif