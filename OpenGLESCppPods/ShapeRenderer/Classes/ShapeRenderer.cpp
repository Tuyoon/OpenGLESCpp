//
//  ShapeRenderer.cpp
//  OpenGLESCpp
//
//  Created by Admin on 20.11.2024.
//

#define GLES_SILENCE_DEPRECATION

#include "ShapeRenderer.hpp"
#include <OpenGLES/ES3/gl.h>
#include <cmath>

/// Vertex shader source.
const char* vertexShaderSource = R"(
    attribute vec3 position;
    uniform mat4 transform;
    void main() {
        gl_Position = transform * vec4(position, 1.0);
    }
)";

/// Filling  shader source. Default iOS tint color.
const char* fillingShaderSource = R"(
    void main() {
        gl_FragColor = vec4(52.0/255.0, 120.0/255.0, 246.0/255.0, 1.0);
    }
)";

/// Shader program.
GLuint shaderProgram;
/// Vertex array.
GLuint vertexArray;
/// Location.
GLuint location;

/// Create shader program.
GLuint createShaderProgram() {
    // Prepare vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // Prepare fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fillingShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // Create program with vertex and fragment shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    return shaderProgram;
}

/// Configure shape renderer.
void ShapeRenderer::setup() {
    
    // Calculate triangle verticles with center in (0, 0) and side length 1
    float sideLength = 1.0f;
    float height = sqrt(sideLength * sideLength - (sideLength/2.0 * sideLength/2.0));
    float centerY = sideLength * sqrt(3.0)/6.0;
    GLfloat triangleVertices[] = {
        0.0f,           height - centerY,   0.0f,
        -sideLength/2,  -centerY,           0.0f,
        sideLength/2,   -centerY,           0.0f,
    };
    
    // Create vertex array and buffer objects
    GLuint vertexBuffers;
    glGenVertexArrays(1, &vertexArray);
    glGenBuffers(1, &vertexBuffers);
    
    glBindVertexArray(vertexArray);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
    
    // Create shader program
    shaderProgram = createShaderProgram();
    
    // Configure position
    GLint positionAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(positionAttrib);
    glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    // Get transform for rotation
    location = glGetUniformLocation(shaderProgram, "transform");
    
    glDisableVertexAttribArray(positionAttrib);
}

/// Draw shape with specified size.
void ShapeRenderer::draw(float width, float height) {
    // Clear.
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Apply shader program
    glUseProgram(shaderProgram);
    
    // Calculate rotation angle in radians
    float radians = rotationAngle * M_PI / 180.0f;
    // Calculate view scale
    float scale = width / height;
    // Create transformation matrix(rotation + scale)
    GLfloat transform[] = {
        cos(radians),   -sin(radians) * scale,  0.0f,   0.0f,
        sin(radians),   cos(radians) * scale,   0.0f,   0.0f,
        0.0f,           0.0f,                   1.0f,   0.0f,
        0.0f,           0.0f,                   0.0f,   1.0f
    };
    
    // Apply transformation matrix
    glUniformMatrix4fv(location, 1, GL_FALSE, transform);
    
    // Draw triangle
    glBindVertexArray(vertexArray);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

/// Rotate shape with specified angle.
void ShapeRenderer::rotate(float angle) {
    rotationAngle = angle;
}
