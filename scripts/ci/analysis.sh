#!/bin/bash
SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
ROOT_DIR=${SCRIPT_DIR}/../../
BUILD_DIR=${ROOT_DIR}/build/
ANALYSIS_DIR=${BUILD_DIR}/analysis
TEST_RESULT_DIR=${BUILD_DIR}/test/results/

OUTPUT_MARKDOWN_FILE=${ANALYSIS_DIR}/analysis.md

function write_output_header() {
    echo "# Analysis" >> ${OUTPUT_MARKDOWN_FILE}
    echo "" >> ${OUTPUT_MARKDOWN_FILE}
}

function parse_test_results() {
    set -u

    # use nullglob in case there are no matching files
    shopt -s nullglob

    # Run tests
    ${SCRIPT_DIR}/run_tests.sh
    RET=$?

    # create an array with all the filer/dir inside ~/myDir
    test_results=(${TEST_RESULT_DIR}/*)

    echo "## Test Results" >> ${OUTPUT_MARKDOWN_FILE}
    echo "" >> ${OUTPUT_MARKDOWN_FILE}

    if [ ${#test_results[@]} -eq 0 ] && [ ${RET} == 0 ]; then
        echo "No tests to run. ✅" >> ${OUTPUT_MARKDOWN_FILE}
        exit 0
    elif [ ${#test_results[@]} == 0 ] && [ ${RET} != 0 ]; then
        echo "Test suite failed! ❌" >> ${OUTPUT_MARKDOWN_FILE}
        exit 1
    else 
        echo "|Name|Run|Passed|Failed|Ignored|Result|" >> ${OUTPUT_MARKDOWN_FILE}
        echo "|----|---|------|------|-------|------|" >> ${OUTPUT_MARKDOWN_FILE}
    fi;

    # iterate through array using a counter
    for f in "${test_results[@]}"; do
        FILE_NAME=$(basename ${f%?????})
        TOTAL_RUN=$(cat ${f} | grep :total: | tr -d ":total:" | tr -d " " )
        TOTAL_PASSED=$(cat ${f} | grep :passed: | tr -d ":passed:" | tr -d " " )
        TOTAL_FAILED=$(cat ${f} | grep :failed: | tr -d ":failed:" | tr -d " " )
        TOTAL_IGNORED=$(cat ${f} | grep :ignored: | tr -d ":ignored:" | tr -d " " )
        


        LINE="|${FILE_NAME}|${TOTAL_RUN}|${TOTAL_PASSED}|${TOTAL_FAILED}|${TOTAL_IGNORED}|" 
        if [ ${TOTAL_FAILED} != 0 ]; then
            LINE="${LINE}❌|"
        else
            LINE="${LINE}✅|"
        fi;
        echo "${LINE}" >> ${OUTPUT_MARKDOWN_FILE}
    done
}

function parse_coverage_results() {
    # Write header
    echo "## Coverage Results" >> ${OUTPUT_MARKDOWN_FILE}
    echo "" >> ${OUTPUT_MARKDOWN_FILE}

    # Run coverage
    ${SCRIPT_DIR}/run_coverage.sh

    if [ ${RET} != 0 ]; then
        echo "Coverage failed! ❌" >> ${OUTPUT_MARKDOWN_FILE}
        exit 1
    fi;

    # Generate report
    echo "\`\`\`" >> ${OUTPUT_MARKDOWN_FILE}
    cd ${ROOT_DIR}
    ceedling utils:gcov >> ${OUTPUT_MARKDOWN_FILE}
    echo "\`\`\`" >> ${OUTPUT_MARKDOWN_FILE}

}

function main() {

    # Delete analysis directory if already exists
    if [ -d ${ANALYSIS_DIR} ]; then
        rm -rf ${ANALYSIS_DIR} &> /dev/null
    fi

    # Create analysis directory
    mkdir -p ${ANALYSIS_DIR}
    write_output_header

    # Parse testing results
    parse_test_results

    # Parse gcov results
    parse_coverage_results

}

main