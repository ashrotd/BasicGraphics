#version 410

uniform float offset; // Add this line to get the offset uniform variable

mat4 buildRotateZ(float rad)
{ mat4 zrot = mat4(cos(rad), -sin(rad), 0.0, 0.0,
 sin(rad), cos(rad), 0.0, 0.0,
 0.0, 0.0, 1.0, 0.0,
 0.0, 0.0, 0.0, 1.0 );
return zrot;
}

mat4 buildScale(float x, float y, float z)
{ mat4 scale = mat4(x, 0.0, 0.0, 0.0,
 0.0, y, 0.0, 0.0,
 0.0, 0.0, z, 0.0,
 0.0, 0.0, 0.0, 1.0 );
return scale;
}

mat4 buildRotateX(float rad)
{
    mat4 xrot = mat4(
        1.0, 0.0, 0.0, 0.0,
        0.0, cos(rad), -sin(rad), 0.0,
        0.0, sin(rad), cos(rad), 0.0,
        0.0, 0.0, 0.0, 1.0
    );
    return xrot;
}

void main()
{
    // Define the angle of rotation (in radians)
    float angle = offset * 3.14159265359; // Convert offset to radians

    // Get the rotation matrix
    mat4 rotationMatrix = buildRotateZ(angle);

    // Scale it 
    mat4 scale = buildScale(2,2,2);

    // Apply the rotation to the vertices
    if (gl_VertexID == 0)
        gl_Position = rotationMatrix * vec4(0.25, -0.25, 0.0, 1.0)*scale;
    else if (gl_VertexID == 1)
        gl_Position = rotationMatrix * vec4(-0.25, -0.25, 0.0, 1.0)*scale;
    else
        gl_Position = rotationMatrix * vec4(0.25, 0.25, 0.0, 1.0)*scale;
}
