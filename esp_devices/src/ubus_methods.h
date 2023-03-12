
#include <libubox/blobmsg_json.h>
#include <libubus.h>

enum { PORT, PIN, __ESP_PIN_MAX };

int get_esp_devices(struct ubus_context *ctx, struct ubus_object *obj, struct ubus_request_data *req,
		    const char *method, struct blob_attr *msg);
int turn_on_esp_pin(struct ubus_context *ctx, struct ubus_object *obj, struct ubus_request_data *req,
		    const char *method, struct blob_attr *msg);
int turn_off_esp_pin(struct ubus_context *ctx, struct ubus_object *obj, struct ubus_request_data *req,
		     const char *method, struct blob_attr *msg);