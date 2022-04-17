
IF(AA_CMAKE_DEBUG)
    MESSAGE(STATUS "================================" )
    MESSAGE(STATUS "main Directory ...: " )
ENDIF() 


set(srcs "aamsg.c" "test004.c" 
            "../aaproto-c/commandmessage.pb-c.c"
            "../aaproto-c/responsemessage.pb-c.c"
        )

idf_component_register(SRCS "${srcs}"
                        INCLUDE_DIRS "."
                        PRIV_INCLUDE_DIRS . ../aaproto-c     
                        REQUIRES aaled json mqtt nvs_flash protobuf-c
    )  

IF(AA_CMAKE_DEBUG)
    MESSAGE(STATUS "================================" )
ENDIF() 
