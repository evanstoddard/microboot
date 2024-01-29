#!/bin/bash
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
ROOT_DIR=${SCRIPT_DIR}/../../

 # Change into root and run tests
cd ${ROOT_DIR}

# Run tests
ceedling