/*
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that: (1) source distributions retain this entire copyright
 * notice and comment, and (2) distributions including binaries display
 * the following acknowledgement:  ``This product includes software
 * developed by the Computer Systems Laboratory, University of
 * California, Santa Barbara and its contributors'' in the documentation
 * or other materials provided with the distribution and in all
 * advertising materials mentioning features or use of this software.
 *
 * Neither the name of the University nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/* LINTLIBRARY */

#include "ipw.h"

#include "hdrio.h"

#include "_hdrio.h"

/*
** NAME
**	hwprmb -- write preamble record
**
** SYNOPSIS
**	#include "hdrio.h"
**
**	int hwid(fd, name, band, version)
**	int fd, band;
**	char *name, *version;
**
** DESCRIPTION
**	Hwid constructs a header ID from header name "name", header band
**	number "band", and header version string "version", and writes the
**	corresponding preamble record to "fd".
**
** RESTRICTIONS
**	All values placed in the preamble record will be truncated to fit the
**	destination field width.  See hdrio.h for the specifics.
**
** RETURN VALUE
**	OK for success, ERROR for failure
**
** APPLICATION USAGE
**	Call hwid to mark the beginning of a new output header.
*/

int
hwprmb(fd, name, band, version)
	int             fd;		/* output file descriptor	 */
	char           *name;		/* header name			 */
	int             band;		/* header band number		 */
	char           *version;	/* header version string	 */
{
	char            buf[HREC_MAX + 1];

	assert(name != NULL);
	assert(version != NULL);
 /*
  * make sure preamble data (including spaces and trailing \n\0) will fit in
  * the buffer
  */
	if (kstrlen(PRMB_MAG) + strlen(name) + ndig(band) + strlen(version)
	    + 5
	    > sizeof(buf)) {
		uferr(fd);
		usrerr("header preamble too long");
		return (ERROR);
	}

	(void) sprintf(buf, "%s %s %d %s\n", PRMB_MAG, name, band, version);
	return (_hwrec(fd, buf));
}

#ifndef	lint
static char     rcsid[] = "$Header: /share1/ipw-1.1/share/src/lib/libipw/hdrio/RCS/hwprmb.c,v 1.3 1997/02/17 04:34:48 ceretha Exp $";

#endif
