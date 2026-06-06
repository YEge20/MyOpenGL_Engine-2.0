#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texcoord;
layout(location = 3) in float top_button;

uniform mat4 u_MVP;
uniform mat4 u_wave;
uniform float u_wave_option;

out float v_wave_option;
out vec2 v_texcood;
void main()
{
    if(u_wave_option == 1.0)
    {
        if(top_button == 1.0)
            {
                gl_Position = u_MVP * u_wave * position;
                v_texcood = texcoord;
            }
        else
            gl_Position = u_MVP * position;
    }
    else
        gl_Position = u_MVP * position;
    v_wave_option = u_wave_option;

};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform sampler2D u_texture_test;

in float v_wave_option;
in vec2 v_texcood;
void main()
{   
    if(v_wave_option == 1.0)
        {
            vec4 texture_test_alpha = texture(u_texture_test , v_texcood);
            if(texture_test_alpha.a < 0.1)
                discard;
        }
};