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

#include <tinyara/config.h>
#include <debug.h>

uint32_t g_link_recv_byte = 0;
uint32_t g_link_recv_cnt = 0;
uint32_t g_link_recv_err = 0;

uint32_t g_app_recv_byte = 0;
uint32_t g_app_recv_cnt = 0;

void netstats_display(void)
{
	nlldbg("[driver] total recv %u\t%u\n", g_link_recv_byte, g_link_recv_cnt);
	nlldbg("[driver] mbox err %u\n", g_link_recv_err);
	nlldbg("[app] total recv %u\t%u\n", g_app_recv_byte, g_app_recv_cnt);
}
