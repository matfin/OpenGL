//
//  CameraPerspectiveDemo.cpp
//  OpenGL
//
//  Created by Matt Finucane on 23/01/2017.
//  Copyright © 2017 Matt Finucane. All rights reserved.
//

#include "CameraPerspectiveDemo.hpp"

using namespace std;
using namespace std::placeholders;

#define gl_viewport_w 1280
#define gl_viewport_h 960

CameraPerspectiveDemo::CameraPerspectiveDemo() {
    cout << "Construct: CameraPerspectiveDemo" << endl;
    
    drawing_method = GL_TRIANGLES;
    
    fov = 67.0f * one_deg_in_rad;
    cam_pitch = 0.0f;
    cam_roll = 0.0f;
    cam_yaw = 0.0f;
    cam_pitch_speed = 2.0f;
    cam_yaw_speed = 2.0f;
    cam_roll_speed = 2.0f;
    
    mouse_distance = 0.0f;
    mouse_angle = 0.0f;
    
    cam_pos.px = 0.0f;
    cam_pos.py = 0.0f;
    cam_pos.pz = 5.0f;
    
    camera_updating = false;
    
    Input::getInstance();
}

CameraPerspectiveDemo::~CameraPerspectiveDemo() {
    cout << "Destruct: CameraPerspectiveDemo" << endl;
    program = 0;
    window = 0;
    meshes.clear();
    glfwTerminate();
}

void CameraPerspectiveDemo::setupCallbacks() {
    Input::getInstance().onMouseDown(std::bind(&CameraPerspectiveDemo::mouseDown, this, _1, _2, _3));
    Input::getInstance().onMouseUp(std::bind(&CameraPerspectiveDemo::mouseUp, this, _1, _2, _3));
    Input::getInstance().onMouseDrag(std::bind(&CameraPerspectiveDemo::mouseDrag, this, _1, _2, _3, _4));
    Input::getInstance().onKeyDown(std::bind(&CameraPerspectiveDemo::keyDown, this, _1, _2, _3, _4));
    Input::getInstance().onKeyStrobe(std::bind(&CameraPerspectiveDemo::keyStrobe, this, _1, _2, _3, _4));
    Input::getInstance().onKeyUp(std::bind(&CameraPerspectiveDemo::keyUp, this, _1, _2, _3, _4));
}

void CameraPerspectiveDemo::mouseDown(int button, int action, int mods) {
    camera_updating = true;
};

void CameraPerspectiveDemo::mouseUp(int button, int action, int mods) {
    camera_updating = false;
    mouse_distance = 0.0f;
    mouse_angle = 0.0f;
    cam_pitch_speed = 2.0f;
    cam_yaw_speed = 2.0f;
    cam_roll_speed = 2.0f;
};

void CameraPerspectiveDemo::mouseMove(float pos_x, float pos_y) {};

void CameraPerspectiveDemo::mouseDrag(float pos_x, float pos_y, float distance, float angle) {
    mouse_distance = distance;
    mouse_angle = angle;
};

