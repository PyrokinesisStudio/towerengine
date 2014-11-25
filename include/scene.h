
#ifndef _SCENE_H
#define _SCENE_H


class tScene
{
	private:
		tWorld *world;

		map<string, tAsset *> assets;
		map<string, tSceneObject *> objects;

		tCubeMapAsset *sky_cubemap;
		tSkyBox *skybox;

		void ParseAssetsNode(xmlNodePtr cur);
		void ParseObjectsNode(xmlNodePtr cur);
		void ParseSceneNode(xmlNodePtr cur);

		void AddObject(string name, tSceneObject *object);

	public:
		tScene(tWorld *world);
		~tScene(void);

		bool LoadFromFile(string file);

		void AddToWorld(void);
		void RemoveFromWorld(void);
};



#endif