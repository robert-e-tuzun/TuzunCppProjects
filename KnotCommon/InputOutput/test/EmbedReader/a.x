#!/bin/bash

INFILE_DIR=${PROJECT_ROOT}"/KnotCommon/InputOutput/test/EmbedReader/"
POLYH_DIR=${DIR_PATH_POLYH_DATA}"/"
testEmbedReader -- ${POLYH_DIR} ${INFILE_DIR}