void CameraPerspectiveDemo::updateCameraFromMouse(void) {

    /**
     *  We need to get the angle of the mouse
     *  and use this to determine the ratio of
     *  pitch and yaw to be applied when we 
     *  transform the camera.
     */
    float attack = abs(fmod(mouse_angle, 90.0f));
    float r1 = (attack / 90.0f);
    float r2 = 1.0f - r1;
    
    /**
     *  Depending on which quartile of the 2D 
     *  coordinate plane we are in, we should 
     *  adjust the camera to give the appearance
     *  that the shape is moving in the direction
     *  the mouse pointer is at.
     */
    if(mouse_angle >= 0.0f && mouse_angle < 90.0f) {
        cam_pitch_speed = (mouse_distance / 100.0f) * r1;
        cam_yaw_speed = (mouse_distance / 100.0f) * r2;
        cam_pitch -= cam_pitch_speed;
        cam_yaw -= cam_yaw_speed;
    }
    else if(mouse_angle >= 90.0f && mouse_angle < 180.0f) {
        cam_pitch_speed = (mouse_distance / 100.0f) * r2;
        cam_yaw_speed = (mouse_distance / 100.0f) * r1;
        cam_pitch -= cam_pitch_speed;
        cam_yaw += cam_yaw_speed;
    }
    else if(mouse_angle >= -180.0f && mouse_angle < -90.0f) {
        cam_pitch_speed = (mouse_distance / 100.0f) * r2;
        cam_yaw_speed = (mouse_distance / 100.0f) * r1;
        cam_pitch += cam_pitch_speed;
        cam_yaw += cam_yaw_speed;
    }
    else if(mouse_angle >= -90.0f && mouse_angle < 0.0f) {
        cam_pitch_speed = (mouse_distance / 100.0f) * r1;
        cam_yaw_speed = (mouse_distance / 100.0f) * r2;
        cam_pitch += cam_pitch_speed;
        cam_yaw -= cam_yaw_speed;
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
void CameraPerspectiveDemo::drawLoop() {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, gl_viewport_w, gl_viewport_h);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    if(GL_TRUE == GLUtilities::programReady(program)) {
        for(auto &mesh: meshes) {
            glBindVertexArray(mesh.getVao());
            mesh.applyIdentityMatrix(program);
            glDrawArrays(drawing_method, 0, mesh.pointsSize());
        }
    }
    
    glfwPollEvents();
    glfwSwapBuffers(window);
}

void CameraPerspectiveDemo::keyDown(int key, int scancode, int action, int mods) {
    switch(key) {
        case GLFW_KEY_ESCAPE: {
            glfwSetWindowShouldClose(window, true);
            break;
        }
        case GLFW_KEY_1: {
            glfwSetWindowTitle(window, "Rendering: GL_TRIANGLES");
            drawing_method = GL_TRIANGLES;
            break;
        }
        case GLFW_KEY_2: {
            glfwSetWindowTitle(window, "Rendering: GL_LINE_STRIP");
            drawing_method = GL_LINE_STRIP;
            break;
        }
        case GLFW_KEY_3: {
            glfwSetWindowTitle(window, "Rendering: GL_LINE_LOOP");
            drawing_method = GL_LINE_LOOP;
            break;
        }
        case GLFW_KEY_4: {
            glfwSetWindowTitle(window, "Rendering: GL_LINES");
            drawing_method = GL_LINES;
            break;
        }
        case GLFW_KEY_5: {
            glfwSetWindowTitle(window, "Rendering: GL_TRIANGLE_STRIP");
            drawing_method = GL_TRIANGLE_STRIP;
            break;
        }
        case GLFW_KEY_6: {
            glfwSetWindowTitle(window, "Rendering: GL_TRIANGLE_FAN");
            drawing_method = GL_TRIANGLE_FAN;
            break;
        }
        case GLFW_KEY_7: {
            glfwSetWindowTitle(window, "Rendering: GL_POINTS");
            drawing_method = GL_POINTS;
            break;
        }
        case GLFW_KEY_DOWN: {
            cam_pitch -= 10.0f;
            camera_updating = true;
            break;
        }
        case GLFW_KEY_UP: {
            cam_pitch += 10.0f;
            camera_updating = true;
            break;
        }
        case GLFW_KEY_LEFT: {
            cam_yaw += 10.0f;
            camera_updating = true;
            break;
        }
        case GLFW_KEY_RIGHT: {
            cam_yaw -= 10.0f;
            camera_updating = true;
            break;
        }
    }
}

void CameraPerspectiveDemo::keyStrobe(int key, int scancode, int action, int mods) {
    
    camera_updating = true;
    
    switch(key) {
        case GLFW_KEY_DOWN: {
            cam_pitch -= 5.0f;
            camera_updating = true;
            break;
        }
        case GLFW_KEY_UP: {
            cam_pitch += 5.0f;
            camera_updating = true;
            break;
        }
        case GLFW_KEY_LEFT: {
            cam_yaw += 5.0f;
            camera_updating = true;
            break;
        }
        case GLFW_KEY_RIGHT: {
            cam_yaw -= 5.0f;
            camera_updating = true;
            break;
        }
    }
}

void CameraPerspectiveDemo::keyUp(int key, int scancode, int action, int mods) {
    camera_updating = false;
}

void CameraPerspectiveDemo::applyProjectionMatrix() const {
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
    
    float Sx = (2.0f * near) / ((range * aspect) + (range * aspect));
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
     *  We then unwind them from a Matrix to a vector of float values which
     *  we can then send through to the program, targeting the variable
     *  in the compiled shader program "projection" and sending the values through.
     */
    vector<float> projection_matrix_unwound = projection_matrix.unwind();
    GLuint projection_loc = glGetUniformLocation(program, "projection");
    glUniformMatrix4fv(projection_loc, 1, GL_FALSE, &projection_matrix_unwound[0]);
}

void CameraPerspectiveDemo::applyViewMatrix() const {
    /**
     *  The member variable cam_pos updates
     *  for each repaint. This is used when we
     *  calculate the view matrix, which is then
     *  used to place each mesh on the x, y, z
     *  access, so we have the impression we are
     *  'moving' around the world even though the
     *  camera always remains at the origin (0,0,0).
     *
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
    m.translateTo(TRANSLATE_X, -cam_pos.px);
    m.translateTo(TRANSLATE_Y, -cam_pos.py);
    m.translateTo(TRANSLATE_Z, -cam_pos.pz);
    
    /**
     *  We apply rotation using the member float variables
     *  cam_pitch, cam_roll, and cam_yaw and the rotation 
     *  matrix we get from this will be multiplied by the 
     *  translation matrix above
     *  to give us our final view matrix.
     */
    m.rotateTo(ROTATE_X, -cam_pitch);
    m.rotateTo(ROTATE_Y, -cam_yaw);
    m.rotateTo(ROTATE_Z, -cam_roll);
    
    /**
     *  So now we have the translation and rotation matrices 
     *  with our values plugged in along with the rotation 
     *  matrix with its values plugged in.
     */
    Matrix<float> T = m.translation_matrix();
    Matrix<float> Rx = m.rotation_x_matrix();
    Matrix<float> Ry = m.rotation_y_matrix();
    Matrix<float> Rz = m.rotation_z_matrix();
    
    /**
     *  We then multiply these matrices together to get 
     *  the view matrix and then unwind to get a vector
     *  of float values.
     */
    Matrix<float> view_matrix = (Rx * Ry * Rz) * T;
    vector<float> view_matrix_unwound = view_matrix.unwind();
    
    /**
     *  Get the reference to the "view" variable inside the 
     *  compiled program. The "view" variable sits inside the 
     *  vertex shader and is used to calculate the final 
     *  gl_Position for each vertex.
     *
     *  We then pass in the floats to the vertex shader.
     */
    GLuint view_loc = glGetUniformLocation(program, "view");
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, &view_matrix_unwound[0]);
}

