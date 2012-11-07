#!/bin/bash

set -e
set -o pipefail

name=$(basename $0 .sh)

result=$name.oval.xml-0.variables-0.xml
stderr=$(mktemp -t ${name}.out.XXXXXX)

$OSCAP xccdf eval --export-variable $srcdir/${name}.xccdf.xml 2> $stderr

echo "Stderr file = $stderr"
echo "Result file = $result"
[ -f $stderr ]; [ ! -s $stderr ]; rm -rf $stderr

assert_exists() { [ $($XPATH $result 'count('$2')') == "$1" ]; }
assert_exists 3 '//variable/value[text()="100"]'

rm -rf $result
