//
//  CameraPerspectiveDemo.hpp
//  OpenGL
//
//  Created by Matt Finucane on 23/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#ifndef CameraPerspectiveDemo_hpp
#define CameraPerspectiveDemo_hpp

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include "ShaderLoader.hpp"
#include "GLParams.hpp"
#include "Matrices.hpp"
#include "Structs.h"
#include "Mesh.hpp"
#include "Input.hpp"

#define one_deg_in_rad (2.0 * M_PI) / 360.0f

class CameraPerspectiveDemo {
private:
    GLuint program;
    GLFWwindow *window;
    GLenum drawing_method;
    
    float fov;
    float cam_t_speed;
    float cam_pitch;
    float cam_roll;
    float cam_yaw;
    float cam_pitch_speed;
    float cam_yaw_speed;
    float cam_roll_speed;
    
    Position cam_pos;
    bool camera_updating;

    std::vector<Mesh> meshes;
    ShaderLoader shader_loader;
    GLParams gl_params;
    
    void prepareMeshes(void);
    bool setupWindow(void);
    GLuint compileShader(const std::string *shader_src_str, GLenum type);
    GLint programReady() const;
    void linkShaders(const GLuint vertex_shader, const GLuint fragment_shader);
    
    void drawLoop() const;
    void keyActionListener(void);
    void applyViewMatrix() const;
    void applyProjectionMatrix() const;
    
//    static void mousePositionCallback(GLFWwindow *window, double x_pos, double y_pos);
//    static void mouseDownCallback(GLFWwindow *window, int button, int action, int mods);
    
public:
    CameraPerspectiveDemo();
    ~CameraPerspectiveDemo();
    void addMesh(Mesh mesh, const Position position, const Rotation rotation);
    int run(void);
    
    void mouseButtonCallback(int x);
};

#endif /* CameraPerspectiveDemo_hpp */
