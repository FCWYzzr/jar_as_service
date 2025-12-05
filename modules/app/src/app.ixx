//
// Created by MuXin on 2025/12/5.
//
module;
#include <Windows.h>
export module app;
import std;

export namespace jas {

struct file_not_found: std::runtime_error {
    explicit
    file_not_found(const std::filesystem::path& file);

    std::filesystem::path
        file;
};

struct java_home_not_found: std::runtime_error {
    explicit
    java_home_not_found();
};

void jar_service(HINSTANCE hInstance, const std::filesystem::path& jar_file);

}
