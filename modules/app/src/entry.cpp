//
// Created by MuXin on 2025/12/5.
//
#include <clocale>
#include <Windows.h>
import std;
import app;
import f;

int WINAPI wWinMain(const HINSTANCE hInstance, HINSTANCE, LPWSTR, int)
    try {
        std::setlocale(LC_ALL, "en_US.utf8");
        auto range = std::filesystem::directory_iterator{"./"}
            | f::filter([](const auto& e){ return e.path().extension() == ".jar";});

        const auto it = std::ranges::begin(range);
        if (it == std::end(range))
            throw f::exception("未找到jar文件");
        auto&& file = it->path();

        jas::jar_service(hInstance, file);
        return 0;
    }
    catch (const std::exception& e) {
        auto err = f::wstring{};
        f::cvt(e.what(), err);

        MessageBoxW(nullptr,
                   err.c_str(),
                   L"Error", MB_OK | MB_ICONERROR);
        return 1;
    }
