#version 330

layout (location=0) in vec3 v_position;
layout (location=1) in vec3 v_normal;
layout (location=2) in vec3 v_textCoord;
layout (location=3) in vec3 v_color;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform float time;

out vec3 frag_color;
out vec3 frag_textCoord;
out vec3 frag_normal;
out vec3 frag_position;

float rand(vec3 position) {
    return fract(33 * sin(position.x + position.y + position.z) * cos(position.x + position.y + position.z));
}
void main()
{
    frag_color = v_color;
    frag_textCoord = v_textCoord;
    frag_normal = v_normal;
    frag_position = v_position;
    float aux = rand(v_position);
    vec3 pos = v_position + v_position * aux * abs(sin(time * (v_position.x + v_position.z)));
    gl_Position = Projection * View * Model * vec4(pos, 1.0);
}
