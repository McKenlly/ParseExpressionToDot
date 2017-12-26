



make
if ! ./parser  > "build.dot" ; then
    echo "ERROR: no run parser"
    continue
fi


dot -Tps build.dot -o picture.ps 
