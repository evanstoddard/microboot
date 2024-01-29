#!/bin/bash
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
ROOT_DIR=${SCRIPT_DIR}/../../
BUILD_DIR=${ROOT_DIR}/build/

function main() {
    if [ ! -d ${BUILD_DIR} ]; then
        mkdir ${BUILD_DIR}
    fi;

    # Remove previous build statuses
    if [ -f ${BUILD_DIR}/build_success ]; then
        rm ${BUILD_DIR}/build_success
    fi;
    
    if [ -f ${BUILD_DIR}/build_fail ]; then
        rm ${BUILD_DIR}/build_fail
    fi;
    
    # Make project
    cd ${BUILD_DIR}
    gcc -c ${ROOT_DIR}/src/*.c
    
    # Save return value and write status
    RET=$?
    if [ ${RET} == 0 ]; then
        touch ${BUILD_DIR}/build_success;
    else
        touch ${BUILD_DIR}/build_fail;
    fi;
    
    return ${RET}
}

main
exit $?