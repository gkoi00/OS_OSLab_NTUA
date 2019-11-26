#!/bin/bash

echo "abcdefghijklmnop" > 16_byte_file

dd if=16_byte_file of=bf00 bs=1 count=16 seek=1073741824
dd if=16_byte_file of=bf01 bs=1 count=16 seek=1073741824
dd if=16_byte_file of=bf02 bs=1 count=16 seek=1073741824
dd if=16_byte_file of=bf03 bs=1 count=16 seek=1073741824
dd if=16_byte_file of=bf04 bs=1 count=16 seek=1073741824
dd if=16_byte_file of=bf05 bs=1 count=16 seek=1073741824
dd if=16_byte_file of=bf06 bs=1 count=16 seek=1073741824
dd if=16_byte_file of=bf07 bs=1 count=16 seek=1073741824
dd if=16_byte_file of=bf08 bs=1 count=16 seek=1073741824
dd if=16_byte_file of=bf09 bs=1 count=16 seek=1073741824

./riddle

rm bf00 bf01 bf02 bf03 bf04 bf05 bf06 bf07 bf08 bf09 16_byte_file

##2nd implementation
#dd if=16_byte_file of=bf00 bs=16 count=1 seek=1073741824/16
#dd if=16_byte_file of=bf01 bs=16 count=1 seek=1073741824/16
#dd if=16_byte_file of=bf02 bs=16 count=1 seek=1073741824/16
#dd if=16_byte_file of=bf03 bs=16 count=1 seek=1073741824/16
#dd if=16_byte_file of=bf04 bs=16 count=1 seek=1073741824/16
#dd if=16_byte_file of=bf05 bs=16 count=1 seek=1073741824/16
#dd if=16_byte_file of=bf06 bs=16 count=1 seek=1073741824/16
#dd if=16_byte_file of=bf07 bs=16 count=1 seek=1073741824/16
#dd if=16_byte_file of=bf08 bs=16 count=1 seek=1073741824/16
#dd if=16_byte_file of=bf09 bs=16 count=1 seek=1073741824/16

#./riddle

#rm bf00 bf01 bf02 bf03 bf04 bf05 bf06 bf07 bf08 bf09 16_byte_file

