#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "imgui_internal.h"

//variables
constexpr int width = 800;
constexpr int height = 480;

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

inline bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
{
    // Load from file
    int image_width = 0;
    int image_height = 0;
    
    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, nullptr, 4);
    if (image_data == nullptr)
        return false;

    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); // Same

    // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;

    return true;
}

inline void AddUnderLine(const ImColor col_)
{
    ImVec2 min = ImGui::GetItemRectMin();
    const ImVec2 max = ImGui::GetItemRectMax();
    min.y = max.y;
    ImGui::GetWindowDrawList()->AddLine(min, max, col_, 1.0f);
}


static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs)
{
    return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y);
}


void ImageRotatedRel(ImTextureID tex_id, ImVec2 center, ImVec2 size, float angle)
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    ImVec2 vMin = ImGui::GetWindowContentRegionMin();
    ImVec2 vMax = ImGui::GetWindowContentRegionMax();

    center.x += ImGui::GetWindowPos().x;
    center.y += ImGui::GetWindowPos().y;

    const float cos_a = cosf(angle);
    const float sin_a = sinf(angle);
    const ImVec2 pos[4] =
    {
        center + ImRotate(ImVec2(-size.x * 0.5f, -size.y * 0.5f), cos_a, sin_a),
        center + ImRotate(ImVec2(+size.x * 0.5f, -size.y * 0.5f), cos_a, sin_a),
        center + ImRotate(ImVec2(+size.x * 0.5f, +size.y * 0.5f), cos_a, sin_a),
        center + ImRotate(ImVec2(-size.x * 0.5f, +size.y * 0.5f), cos_a, sin_a)
    };
    const ImVec2 uvs[4] =
    {
        ImVec2(0.0f, 0.0f),
        ImVec2(1.0f, 0.0f),
        ImVec2(1.0f, 1.0f),
        ImVec2(0.0f, 1.0f)
    };

    draw_list->AddImageQuad(tex_id, pos[0], pos[1], pos[2], pos[3], uvs[0], uvs[1], uvs[2], uvs[3], IM_COL32_WHITE);
}


int init_gui()
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
    //GLFWwindow* window = glfwCreateWindow(width, height, "Hyperloop Hoverpod", glfwGetPrimaryMonitor(), nullptr);
    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Hyperloop Hoverpod", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    const auto large_font = io.Fonts->AddFontFromFileTTF("resources/OpenSans-Medium.ttf", 60.0f);
    const auto medium_font = io.Fonts->AddFontFromFileTTF("resources/OpenSans-Medium.ttf", 40.0f);

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    bool show_speedometer_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0, 0, 0, 1.00f);

    int out_width, out_height;

    GLuint logo_texture = 0;
    LoadTextureFromFile("resources/logo.png", &logo_texture, &out_width, &out_height);

    GLuint battery_texture = 0;
    LoadTextureFromFile("resources/battery.png", &battery_texture, &out_width, &out_height);

    GLuint arrow_texture = 0;
    LoadTextureFromFile("resources/arrow.png", &arrow_texture, &out_width, &out_height);

    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    //window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoScrollbar;
    window_flags |= ImGuiWindowFlags_NoTitleBar;
    window_flags |= ImGuiWindowFlags_NoDecoration;

    ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_Always); // make maximized
    ImGui::SetNextWindowPos(ImVec2(1920/2, 1080/2), ImGuiCond_Always); // set to top left
    static bool is_start_menu_open;
    bool next_menu = false;
	std::array<char, 20> battery_str {};

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (!next_menu)
        {
            ImGui::Begin("Hoverpod", &is_start_menu_open, window_flags);
            ImGui::Image(reinterpret_cast<ImTextureID>(logo_texture), ImVec2(width, height - 80));
            next_menu = ImGui::Button("Begin", ImVec2(width - 15, 65));
            ImGui::End();
        } else {
            ImGui::Begin("Hoverpod", &is_start_menu_open, window_flags);

        	static int battery_percent = 100;
            static float accel_percent = 100;
            sprintf(battery_str.data(), "%d%%", battery_percent);
            if (battery_percent >= 75)
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 255, 0)));
            else if (battery_percent <= 75 && battery_percent >= 50)
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(240, 210, 50)));
            else if (battery_percent <= 50 && battery_percent >= 25)
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(255, 100, 0)));
            else
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(255, 0, 0)));
            ImGui::Button(battery_str.data(), ImVec2(200, 65));
            ImGui::SameLine(0);
            ImGui::SetCursorPos(ImVec2(200, 30));
            ImGui::Button("##", ImVec2(15, 20));
            ImGui::PopStyleColor();
            ImGui::PushFont(medium_font);
            ImGui::NewLine();
            ImGui::Text("Battery Current: %dA", 100);
            AddUnderLine(ImColor(255, 255, 255));
            ImGui::NewLine();
            ImGui::Text("Battery Voltage: %.1fV", 5.1);
            AddUnderLine(ImColor(255, 255, 255));
            if (accel_percent > 0) {
                ImageRotatedRel(reinterpret_cast<ImTextureID>(arrow_texture), ImVec2(600, 200), ImVec2(75, accel_percent * 3), 0);
            } else
            {
                ImageRotatedRel(reinterpret_cast<ImTextureID>(arrow_texture), ImVec2(600, 200), ImVec2(75, accel_percent * 3), 2 * 3.14);
            }
            ImGui::NewLine();
            ImGui::Text("Battery Temperature: %.1fC", 21.5);
            AddUnderLine(ImColor(255, 255, 255));
            ImGui::NewLine();
            ImGui::SliderInt("Battery %", &battery_percent, 0, 100);
            ImGui::NewLine();
            ImGui::SliderFloat("Acceleration %", &accel_percent, -100, 100);
            ImGui::PopFont();

            ImGui::End();
        }

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
