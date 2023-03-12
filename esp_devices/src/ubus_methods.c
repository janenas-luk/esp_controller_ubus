#include "ubus_methods.h"
#include "esp_devices.h"
#include <string.h>

static const struct blobmsg_policy esp_pin_policy[] = {
	[PORT] = { .name = "port", .type = BLOBMSG_TYPE_STRING },
	[PIN]  = { .name = "pin", .type = BLOBMSG_TYPE_INT32 },
};

static const struct ubus_method esp_devices_methods[] = {
	UBUS_METHOD_NOARG("devices", get_esp_devices),
	UBUS_METHOD("on", turn_on_esp_pin, esp_pin_policy),
	UBUS_METHOD("off", turn_off_esp_pin, esp_pin_policy),
};

static struct ubus_object_type esp_devices_object_type = UBUS_OBJECT_TYPE("esp", esp_devices_methods);

static struct ubus_object esp_devices_object = {
	.name	   = "esp_devices",
	.type	   = &esp_devices_object_type,
	.methods   = esp_devices_methods,
	.n_methods = ARRAY_SIZE(esp_devices_methods),
};

int get_esp_devices(struct ubus_context *ctx, struct ubus_object *obj, struct ubus_request_data *req,
		    const char *method, struct blob_attr *msg)
{
	struct esp_device *esp_list = malloc(sizeof(struct esp_device) * 10);
	size_t count		    = 0;
	struct blob_buf devices	    = {};
	void *a, *t;
	blob_buf_init(&devices, 0);
	count = find_esp_ports(esp_list);
	a     = blobmsg_open_array(&devices, "devices");
	for (int i = 0; i < count; i++) {
		t = blobmsg_open_table(&devices, NULL);
		blobmsg_add_string(&devices, "vid", esp_list[i].vid);
		blobmsg_add_string(&devices, "pid", esp_list[i].pid);
		blobmsg_add_string(&devices, "description", esp_list[i].description);
		blobmsg_add_string(&devices, "port_name", esp_list[i].port_name);
		blobmsg_close_table(&devices, t);
	}
	blobmsg_close_array(&devices, a);
	ubus_send_reply(ctx, req, devices.head);
	blob_buf_free(&devices);
	free(esp_list);
	return 0;
}

int turn_off_esp_pin(struct ubus_context *ctx, struct ubus_object *obj, struct ubus_request_data *req,
		     const char *method, struct blob_attr *msg)
{
	struct blob_attr *tb[__ESP_PIN_MAX];
	struct blob_buf b = {};
	int pin;
	char port[255];
	char command[512];

	blobmsg_parse(esp_pin_policy, __ESP_PIN_MAX, tb, blob_data(msg), blob_len(msg));

	if (!tb[PORT])
		return UBUS_STATUS_INVALID_ARGUMENT;

	if (!tb[PIN])
		return UBUS_STATUS_INVALID_ARGUMENT;

	strncpy(port, blobmsg_get_string(tb[PORT]), 254);
	pin = blobmsg_get_u32(tb[PIN]);

	sprintf(command, "echo -e \"{'action': 'off', 'pin': %d}\" > %s", pin, port);
	printf("%s\n", command);
	system(command);

	return 0;
}

int turn_on_esp_pin(struct ubus_context *ctx, struct ubus_object *obj, struct ubus_request_data *req,
		    const char *method, struct blob_attr *msg)
{
	struct blob_attr *tb[__ESP_PIN_MAX];
	struct blob_buf b = {};
	int pin;
	char port[255];
	char command[512];

	blobmsg_parse(esp_pin_policy, __ESP_PIN_MAX, tb, blob_data(msg), blob_len(msg));

	if (!tb[PORT])
		return UBUS_STATUS_INVALID_ARGUMENT;

	if (!tb[PIN])
		return UBUS_STATUS_INVALID_ARGUMENT;

	strncpy(port, blobmsg_get_string(tb[PORT]), 254);
	pin = blobmsg_get_u32(tb[PIN]);

	sprintf(command, "echo -e \"{'action': 'on', 'pin': %d}\" > %s", pin, port);
	printf("%s\n", command);
	system(command);

	return 0;
}

void init_ubus()
{
	struct ubus_context *ctx;
	uloop_init();

	ctx = ubus_connect(NULL);
	if (!ctx) {
		fprintf(stderr, "Failed to connect to ubus\n");
		return -1;
	}

	ubus_add_uloop(ctx);
	ubus_add_object(ctx, &esp_devices_object);
	uloop_run();

	ubus_free(ctx);
	uloop_done();
}