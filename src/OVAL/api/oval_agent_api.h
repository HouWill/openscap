/**
 * @file oval_agent_api.h 
 * \brief Open Vulnerability and Assessment Language
 *
 * See more details at http://oval.mitre.org/
 */

/*
 * Copyright 2008 Red Hat Inc., Durham, North Carolina.
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
 *      "David Niemoller" <David.Niemoller@g2-inc.com>
 */


#ifndef OVAL_AGENT_API_H_
#define OVAL_AGENT_API_H_

#include "oval_definitions.h"
#include "oval_system_characteristics.h"
#include "oval_results.h"

struct export_target;
struct import_source;

struct import_source *import_source_file(char *filename);
void import_source_free(struct import_source *);

struct oval_object_model;

struct oval_object_model *oval_object_model_new();

typedef enum {
	XML_VALIDITY_WARNING = 1,
	XML_VALIDITY_ERROR = 2,
	XML_WARNING = 3,
	XML_ERROR = 4
} oval_xml_severity_enum;

struct oval_xml_error {
	void *user_arg;
	char *message;
	oval_xml_severity_enum severity;
	int line_number;
	char *system_id;
};

typedef int (*oval_xml_error_handler) (struct oval_xml_error *, void *user_arg);

void load_oval_definitions(struct oval_object_model *, struct import_source *,
			   oval_xml_error_handler, void *);

struct oval_definition *get_oval_definition(struct oval_object_model *,
					    char *def_urn);
struct oval_test *get_oval_test(struct oval_object_model *, char *tst_urn);
struct oval_object *get_oval_object(struct oval_object_model *, char *obj_urn);
struct oval_state *get_oval_state(struct oval_object_model *, char *ste_urn);
struct oval_variable *get_oval_variable(struct oval_object_model *,
					char *var_urn);

struct oval_iterator_definition *get_oval_definitions(struct oval_object_model
						      *);
struct oval_iterator_test *get_oval_tests(struct oval_object_model *);
struct oval_iterator_object *get_oval_objects(struct oval_object_model *);
struct oval_iterator_state *get_oval_states(struct oval_object_model *);
struct oval_iterator_variable *get_oval_variables(struct oval_object_model *);

	/* needs oval_characteristics, export_target struct definitions */
int export_characteristics(struct oval_iterator_syschar *,
			   struct export_target *);

	/* needs oval_results, export_target struct definitions */
int export_results(struct oval_result *, struct export_target *);

struct oval_iterator_syschar *probe_object(struct oval_object *,
					   struct oval_iterator_variable_binding
					   *);
struct oval_result_test *resolve_test(struct oval_test *,
				      struct oval_iterator_syschar *,
				      struct oval_iterator_variable_binding *);
struct oval_result *resolve_definition(struct oval_definition *,
				       struct oval_iterator_syschar *,
				       struct oval_iterator_variable_binding *);

#endif				/*OVAL_AGENT_API_H_ */
