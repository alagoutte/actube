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


#include "mbag.h"


static struct mbag_item *  from_str(const char *src)
{
	mbag_item_t * i = mbag_item_new(MBAG_BYTE);
	if (!i)
		return NULL;
	i->byte=atoi(src);
	return i;
}

static int to_str(void *item,char *dst)
{
	mbag_item_t *i= item;
        return sprintf(dst, "%d", i->byte);
}


/** Defines a word, two bytes. */
const struct mbag_typedef mbag_type_byte = {
	"Byte",NULL,to_str,from_str
};


