/****************************************************************************
 *
 * Copyright 2021 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/
#include <tinyara/config.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <debug.h>
#include <time.h>
#include <tinyara/wifi/wifi_common.h>
#include <tinyara/lwnl/lwnl.h>
#include <tinyara/net/if/wifi.h>
#include "vdev_handler.h"

extern trwifi_scan_list_s *vwifi_get_scan_list(void);
extern struct vwifi_ops *get_vdev_onoff(void);
extern struct vwifi_ops *get_vdev_auto(void);
extern struct netdev *g_vwifi_dev;

static void vwifi_callback_handler(lwnl_cb_status evt)
{
	if (evt.evt == LWNL_EVT_SCAN_DONE) {
		trwifi_scan_list_s *scanlist = vwifi_get_scan_list();
		TRWIFI_POST_SCANEVENT(g_vwifi_dev, LWNL_EVT_SCAN_DONE, scanlist);
	} else {
		trwifi_post_event(g_vwifi_dev, evt.evt, NULL, 0);
	}
}

static void _generate_disconnect(int argc, char *argv[])
{
	int sleep_time = atoi(argv[1]);
	lwnl_cb_status event_type = {LWNL_DEV_WIFI, 0};
	event_type.evt = atoi(argv[2]);

	vdvdbg("[VDEV] sleep (%d) event type(%d)\n", sleep_time, event_type.evt);
	sleep(sleep_time);
	vwifi_callback_handler(event_type);
}

int vwifi_create_event(struct vwifi_evt *vevent, int sleep, uint32_t event)
{
	(void)vevent;
	char sleep_buf[16] = {0,};
	char event_buf[16] = {0,};
	memset(sleep_buf, 0, 16);
	memset(event_buf, 0, 16);

	snprintf(sleep_buf, 16, "%d", sleep);
	snprintf(event_buf, 16, "%d", event);
	char *argv[3] = {0,};
	argv[0] = sleep_buf;
	argv[1] = event_buf;
	argv[2] = NULL;

	int res = kernel_thread("vwifi_evt", 100, 2048, _generate_disconnect, argv);
	if (res < 0) {
		VWIFI_ERROR(0);
		return -1;
	}
	return 0;
}


int vwifi_handle_message(struct vwifi_req *req)
{
	#if 1
	struct vwifi_ops *ops = get_vdev_auto();
	#else
	struct vwifi_ops *ops = get_vdev_onoff();
	#endif
	int res = 0;
	switch (req->type) {
	case VWIFI_MSG_INIT:
		req->res = ops->init(req);
		break;
	case VWIFI_MSG_DEINIT:
		req->res = ops->deinit(req);
		break;
	case VWIFI_MSG_SCANAP:
		req->res = ops->scan_ap(req);
		break;
	case VWIFI_MSG_CONNECTAP:
		req->res = ops->connect_ap(req);
		break;
	case VWIFI_MSG_DISCONENCTAP:
		req->res = ops->disconnect_ap(req);
		break;
	case VWIFI_MSG_GETINFO:
		req->res = ops->get_info(req);
		break;
	case VWIFI_MSG_STARTSTA:
		req->res = ops->start_sta(req);
		break;
	case VWIFI_MSG_STARTSOFTAP:
		req->res = ops->start_softap(req);
		break;
	case VWIFI_MSG_STOPSOFTAP:
		req->res = ops->stop_softap(req);
		break;
	case VWIFI_MSG_SETAUTOCONNECT:
		req->res = ops->set_autoconnect(req);
		break;
	default:
		VWIFI_ERROR(0);
		break;
	}
	return res;
}
