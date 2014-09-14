
#ifndef _DEFAULT_FACE_SHADER_H
#define _DEFAULT_FACE_SHADER_H


class CGeometryPassShader : public CFaceShader
{
	private:
		GLint transformation_uniform;

		GLint diffuse_color_uniform;
		GLint diffuse_color2_uniform;
		GLint specular_color_uniform;

		GLint specular_size_uniform; // TODO: in exponent umbenennen

		GLint diffuse_tex_enabled_uniform;
		GLint normal_tex_enabled_uniform;
		GLint specular_tex_enabled_uniform;

		GLint diffuse_tex_uniform;
		GLint normal_tex_uniform;
		GLint specular_tex_uniform;

		GLint clip_uniform;
		GLint clip_dist_uniform;

		GLint vertex_mix_uniform;

	public:
		void Init(void);

		void SetClip(CVector c, float d);
		void SetDiffuseColor(CVector color);
		void SetDiffuseColor2(CVector color, float alpha);
		void SetSpecularColor(CVector color);
		void SetSpecular(float size);
		void SetDiffuseTexture(bool enabled, GLuint tex = 0);
		void SetSpecularTexture(bool enabled, GLuint tex = 0);
		void SetNormalTexture(bool enabled, GLuint tex = 0);
		void SetHeightTexture(bool enabled, GLuint tex = 0);
		void SetTexCoord(CVector2 coord);
		void SetVectors(CVector normal, CVector tangx, CVector tangy, CVector fnormal = Vec(0.0, 0.0, 0.0));
		void SetBumpFactor(float f);
		void SetTransformation(const float m[16]);
		void SetVertexMix(float m = 0.0);
		void ResetUniforms(void);
};


#endif
