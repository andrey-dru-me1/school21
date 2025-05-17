#ifndef COMMAND_LINE_PARSER_H
#define COMMAND_LINE_PARSER_H

/**
 * Represents an option type.
 * One of `label` and `long_label` could be not set: `0` and `NULL` values
 * respectively.
 *
 * @param apply function to call when particular option is present
 * @param long_label a string that covers this option
 * @param arity count of arguments to pass to that function from a command line
 * @param label a character that covers this option
 */
typedef struct option_s {
  int (*apply)(void *obj, char **args);
  char *long_label;
  int arity;
  char label;
} option;

#define TYPE option
#define NAME op
#include "../arr/arr.h"
#undef TYPE
#undef NAME

#define TYPE char *
#define NAME str
#include "../vector/vector_decl.h"
#undef TYPE
#undef NAME

/**
 * Gets a line to parse, applies funtions connected to parsed options and
 * returns unused line parameters.
 *
 * @param line_to_parse array of string tokens which contains options, arguments
 * to these options and other line parameters
 * @param obj some thing that will be passed to an each option's function. Could
 * be a pointer to some enum that function changes
 * @param available_options array of all the possible options with their arity
 * and functions to apply if option is present
 * @param line_parameters filled by the function and contains all the
 * string tokens which are neither options nor arguments to options. `dat`
 * field of this variable has to be freed.
 * @return 0 on successful completition and some non-zero value otherwise
 */
int parse_line(str_arr line_to_parse, void *obj, op_arr available_options,
               str_arr *line_parameters);

#endif
