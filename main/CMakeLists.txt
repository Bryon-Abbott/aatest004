idf_component_register(SRCS "aamsg.c" "test003.c" 
                        INCLUDE_DIRS "."
                        REQUIRES aaled json mqtt nvs_flash
    )  