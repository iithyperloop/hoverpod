#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED


    //inline funciton bodies in the header file??

class GUI{

    public:

        //init funtions (main??)
        int init_gui();

        //glfw_error_callback inline function
        static void glfw_error_callback(int error, const char* description);
        
        //LoadTectureFromFile inline Function
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

        //AddUnderLine inline Function
        inline void AddUnderLine(const ImColor col_)
        {
            ImVec2 min = ImGui::GetItemRectMin();
            const ImVec2 max = ImGui::GetItemRectMax();
            min.y = max.y;
            ImGui::GetWindowDrawList()->AddLine(min, max, col_, 1.0f);
        }

        //operator+ inline function
        static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs)
        {
            return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y);
        }

        //AddUnderLine inline function
        inline void AddUnderLine(const ImColor col_)
        {
            ImVec2 min = ImGui::GetItemRectMin();
            const ImVec2 max = ImGui::GetItemRectMax();
            min.y = max.y;
            ImGui::GetWindowDrawList()->AddLine(min, max, col_, 1.0f);
        }
        //ImVec2 inline function
        static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs)
        {
        return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y);
        }

        void ImageRotatedRel(ImTextureID tex_id, ImVec2 center, ImVec2 size, float angle);

    }
#endif GUI_H_INCLUDED




