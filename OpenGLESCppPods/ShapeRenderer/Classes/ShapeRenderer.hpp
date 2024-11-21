//
//  ShapeRenderer.hpp
//  OpenGLESCpp
//
//  Created by Admin on 20.11.2024.
//

#ifndef ShapeRenderer_hpp
#define ShapeRenderer_hpp

#include <stdio.h>

/// Shape renderer.
class ShapeRenderer {
private:
    /// Rotation angle.
    float rotationAngle;
public:
    /// Configure shape renderer.
    void setup();
    /// Draw shape with specified size.
    void draw(float width, float height);
    /// Rotate shape with specified angle.
    void rotate(float angle);
};

#endif /* ShapeRenderer_hpp */
