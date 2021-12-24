#version 330 core

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 TexCoords;

out vec3 FragColor;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;
uniform vec3 uCameraPos;
uniform vec3 uCameraDir;
uniform vec3 uRodPos;
uniform vec3 uRodDir;
uniform vec3 uColor;
uniform bool uCameraLight;
uniform bool uRodLight;
uniform bool uRoomLights;
uniform bool uFlashLightMode;
uniform vec3 uRoomPos;

vec3 blinnPhongSpot(vec3 uLightPos_vs,vec3 uLightDir,vec3 Kd,vec3 Ks )
{
    vec3 uLightIntensity = vec3(100,100,100);
    vec3 w0 = normalize(-vPosition_vs);
    vec3 N = normalize(vNormal_vs);
    vec3 wi = normalize(-uLightDir);
    float d = distance(vPosition_vs,uLightPos_vs);
    vec3 Li = (uLightIntensity/(d*d));
    vec3 halfVector = normalize((wi+w0)/2.);
    float shininess = 128;
    if(uFlashLightMode)
    {
        float flashLightSize = -0.85;
        vec3 v = normalize(uLightPos_vs-vPosition_vs);
        float angleEffect = dot(-wi,v);
        if(angleEffect<flashLightSize)
        {
            return  Li * uColor * ((flashLightSize - angleEffect)*10) * ( Kd * dot(wi,N)  + Ks * pow(dot( halfVector,N ),shininess));
        }else{
            return vec3(0,0,0);
        }
    }
    return  Li * uColor  * ( Kd * dot(wi,N)  + Ks * pow(dot( halfVector,N ),shininess));
}

vec3 blinnPhongPoint(vec3 uLightPos_vs,vec3 Kd,vec3 Ks )
{
    vec3 uLightIntensity = vec3(200,200,200);
    vec3 w0 = normalize(-vPosition_vs);
    vec3 N = normalize(vNormal_vs);
    vec3 wi = normalize(uLightPos_vs - vPosition_vs);
    float d = distance(vPosition_vs,uLightPos_vs);
    vec3 Li = (uLightIntensity/(d*d));
    vec3 halfVector = normalize((wi+w0)/2.);
    float shininess = 20;
    return Li * uColor * ( Kd * dot(wi,N)  + Ks * pow(dot( halfVector,N ),shininess));
}

void main()
{
    vec3 Kd = texture(texture_diffuse1,TexCoords).xyz;
    vec3 Ks = texture(texture_specular1,TexCoords).xyz;
    FragColor = vec3(0,0,0);
    if(uCameraLight)
    {
        FragColor += blinnPhongSpot(uCameraPos,uCameraDir,Kd,Ks);
    }
    if(uRodLight)
    {
        FragColor += blinnPhongSpot(uRodPos,uRodDir,Kd,Ks);
    }
    if(uRoomLights)
    {
        FragColor += blinnPhongPoint(uRoomPos,Kd,Ks);
    }
    
}

