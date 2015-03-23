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

#ifndef	_PIXIO_H
#define	_PIXIO_H

typedef struct {
	unsigned        flags;		/* bit flags			 */
	int             nbands;		/* # bands			 */
	int            *pixsiz;		/* -> array of # bytes / pixel	 */
	int            *bandsiz;	/* -> array of # bytes / band	 */
	int             pixvsiz;	/* # bytes / pixel vector	 */
	addr_t          rawbuf;		/* -> base of "raw" I/O buffer	 */
	int             rawsiz;		/* size (bytes) of rawbuf	 */
	int            *pixmask;	/* -> pixel_t <-> raw masks	 */
	int            *bandmask;	/* -> array of band masks	 */
	int             npixv;		/* requested # pixel vectors	 */
	int             npixels;	/* requested # pixels		 */
	int             nbytes;		/* requested # bytes		 */
} PIXIO_T;

/* bits in "flags" */
#define	PIXIO_READ	bit(0)		/* initialized for reading	 */
#define	PIXIO_WRITE	bit(1)		/* initialized for writing	 */
#define	PIXIO_SWAP	bit(2)		/* swap bytes			 */

extern PIXIO_T *_piocb[];

extern PIXIO_T *_pioinit();

/* $Header: /tmp7/jimbo/ipw.v1.0/src/lib/libipw/pixio/RCS/_pixio.h,v 1.8 93/02/02 08:45:44 jimbo Exp $ */
#endif
