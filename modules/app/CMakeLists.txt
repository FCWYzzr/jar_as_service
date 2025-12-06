add_executable(JarAsService WIN32)
configure_target(JarAsService)
target_sources(JarAsService PRIVATE
    src/app.rc
    src/icon.ico)

# 添加对f和f.win32模块的依赖
target_link_libraries(JarAsService PRIVATE f f.win32)

install(TARGETS JarAsService
    RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/dist/)