/* signature extension for PHP */

#ifndef PHP_SIGNATURE_H
# define PHP_SIGNATURE_H

extern zend_module_entry signature_module_entry;
# define phpext_signature_ptr &signature_module_entry


# define PHP_SIGNATURE_VERSION "0.1.0"
# define PHP_SIGNATURE_SECRET "OULWpO7bckZh8zZi"

# if defined(ZTS) && defined(COMPILE_DL_SIGNATURE)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_SIGNATURE_H */
