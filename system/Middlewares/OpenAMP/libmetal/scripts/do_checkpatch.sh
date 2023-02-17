#!/bin/sh

#
# Copyright (c) 2019 STMicroelectronics .
# Copyright (c) 2015 Intel Corporation.
#
# SPDX-License-Identifier: Apache-2.0
#

res=$1
[ -z "$res" ] && res="checkpatch_log"
[ -f ${res} ] && rm ${res}
[ -f ${res}_error.types ] && rm ${res}_error.types
[ -f ${res}_warning.types ] && rm ${res}_warning.types

dirs_to_check="lib"
files=$(for d in ${dirs_to_check}; do find $d/ -type f -name '*.[ch]'; done)

for i in $files; do
	./scripts/checkpatch.pl  --no-tree -f --emacs --summary-file --show-types --ignore BRACES,PRINTK_WITHOUT_KERN_LEVEL,SPLIT_STRING,PREFER_KERNEL_TYPES,NEW_TYPEDEFS --max-line-length=90 $i >> ${res}
done
grep ERROR: ${res} |cut -d : -f 3,4 |sort -u > ${res}_error.types
grep WARNING: ${res} |cut -d : -f 3,4 |sort -u > ${res}_warning.types
for i in `cat ${res}_error.types`; do
	echo -n $i ' '; grep $i ${res} | wc -l
done
for i in `cat ${res}_warning.types`; do
	echo -n $i ' '; grep $i ${res} | wc -l
done
