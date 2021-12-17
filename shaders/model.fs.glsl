#version 330 core

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 TexCoords;

out vec3 FragColor;

uniform sampler2D texture_diffuse1;
uniform vec3 uCameraPos;
uniform vec4 uColor;
uniform vec3 uRodPos;
uniform bool uCameraLight;
uniform bool uRodLight;
uniform bool uRoomLights;

vec3 blinnPhong(vec3 uLightPos_vs)
{
    vec3 uLightIntensity = vec3(10.,10.,10.);
    vec3 w0 = normalize(-vPosition_vs);
    vec3 N = normalize(vNormal_vs);
    vec3 wi = normalize(uLightPos_vs - vPosition_vs);
    float d = distance(vPosition_vs,uLightPos_vs);
    return (uLightIntensity/(d*d)) * ( normalize(vec3(0.5,0.5,0.5)) * dot(wi,N)  +  normalize(vec3(0.5,0.5,0.5)) * pow(dot( (wi+w0)/2.,N ),1) );
}

void main()
{
    FragColor = vec3(0,0,0);
    if(uCameraLight)
    {
        FragColor += blinnPhong(uCameraPos);
    }
    if(uRodLight)
    {
        FragColor += blinnPhong(uRodPos);
    }
    if(uRoomLights)
    {
        
    }
    
    //texture(texture_diffuse1, TexCoords);
}

