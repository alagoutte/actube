/*
    This file is part of libcapwap.

    libcapwap is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libcapwap is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

*/

/**
 * @file
 * @brief Implementation of methods for actionlists.
 */


#include <stdlib.h>
#include <string.h>

#include "action.h"



static inline int cw_action_in_cmp(const void *elem1, const void *elem2)
{
	struct cw_action_in *e1 = (struct cw_action_in *) elem1;
	struct cw_action_in *e2 = (struct cw_action_in *) elem2;
	int r;

	r = e1->capwap_state - e2->capwap_state;
	if (r != 0)
		return r;

	r = e1->msg_id - e2->msg_id;
	if (r != 0)
		return r;

	r = e1->elem_id - e2->elem_id;
	if (r != 0)
		return r;

	r = e1->vendor_id - e2->vendor_id;
	if (r != 0)
		return r;

	r = e1->proto - e2->proto;
	if (r != 0)
		return r;



	return 0;
}


		
/*
cw_action_fun_t cw_set_msg_end_callback(struct conn *conn, 
		int capwap_state,int msg_id, cw_action_fun_t callback)
{
	cw_action_in_t as;
	as.capwap_state = capwap_state;
	as.msg_id = msg_id;
	as.vendor_id = 0;
	as.elem_id = 0;
	as.proto = 0;
	
	cw_action_in_t *af;
	

	af = cw_actionlist_in_get(conn->actions->in, &as);
	if (!af) 
		return NULL;

	cw_action_fun_t  old = af->end;
	af->end =callback;
	return old;
		

}

*/


cw_action_in_t *cw_actionlist_in_add(cw_actionlist_in_t t, struct cw_action_in * a)
{
	int s = sizeof(struct cw_action_in);

	void *r = mavl_replace_data(t, a, s);
	if (r) 
		return r;

	void *an = malloc(s);
	if (!an)
		return NULL;

	memcpy(an, a, s);
	return mavl_add(t, an);




//	return cw_actionlist_add(t, a, sizeof(struct cw_action_in));
}


struct cw_action_in *cw_actionlist_in_get(cw_actionlist_in_t t, struct cw_action_in *a)
{
	return avltree_get(t, a);
}


/**
 * Create an action list for incomming messages
 */
cw_actionlist_in_t cw_actionlist_in_create()
{
	return mavl_create(cw_action_in_cmp, free);
}

/**
 * Register actions in an action list for incommin messages 
 * @param t action list, where messaes will be registered
 * @param actions an array of actions to reggister
 */
int cw_actionlist_in_register_actions(cw_actionlist_in_t t, cw_action_in_t * actions)
{
	int n=0;
	while (actions->capwap_state) {
		cw_action_in_t *rc = cw_actionlist_in_add(t, actions);
		if (!rc)
			return 0;
		actions++;
		n++;
	}
	return n;
}

int cw_actionlist_out_register_actions(cw_actionlist_out_t t, cw_action_out_t * actions)
{



	int n=0;
	while (actions->msg_id != 0) {
		cw_action_out_t *rc = cw_actionlist_out_add(t, actions);
		if (rc == 0)
			return 0;
		actions++;
		n++;
	}
	return n;
}



struct outelem{
	uint32_t msg_id;
	mlist_t * mlist;
};




/* 
 * Compare function for actionlist_out_t lists
 */
static int cw_action_out_cmp(const void *elem1, const void *elem2)
{
	struct outelem *e1 = (struct outelem *) elem1;
	struct outelem *e2 = (struct outelem *) elem2;
	return e1->msg_id - e2->msg_id;
	return 0;
}



static int mout_cmp(void *elem1,void *elem2)
{

	struct cw_action_out *e1 = (struct cw_action_out *) elem1;
	struct cw_action_out *e2 = (struct cw_action_out *) elem2;
	int r;

	r = e1->msg_id - e2->msg_id;
	if (r )
		return r;

	r = e1->elem_id - e2->elem_id;
	if (r )
		return r;


	r = e1->vendor_id - e2->vendor_id;
	if (r )
		return r;

	if (e1->item_id == e2->item_id)
		return 0;

	if (e1->item_id && e2->item_id)
		return strcmp(e1->item_id,e2->item_id);

	
	return 1;	

}





/**
 * Add an action to an action 
 * @param t actionlist
 * @param a action to add
 * @param s size of element to add
 * @return pointer to added element or NULL if an error has opccured
 */
void *cw_actionlist_add(struct avltree *t, void *a, size_t s)
{

	void *r = mavl_replace_data(t, a, s); //sizeof(struct cw_action_in));
	if (r) {
		return r;
	}

	void *an = malloc(s);
	if (!an)
		return NULL;

	memcpy(an, a, s);
	return avltree_add(t, an);

}

#include "dbg.h" // Tube

/**
 * Create an action list for outgoing message lements
 * @return the created action list or NULL if an erro has occured.
 */
cw_actionlist_out_t cw_actionlist_out_create()
{
	return mavl_create(cw_action_out_cmp, free);
}


static struct outelem * cw_actionlist_out_get_outelem(cw_actionlist_out_t t, int msg_id)
{
	struct outelem search;
	search.msg_id=msg_id;
	//printf("Searching for %d\n",msg_id);
	return mavl_get(t,&search);
	
}

mlist_t * cw_actionlist_out_get(cw_actionlist_out_t t,int msg_id)
{
	struct outelem *o = cw_actionlist_out_get_outelem(t,msg_id);
	if (!o)
		return NULL;
	return o->mlist;
}

struct outelem * cw_actionlist_mout_create(int msg_id)
{
	struct outelem * o = malloc(sizeof(struct outelem));
	if (!o)
		return NULL;

	o->mlist= mlist_create(mout_cmp);
	if (!o->mlist){
		free(o);
		return NULL;
	}
	o->msg_id=msg_id;
	return o;
}




#include "capwap.h"

cw_action_out_t *cw_actionlist_out_add(cw_actionlist_out_t t, struct cw_action_out * a)
{
/*	if (a->msg_id==CW_MSG_DISCOVERY_RESPONSE){
		printf("Add discovery response\n");
	}
*/

	//printf("Add %d %d\n",a->msg_id,a->elem_id);

	struct outelem * o =  cw_actionlist_out_get_outelem(t,a->msg_id);


	if (!o){
	/*	if (a->msg_id==CW_MSG_DISCOVERY_RESPONSE){
			printf("m was 0 creating \n");
		}
		*/
		o = cw_actionlist_mout_create(a->msg_id);
		if (!o) {
			return NULL;
		}
		mavl_add(t,o);


	}

	

	struct mlist_elem * e = mlist_replace(o->mlist,NULL,a);
	if (!e)
		e = mlist_append(o->mlist,a);

	if (e)
		return a;

	return 0;


}


/*
cw_action_in_t *cw_actionlist_in_set_msg_end_callback(cw_actionlist_in_t a, 
				      uint8_t capwap_state,
					uint32_t msg_id,
				      int (*fun) (struct conn * conn,
						  struct cw_action_in * a, uint8_t * data,
						  int len,struct sockaddr *from))
{
	cw_action_in_t as,*ar;
	as.vendor_id=0;
	as.proto=0;
	as.elem_id=-1;
	as.msg_id=msg_id;
	as.capwap_state=capwap_state;

	ar = cw_actionlist_in_get(a,&as);
	if (!ar)
		return NULL;

	ar->end=fun;		
	return ar;
}


*/


