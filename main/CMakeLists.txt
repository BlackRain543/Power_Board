idf_component_register(
    SRCS            "main.c" "freertos_tasks.c" "hal_init.c" "hal_func.c" "hal_wifi.c"
    INCLUDE_DIRS    "." "TonePlayer")

target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")


# include_directories(TonePlayer)