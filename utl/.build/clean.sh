#!/bin/sh



#INPUT_H=utl_error.h utl_ini.h utl_locale.h utl_rand.h utl_str_type.h utl_cmdln.h utl_file.h utl_llist.h utl_mem.h utl_str.h utl_type.h utl.h utl_assert.h utl_env.h

#INPUT_C=utl_cmdln.c utl_file.c utl_llist.c utl_mem.c utl_str.c utl_type.c utl_env.c utl_ini.c utl_locale.c utl_rand.c utl_str_type.c

#OUTPUT_O=utl_cmdln.o utl_file.o utl_llist.o utl_mem.o utl_str.o utl_type.o utl_env.o utl_ini.o utl_locale.o utl_rand.o utl_str_type.o

OUTPUT=utl.a

echo "object files and lib '$OUTPUT' will be removed."
rm -f *.o $OUTPUT
exit 0