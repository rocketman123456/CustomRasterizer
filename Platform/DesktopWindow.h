#pragma once
#include "Platform/WindowInfo.h"

namespace Rocket {
    class DesktopWindow {
    public:
        DesktopWindow() = default;
        ~DesktopWindow() = default;

        int32_t Initialize(const WindowInfo& info);
        void Finalize();
        void Tick(double dt);
        bool GetShouldClose();

        inline void* GetWindowHandle() const { return handle_; }

        // Cannot Copy Window Class
        DesktopWindow(const DesktopWindow& buffer) = delete;
        DesktopWindow(DesktopWindow&& buffer) = delete;
        DesktopWindow& operator = (const DesktopWindow& buffer) = delete;
        DesktopWindow& operator = (DesktopWindow&& buffer) = delete;

    protected:
        WindowInfo info_;
        void* handle_ = nullptr;
    };
}