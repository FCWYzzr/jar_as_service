//
// Created by MuXin on 2025/12/5.
//
// ReSharper disable CppDeprecatedEntity
module;
#include <Windows.h>

module app;
import f;
import std;
import f.win32;

namespace jas {

file_not_found::file_not_found(
    const std::filesystem::path& file):
    std::runtime_error{(file.string() + " 文件未找到").c_str()},
    file{file} {}

java_home_not_found::java_home_not_found():
    std::runtime_error{"未找到JAVA_HOME环境变量"} {}


auto jar_service(const HINSTANCE hInstance, const std::filesystem::path& jar_file) -> void {
    if (!std::filesystem::exists(jar_file))
        throw file_not_found{jar_file};

    auto window = f::win32::window{hInstance, "Jar Service"};
    const auto tray_name = f::format("点击终止{}", jar_file.filename().string());
    auto tray = f::win32::tray{
        std::string_view{tray_name},
        WM_USER, LoadIconA(nullptr, IDI_APPLICATION),
        0, 7, &window
    };


    auto length = std::size_t{};
    wchar_t cmd[MAX_PATH] = {};
    _wgetenv_s(&length, cmd, MAX_PATH, L"JAVA_HOME");
    std::ranges::copy(L"\\bin\\java.exe -jar ", cmd + length - 1);
    std::wcscpy(cmd + std::wcslen(cmd), jar_file.c_str());
    auto process = f::win32::process{cmd, jar_file.c_str()};
    auto stop = std::atomic_bool{false};

    auto thread = std::jthread{[&] {
        process.join();
        stop = true;
    }};

    window.on(WM_USER, [&process](const f::win32::window* wnd, WPARAM, const LPARAM lp) -> LRESULT {
        if (LOWORD(lp) == WM_LBUTTONDOWN) {
            process.terminate();
            DestroyWindow(wnd->handle());
        }
        return S_OK;
    });

    window.on(WM_DESTROY, [](f::win32::window*, WPARAM, const LPARAM) -> LRESULT {
        PostQuitMessage(0);
        return S_OK;
    });

    while (window.try_consume_message())
        if (stop)
            window.destroy();


}

}