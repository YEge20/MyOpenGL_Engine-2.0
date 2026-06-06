#shader vertex
#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 u_MVP;
uniform mat4 u_Rota;

out vec2 v_uv;
out vec3 v_fragPos;
out vec3 v_Normal;

void main()
{
    gl_Position = u_MVP * vec4(position, 1.0);
    v_uv = uv;
    v_fragPos = vec3(u_Rota * vec4(position, 1.0));
    v_Normal = normalize(vec3(u_Rota * vec4(normal, 1.0)));
}

#shader fragment
#version 460 core

layout(location = 0) out vec4 color;

in vec2 v_uv;
in vec3 v_fragPos;
in vec3 v_Normal;

uniform vec3 u_CamPos;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

uniform sampler2D extra_roughness;

vec3 CalcPointLight(vec3 light, vec3 normal, vec3 fragPos, vec2 UV)
{
    vec3 lightDir = normalize(light - fragPos);
    vec3 viewDir = normalize(u_CamPos - fragPos);

    float environment = 0.1;
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);

    float dist = length(light - fragPos);
    float attenuation = 1.0 / (1.0 + 0.25 * dist);

    vec4 roughtness = texture(extra_roughness, UV);

    vec3 source1 = environment * vec3(texture(texture_diffuse1, UV));
    vec3 source2 = diff * attenuation * vec3(texture(texture_diffuse1, UV));
    vec3 source3 = spec * vec3(texture(texture_specular1, UV) * roughtness);

    return (source1 + source2 + source3);
}

void main()
{
    vec3 LightPos[8];
    LightPos[0] = vec3(-5.0,-5.0, 5.0);
    LightPos[1] = vec3( 5.0,-5.0, 5.0);
    LightPos[2] = vec3(-5.0, 5.0, 5.0);
    LightPos[3] = vec3( 5.0, 5.0, 5.0);
    LightPos[4] = vec3(-5.0,-5.0,-5.0);
    LightPos[5] = vec3( 5.0, 5.0,-5.0);
    LightPos[6] = vec3( 5.0,-5.0,-5.0);
    LightPos[7] = vec3(-5.0, 5.0,-5.0);

    vec3 result;
    for(int i = 0; i < 8; i++)
        result += CalcPointLight(LightPos[i], v_Normal, v_fragPos, v_uv);
    
    color = vec4(result, 1.0);
}