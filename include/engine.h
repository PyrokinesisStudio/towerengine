#ifndef _ENGINE_H
#define _ENGINE_H

class CEngine
{
private:
	static CFaceShader *face_shader;

public:
	static void Init(void);
	static void Destroy(void);

	static void BindFaceShader(void);
	static void UnbindShader(void);
	static void BindShader(GLhandleARB s);

	static CFaceShader *GetFaceShader(void)		{ return face_shader; }
};

#endif