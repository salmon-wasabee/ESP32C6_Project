idf_component_register(SRCS ./app_driver.c ./app_main.c ./jarvis_ui.c
                       INCLUDE_DIRS "."
)

# idf_component_register(SRCS ./app_driver.c ./app_main.c ./jarvis_ui.c ./mic_test.c
#                        INCLUDE_DIRS "."
#                        EMBED_FILES "../certs/google_cloud_cert.pem"
# )