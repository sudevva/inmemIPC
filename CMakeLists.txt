cmake_minimum_required(VERSION 3.7)
project(ext)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        kernel/extended/array.c
        kernel/extended/array.h
        kernel/extended/fcall.c
        kernel/extended/fcall.h
        kernel/array.c
        kernel/array.h
        kernel/assert.c
        kernel/assert.h
        kernel/backtrace.c
        kernel/backtrace.h
        kernel/concat.c
        kernel/concat.h
        kernel/debug.c
        kernel/debug.h
        kernel/exception.c
        kernel/exception.h
        kernel/exit.c
        kernel/exit.h
        kernel/fcall.c
        kernel/fcall.h
        kernel/fcall_internal.h
        kernel/file.c
        kernel/file.h
        kernel/filter.c
        kernel/filter.h
        kernel/globals.h
        kernel/hash.c
        kernel/hash.h
        kernel/iterator.c
        kernel/iterator.h
        kernel/main.c
        kernel/main.h
        kernel/math.c
        kernel/math.h
        kernel/memory.c
        kernel/memory.h
        kernel/object.c
        kernel/object.h
        kernel/operators.c
        kernel/operators.h
        kernel/output.c
        kernel/output.h
        kernel/persistent.c
        kernel/persistent.h
        kernel/require.c
        kernel/require.h
        kernel/session.c
        kernel/session.h
        kernel/string.c
        kernel/string.h
        kernel/time.c
        kernel/time.h
        kernel/variables.c
        kernel/variables.h
        memcp/greeting.zep.c
        memcp/greeting.zep.h
        config.h
        ext.h
        ext_config.h
        memcp.c
        memcp.h
        php_ext.h
        php_memcp.h)

add_executable(ext ${SOURCE_FILES})
include_directories(/usr/include/php/20160303/)
include_directories(/usr/include/php/20160303/Zend)
include_directories(/usr/include/php/20160303/main)
include_directories(/tmp/php-src/)