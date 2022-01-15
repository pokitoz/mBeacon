#include <zephyr.h>
#include <sys/printk.h>
#include <device.h>
#include <drivers/gpio.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>

#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)

#define LED0_NODE DT_ALIAS(led0)

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
#define LED0  DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN  DT_GPIO_PIN(LED0_NODE, gpios)
#define FLAGS  DT_GPIO_FLAGS(LED0_NODE, gpios)
#else
#error "No LED0"
#endif
#define MIN_PERIOD_USEC  (USEC_PER_SEC / 64U)
#define MAX_PERIOD_USEC  USEC_PER_SEC
#define SLEEP_TIME_MS   1000

static uint8_t mfg_data[] = {
  0xda, 0x09, // Nagra ID code
  0x64, // Battery level
  0xFF, 0xFA, 0xAC, 0xFF, 0xDE, 0xAD, // Mac
  'A', 'n', 'T', 'Z', 'o', 'n', '-', 'E', '8', // Whitelist
  0xb0, 0x01
};


// Advertizing should be on 31 bytes max
static struct bt_data ad[] = {
  BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
  BT_DATA_BYTES(BT_DATA_UUID16_ALL, 0xFF, 0xF1),
  BT_DATA(BT_DATA_MANUFACTURER_DATA, mfg_data, sizeof(mfg_data))
};

/* Set Scan Response data */
static const struct bt_data sd[] = {
  BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
};

static void bt_ready(int err)
{
  char addr_s[BT_ADDR_LE_STR_LEN];
  bt_addr_le_t addr = {0};
  size_t count = 1;

  if (err) {
    printk("Bluetooth init failed (err %d)\n", err);
    return;
  }

  printk("Bluetooth initialized\n");

  /* Start advertising */
  err = bt_le_adv_start(BT_LE_ADV_NCONN_IDENTITY, ad, ARRAY_SIZE(ad),
            sd, ARRAY_SIZE(sd));
  if (err) {
    printk("Advertising failed to start (err %d)\n", err);
    return;
  }

  bt_id_get(&addr, &count);
  bt_addr_le_to_str(&addr, addr_s, sizeof(addr_s));

  printk("mBeacon started, advertising as %s\n", addr_s);
}

void main(void)
{
  const struct device *dev;
  bool led_is_on = true;
  int ret;

  dev = device_get_binding(LED0);
  if (dev == NULL) {
    return;
  }

  ret = gpio_pin_configure(dev, PIN, GPIO_OUTPUT_ACTIVE | FLAGS);
  if (ret < 0) {
    return;
  }

  int err = bt_enable(bt_ready);
  if (err) {
    while (1) {
      gpio_pin_set(dev, PIN, (int)1);
    }
  }

  while (1) {
    gpio_pin_set(dev, PIN, (int)led_is_on);
    led_is_on = !led_is_on;
    k_msleep(SLEEP_TIME_MS);
    printk("Alive!\n");
  }
}
