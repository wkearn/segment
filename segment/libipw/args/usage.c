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

#include <ctype.h>

#include "ipw.h"

#include "_getargs.h"
#include "../error/_error.h"

/*
** NAME
**	usage -- print usage message and exit
**
** SYNOPSIS
**	#include "getargs.h"
**
**	void usage()
**
** DESCRIPTION
**	Usage prints a usage message on the standard error output, then exits
**	with a nonzero status.  The usage message contains the command name, a
**	one line description of the command, and a synopsis of the command's
**	options.
**
** RESTRICTIONS
**	Getargs() must be called before usage, or else the command name,
**	descripton, and option synopsis that are printed will not be very
**	useful (see GLOBALS below).
**
** RETURN VALUE
**	never returns
**
** GLOBALS ACCESSED
**	_argv	pointer to command-line argument vector (esp., _argv[0] is
**		assumed to be the command name) (initialized by getargs())
**
**	_descrip
**		pointer to string containing description of current command
**
**	_optv	pointer to option-descriptor vector (initialized by getargs())
**
** APPLICATION USAGE
**	Call usage whenever it is evident that the user supplied an incorrect
**	command line (e.g., when getargs() returns NULL).
*/

static void
pr_args(optp)
	REG_1 OPTION_T *optp;		/* -> current option descriptor	 */
{
	REG_2 int       j;		/* loop counter			 */
	REG_3 char      sep;		/* optarg/operand separators	 */

	(void) fprintf(stderr, " ");

	if (!optp->required) {
		(void) fprintf(stderr, "[");
	}

	if (optp->option != OPERAND) {
		(void) fprintf(stderr, "-%c", optp->option);
	}

	if (optp->type != NO_OPTARGS) {
		assert(optp->arg_descrip != NULL);

		if (optp->option == OPERAND) {
			sep = BLANK;
		}
		else {
			(void) fprintf(stderr, " ");
			sep = ',';
		}

		(void) fprintf(stderr, "%s", optp->arg_descrip);

		for (j = 1; j < optp->min_nargs; ++j) {
			(void) fprintf(stderr, "%c%s", sep, optp->arg_descrip);
		}

		if (optp->max_nargs == 0) {
			(void) fprintf(stderr, "%c...", sep);
		}
		else if (j < optp->max_nargs) {
			(void) fprintf(stderr, "[");

			do {
				(void) fprintf(stderr, "%c%s",
					       sep, optp->arg_descrip);
			} while (++j < optp->max_nargs);

			(void) fprintf(stderr, "]");
		}
	}

	if (!optp->required) {
		(void) fprintf(stderr, "]");
	}
}


void
usage()
{

	REG_2 int       i;		/* _optv index of current option */
	REG_1 OPTION_T *optp;		/* -> current option		 */

	assert(_argv != NULL && _argv[0] != NULL);
	assert(_descrip != NULL);

	(void) fflush(stdout);
 /*
  * print error string if set, else program description
  */
	if (_usrerr[0] != EOS) {
		(void) fprintf(stderr, "\nERROR: %s\n", _usrerr);
	}
	else {
		(void) fprintf(stderr, "\n%s -- %s\n", _argv[0], _descrip);
	}
 /*
  * print program synopsis
  * 
  * - name
  */
	(void) fprintf(stderr, "\nUsage: %s", _argv[0]);

	if (_optv == NULL) {
		(void) fprintf(stderr, "\n\n");
		ipwexit(EX_ERROR);
	}
 /*
  * - options
  */
	i = 0;

	for (; (optp = _optv[i]) != NULL && optp->option != OPERAND; ++i) {
		assert(isascii(optp->option));
		assert(isgraph(optp->option));

		pr_args(optp);
	}
 /*
  * - operands
  */
	for (; (optp = _optv[i]) != NULL; ++i) {
		assert(optp->option == OPERAND);

		pr_args(optp);
	}

	(void) fprintf(stderr, "\n");
 /*
  * print option descriptions
  */
	i = 0;

	if ((optp = _optv[i]) != NULL && optp->option != OPERAND) {
		(void) fprintf(stderr, "\nOptions:\n");

		do {
			assert(optp->descrip != NULL);

			(void) fprintf(stderr, "\t%c\t%s\n",
				       optp->option, optp->descrip);

			++i;
		} while ((optp = _optv[i]) != NULL
			 && optp->option != OPERAND);
	}
 /*
  * print operand descriptions
  */
	if ((optp = _optv[i]) != NULL) {
		(void) fprintf(stderr, "\nOperands:\n");

		do {
			assert(optp->descrip != NULL);

			(void) fprintf(stderr, "\t%s\t%s\n",
				       optp->arg_descrip, optp->descrip);

			++i;
		} while ((optp = _optv[i]) != NULL);
	}
 /*
  * all done
  */
	(void) fprintf(stderr, "\n");
	ipwexit(EX_ERROR);
}

#ifndef	lint
static char     rcsid[] = "$Header: /share1/ipw-1.1/share/src/lib/libipw/args/RCS/usage.c,v 1.13 1993/02/02 08:32:10 jimbo Exp $";

#endif
