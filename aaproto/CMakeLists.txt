cmake_minimum_required(VERSION 3.5)
IF(AA_CMAKE_DEBUG)
    MESSAGE(STATUS "=========== AAPROTO START =====================" )
    MESSAGE(STATUS "aaproto Directory ...: " )
    MESSAGE(STATUS "CMake Current Binary Dir: " ${CMAKE_CURRENT_BINARY_DIR})
    MESSAGE(STATUS "CMake Current Make List Dir: " ${CMAKE_CURRENT_LIST_DIR})
ENDIF() 

set(PROTO_COMPILER "protoc")
set(PROTO_C_COMPILER "protoc-c")
#set(C_OUT_PATH "${CMAKE_CURRENT_LIST_DIR}/../aaproto-c")
set(C_OUT_PATH "${CMAKE_CURRENT_LIST_DIR}/../aaproto-c")
#set(PROTO_INCL_PATH "${CMAKE_CURRENT_LIST_DIR}/../../aaproto/proto")
set(PROTO_SRC_PATH "${CMAKE_CURRENT_BINARY_DIR}/aaproto/proto-c")
set(PROTO_INCL_PATH "/usr/local/include")

IF(AA_CMAKE_DEBUG)
    MESSAGE(STATUS "Proto Include Path: " ${PROTO_INCL_PATH})
    MESSAGE(STATUS "Proto C Out Path: " ${C_OUT_PATH})

ENDIF() 


set(PROTO_SRCS "commandmessage.proto"
               "responsemessage.proto")

add_custom_target(c_proto
    COMMAND ${PROTO_C_COMPILER} --c_out=${C_OUT_PATH} -I${PROTO_INCL_PATH} -I${CMAKE_CURRENT_LIST_DIR} ${PROTO_SRCS}
    VERBATIM
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    )

add_custom_target(proto ALL
    DEPENDS c_proto
    VERBATIM
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    )

# PROTO Include path required for google includes
EXEC_PROGRAM(${PROTO_C_COMPILER} ARGS --c_out ${C_OUT_PATH} -I${PROTO_INCL_PATH} -I${CMAKE_CURRENT_LIST_DIR}  ${PROTO_SRCS})

IF(AA_CMAKE_DEBUG)
    MESSAGE(STATUS "=========== AAPROTO END =====================" )
ENDIF() 
