#!/bin/bash

make_proxies() {
    cd ./src/
    list=`ls *.cpp`
    cd ../proxies/
    rm -fr *
    for item in $list ; do
        [ ${item} == "++cpp11.cpp" ] && continue
        str=${item%.cpp} # use filename but extension
        echo "#include <++cpp11.h>" >> ${item}
        echo "" >> ${item}
        echo "void "${str}"() {" >> ${item}
        echo "    std::cout << std::endl << \"Feature \\\""${str}"\\\" not implemented.\" << std::endl;" >> ${item}
        echo "}" >> ${item}
    done
    cd ../
}

make_declarations() {
    cd ./proxies/
    decls="../include/declarations.h"
    [ -f ${decls} ] `rm -f ${decls}`
    echo "#ifndef DECLARATIONS_H" >> ${decls}
    echo "#define DACLARATIONS_H" >> ${decls}
    echo "" >> ${decls}
    for item in `ls *.cpp` ; do
        [ ${item} == "++cpp11.cpp" ] && continue
        str=${item%.cpp} # use filename but extension
        echo "void "${str}"();" >> ${decls}
    done
    echo "" >> ${decls}
    echo "#endif // DECLARATIONS_H" >> ${decls}
    cd ../
}

make_proxies
make_declarations
