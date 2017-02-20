
extern zend_class_entry *memcp_greeting_ce;

ZEPHIR_INIT_CLASS(Memcp_Greeting);

PHP_METHOD(Memcp_Greeting, getRef);
PHP_METHOD(Memcp_Greeting, getCopy);

ZEND_BEGIN_ARG_INFO(arginfo_memcp_greeting_getref, 1)
	ZEND_ARG_PASS_INFO(1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_memcp_greeting_getcopy, 0, 0, 2)
	ZEND_ARG_INFO(0, pid)
	ZEND_ARG_INFO(0, mem)
ZEND_END_ARG_INFO()

ZEPHIR_INIT_FUNCS(memcp_greeting_method_entry) {
	PHP_ME(Memcp_Greeting, getRef, arginfo_memcp_greeting_getref, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_ME(Memcp_Greeting, getCopy, arginfo_memcp_greeting_getcopy, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	PHP_FE_END
};
