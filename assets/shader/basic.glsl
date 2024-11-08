/// vertex ///
#version 330 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 vTex;
layout (location = 2) in vec3 vCol;

// uniform mat4 uModelMatrix;
// uniform mat4 uProjMatrix;
uniform mat4 uModelMat;

out vec2 fragUV;
out vec3 fragCol;

void main()
{
    // gl_Position = uProjMatrix * uModelMatrix * vec4(vPos.xyz, 1.0);
    fragUV = vTex;
    fragCol = vCol;
    gl_Position = uModelMat * vec4(vPos.xyz, 1.0);
}

/// frag ///
#version 330 core

uniform sampler2D inTexture;
uniform sampler2D inTexture2;
uniform int ceva;

in vec2 fragUV;
in vec3 fragCol;

void main()
{
    vec4 color = mix(texture(inTexture, fragUV*ceva), texture(inTexture2, fragUV*ceva), 0.5);
    // gl_FragColor = vec4(fragUV*ceva, 0.0, 1.0);
    gl_FragColor = color;
    // gl_FragColor = vec4(color, 1.0);
}