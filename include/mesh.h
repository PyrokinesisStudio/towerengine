#ifndef MESH_H
#define MESH_H

#define TEM_VERSION_0_1				1
#define TEM_VERSION_0_2				2
#define TEM_VERSION_0_3				3
#define TEM_VERSION_0_4				3

#define TEM_VERSION_0_1_STRING		"0.1"
#define TEM_VERSION_0_2_STRING		"0.2"
#define TEM_VERSION_0_3_STRING		"0.3"
#define TEM_VERSION_0_4_STRING		"0.4"

#define TEM_CURRENT_VERSION			TEM_VERSION_0_4
#define TEM_CURRENT_VERSION_STRING	TEM_VERSION_0_4_STRING

template <class T> class tVBO;

// rapidxml forward declarations
namespace rapidxml
{
    template<class Ch> class xml_node;
    template<class Ch> class xml_attribute;
    template<class Ch> class xml_document;
}

class tMesh
{
	private:
		int file_version;

		bool loop_anim;
		bool anim_finished;
		bool animation_mode;

		bool refresh_vbos;
		bool refresh_ibos;

		tVAO *vao;
		tVBO<float> *vertex_vbo;
		tVBO<float> *normal_vbo;
		tVBO<float> *tang_vbo;
		tVBO<float> *bitang_vbo;
		tVBO<float> *face_normal_vbo;
		tVBO<float> *uvcoord_vbo;
		int data_count;

		std::map<tMaterial *, tMaterialIBO *> material_ibos;

		tBoundingBox bounding_box;

		std::set<tVertex *> outdated_vertices;

		tMeshPose *current_pose;
		tAnimation *current_animation;

		tMeshPose *idle_pose;

		tMaterial *idle_material;

		std::vector<tVertex *> vertices;
		std::vector<tTriangle *> triangles;
		std::map<std::string, tMaterial *> materials;
		std::map<std::string, tMeshPose *> custom_pose;
		std::vector<tAnimation *> animations;
		std::vector<tEntity *> entities;

		std::set<tMaterial *> own_materials;

		std::map<int, tVertex *> vertex_indices;


		btTriangleMesh *physics_triangle_mesh;

		void (*refresh_func)(void);

		//void CallRefresh(void) { if(refresh_func != 0) (*refresh_func)(); }


		void RefreshAllVBOs(void);
		void DeleteVBOData(void);

		tVertex *ParseVertexNode(rapidxml::xml_node<char> *cur);
		tMaterial *ParseMaterialNode(rapidxml::xml_node<char> *cur, std::string path);
		tTriangle *ParseTriangleNode(rapidxml::xml_node<char> *cur, tMaterialManager *material_manager);
		void ParseMeshDataNode(rapidxml::xml_node<char> *cur, tMaterialManager *material_manager, int &current_vertex_id);
		tMeshPose *ParsePoseNode(rapidxml::xml_node<char> *cur);
		tAnimation *ParseAnimationNode(rapidxml::xml_node<char> *cur);
		tKeyFrame *ParseKeyFrameNode(rapidxml::xml_node<char> *cur, tAnimation *anim);
		tEntity *ParseEntityNode(rapidxml::xml_node<char> *cur);

		static tDefaultMaterial *ParseXMLDefaultMaterialNode(rapidxml::xml_node<char> *cur, std::string &name, std::string path);
		static tSimpleForwardMaterial *ParseXMLSimpleForwardMaterialNode(rapidxml::xml_node<char> *cur, std::string &name, std::string path);
		static tRefractionMaterial *ParseXMLRefractionMaterialNode(rapidxml::xml_node<char> *cur, std::string &name, std::string path);

	public:
		static tMaterial *ParseXMLMaterialNode(rapidxml::xml_node<char> *cur, std::string &name, std::string path);


		//void ApplyMatrix(float m[16]);

		bool LoadFromFile(const char *file, tMaterialManager *material_manager = 0);
		bool LoadFromData(char *data, std::string path = "", tMaterialManager *material_manager = 0);
		bool LoadFromXML(rapidxml::xml_document<char> *doc, std::string path, tMaterialManager *material_manager = 0);

		void DepthPrePass(tRenderer *renderer, std::map<tMaterial *, tMaterial *> *replace_materials);
		void GeometryPass(tRenderer *renderer, std::map<tMaterial *, tMaterial *> *replace_materials);
		void ForwardPass(tRenderer *renderer, float *transform, std::map<tMaterial *, tMaterial *> *replace_materials);
		void RefractionPass(tRenderer *renderer, float *transform, std::map<tMaterial *, tMaterial *> *replace_materials);

