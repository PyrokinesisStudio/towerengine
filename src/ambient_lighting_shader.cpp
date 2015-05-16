
#include "towerengine.h"
#include "tresources.h"


void tAmbientLightingShader::Init(tGBuffer *gbuffer)
{
	InitLightingShader(ambient_lighting_shader_frag, "Ambient Lighting Shader");

	diffuse_tex_uniform = GetUniformLocation("diffuse_tex_uni");
	self_illumination_tex_uniform = GetUniformLocation("self_illumination_tex_uni");

	light_ambient_color_uniform = GetUniformLocation("light_ambient_color_uni");

	Bind();
	glUniform1i(diffuse_tex_uniform, gbuffer->GetTextureUnit(tGBuffer::DIFFUSE_TEX));
	glUniform1i(self_illumination_tex_uniform, gbuffer->GetTextureUnit(tGBuffer::SELF_ILLUMINATION_TEX));
}

void tAmbientLightingShader::SetAmbientLight(tVector color)
{
	glUniform3f(light_ambient_color_uniform, color.x, color.y, color.z);
}
