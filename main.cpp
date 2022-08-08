#include "renderer.h"

#include "Geometry/Sphere.h"

#include <thread>

using namespace Rocket;

void setup_rasterizer(SoftRasterizer& rst) {
    rst.ClearAll(BufferType::COLOR | BufferType::DEPTH);

    VertexShaderFunc vertex_shader = ::vertex_shader;
    FragmentShaderFunc fragment_shader = ::normal_fragment_shader;
    rst.SetVertexShader(vertex_shader);
    rst.SetFragmentShader(fragment_shader);

    //rst.DisableWireFrame();
    //rst.EnableWireFrame();
    rst.EnableShader();
    //rst.EnableMsaa();
    //rst.SetMsaaLevel(2);
    //rst.SetClearColor({0.2f, 0.3f, 0.3f});
    rst.SetClearColor({0.0f, 0.0f, 0.0f});
}

void draw_scene(SoftRasterizer& rst, RenderApp& app, std::vector<SoftTrianglePtr>& triangle_list) {
    Eigen::Vector3f eye_pos = {0.0, 0.0, 5};

    int32_t frame_count = 0;
    while(!app.ShouldClose()) {
        rst.NextFrame();
        if(global_change) {
            global_change = false;
            rst.SetCurrentFinish(false);
            rst.SetLastFinish(false);
        }
        if(!rst.IsCurrentFinish()) {
            rst.Clear(BufferType::COLOR | BufferType::DEPTH);
            rst.SetModel(get_model_matrix(global_angle_x, global_angle_y, global_angle_z));
            rst.SetView(get_view_matrix(eye_pos));
            rst.SetProjection(get_perspective_matrix(45, ((float)rst.GetWidth()/(float)rst.GetHeight()), 0.1, 50));
            //rst.SetProjection(get_orthographic_matrix(-6.4, 6.4, -50, 50, 3.6, -3.6));

            rst.Draw(triangle_list);

            frame_count++;
            RK_TRACE(App, "Frame Count: {}", frame_count);
        }
    }
}

int main(int argv, char** argc) {
    RenderApp app;
    app.Initialize(1280, 720);

    int32_t width = 1280;
    int32_t height = 720;
    int32_t nrChannels = 4;

    SoftRasterizer rst(width, height);
    setup_rasterizer(rst);

    Geometry::Sphere sphere(Eigen::Vector3d::Zero(), 1.0);
    sphere.GenerateIcosahedronMesh(2);
    //sphere.GenerateUVMesh(10, 12);
    
    auto& mesh = sphere.mesh;
    std::vector<SoftTrianglePtr> triangle_list;
    for(auto face : mesh) {
        SoftTrianglePtr t = std::make_shared<SoftTriangle>(face);
        triangle_list.push_back(t);
    }

    std::thread render(draw_scene, std::ref(rst), std::ref(app), std::ref(triangle_list));

    while(!app.ShouldClose()) {
        app.Tick();
        auto data = rst.FrameBuffer().data();
        app.Render(data);
    }

    render.join();

    app.Finalize();

    return 0;
}
