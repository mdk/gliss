#!/bin/sh

function print_line ()
{
    word_len=`expr length $1`
    status_len=`expr length $2`
    let dots=78-word_len-status_len-2

    echo -n "$1 "

    for ((i=0;i<dots;i++)); do
        echo -n "$3"
    done

    echo " $2"
}

test_programs="
gliss-test-slices
gliss-test-list-prepend
gliss-test-list-reverse
gliss-test-simple-line-vis
gliss-test-line-accumulation
gliss-test-quadratic-accumulation
gliss-test-quadratic-intersecting-vis
gliss-test-simple-quadratic-vis
gliss-test-simple-cubic-vis
gliss-test-cubic-flower-vis
gliss-test-quadratic-and-lines-vis
gliss-test-quadratic-closing-vis
gliss-test-line-intersecting-vis
gliss-test-control-triangulation-vis
gliss-test-list-append-sorted
gliss-test-cubic-font-vis
gliss-test-cubic-mono-logo-vis
gliss-test-allocators
gliss-test-allocators-resolve
gliss-test-allocators-uninitialized
"

report=""
current_date=`date -R`

echo
echo "GLISS TEST SUITE: $current_date"
echo

for program in $test_programs; do

    output=`./$program --non-interactive`

    if [ "$?" == 0 ]; then
        print_line "$program" "[OK]" "."
    elif [ "$?" != 1 ]; then
        print_line "$program" "[FAIL]" "."
    else
        print_line "$program" "[SEGFAULT]" "."
    fi

    if [ -n "$output" ]; then
        report="$report$program:\n$output\n\n"
    fi

done

echo
echo "REPORT:"
echo
echo -e "$report"
