
#ifndef _STANDARD_FORWARD_SHADER_H
#define _STANDARD_FORWARD_SHADER_H

class tStandardForwardShader : public tFaceShader
{
	private:
		GLint cam_pos_uniform;

		GLint transformation_uniform;

		GLint base_color_tex_uniform;
		GLint metallic_roughness_tex_uniform;
		GLint normal_tex_uniform;
		GLint bump_tex_uniform;
		GLint emission_tex_uniform;

	public:
		tStandardForwardShader(void);

		void SetCameraPosition(tVector pos);
		void SetTransformation(const float m[16]);

		void SetBaseColorTexture(bool enabled, GLuint tex);
		void SetMetallicRoughnessTexture(GLuint tex);
		void SetNormalTexture(GLuint tex);
		void SetBumpTexture(GLuint tex);
		void SetEmissionTexture(GLuint tex);
};


#endif
