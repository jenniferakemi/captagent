/*
 * $Id$
 *
 *  captagent - Homer capture agent. Modular
 *  Duplicate SIP messages in Homer Encapulate Protocol [HEP] [ipv6 version]
 *
 *  Author: Alexandr Dubovikov <alexandr.dubovikov@gmail.com>
 *  (C) Homer Project 2012-2015 (http://www.sipcapture.org)
 *
 * Homer capture agent is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version
 *
 * Homer capture agent is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
*/

#ifndef SOCKET_RAW_API_H_
#define SOCKET_RAW_API_H_

#include <captagent/log.h>
#include <captagent/export_function.h>

typedef int (*rawapi_set_filter_f)(unsigned int index, char *filter);
int rawapi_set_filter(unsigned int index, char *filter);

typedef struct socket_raw_api {
	rawapi_set_filter_f       setfilter;
} socket_raw_api_t;

typedef int (*bind_socket_raw_f)(socket_raw_api_t* api);
int bind_socket_raw(socket_raw_api_t* api);

/**
 * @brief Load the socket_raw API
 */
static inline int socket_raw_load_api(socket_raw_api_t *api)
{
        bind_socket_raw_f bindsocket_raw;

        bindsocket_raw = (bind_socket_raw_f)find_export("bind_socket_raw", 0, 0);
        if(bindsocket_raw == 0) {
        	LERR("cannot find bind_socket_raw\n");
                return -1;
        }
        if (bindsocket_raw(api) < 0)
        {
        	LERR("cannot bind socket_raw api\n");
                return -1;
        }
        return 0;
}



#endif /* SOCKET_RAW_API_H_ */
