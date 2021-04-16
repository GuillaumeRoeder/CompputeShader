#version 430 core



attribute vec2 a_v4Position;
//attribute vec4 a_v4FillColor;
varying vec4 v_v4FillColor;

void main()
{
    v_v4FillColor = a_v4FillColor;
    //v_v4FillColor = vec4(1.0,1.0,0.0,1.0);
    gl_Position = vec4(a_v4Position,0.0,0.0);
}


/*
layout(location = 0) in vec4 position;

void main() {

    gl_Position = position;
}*/