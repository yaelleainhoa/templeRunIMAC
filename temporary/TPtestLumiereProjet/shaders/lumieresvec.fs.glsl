#version 330 core

in vec3 vPosition;
in vec3 vNormale;
in vec2 vTexture;

uniform int nbLumieres;
uniform int nbLumieresPonct;
uniform float shininess;
 
// uniform vec3 uLightDir_vs; //w_i
// uniform vec3 uLightIntensity; //L_i

uniform sampler2D uTexture;
uniform sampler2D uTextureNuages;

uniform vec4 uPositions[2];
uniform vec3 uIntensites[2];

uniform vec4 uPositionsPonct[10];
uniform vec3 uIntensitesPonct[10];

vec3 blinnPhong(vec3 uKd, vec3 uKs, float shininess, vec3 uLightDir_vs, vec3 uLightIntensity){
    vec3 w_i=normalize(uLightDir_vs);
    vec3 w_o=normalize(-vPosition);
    vec3 N = normalize(vNormale);
    vec3 halfVector=normalize((w_i+w_o));
    vec3 color1 = uKd * dot(w_i, N);
    vec3 color2 = uKs * pow(dot(halfVector,N),shininess);
    vec3 color=uLightIntensity*(color1 + color2);
    return color;
}

vec3 blinnPhongPonctuel(vec3 uKd, vec3 uKs, float shininess, vec3 uLightDir_vs, vec3 uLightIntensity){
    vec3 w_i=normalize(uLightDir_vs);
    vec3 w_o=normalize(uLightDir_vs-vPosition);
    vec3 N = normalize(vNormale);
    float d=distance(uLightDir_vs, vPosition);
    vec3 halfVector=(w_i+w_o)/2;
    vec3 color1 = uKd * dot(w_i, N);
    vec3 color2 = uKs * pow(dot(halfVector,N),shininess);
    vec3 color=uLightIntensity/(d*d)*(color1 + color2);
    return color;
}

out vec3 fFragColor;

void main() {
    vec3 textColor=(texture(uTexture, vTexture)+texture(uTextureNuages, vTexture)).xyz;
    vec3 uKs=textColor*0.5;
    vec3 uKd=textColor;
    vec3 color=vec3(0,0,0);
    for(int i=0; i<nbLumieres; i++){
        color+=blinnPhong(uKd, uKs, shininess, uPositions[i].xyz, uIntensites[i]);
    }
    for(int i=0; i<nbLumieresPonct; i++){
        color+=blinnPhongPonctuel(uKd, uKs, shininess, uPositionsPonct[i].xyz, uIntensitesPonct[i]);
    }
    fFragColor=color;
};
