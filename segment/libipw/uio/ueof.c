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
**         ueof -- check for uio end-of-file
**  
** 
** SYNOPSIS
**         bool_t ueof(fd)
**         int fd;
**  
** 
** DESCRIPTION
**         ueof tests whether there any data remaining to be read from
**         file descriptor {fd}, which must have been opened for
**         reading by uropen.
**  
** 
** RETURN VALUE
**         TRUE if end-of-file has been reached; else FALSE
**  
** 
** GLOBALS ACCESSED
**         _uiocb[fd]      uio control block for file descriptor fd
**  
** 
** SEE ALSO
**         IPW: uread
*/  

bool_t
ueof(fd)
	int             fd;		/* file descriptor		 */
{
	UIO_T          *p;		/* -> UIO control block		 */

	assert(OK_FD(fd));

	p = &_uiocb[fd];
	assert(p->flags & UIO_READ);
 /*
  * is EOF flag already set?
  */
	if (p->flags & UIO_EOF) {
		return (TRUE);
	}
 /*
  * else, is uio buffer (partially) full?
  */
	if (p->nbytes > 0) {
		return (FALSE);
	}
 /*
  * else, anything else to read?
  */
	return (_uread(p) == 0);
}

#ifndef	lint
static char     rcsid[] = "$Header: /share1/ipw-1.1/share/src/lib/libipw/uio/RCS/ueof.c,v 1.5 1997/02/17 04:12:09 ceretha Exp $";

#endif
