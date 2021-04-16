
#version 430 core


// The uniform parameters that are passed from application for every frame.
layout(local_size_x = 1024, local_size_y = 1, local_size_z = 1) in;

layout(std430, binding = 0) buffer destBuffer
{
    //AttribData data[];
    vec2 data[];
} outBuffer;

layout(std430, binding = 1) buffer center
{
    //AttribData data[];
    vec2 coord[];
} origine;



void main()
{
    float speed = 0.000008;
   

    uint storePos = gl_LocalInvocationID.x;

    outBuffer.data[storePos] += (speed * outBuffer.data[storePos]) - origine.coord[storePos]/500;
 

    /*if (storePos % 2 == 0) {
        outBuffer.data[storePos] += speed* outBuffer.data[storePos]+ (speed/5);
    }
    else {
        outBuffer.data[storePos] += speed * outBuffer.data[storePos];
    }*/
   

}