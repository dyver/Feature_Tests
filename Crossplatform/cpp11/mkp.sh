#!/bin/bash

#exit 0

make_proxies() {
    cd ./proxies/
    for item in `ls *.cpp`
    do
        if [ ${item} != "cpp11.cpp" ]
        then
            str=${item%.cpp} # use filename but extension
            [ -f ${item} ] `rm -f ${item}`
            echo "#include <++cpp11.h>" >> ${item}
            echo "" >> ${item}
            echo "void "${str}"() {" >> ${item}
            echo "    std::cout << std::endl << \"Feature \\\""${str}"\\\" not implemented.\" << std::endl;" >> ${item}
            echo "}" >> ${item}
        fi
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
    for item in `ls *.cpp`
    do
        if [ ${item} != "++cpp11.cpp" ]
        then
            str=${item%.cpp} # use filename but extension
            echo "void "${str}"();" >> ${decls}
        fi
    done
    echo "" >> ${decls}
    echo "#endif // DECLARATIONS_H" >> ${decls}
    cd ../
}

make_proxies
make_declarations

#rm ./list3

        #echo "src/"${item} >> list

        #echo "proxies/"${item} >> list2

        #echo "    src/"${item}" \\" >> list3
