file(GLOB_RECURSE app_sources "app/src/*.c")
file(GLOB_RECURSE bsp_sources "bsp/src/*.c")
file(GLOB_RECURSE service_sources "service/src/*.c")

idf_component_register(SRCS "main.c"
                         ${app_sources}
                         ${bsp_sources}
                         ${service_sources}
                    INCLUDE_DIRS "."
                                 "app/include"
                                 "bsp/include"
                                 "service/include"
                    REQUIRES unity driver esp_lcd espressif__esp_lvgl_port spiffs)

# 添加此注释以尝试强制重新配置