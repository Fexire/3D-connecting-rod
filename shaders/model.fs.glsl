#version 330 core

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 TexCoords;

out vec3 FragColor;

uniform sampler2D texture_diffuse1;
uniform vec3 uCameraPos;
uniform vec3 uCameraDir;
uniform vec3 uRodPos;
uniform vec3 uRodDir;
uniform vec4 uColor;
uniform bool uCameraLight;
uniform bool uRodLight;
uniform bool uRoomLights;
uniform vec3 uRoomPos;

vec3 blinnPhongSpot(vec3 uLightDir)
{
    vec3 uLightIntensity = vec3(1,1,1);
    vec3 w0 = normalize(-vPosition_vs);
    vec3 N = normalize(vNormal_vs);
    vec3 wi = normalize(-uLightDir);
    vec3 Li = uLightIntensity;
    vec3 Kd = normalize(vec3(0.5,0.5,0.5));
    vec3 Ks = normalize(vec3(0.5,0.5,0.5));
    vec3 halfVector = normalize((wi+w0)/2.);
    float shininess = 16.;
    return Li * ( Kd * dot(wi,N)  + Ks * pow(max(dot( halfVector,N ),0),shininess));
}

vec3 blinnPhongPoint(vec3 uLightPos_vs)
{
    vec3 uLightIntensity = vec3(100,100,100);
    vec3 w0 = normalize(-vPosition_vs);
    vec3 N = normalize(vNormal_vs);
    vec3 wi = normalize(uLightPos_vs - vPosition_vs);
    float d = distance(vPosition_vs,uLightPos_vs);
    vec3 Li = (uLightIntensity/(d*d));
    vec3 Kd = normalize(vec3(0.5,0.5,0.5));
    vec3 Ks = normalize(vec3(0.5,0.5,0.5));
    vec3 halfVector = normalize((wi+w0)/2.);
    float shininess = 24;
    return Li * ( Kd * dot(wi,N)  + Ks * pow(dot( halfVector,N ),shininess));
}

void main()
{

    FragColor = vec3(0,0,0);
    if(uCameraLight)
    {
        FragColor += blinnPhongSpot(uCameraDir);
    }
    if(uRodLight)
    {
        FragColor += blinnPhongSpot(uRodDir);
    }
    if(uRoomLights)
    {
        FragColor += blinnPhongPoint(uRoomPos);
    }
}

