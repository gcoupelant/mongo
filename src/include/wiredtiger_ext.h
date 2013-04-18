/*-
 * Copyright (c) 2008-2013 WiredTiger, Inc.
 *	All rights reserved.
 *
 * See the file LICENSE for redistribution information.
 */

#ifndef	__WIREDTIGER_EXT_H_
#define	__WIREDTIGER_EXT_H_

#include <wiredtiger.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*! @addtogroup wt_ext
 * @{
 */

/*! Table of WiredTiger extension methods.
 *
 * This structure is used to provide a set of WiredTiger methods to extension
 * modules without needing to link the modules with the WiredTiger library.
 *
 * The extension methods may be used both by modules that are linked with
 * the WiredTiger library (for example, a data source configured using the
 * WT_CONNECTION::add_data_source method), and by modules not linked with the
 * WiredTiger library (for example, a compression module configured using the
 * WT_CONNECTION::add_compressor method).
 *
 * To use these functions:
 * - include the wiredtiger_ext.h header file,
 * - declare a variable which references a WT_EXTENSION_API structure, and
 * - initialize the variable using WT_CONNECTION::get_extension_api method.
 *
 * @snippet ex_data_source.c WT_EXTENSION_API declaration
 *
 * The following code is from the sample compression module, where the
 * extension functions are configured  in the extension's entry point:
 *
 * @snippet nop_compress.c WT_EXTENSION_API declaration
 * @snippet nop_compress.c WT_EXTENSION_API initialization
 */
struct __wt_extension_api {
/* !!! To maintain backwards compatibility, this structure is append-only. */
#if !defined(SWIG) && !defined(DOXYGEN)
	/*
	 * Private fields.
	 */
	WT_CONNECTION *conn;		/* Enclosing connection */
#endif
	/*! Insert an error message into the WiredTiger error stream.
	 *
	 * @param wt_api the extension handle
	 * @param session the session handle (or NULL if none available)
	 * @param fmt a printf-like format specification
	 * @errors
	 *
	 * @snippet ex_data_source.c WT_EXTENSION_API err_printf
	 */
	int (*err_printf)(WT_EXTENSION_API *wt_api,
	    WT_SESSION *session, const char *fmt, ...);

	/*! Insert a message into the WiredTiger message stream.
	 *
	 * @param wt_api the extension handle
	 * @param session the session handle (or NULL if none available)
	 * @param fmt a printf-like format specification
	 * @errors
	 *
	 * @snippet ex_data_source.c WT_EXTENSION_API msg_printf
	 */
	int (*msg_printf)(
	    WT_EXTENSION_API *, WT_SESSION *session, const char *fmt, ...);

	/*! Allocate short-term use scratch memory.
	 *
	 * @param wt_api the extension handle
	 * @param session the session handle (or NULL if none available)
	 * @param bytes the number of bytes of memory needed
	 * @returns A valid memory reference on success or NULL on error
	 *
	 * @snippet ex_data_source.c WT_EXTENSION_API scr_alloc
	 */
	void *(*scr_alloc)(
	    WT_EXTENSION_API *wt_api, WT_SESSION *session, size_t bytes);

	/*! Free short-term use scratch memory.
	 *
	 * @param wt_api the extension handle
	 * @param session the session handle (or NULL if none available)
	 * @param ref a memory reference returned by WT_EXTENSION_API::scr_alloc
	 *
	 * @snippet ex_data_source.c WT_EXTENSION_API scr_free
	 */
	void (*scr_free)(WT_EXTENSION_API *, WT_SESSION *session, void *ref);

	/*! Return the value of a configuration string.
	 *
	 * @param wt_api the extension handle
	 * @param session the session handle (or NULL if none available)
	 * @param key configuration key string
	 * @param config the configuration information passed to an application
	 * callback
	 * @param value the returned value
	 * @errors
	 *
	 * @snippet ex_data_source.c WT_EXTENSION get_config
	 */
	int (*get_config)(WT_EXTENSION_API *wt_api, WT_SESSION *session,
	    const char *key, WT_CONFIG_ARG *config, WT_CONFIG_ITEM *value);

	/*! Return the list entries of a configuration string value.
	 * This method steps through the entries found in the last returned
	 * value from WT_EXTENSION_API::get_config.  The last returned value
	 * should be of type "list".
	 *
	 * @param wt_api the extension handle
	 * @param session the session handle (or NULL if none available)
	 * @param value the returned value
	 * @errors
	 *
	 * @snippet ex_data_source.c WT_EXTENSION get_config_next
	 */
	int (*get_config_next)(WT_EXTENSION_API *wt_api, WT_SESSION *session,
	    WT_CONFIG_ITEM *value);
};

/*! @} */

#if defined(__cplusplus)
}
#endif
#endif /* __WIREDTIGER_EXT_H_ */
