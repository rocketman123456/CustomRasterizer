#pragma once
#include <Eigen/Eigen>

#include <algorithm>
#include <vector>
#include <memory>

namespace Rocket {
    class SoftTexture {
    public:
        SoftTexture(const std::string& path, const std::string& name);
        SoftTexture(const std::string& full_path);
        virtual ~SoftTexture() = default;

        virtual Eigen::Vector4f GetColorRGBA(float u, float v) final;
        virtual Eigen::Vector3f GetColorRGB(float u, float v) final;
        virtual Eigen::Vector4f GetPixelRGBA(int32_t x, int32_t y) final;
        virtual Eigen::Vector3f GetPixelRGB(int32_t x, int32_t y) final;

    public:
        std::vector<Eigen::Vector4f> image_data = {};
        int32_t width = 0;
        int32_t height = 0;
    };

    using SoftTexturePtr = std::shared_ptr<SoftTexture>;
}
