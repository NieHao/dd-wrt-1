/*
 * $Id: callid.h,v 1.1.1.1 2005/06/13 16:47:45 bogdan_iancu Exp $
 *
 * Fast Call-ID Generator
 *
 * Copyright (C) 2001-2003 FhG Fokus
 *
 * This file is part of openser, a free SIP server.
 *
 * openser is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version
 *
 * openser is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program; if not, write to the Free Software 
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 * ----------
 * 2003-04-09 Created by janakj
 */

#ifndef CALLID_H
#define CALLID_H

#include "../../str.h"


/*
 * Initialize the Call-ID generator -- generates random prefix
 */
int init_callid(void);


/*
 * Child initialization -- generates suffix
 */
int child_init_callid(int rank);


/*
 * Get a unique Call-ID
 */
void generate_callid(str* callid);


#endif /* CALLID_H */
