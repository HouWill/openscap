/**
 * @file   family.c
 * @brief  family probe
 * @author "Tomas Heinrich" <theinric@redhat.com>
 * @author "Daniel Kopecek" <dkopecek@redhat.com>
 *
 * 2010/06/13 dkopecek@redhat.com
 *  This probe is able to process a family_object as defined in OVAL 5.4 and 5.5.
 *
 */

/*
 * Copyright 2009 Red Hat Inc., Durham, North Carolina.
 * All Rights Reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Authors:
 *      "Tomas Heinrich" <theinric@redhat.com>
 *      "Daniel Kopecek" <dkopecek@redhat.com>
 */

/*
 * family probe:
 *
 *  family_object
 *
 *  family_item
 *    attrs
 *      id
 *      status_enum status
 *    [0..1] string family
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <seap.h>
#include <string.h>
#include <probe-api.h>

int probe_main(SEXP_t *probe_in, SEXP_t *probe_out, void *arg, SEXP_t *filters)
{
	SEXP_t *item;

        (void)arg;
        (void)filters;

	const char *family =
#if defined(_WIN32)
        "windows";
#elif defined(Macintosh) || defined(macintosh) || (defined(__APPLE__) && defined(__MACH__))
        "macos";
#elif defined(__unix__) || defined(__unix)
        "unix";
#elif defined(CISCO_IOS) /* XXX: how to detect IOS? */
        "ios";
#else
        "error";
#endif

	if (probe_in == NULL || probe_out == NULL) {
		return PROBE_EINVAL;
	}

        item = probe_item_create(OVAL_INDEPENDENT_FAMILY, NULL,
                                 "family", OVAL_DATATYPE_STRING, family,
                                 NULL);

	probe_cobj_add_item(probe_out, item);
        SEXP_free (item);

	return (0);
}
