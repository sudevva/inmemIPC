
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include "../kernel/main.h"
#include "../kernel/operators.h"
#include "../kernel/time.h"

// top statement before class, add to after headers
// test include .h
#include <fcntl.h>
#include <sys/ptrace.h>
#include <wait.h>


ZEPHIR_INIT_CLASS(Memcp_Greeting) {

    ZEPHIR_REGISTER_CLASS(Memcp, Greeting, memcp, greeting, memcp_greeting_method_entry, 0);

    return SUCCESS;

}

PHP_METHOD (Memcp_Greeting, getRef) {

    long c = 0;
    zval *n;

    if (zend_parse_parameters(ZEND_NUM_ARGS()TSRMLS_CC, "z/", &n) == FAILURE) {
        return;
    }

    zend_uchar type = Z_TYPE(*n);

    if (type == IS_STRING) {
        printf("%p\n", n->value.str);
        printf("%d\n", n->value.str->len);
        int i;
    }
    if (type == IS_ARRAY) {
        printf("n->value.arr %p\n", n->value.arr);
        printf("n->value.arr %p\n", n->value);
        printf("n->value.arr %p\n", &n->value);
        printf("nNumUsed %d\n", n->value.arr->nNumUsed);
        int i;
        for (i = 0; i < n->value.arr->nNumUsed; i++) {
            Bucket *b = n->value.arr->arData + i;
            printf("%i - %d - %p\n", i, b->val.value.lval, &b->val.value.str->val);
        }
    }


    RETURN_LONG(n);

}

#define Z_GC(p)                (p)->gc


void PREAD_MEM(int fd, void *b_buf, size_t size, void *mem_addr){
//    struct timeval tp = {0};
//    gettimeofday(&tp, NULL);
//    double start = (double)(tp.tv_sec + tp.tv_usec / MICRO_IN_SEC);

    pread(fd, b_buf, size, (long)mem_addr);
//    gettimeofday(&tp, NULL);
//    double end = (double)(tp.tv_sec + tp.tv_usec / MICRO_IN_SEC);
//    printf("time %f\n", (end - start));
}

void loadStringValue(int fd, zval *z) {
    zend_string *zvaluez;
    zvaluez = zend_string_alloc(sizeof(char) * 8, 0);

    PREAD_MEM(fd, zvaluez, sizeof(zend_string), Z_STR_P(z));

    zend_string *zvaluen;
    zvaluen = zend_string_alloc(zvaluez->len, 0);
    zend_refcounted_h *refcounted_p = &Z_GC(zvaluen);

    PREAD_MEM(fd, zvaluen, (sizeof(zend_string) + (sizeof(char) * zvaluez->len)) - sizeof(char) * 8, Z_STR_P(z));
    Z_GC(zvaluen) = *refcounted_p;
    ZVAL_STR(z, zvaluen);
}

#define loadZval(z, fd, mem, reread) do {\
    if(reread) PREAD_MEM(fd, z, sizeof(zval), mem); \
    zend_uchar type = Z_TYPE_P(z); \
    if (type == IS_STRING) { \
        loadStringValue(fd, z); \
    } else if (type == IS_ARRAY) { \
        loadArrayValue(fd, z); \
    }\
}while(0)


void loadArrayValue(int fd, zval *z) {
    zend_array *zendArray;
    zendArray = emalloc(sizeof(zend_array));
    PREAD_MEM(fd, zendArray, sizeof(zend_array), Z_ARR_P(z));

    zend_refcounted_h *refcounted_p = &Z_GC(zendArray);

    Bucket* b_buf;
    b_buf = emalloc(sizeof(Bucket) * (zendArray->nNumOfElements));
    PREAD_MEM(fd, b_buf, sizeof(Bucket) * zendArray->nNumOfElements, zendArray->arData);


    int i;
    array_init_size(z, (uint32_t)zendArray->nNumOfElements);
    zend_hash_real_init(Z_ARRVAL_P(z), 1);

    Bucket *bucket2;
    int nel = zendArray->nNumOfElements;
    ZEND_HASH_FILL_PACKED(Z_ARRVAL_P(z)) {
            for (i = 0; i < nel; ++i) {
                bucket2 = b_buf+i;

                if (Z_TYPE_P(&bucket2->val) == IS_LONG || Z_TYPE_P(&bucket2->val) == IS_DOUBLE) {
                    ZEND_HASH_FILL_ADD(&bucket2->val);
                } else {
                    loadZval(&bucket2->val, fd, &bucket2->val, 0);
                    ZEND_HASH_FILL_ADD(&bucket2->val);
                }
            }
        } ZEND_HASH_FILL_END();
    efree(b_buf);
    efree(zendArray);
}

PHP_METHOD (Memcp_Greeting, getCopy) {

    long mem;
    int pid;
    zval *pid_param = NULL, *mem_param = NULL, c;

    if (zend_parse_parameters(2, "zz", &pid_param, &mem_param) == FAILURE) {
        return;
    }


    pid = (int) zephir_get_intval(pid_param);
    mem = zephir_get_intval(mem_param);

    ptrace(PTRACE_ATTACH, pid, 0, 0);
    waitpid(pid, NULL, 0);

    char file[64];
    sprintf(file, "/proc/%ld/mem", pid);
    int fd = open(file, O_RDWR);

    zval *z = NULL;
    z = emalloc(sizeof(zval));

    loadZval(z, fd, (void *)mem, 1);

    ptrace(PTRACE_DETACH, pid, 0, 0);
    close(fd);

    RETURN_ZVAL(z, 0, 0);
}
