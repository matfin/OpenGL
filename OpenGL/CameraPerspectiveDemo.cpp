//
//  CameraPerspectiveDemo.cpp
//  OpenGL
//
//  Created by Matt Finucane on 23/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include "CameraPerspectiveDemo.hpp"

using namespace std;

int Matrices::objectCount = 0;

CameraPerspectiveDemo::CameraPerspectiveDemo() {
    cout << "Construct: CameraPerspectiveDemo" << endl;
}

CameraPerspectiveDemo::~CameraPerspectiveDemo() {
    cout << "Destruct: CameraPerspectiveDemo" << endl;
    cout << "We had: " << Matrices::getObjectCount() << " Matrices objects." << endl;
    program = 0;
    window = 0;
    meshes.clear();
    glfwTerminate();
}

/**
 *  This is where we need to set the window up
 *  and tee up GLFW. We need to do this first
 *  before we do anything else.
 */
bool CameraPerspectiveDemo::setupWindow(void) {
    
    if(!glfwInit()) {
        throw runtime_error("Could not initialise the GLFW window.");
        return false;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(1024, 1024, "Camera Perspective Demo", NULL, NULL);
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

/**
 *  This function will compile a shader (vertex/fragment) and 
 *  return the reference as a GLuint, so it can be attached 
 *  to a program for linking.
 */
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

/**
 *  Checks to see if the program is ready by 
 *  checking its GL_LINK_STATUS
 */
GLint CameraPerspectiveDemo::programReady() const {
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    return status;
}

/**
 *  This takes in the reference to two shaders that have been compiled and 
 *  returns a reference to the linked program.
 */
void CameraPerspectiveDemo::linkShaders(const GLuint vertex_shader, const GLuint fragment_shader) {
    
    program = glCreateProgram();
    
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    
    if(GL_TRUE != programReady()) {
        cout << "Failed to link the program with reference: " << program << endl;
        gl_params.print_program_info_log(program);
    }
}

/**
 *  This prepares the VBOs and VAO for a mesh. It takes care of 
 *  buffering so we can use them later on in the drawing loop.
 *
 *  A Mesh in this case is a struct that stores its own GLfloats 
 *  for points and colours, along with a reference to a VAO we 
 *  set down here. 
 *  
 *  In the drawing loop we need points and a reference to this VAO.
 */
void CameraPerspectiveDemo::prepareMeshes(void) {
    for(auto &mesh: meshes) {
        /**
         *  Grab the points and colours.
         */
        vector<GLfloat> points = mesh.pointsUnwound();
        vector<GLfloat> colours = mesh.coloursUnwound();
        
        /**
         *  Tee uo the VBOs.
         */
        GLuint points_vbo;
        glGenBuffers(1, &points_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(GLfloat), &points[0], GL_STATIC_DRAW);
        
        GLuint colours_vbo;
        glGenBuffers(1, &colours_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
        glBufferData(GL_ARRAY_BUFFER, colours.size() * sizeof(GLfloat), &colours[0], GL_STATIC_DRAW);
        
        /**
         *  Tee up the VAO.
         */
        GLuint vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        /**
         *  The set up the vertex attrib pointers.
         */
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        
        /**
         *  Then assign the mesh a reference to its VAO.
         */
        mesh.setVao(vao);
    }
}

/**
 *  Called from another function, the first thing we need to do is 
 *  add some meshes that we can later prepare.
 */
void CameraPerspectiveDemo::addMesh(Mesh mesh, const Position position, const Rotation rotation) {
    
    /**
     *  Since the mesh might be a little big,
     *  we should scale it down.
     *  We should then use matrix translation
     *  to place it where we want it to go.
     */
    mesh.getMatrices()->scaleTo(0.2f);
    
    mesh.getMatrices()->translateXTo(position.px);
    mesh.getMatrices()->translateYTo(position.py);
    mesh.getMatrices()->translateZTo(position.pz);
    
    mesh.getMatrices()->rotateXTo(rotation.rx);
    mesh.getMatrices()->rotateYTo(rotation.ry);
    mesh.getMatrices()->rotateZTo(rotation.rz);
    
    meshes.push_back(mesh);
    
    Position difference = mesh.originDifference();
    
    cout << "Mesh added with dx: " << difference.px << ", dy: " << difference.py << ", dz: " << difference.pz << endl;
}

/**
 *  The main drawing loop where we go through each mesh
 *  and draw it to the screen.
 */
void CameraPerspectiveDemo::drawLoop() const {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, 1024, 1024);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    if(GL_TRUE == programReady()) {
        for(auto &mesh: meshes) {
            {
                auto i = &mesh - &meshes[0];
                Matrices *m = mesh.getMatrices();
                if(!i || !i % 2) {
                    m->rotateZ(RIGHT);
                }
                else {
                    m->rotateX(UP);
                }
            }
            
            glBindVertexArray(mesh.getVao());
            mesh.applyMatrices(program);
            glDrawArrays(GL_TRIANGLES, 0, mesh.pointsSize());
        }
    }
    
    glfwPollEvents();
    glfwSwapBuffers(window);
}

void CameraPerspectiveDemo::keyActionListener(void) const {}

int CameraPerspectiveDemo::run(void) {
    
    try {
        /**
         *  Set up the window. We need to call this before doing anything
         *  with preparing VBOs and VAOs or we will get a Thread access exception.
         */
        setupWindow();
    }
    catch(exception &e) {
        cout << e.what();
        return -1;
    }
    
    /**
     *  We then need to grab the vertex and fragment shaders, compile
     *  both of them and then link them to form a program. We then
     *  print the program status.
     */
    string vertex_shader_str = shader_loader.load("camera_perspective_demo.vert");
    string fragment_shader_str = shader_loader.load("camera_perspective_demo.frag");
    GLuint vertex_shader = compileShader(&vertex_shader_str, GL_VERTEX_SHADER);
    GLuint fragment_shader = compileShader(&fragment_shader_str, GL_FRAGMENT_SHADER);
    linkShaders(vertex_shader, fragment_shader);
    gl_params.print_program_info_log(program);
    
    /**
     *  This is where we tee up the meshes that have been added.
     */
    prepareMeshes();
    
    /**
     *  Then we use the compiled program.
     */
    glUseProgram(program);
    
    while(!glfwWindowShouldClose(window)) {
        drawLoop();
    }
    return 0;
}
