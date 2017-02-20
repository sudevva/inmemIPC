
/* This file was generated automatically by Zephir do not modify it! */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#include "php_ext.h"
#include "memcp.h"

#include <ext/standard/info.h>

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/globals.h"
#include "kernel/main.h"
#include "kernel/fcall.h"
#include "kernel/memory.h"



zend_class_entry *memcp_greeting_ce;

ZEND_DECLARE_MODULE_GLOBALS(memcp)

PHP_INI_BEGIN()
	
PHP_INI_END()

static PHP_MINIT_FUNCTION(memcp)
{
	REGISTER_INI_ENTRIES();
	ZEPHIR_INIT(Memcp_Greeting);
	return SUCCESS;
}

#ifndef ZEPHIR_RELEASE
static PHP_MSHUTDOWN_FUNCTION(memcp)
{
	zephir_deinitialize_memory(TSRMLS_C);
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
#endif

/**
 * Initialize globals on each request or each thread started
 */
static void php_zephir_init_globals(zend_memcp_globals *memcp_globals TSRMLS_DC)
{
	memcp_globals->initialized = 0;

	/* Memory options */
	memcp_globals->active_memory = NULL;

	/* Virtual Symbol Tables */
	memcp_globals->active_symbol_table = NULL;

	/* Cache Enabled */
	memcp_globals->cache_enabled = 1;

	/* Recursive Lock */
	memcp_globals->recursive_lock = 0;

	/* Static cache */
	memset(memcp_globals->scache, '\0', sizeof(zephir_fcall_cache_entry*) * ZEPHIR_MAX_CACHE_SLOTS);


}

/**
 * Initialize globals only on each thread started
 */
static void php_zephir_init_module_globals(zend_memcp_globals *memcp_globals TSRMLS_DC)
{

}

static PHP_RINIT_FUNCTION(memcp)
{

	zend_memcp_globals *memcp_globals_ptr;
#ifdef ZTS
	tsrm_ls = ts_resource(0);
#endif
	memcp_globals_ptr = ZEPHIR_VGLOBAL;

	php_zephir_init_globals(memcp_globals_ptr TSRMLS_CC);
	zephir_initialize_memory(memcp_globals_ptr TSRMLS_CC);


	return SUCCESS;
}

static PHP_RSHUTDOWN_FUNCTION(memcp)
{
	
	zephir_deinitialize_memory(TSRMLS_C);
	return SUCCESS;
}

static PHP_MINFO_FUNCTION(memcp)
{
	php_info_print_box_start(0);
	php_printf("%s", PHP_MEMCP_DESCRIPTION);
	php_info_print_box_end();

	php_info_print_table_start();
	php_info_print_table_header(2, PHP_MEMCP_NAME, "enabled");
	php_info_print_table_row(2, "Author", PHP_MEMCP_AUTHOR);
	php_info_print_table_row(2, "Version", PHP_MEMCP_VERSION);
	php_info_print_table_row(2, "Build Date", __DATE__ " " __TIME__ );
	php_info_print_table_row(2, "Powered by Zephir", "Version " PHP_MEMCP_ZEPVERSION);
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}

static PHP_GINIT_FUNCTION(memcp)
{
	php_zephir_init_globals(memcp_globals TSRMLS_CC);
	php_zephir_init_module_globals(memcp_globals TSRMLS_CC);
}

static PHP_GSHUTDOWN_FUNCTION(memcp)
{

}


zend_function_entry php_memcp_functions[] = {
ZEND_FE_END

};

zend_module_entry memcp_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	NULL,
	PHP_MEMCP_EXTNAME,
	php_memcp_functions,
	PHP_MINIT(memcp),
#ifndef ZEPHIR_RELEASE
	PHP_MSHUTDOWN(memcp),
#else
	NULL,
#endif
	PHP_RINIT(memcp),
	PHP_RSHUTDOWN(memcp),
	PHP_MINFO(memcp),
	PHP_MEMCP_VERSION,
	ZEND_MODULE_GLOBALS(memcp),
	PHP_GINIT(memcp),
	PHP_GSHUTDOWN(memcp),
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_MEMCP
ZEND_GET_MODULE(memcp)
#endif
