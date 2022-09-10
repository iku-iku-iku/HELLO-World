#shader vertex
#version 330 core

struct Light
{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec3 position;
};

struct Material
{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

layout(location = 0) in vec4 vertPos;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 vertNormal;

out vec2 v_TexCoord;

uniform vec4 u_GlobalAmbient;
uniform mat4 u_MVP;
uniform mat4 u_MV;
uniform mat4 u_V;
uniform Light u_Light;
uniform Material u_Material;
uniform sampler2D u_Texture;

out vec3 varyingHalfVector;
out vec3 varyingVertPos;
out vec3 varyingNormal;
out vec3 varyingLightDir;

void main()
{
    varyingVertPos = (u_MV * vertPos).xyz;
    varyingNormal = (u_MV * vec4(vertNormal, 0.f)).xyz;
    vec4 lightPos = u_V * vec4(u_Light.position, 1.f);
    varyingLightDir = lightPos.xyz - varyingVertPos;
    varyingHalfVector = varyingLightDir - varyingVertPos;

    gl_Position = u_MVP * vertPos;
    v_TexCoord = texCoord;
}

#shader fragment
#version 330 core

struct Light
{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec3 position;
};

struct Material
{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

uniform vec4 u_GlobalAmbient;
uniform mat4 u_MVP;
uniform mat4 u_MV;
uniform Light u_Light;
uniform Material u_Material;
uniform sampler2D u_Texture;

in vec3 varyingHalfVector;
in vec3 varyingVertPos;
in vec3 varyingNormal;
in vec3 varyingLightDir;
in vec2 v_TexCoord;

out vec4 fragColor;
void main()
{
    vec3 L = normalize(varyingLightDir);
    vec3 N = normalize(varyingNormal);
    vec3 H = normalize(varyingHalfVector);

    float cosPhi = dot(N, H);
    float cosTheta = dot(N, L);

    vec4 lightAmbient = u_GlobalAmbient + u_Light.ambient;
    vec4 lightDiffuse = u_Light.diffuse * max(cosTheta, 0.f);
    vec4 lightSpecular = u_Light.specular * pow(max(cosPhi, 0.f), u_Material.shininess * 3.f);

    vec4 textureColor = texture(u_Texture, v_TexCoord);
    vec4 lightColor = (lightAmbient * u_Material.ambient + lightDiffuse * u_Material.diffuse + lightSpecular * u_Material.specular);

    fragColor = 0.5f * vec4(lightColor.xyz, 1.f) + 0.5f * textureColor;
}
