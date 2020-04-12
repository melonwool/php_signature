/* signature extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_signature.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

PHPAPI zval signataure_in_ex(zend_string *unsign, zend_bool suffix)
{
    // 初始化secret为zend_string
    zend_string *secret = zend_string_init(PHP_SIGNATURE_SECRET, strlen(PHP_SIGNATURE_SECRET), 0);
    // 转换原始字符串并拼接秘钥
    zend_string *z_unsign_new;
    // 判定是否为后置添加字秘钥
    if (suffix){
        z_unsign_new = strpprintf(0, "%s%s", ZSTR_VAL(unsign), ZSTR_VAL(secret));
    }else{
        z_unsign_new = strpprintf(0, "%s%s", ZSTR_VAL(secret), ZSTR_VAL(unsign));
    }
    
    zval call_func_name, call_func_ret, call_func_params[1];
    char *func_name = "sha1";
    zend_string *call_func_str;
    uint32_t call_func_param_cnt = 1;
    zend_string result;

    // 分配zend_string
    call_func_str = zend_string_init(func_name,strlen(func_name),0);
    // 设置到zval
    ZVAL_STR(&call_func_name, call_func_str);
    // 设置参数
    ZVAL_STR(&call_func_params[0], z_unsign_new);
    
    // 调用
    if (SUCCESS != call_user_function(EG(function_table), NULL, &call_func_name, &call_func_ret, call_func_param_cnt, call_func_params)){
        // 异常处理
    }
    return call_func_ret;
}

/* {{{ void signature_in()
 */
PHP_FUNCTION(signature_in)
{
	zend_string *unsign;
    zend_bool suffix = 0;
    // 处理参数,最少1个参数,最多两个参数
    ZEND_PARSE_PARAMETERS_START(1, 2)
        Z_PARAM_STR(unsign)
		Z_PARAM_OPTIONAL
        Z_PARAM_BOOL(suffix)
    ZEND_PARSE_PARAMETERS_END();

    zval result = signataure_in_ex(unsign, suffix);

	RETURN_STRING(Z_STRVAL(result));
}
/* }}} */

/* {{{ string signature_verify( [ string $var ] )
 */
PHP_FUNCTION(signature_verify)
{
	zend_string *str;
    zend_string *signed_str;
    zend_bool suffix = 0;

	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_STR(str)
		Z_PARAM_STR(signed_str)
		Z_PARAM_OPTIONAL
		Z_PARAM_BOOL(suffix)
	ZEND_PARSE_PARAMETERS_END();

    zval result = signataure_in_ex(str, suffix);
    //printf("%s:%s", ZSTR_VAL(signed_str), Z_STRVAL(result));

    if (strcmp(ZSTR_VAL(signed_str), Z_STRVAL(result)) == 0) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}
/* }}}*/

/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(signature)
{
#if defined(ZTS) && defined(COMPILE_DL_SIGNATURE)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(signature)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "signature support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ arginfo
 */
ZEND_BEGIN_ARG_INFO(arginfo_signature_in, 1)
ZEND_END_ARG_INFO()

/* }}} */

/* {{{ signature_functions[]
 */
static const zend_function_entry signature_functions[] = {
	PHP_FE(signature_in,		arginfo_signature_in)
	PHP_FE(signature_verify,		arginfo_signature_in)
	PHP_FE_END
};
/* }}} */

/* {{{ signature_module_entry
 */
zend_module_entry signature_module_entry = {
	STANDARD_MODULE_HEADER,
	"signature",					/* Extension name */
	signature_functions,			/* zend_function_entry */
	NULL,							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(signature),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(signature),			/* PHP_MINFO - Module info */
	PHP_SIGNATURE_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_SIGNATURE
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(signature)
#endif
