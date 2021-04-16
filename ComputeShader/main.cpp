#include<iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>


#include <glew.h>
#include <glfw3.h>


static std::string Parse(const std::string& filepath) {

    std::ifstream stream(filepath);


    std::string line;
    std::stringstream ss;


    while (std::getline(stream, line))
    {
        ss << line << '\n';
    };
    

    return { ss.str() };

}


static unsigned int CompileShader( GLuint type, const std::string& source) {

    GLuint id = glCreateShader(type);
    const char* src = &source[0];
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if(result == GL_FALSE){
        int length;
        glGetShaderiv(id, GL_COMPILE_STATUS, &length);
        char* message = (char*)alloca(length*sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "fail to compile : " << message << source << std::endl;

        glDeleteShader(id);
        return 0;
    }


    return id;
}


float origine[44] = {
    -0.05f,  0.00f,
   -0.04f,  0.03f,
   -0.03f,  0.4f,
   -0.02f,  00.458f,
   -0.01,   0.049f,
    0.00f,  0.05f,
   0.05f,  0.00f,
   0.04f,  0.03f,
   0.03f,  0.04f,
   0.02f,  0.0458f,
   0.01f,   0.049f,
   0.05f, -0.05f,
   -0.04f,  -0.03f,
   -0.03f,  -0.04f,
   -0.02f,  -0.0458f,
   -0.1,   -0.049f,
    0.00f,  -0.05f,
   0.05f,  -0.00f,
   0.04f,  -0.03f,
   0.03f,  -0.04f,
   0.02f,  -0.0458f,
   0.01,   -0.049f
};

float positions[44] = {
   -0.05f,  0.00f,
   -0.04f,  0.03f,
   -0.03f,  0.4f,
   -0.02f,  00.458f,
   -0.01,   0.049f,
    0.00f,  0.05f,
   0.05f,  0.00f,
   0.04f,  0.03f,
   0.03f,  0.04f,
   0.02f,  0.0458f,
   0.01f,   0.049f,
   0.05f, -0.05f,
   -0.04f,  -0.03f,
   -0.03f,  -0.04f,
   -0.02f,  -0.0458f,
   -0.1,   -0.049f,
    0.00f,  -0.05f,
   0.05f,  -0.00f,
   0.04f,  -0.03f,
   0.03f,  -0.04f,
   0.02f,  -0.0458f,
   0.01,   -0.049f
};

float center_click[2]{0.0, 0.0};

bool click = false;


void center(float pos_x, float pos_y, GLuint buff) {
    


    for (int i = 0; i < sizeof(positions); i++) {
        if (i % 2 == 0) {
            positions[i] = origine[i] + pos_x ;
        }
        else
        {
            positions[i] = origine[i] + pos_y;
        };

    };

    glBindBuffer(GL_ARRAY_BUFFER, buff);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
};

static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos) {

    //std::cout << xPos - 320 << " : " << 240 - yPos << std::endl;
    center_click[0] = (xPos - 320) / 320;
    center_click[1] = (240 - yPos) / 240 ;
       

}


void mousClickCallback(GLFWwindow* window, int Button, int action, int mods) {


  
    if (Button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
       
        click = true;
        std::cout << "click is " << click <<  std::endl;

    }

}



int main(void)
{
    GLFWwindow* window;





    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) { std::cout << "error ok" << std::endl; }

    std::cout << glGetString(GL_VERSION) << std::endl;


    /* VERTEX BUFFER */

    static unsigned int gVBO;
    glGenBuffers(1, &gVBO); // create 1 buffer
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);  //// bind the buffer to the active context.
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);  // define mapping in the buffer. "start at index 0, read 2 elements at a time"
    //glEnableVertexAttribArray(0);    


    // center
  
 

    unsigned int centerBuff;
    glGenBuffers(1, &centerBuff); // create 1 buffer
    glBindBuffer(GL_ARRAY_BUFFER, centerBuff);  //// bind the buffer to the active context.
    glBufferData(GL_ARRAY_BUFFER, sizeof(origine), origine, GL_STATIC_DRAW);

    //glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);  // define mapping in the buffer. "start at index 0, read 2 elements at a time"
    //glEnableVertexAttribArray(0);

   

    //ssbo
/*  
    float SSBO[6];

    unsigned int gssbo;
    glGenBuffers(1, &gssbo); // create 1 buffer
    glBindBuffer(GL_ARRAY_BUFFER, gssbo);  //// bind the buffer to the active context.
    glBufferData(GL_ARRAY_BUFFER, sizeof(SSBO), SSBO, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);  // define mapping in the buffer. "start at index 0, read 2 elements at a time"
    glEnableVertexAttribArray(0);*/



    GLuint program = glCreateProgram();

    //std::string vertexShader = Parse("vertex.shader");
    std::string fragmentShader = Parse("fragment.shader");
   // GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

   
    //glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

   // glDeleteShader(vs);
    glDeleteShader(fs);

    glUseProgram(program);


    /// ////////// Compute shader
    std::string computeshader = Parse("compute.shader");
    GLuint cs = CompileShader(GL_COMPUTE_SHADER, computeshader);

    GLuint csprogram = glCreateProgram();

    glAttachShader(csprogram, cs);
    glLinkProgram(csprogram);





    /// mouse inputs.
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetMouseButtonCallback(window, mousClickCallback);


    

    /* Loop until the user closes the window */
   while (!glfwWindowShouldClose(window))
    {   
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

       

        ////////////////////////////////////////////
     
        glUseProgram(csprogram);
  
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, gVBO);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, centerBuff);
        if (click) {

            center(center_click[0], center_click[1], gVBO);
            click = false;

        };
  
        glDispatchCompute(22, 1, 1);


        // Unbind the SSBO buffer.
        // gIndexBufferBinding is equal to 0. This is the same as the compute shader binding.
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, 0);

        glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);

        // Bind the VBO
        glBindBuffer(GL_ARRAY_BUFFER, gVBO);


        // Bind the vertex and fragment rendering shaders
        glUseProgram(program);

    

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);


        //////////////////////////////////////////////
    

        //glDrawArrays(GL_TRIANGLES, 0, 3); // draw a triangle from the active buffer, starting to reas the verteces from indice 0 and read 3 verteces
        glDrawArrays(GL_POINTS, 0, 22);
        glPointSize(5);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

