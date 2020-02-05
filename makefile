#
# cmdline_params Makefile
# 
#

# The Basics:
INC_DIR = include
BIN_DIR = bin
SRC_DIR = src
TMP_DIR = .temp

# CCC_FLAGS = 
CCC = @g++ -g 

# Default Final Program
EXE_SRC = main.cxx



# Find The Files
SRC_FILES = ${shell ls $(SRC_DIR)}
INC_FILES = ${shell ls $(INC_DIR)}

#Also Includes and Libs
INC_FLAGS = -I${INC_DIR}





INCLUDE = $(patsubst %.h,${INC_DIR}/%.h,$(filter %.h,$(INC_FILES)))
INCLUDE+= $(patsubst %.hpp,${INC_DIR}/%.hpp,$(filter %.hpp,$(INC_FILES)))

SOURCES = $(patsubst %.cpp,${SRC_DIR}/%.cpp,$(filter %.cpp,$(SRC_FILES)))
#SOURCES+= $(patsubst %.cxx,${SRC_DIR}/%.cpp,$(filter %.cxx,$(SRC_FILES)))

OBJECTS = $(patsubst %.cpp,$(TMP_DIR)/%.o,$(filter %.cpp,$(SRC_FILES)))
EXE_OBJ = $(patsubst %.cxx,$(TMP_DIR)/%.o,$(filter %.cxx,$(SRC_FILES)))

PROGRAM = ${BIN_DIR}/$(basename ${EXE_SRC})


.PHONY : program all _all build install clean buildall directories includes intro

all : _all



_all : intro ${PROGRAM} directories
	@echo
	@echo "Target : '"$(basename ${EXE_SRC})"' Succesfully Built"

intro:
	@echo "Building Target : " $(basename ${EXE_SRC})
	@echo "Please Wait..."


${PROGRAM} : ${OBJECTS} ${EXE_OBJ}
	@echo " - Building Target"
	${CCC} -o $@ $^ ${INC_FLAGS}


${EXE_OBJ} : ${SRC_DIR}/${EXE_SRC} ${INCLUDE}
	@echo " - Compiling Target : " $(notdir $(basename $@))
	${CCC} -c $< -o $@ ${INC_FLAGS}


${OBJECTS} : ${TMP_DIR}/%.o : ${SRC_DIR}/%.cpp ${INCLUDE}
	@echo " - Compiling Source : " $(notdir $(basename $@))
	${CCC} -c $< -o $@ ${INC_FLAGS}



directories : ${BIN_DIR} ${SRC_DIR} ${INC_DIR} ${TMP_DIR}


${BIN_DIR} :
	mkdir -p ${BIN_DIR}

${SRC_DIR} :
	mkdir -p ${SRC_DIR}

${INC_DIR} :
	mkdir -p ${INC_DIR}

${TMP_DIR} :
	mkdir -p ${TMP_DIR}



clean :
	rm -f ${TMP_DIR}/*
	rm -f ${BIN_DIR}/*


