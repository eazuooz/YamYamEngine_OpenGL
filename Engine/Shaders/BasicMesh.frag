// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

// Request GLSL 3.3
#version 330

in vec2 fragTexCoord;

out vec4 outColor;

uniform sampler2D uTexture;

void main()
{
	// RGBA of 100% blue, 100% opaque
    outColor = texture(uTexture, fragTexCoord);
}
