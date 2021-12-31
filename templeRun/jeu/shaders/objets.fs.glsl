#version 330 core

in vec3 vPosition;
in vec3 vNormale;
in vec2 vTexture;

uniform int nbLumieres;
uniform int nbLumieresPonct;
uniform float shininess;

uniform sampler2D uTexture;
uniform sampler2D uTextureNuages;

uniform vec4 uPositions[2];
uniform vec3 uIntensites[2];

uniform vec4 uPositionsPonct[10];
uniform vec3 uIntensitesPonct[10];

uniform int rouge;

vec4 blinnPhong(vec3 uKd, vec3 uKs, float shininess, vec3 uLightDir_vs, vec3 uLightIntensity){
    vec3 w_i=normalize(uLightDir_vs);
    vec3 w_o=normalize(-vPosition);
    vec3 N = normalize(vNormale);
    vec3 halfVector=normalize((w_i+w_o));
    vec3 color1 = uKd * dot(w_i, N);
    vec3 color2 = uKs * pow(dot(halfVector,N),shininess);
    vec4 color=vec4(uLightIntensity*(color1 + color2),0);
    return color;
}

vec4 blinnPhongPonctuel(vec3 uKd, vec3 uKs, float shininess, vec3 uLightDir_vs, vec3 uLightIntensity){
    vec3 w_i=normalize(uLightDir_vs-vPosition);
    vec3 w_o=normalize(-vPosition);
    vec3 N = normalize(vNormale);
    float d=distance(uLightDir_vs, vPosition);
    vec3 halfVector=(w_i+w_o)/2;
    vec3 color1 = uKd * dot(w_i, N);
    vec3 color2 = uKs * pow(dot(halfVector,N),shininess);
    vec4 color=vec4(uLightIntensity/(d*d)*(color1 + color2),0);
    return color;
}

out vec4 fFragColor;

void main() {
    vec4 textColor=(texture(uTexture, vTexture));//+texture(uTextureNuages, vTexture));
    vec3 uKs=(textColor*0.5).xyz;
    vec3 uKd=textColor.xyz;
    vec4 color=vec4(rouge+0.01,0.01,0.01,0);
    for(int i=0; i<nbLumieres; i++){
        color+=blinnPhong(uKd, uKs, shininess, uPositions[i].xyz, uIntensites[i]);
    }
    for(int i=0; i<nbLumieresPonct; i++){
        color+=blinnPhongPonctuel(uKd, uKs, shininess, uPositionsPonct[i].xyz, uIntensitesPonct[i]);
    }
    fFragColor=color;
};