		//bool GetCubeMapReflectionEnabled(void);

		int GetVertexCount(void)					{ return vertices.size(); }
		int GetTriangleCount(void)					{ return triangles.size(); }
		int GetMaterialCount(void)					{ return materials.size(); }
		int GetCustomPosesCount(void)				{ return custom_pose.size(); }
		int GetAnimationCount(void)					{ return animations.size(); }
		int GetEntityCount(void)					{ return entities.size(); }

		tVertex *GetVertex(int i)					{ return vertices.at(i); }
		tTriangle *GetTriangle(int i)				{ return triangles.at(i); }
		tMeshPose *GetCustomPose(std::string s) 			{ return custom_pose.at(s); }
		tAnimation *GetAnimation(int i)				{ return animations.at(i); }
		tEntity *GetEntity(int i)					{ return entities.at(i); }

		tMaterial *GetIdleMaterial(void)			{ return idle_material; }

		std::map<std::string, tEntity *> GetEntitiesInGroup(const char *group = "");

		tBoundingBox GetBoundingBox(void)			{ return bounding_box; }

		void AddVertex(tVertex *v);
		void AddTriangle(tTriangle *t);
		void AddMaterial(std::string name, tMaterial *m);
		void AddCustomPose(std::string name, tMeshPose *p);
		void AddAnimation(tAnimation *a);

		void RemoveVertex(tVertex *v);
		void RemoveTriangle(tTriangle *t);
		void RemoveMaterial(std::string name);
		void RemoveCustomPose(std::string name);
		void RemoveAnimation(tAnimation *a);
		void RemoveEntity(tEntity *e);

		//tIBO *CreateIBO(void)						{ return new tIBO(); }

		tMeshPose *GetIdlePose(void)		{ return idle_pose; }
		tMeshPose *GetCustomPoseByName(std::string name);
		tMeshPose *GetCurrentPose(void);
		std::string GetCurrentPoseName(std::string idle = std::string("Idle"));

		tAnimation *CreateAnimation(const char *name, float len = 1.0);
		void ChangeAnimation(tAnimation *a);
		void ChangeAnimation(const char *name);
		tAnimation *GetAnimationByName(const char *name);
		tAnimation *GetCurrentAnimation(void);
		char *GetCurrentAnimationName(void);
		void PlayAnimation(float t);
		void ApplyAnimation(void);
		void ResetAnimationFinished(void) { anim_finished = 0; };
		void SetAnimationLoop(int l) { loop_anim = l ? 1 : 0; anim_finished = 0; };
		int GetAnimationFinished(void) { return anim_finished; };

        //void SetTriangleMaterials(void);
		//void CalculateNormalsSolid(void);

		void GenerateBoundingBox(void);

		btTriangleMesh *GeneratePhysicsMesh(void);
		btTriangleMesh *GetPhysicsMesh(void)		{ return physics_triangle_mesh; }

		tVertex *CreateVertex(tVector v);
		tTriangle *CreateTriangle(tVertex *v1, tVertex *v2, tVertex *v3, tVector color, tMaterial *material);
		//tTriangle *CreateTriangleAuto(tVector v1, tVector v2, tVector v3, tVector color, std::string material, tVector t1, tVector t2, tVector t3);
		tMeshPose *CreateCustomPose(std::string name);
		tEntity *CreateEntity(std::string name, std::string group = std::string());

		tVBO<float> *CreateFloatVBO(int components);
		void AssignVertexArrayPositions(void);

		void ChangePose(std::string name, std::string idle = "Idle");
		void ChangePose(tMeshPose *pos);
		void CopyPoseFromVertices(void);

		tMaterial *GetMaterialByName(std::string name);
		tVertex *GetVertexByID(int id);

		void SetVertexId(tVertex *v, int id);

		void TriggerAllVBOsRefresh(void)	{ refresh_vbos = true; }
		void TriggerIBOsRefresh(void)		{ refresh_ibos = true; }
		void RefreshIBOs(void);

		//void SortTriangles(tVector cam);
		void SortMaterials(void);

		void SetIDs(void);

		void SetRefreshFunc(void (*func)(void)) { refresh_func = func; }

		tMesh(const char *file = 0, tMaterialManager *material_manager = 0);
		~tMesh(void);
};

#endif
















