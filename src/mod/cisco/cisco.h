#ifndef __CISCO_H
#define __CISCO_H

#include "cw/conn.h"
#include "cw/action.h"

extern int cisco_out_ap_timesync(struct conn *conn,struct cw_action_out * a,uint8_t *dst);
extern int cisco_in_wtp_descriptor(struct conn *conn, struct cw_action_in *a, uint8_t * data,
			 int len, struct sockaddr *from);
extern int cisco_out_ac_descriptor(struct conn *conn,struct cw_action_out * a,uint8_t *dst) ;
extern int cisco_out_wtp_descriptor(struct conn *conn, struct cw_action_out *a, uint8_t * dst);


extern int cisco_in_ac_descriptor(struct conn *conn, struct cw_action_in *a, uint8_t * data,
			int len, struct sockaddr *from);

#endif
