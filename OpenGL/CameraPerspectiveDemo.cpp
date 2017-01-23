//
//  CameraPerspectiveDemo.cpp
//  OpenGL
//
//  Created by Matt Finucane on 23/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include "CameraPerspectiveDemo.hpp"

using namespace std;

CameraPerspectiveDemo::CameraPerspectiveDemo() {
    cout << "Construct: CameraPerspectiveDemo" << endl;
    meshes = {};
    m = new Matrices();
    shader_loader = new ShaderLoader();
}

CameraPerspectiveDemo::~CameraPerspectiveDemo() {
    delete(m);
    delete(meshes);
}

void CameraPerspectiveDemo::prepare() {
    
    try {
        setupWindow();
        
        string vertex_shader_str = shader_loader->load("camera_perspective_demo.vert");
        string fragment_shader_str = shader_loader->load("camera_perspective_demo.frag");
        
        delete(shader_loader);
        
        GLuint vertex_shader = compileShader(&vertex_shader_str, GL_VERTEX_SHADER);
        GLuint fragment_shader = compileShader(&fragment_shader_str, GL_FRAGMENT_SHADER);
        linkShaders(vertex_shader, fragment_shader);
        gl_params.print_program_info_log(program);
    }
    catch(exception &e) {
        cout << e.what();
    }
}

bool CameraPerspectiveDemo::setupWindow(void) {
    
    if(!glfwInit()) {
        throw runtime_error("Could not initialise the GLFW window.");
        return false;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(1280, 960, "Camera Perspective Demo", NULL, NULL);
    if(!window) {
        glfwTerminate();
        throw runtime_error("GLFW failed to create a window.");
        return false;
    }
    
    glfwMakeContextCurrent(window);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);
    
    return true;
}

GLuint CameraPerspectiveDemo::compileShader(const string *shader_src_str, GLenum type) {
    
    GLuint shader = glCreateShader(type);
    const char *shader_src = shader_src_str->c_str();
    GLint shader_src_len = shader_src_str->length();
    glShaderSource(shader, 1, &shader_src, &shader_src_len);
    glCompileShader(shader);
    
    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(GL_TRUE != status) {
        cout << "Failed to compile the shader with reference: " << shader << endl;
        gl_params.print_shader_log(shader);
        return false;
    }
    
    return shader;
}

void CameraPerspectiveDemo::linkShaders(const GLuint vertex_shader, const GLuint fragment_shader) {
    
    program = glCreateProgram();
    
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    
    int status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if(GL_TRUE != status) {
        cout << "Failed to link the program with reference: " << program << endl;
        gl_params.print_program_info_log(program);
    }
}

void CameraPerspectiveDemo::addMesh(Mesh *mesh, const GLfloat pos_x, const GLfloat pos_y, const GLfloat pos_z) {
    
    /**
     *  The given points for the mesh might need to be 
     *  altered so we can place it relative to the world
     *  origin. We do this here.
     */
    transform(begin(mesh->points), end(mesh->points), begin(mesh->points), [pos_x, pos_y, pos_z] (Point &point) {
        point.x += pos_x;
        point.y += pos_y;
        point.z += pos_z;
        return point;
    });
    
    /**
     *  We need to set up an array of points from the mesh Point structs.
     */
    GLfloat points[mesh->points.size() * 3];
    int size_i = 0;
    for(auto const point: mesh->points) {
        points[++size_i] = point.x;
        points[++size_i] = point.y;
        points[++size_i] = point.z;
    }
    
    /**
     *  We also need to do the same for colours
     */
    GLfloat colours[mesh->colours.size() * 3];
    int size_j = 0;
    for(auto const colour: mesh->colours) {
        colours[++size_j] = colour.r;
        colours[++size_j] = colour.g;
        colours[++size_j] = colour.b;
    }
    
    GLuint points_vbo;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, size_i * sizeof(GLfloat), &points, GL_STATIC_DRAW);
    
    GLuint colours_vbo;
    glGenBuffers(1, &colours_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
    glBufferData(GL_ARRAY_BUFFER, size_j * sizeof(GLfloat), &colours, GL_STATIC_DRAW);
    
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    mesh->vao = vao;
    meshes->push_back(*mesh);
}

void CameraPerspectiveDemo::drawLoop() const {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, 1280, 960);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    int program_ready;
    glGetProgramiv(program, GL_LINK_STATUS, &program_ready);
    
    if(meshes && GL_TRUE == program_ready) {
        for(auto const mesh: *meshes) {
            glBindVertexArray(mesh.vao);
            glDrawArrays(GL_TRIANGLES, 0, mesh.points.size());
        }
    }
    
    glfwSwapBuffers(window);
}

void CameraPerspectiveDemo::applyMatrices(void) const {
    int rot_x_matrix = glGetUniformLocation(program, "rot_x_matrix");
    int rot_y_matrix = glGetUniformLocation(program, "rot_y_matrix");
    int rot_z_matrix = glGetUniformLocation(program, "rot_z_matrix");
    int scale_matrix = glGetUniformLocation(program, "scale_matrix");
    int translate_matrix = glGetUniformLocation(program, "translate_matrix");
    
    if(
       GL_TRUE != rot_x_matrix ||
       GL_TRUE != rot_y_matrix ||
       GL_TRUE != rot_z_matrix ||
       GL_TRUE != scale_matrix ||
       GL_TRUE != translate_matrix
    ) {
        cout << "Matrix transformation could match to uniform locations inside the shaders.";
    }
    else {
        glUniformMatrix4fv(rot_x_matrix, 1, GL_FALSE, m->rotation_x);
        glUniformMatrix4fv(rot_y_matrix, 1, GL_FALSE, m->rotation_y);
        glUniformMatrix4fv(rot_z_matrix, 1, GL_FALSE, m->rotation_z);
        glUniformMatrix4fv(translate_matrix, 1, GL_FALSE, m->translation);
        glUniformMatrix4fv(scale_matrix, 1, GL_FALSE, m->scaling);
    }
}

void CameraPerspectiveDemo::keyActionListener(void) const {}

int CameraPerspectiveDemo::run(void) {
    prepare();
    
    glUseProgram(program);
    
    while(!glfwWindowShouldClose(window)) {
        drawLoop();
    }
    return 0;
}