int CameraPerspectiveDemo::run(void) {
    
    try {
        /**
         *  Set up the window. We need to call this before doing anything
         *  with preparing VBOs and VAOs or we will get a Thread access exception.
         */
        window = GLUtilities::setupWindow(gl_viewport_w, gl_viewport_h, "Camera Perspective Demo");
        /**
         *  We can then set up some event listeners using the 
         *  Input class.
         *
         *  Mouse and key input that will be routed
         *  to our Input instance. GFLW only accepts
         *  static methods as callbacks. We specify
         *  some static functions which can then get
         *  our instance and call its member variables.
         *
         *  This is a long-winded way to allow us to
         *  call member functions inside this class
         *  from GLFW - using function pointers.
         */
        glfwSetMouseButtonCallback(window, &Input::glfwMouseButtonCallback);
        glfwSetCursorPosCallback(window, &Input::glfwMouseMoveCallback);
        glfwSetKeyCallback(window, &Input::glfwKeyCallback);
        glfwSetCharCallback(window, &Input::glfwKeyCharCallback);
        
        /**
         *  Set up the callbacks
         */
        setupCallbacks();
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
    string vertex_shader_str = ShaderLoader::load("camera_perspective_demo.vert");
    string fragment_shader_str = ShaderLoader::load("camera_perspective_demo.frag");
    
    GLuint vertex_shader = GLUtilities::compileShader(vertex_shader_str, GL_VERTEX_SHADER);
    GLuint fragment_shader = GLUtilities::compileShader(fragment_shader_str, GL_FRAGMENT_SHADER);
    
    program = GLUtilities::linkShaders(vertex_shader, fragment_shader);
    GLParams::print_program_info_log(program);
    
    /**
     *  This is where we tee up the meshes that have been added.
     */
    prepareMeshes();
    
    /**
     *  Then we use the compiled program.
     */
    glUseProgram(program);
    
    /**
     *  Apply perspective, which is something we 
     *  should only need to do once.
     */
    if(GLUtilities::programReady(program)) {
        applyProjectionMatrix();
        applyViewMatrix();
    }
    
    while(!glfwWindowShouldClose(window)) {
        drawLoop();
        if(camera_updating) {
            updateCameraFromMouse();
            applyViewMatrix();
        }
    }
    return 0;
}
