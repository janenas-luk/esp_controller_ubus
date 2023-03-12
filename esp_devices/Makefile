include $(TOPDIR)/rules.mk

PKG_NAME:=esp_devices
PKG_VERSION:=1.0
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/esp_devices
	DEPENDS:=+libubus +libubox +libblobmsg-json +libserialport
	SECTION:=utils
	CATEGORY:=Utilities
	TITLE:=Program which is used to communicate with esp devices over serial with special FW
endef

define Package/esp_devices/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/esp_devices $(1)/usr/bin/
endef

$(eval $(call BuildPackage,esp_devices))
