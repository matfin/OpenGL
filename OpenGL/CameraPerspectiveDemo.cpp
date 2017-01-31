//
//  CameraPerspectiveDemo.cpp
//  OpenGL
//
//  Created by Matt Finucane on 23/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include "CameraPerspectiveDemo.hpp"

using namespace std;

#define gl_viewport_w 1280
#define gl_viewport_h 960

CameraPerspectiveDemo::CameraPerspectiveDemo() {
    cout << "Construct: CameraPerspectiveDemo" << endl;
}

CameraPerspectiveDemo::~CameraPerspectiveDemo() {
    cout << "Destruct: CameraPerspectiveDemo" << endl;
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
    glfwWindowHint(GLFW_SAMPLES, 4);
    
    window = glfwCreateWindow(gl_viewport_w, gl_viewport_h, "Camera Perspective Demo", NULL, NULL);
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
    
    mesh.getMatrices()->rotateTo(ROTATE_X, rotation.rx);
    mesh.getMatrices()->rotateTo(ROTATE_Y, rotation.ry);
    mesh.getMatrices()->rotateTo(ROTATE_Z, rotation.rz);
    
    mesh.getMatrices()->translateTo(TRANSLATE_X, position.px);
    mesh.getMatrices()->translateTo(TRANSLATE_Y, position.py);
    mesh.getMatrices()->translateTo(TRANSLATE_Z, position.pz);
    
    meshes.push_back(mesh);
}

/**
 *  The main drawing loop where we go through each mesh
 *  and draw it to the screen.
 */
void CameraPerspectiveDemo::drawLoop() const {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, gl_viewport_w, gl_viewport_h);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    if(GL_TRUE == programReady()) {
        for(auto &mesh: meshes) {
            glBindVertexArray(mesh.getVao());
            
            mesh.getMatrices()->rotate(ROTATE_Z, LEFT);
            
            mesh.applyMatrices(program);
            glDrawArrays(GL_TRIANGLES, 0, mesh.pointsSize());
        }
        
        applyPerspective();
    }
    
    glfwPollEvents();
    glfwSwapBuffers(window);
}

void CameraPerspectiveDemo::keyActionListener(void) const {
    
    if(glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, true);
    }
    
    if(glfwGetKey(window, GLFW_KEY_LEFT)) {
        cam_pos_x -= 0.2f;
    }
    
    if(glfwGetKey(window, GLFW_KEY_RIGHT)) {
        cam_pos_x += 0.2f;
    }
    
    if(glfwGetKey(window, GLFW_KEY_DOWN)) {
        cam_pos_y -= 0.2f;
    }
    
    if(glfwGetKey(window, GLFW_KEY_UP)) {
        cam_pos_y += 0.2f;
    }
    
    if(glfwGetKey(window, GLFW_KEY_W)) {
        cam_pos_z -= 0.25f;
    }
    
    if(glfwGetKey(window, GLFW_KEY_S)) {
        cam_pos_z += 0.25f;
    }
    
    if(glfwGetKey(window, GLFW_KEY_A)) {
        cam_yaw += 1.0f;
    }
    
    if(glfwGetKey(window, GLFW_KEY_D)) {
        cam_yaw -= 1.0f;
    }
    
}

void CameraPerspectiveDemo::applyPerspective() const {
    
    /**
     *  This sets up the Projection Matrix.
     *  
     *  These are part of the mathematical formula 
     *  needed to calculate the correct projection
     *  to make the scene look more realistic. 
     *  
     *  This sets up the camera frustrum, the part of
     *  the scene that the camera covers and is therefore
     *  visible.
     */
    float near = 0.1f;
    float far = 100.0f;
    float aspect = (float)gl_viewport_w / (float)gl_viewport_h;
    float range = tan(fov * 0.5f) * near;
    
    float Sx = (2.0 * near) / (range * aspect + range * aspect);
    float Sy = near / range;
    float Sz = -(far + near) / (far - near);
    float Pz = -(2.0f * far * near) / (far - near);
    
    /**
     *  With the above calculations completed, we can then put 
     *  this projection matrix together.
     */
    Matrix<float> projection_matrix({
        Row<float>({Sx, 0.0f, 0.0f, 0.0f}),
        Row<float>({0.0f, Sy, 0.0f, 0.0f}),
        Row<float>({0.0f, 0.0f, Sz, -1.0f}),
        Row<float>({0.0f, 0.0f, Pz, 0.0f})
    });
    
    /**
     *  This is the camera position which updates 
     *  for each repaint. This is used when we 
     *  calculate the view matrix, which is then 
     *  used to place each mesh on the x, y, z 
     *  access, so we have the impression we are 
     *  'moving' around the world even though the 
     *  camera always remains at the origin (0,0,0).
     */
    float cam_pos[] = {
        cam_pos_x,
        cam_pos_y,
        cam_pos_z
    };
    
    /**
     *  Grab an instance of a Matrix and then apply
     *  the translations we need to it for all axes,
     *  based on the camera position.
     */
    Matrices m;
    
    /**
     *  These three will update the translation matrix,
     *  which we will then use later when we pass them in
     *  to the vertex shader. In there, it will be bound
     *  to the shader variable "view" and multiplied with 
     *  the other items that make up the final value for 
     *  gl_Position.
     */
    m.translateTo(TRANSLATE_X, -cam_pos[0]);
    m.translateTo(TRANSLATE_Y, -cam_pos[1]);
    m.translateTo(TRANSLATE_Z, -cam_pos[2]);
    
    /**
     *  We apply rotation using a float variable called 
     *  cam_yaw and the rotation matrix we get from this 
     *  will be multiplied by the translation matrix above
     *  to give us our final view matrix.
     */
    m.rotateTo(ROTATE_Y, -cam_yaw);
    
    /**
     *  So now we have the translation matrix with our values
     *  plugged in along with the rotation matrix with its 
     *  values plugged in.
     */
    Matrix<float> T = m.translation_matrix();
    Matrix<float> R = m.rotation_y_matrix();
    
    /**
     *  We then multiply them together to get the view matrix.
     */
    Matrix<float> view_matrix = T * R;
    
    /**
     *  We then unwind them from a Matrix to a vector of float values.
     */
    vector<float> view_matrix_unwound = view_matrix.unwind();
    vector<float> projection_matrix_unwound = projection_matrix.unwind();
    
    /**
     *  We need a reference to the "view" and "projection" variables
     *  inside the program. Both of these sit inside the vertex shader.
     */
    GLuint view_loc = glGetUniformLocation(program, "view");
    GLuint projection_loc = glGetUniformLocation(program, "projection");
    
    /**
     *  And we apply our unwound vectors with the &vector[0] which 
     *  means we can pass in a vector this way without needing to 
     *  go to the trouble of converting it to an array of floats.
     */
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, &view_matrix_unwound[0]);
    glUniformMatrix4fv(projection_loc, 1, GL_FALSE, &projection_matrix_unwound[0]);
}

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
        keyActionListener();
    }
    return 0;
}
