#ifndef _HEIGHTMAP_H
#define _HEIGHTMAP_H

class CHeightMap
{
	private:
		int size;
		float **data;

		GLuint height_tex;

	public:
		CHeightMap(int size);

		bool Load(const char *file);

		GLuint GetHeightTex(void)	{ return height_tex; }
		float GetValue(int x, int y) { return data[min(max(x, 0), size)][min(max(y, 0), size)]; }
		int GetSize(void) { return size; }
};

#endif