#include "shaders.h"

#if defined(PLATFORM_DESKTOP)
const char* shaderDropShadowSource =
	"#version 330\n"
	"\n"
	"in vec2 fragTexCoord;\n"
	"\n"
	"uniform sampler2D texture0;\n"
	"\n"
	"uniform vec2 Direction;\n"
	"uniform float Size;\n"
	"uniform float TextureWidth;\n"
	"uniform float TextureHeight;\n"
	"uniform vec4 Color;\n"
	"\n"
	"out vec4 finalColor;\n"
	"\n"
	"void main()\n"
	"{\n"
	"	vec4 color = texture(texture0, fragTexCoord);\n"
	"\n"
	"	if (color.a >= 1.0) {\n"
	"		finalColor = color;\n"
	"		return;\n"
	"	}\n"
	"\n"
	"	float texelWidth = 1.0 / TextureWidth;\n"
	"	float texelHeight = 1.0 / TextureHeight;\n"
	"\n"
	"	vec2 sizeScaled = vec2(Size * texelWidth, Size * texelHeight);\n"
	"	vec2 sampleTexCoord = fragTexCoord - sizeScaled * Direction;\n"
	"\n"
	"	sampleTexCoord.x = max(sampleTexCoord.x, texelWidth);\n"
	"	sampleTexCoord.x = min(sampleTexCoord.x, 1.0 - texelWidth);\n"
	"	sampleTexCoord.y = max(sampleTexCoord.y, texelHeight);\n"
	"	sampleTexCoord.y = min(sampleTexCoord.y, 1.0 - texelHeight);\n"
	"\n"
	"	vec4 sampleColor = texture(texture0, sampleTexCoord);\n"
	"\n"
	"	if (sampleColor.a >= 1.0) {\n"
	"		finalColor = Color + color;\n"
	"		return;\n"
	"	}\n"
	"\n"
	"	finalColor = color;\n"
	"	return;\n"
	"}\n";
#endif

#if defined(PLATFORM_WEB)
const char* shaderDropShadowSource =
	"#version 100\n"
	"precision mediump float;\n"
	"\n"
	"uniform sampler2D texture0;\n"
	"\n"
	"uniform vec2 Direction;\n"
	"uniform float Size;\n"
	"uniform float TextureWidth;\n"
	"uniform float TextureHeight;\n"
	"uniform vec4 Color;\n"
	"\n"
	"varying lowp vec2 fragTexCoord;\n"
	"\n"
	"void main()\n"
	"{\n"
	"	vec4 color = texture2D(texture0, fragTexCoord);\n"
	"\n"
	"	if (color.a >= 1.0) {\n"
	"		gl_FragColor = color;\n"
	"		return;\n"
	"	}\n"
	"\n"
	"	float texelWidth = 1.0 / TextureWidth;\n"
	"	float texelHeight = 1.0 / TextureHeight;\n"
	"\n"
	"	vec2 sizeScaled = vec2(Size * texelWidth, Size * texelHeight);\n"
	"	vec2 sampleTexCoord = fragTexCoord - sizeScaled * Direction;\n"
	"\n"
	"	sampleTexCoord.x = max(sampleTexCoord.x, texelWidth);\n"
	"	sampleTexCoord.x = min(sampleTexCoord.x, 1.0 - texelWidth);\n"
	"	sampleTexCoord.y = max(sampleTexCoord.y, texelHeight);\n"
	"	sampleTexCoord.y = min(sampleTexCoord.y, 1.0 - texelHeight);\n"
	"\n"
	"	vec4 sampleColor = texture2D(texture0, sampleTexCoord);\n"
	"\n"
	"	if (sampleColor.a >= 1.0) {\n"
	"		gl_FragColor = Color + color;\n"
	"		return;\n"
	"	}\n"
	"\n"
	"	gl_FragColor = color;\n"
	"}\n";
#endif