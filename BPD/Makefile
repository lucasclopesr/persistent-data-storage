CC=g++
CFLAGS=-std=c++11 -Wall
TARGET=lib

TEST_DIR    = ./test
BUILD_DIR   = ./build
SRC_DIR     = ./src
INCLUDE_DIR = ./include

# Testes
#${BUILD_DIR}/DBtest: ${BUILD_DIR}/DataBase.o ${BUILD_DIR}/Table.o ${BUILD_DIR}/Register.o build_dir
#	${CC} ${CFLAGS} -I ${INCLUDE_DIR} -o ${BUILD_DIR}/DBtest ${TEST_DIR}/DBtests.cpp ${BUILD_DIR}/*.o

#${BUILD_DIR}/Tabletest: ${BUILD_DIR}/DataBase.o ${BUILD_DIR}/Table.o ${BUILD_DIR}/Register.o build_dir
#	${CC} ${CFLAGS} -I ${INCLUDE_DIR} -o ${BUILD_DIR}/Tabletest ${TEST_DIR}/Tabletests.cpp ${BUILD_DIR}/*.o

# Main
${BUILD_DIR}/${TARGET}: ${BUILD_DIR}/main.o ${BUILD_DIR}/DataBase.o ${BUILD_DIR}/Table.o ${BUILD_DIR}/Register.o
	${CC} ${CFLAGS} -o ${BUILD_DIR}/${TARGET} ${BUILD_DIR}/*.o

# Dependencies
${BUILD_DIR}/DataBase.o: ${INCLUDE_DIR}/UnknownTableException.hpp ${INCLUDE_DIR}/CreateFolderException.hpp ${INCLUDE_DIR}/DeleteFileException.hpp ${INCLUDE_DIR}/DataBase.hpp ${SRC_DIR}/DataBase.cpp build_dir
	${CC} ${CFLAGS} -I ${INCLUDE_DIR} -c ${SRC_DIR}/DataBase.cpp -o ${BUILD_DIR}/DataBase.o

${BUILD_DIR}/Table.o: ${INCLUDE_DIR}/UnknownColumnException.hpp ${INCLUDE_DIR}/CreateFileException.hpp ${INCLUDE_DIR}/Table.hpp ${SRC_DIR}/Table.cpp build_dir
	${CC} ${CFLAGS} -I ${INCLUDE_DIR} -c ${SRC_DIR}/Table.cpp -o ${BUILD_DIR}/Table.o

${BUILD_DIR}/Register.o: ${INCLUDE_DIR}/Register.hpp ${SRC_DIR}/Register.cpp build_dir
	${CC} ${CFLAGS} -I ${INCLUDE_DIR} -c ${SRC_DIR}/Register.cpp -o ${BUILD_DIR}/Register.o

${BUILD_DIR}/main.o: ${INCLUDE_DIR}/DataBase.hpp ${SRC_DIR}/main.cpp build_dir
	${CC} ${CFLAGS} -I ${INCLUDE_DIR} -c ${SRC_DIR}/main.cpp -o ${BUILD_DIR}/main.o

build_dir:
	mkdir -p build

clean:
	rm -f ${BUILD_DIR}/*