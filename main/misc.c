#include "misc.h"

#include <string.h>
#include <time.h>

#include "esp_log.h"
#include "esp_sntp.h"

static const char *TAG = "common";



static void sntp_synced_cb(struct timeval *tv)
{
    time_t now = 0;
    time(&now);

    struct tm timeinfo = { 0 };
    localtime_r(&now, &timeinfo);

    char strftime_buf[64];
    strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);

    ESP_LOGI(TAG, "Time has been synchronised to %s UTC", strftime_buf);
}

void initialize_sntp()
{
    ESP_LOGI(TAG, "Initializing SNTP");
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
#if LWIP_DHCP_GET_NTP_SRV && SNTP_MAX_SERVERS > 1
    sntp_servermode_dhcp(1);
    sntp_setservername(1, "pool.ntp.org");
#endif
    sntp_set_time_sync_notification_cb(sntp_synced_cb);
    sntp_set_sync_mode(SNTP_SYNC_MODE_SMOOTH);

    sntp_init();
}