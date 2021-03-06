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

#include "_uio.h"

/*
** NAME
**	uwflush -- flush buffered UIO output
**
** SYNOPSIS
**	int uwflush(fd)
**	int fd;
**
** DESCRIPTION
**	uwflush forces any pending UIO output to be written to file
**	descriptor fd.
**
** RETURN VALUE
**	OK for success, ERROR for failure
**
** GLOBALS ACCESSED
**	_uiocb[fd]	UIO control block for file descriptor fd
**
** APPLICATION USAGE
**	uwflush is usually called to force pending output down a pipe before
**	beginning a potentially lengthy calculation.
*/

int
uwflush(fd)
	int             fd;		/* file descriptor		 */
{
	UIO_T          *p;		/* -> UIO control block		 */

	assert(OK_FD(fd));
	p = &_uiocb[fd];
 /*
  * Return harmlessly if not open for writing; this allows ipwexit() to call
  * uwflush() and report any error returns as write errors.
  */
	if (! (p->flags & UIO_WRITE)) {
		return (OK);
	}

	if (p->nbytes <= 0) {
		return (OK);
	}

	return (_uwrite(p));
}

#ifndef	lint
static char     rcsid[] = "$Header: /share1/ipw-1.1/share/src/lib/libipw/uio/RCS/uwflush.c,v 1.4 1997/02/17 04:12:09 ceretha Exp $";

#endif
