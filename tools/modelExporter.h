#include <iostream>
#include <fstream>

#include <vector>
#include <map>
#include <cassert>
#include <string>



#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "ogldev/ogldev_util.h"

#define MAX_NUM_BONES_PER_VERTEX 51

typedef unsigned char uchar;

//https://www.youtube.com/watch?v=sP_kiODC25Q&t=250s
// https://github.com/assimp/assimp
//export LD_LIBRARY_PATH=/usr/local/lib
struct Position{
    float x,y,z;
};

struct VertexBoneData{
    uint BoneIDs[MAX_NUM_BONES_PER_VERTEX] = { 0 };
    float Weights[MAX_NUM_BONES_PER_VERTEX] = { 0.0f};
    VertexBoneData(){

    };
    void AddBoneData(uint BoneID, float Weight){
        for (uint i = 0 ; i < ARRAY_SIZE_IN_ELEMENTS(BoneIDs) ; i++) {
            if (Weights[i] == 0.0) {
                BoneIDs[i] = BoneID;
                Weights[i] = Weight;
                std::cout<<" bone -> "<< BoneID <<" weight -> "<< Weight<< " index -> "  <<i<<std::endl;
                return;
            }
        }
    // should never get here - more bones than we have space for
        assert(0);
    }
};


class ModelExporter{
    private:
        std::vector<Position> positions;
        std::vector<uint32_t> indices;
        //std::vector<uchar> indices;
        std::vector<VertexBoneData> vertex_to_bones;
        std::vector<int> mesh_base_vertex;
        std::map<std::string,uint> bone_name_to_index_map;


        void processScene(const aiScene * scene);
        void parseMesh(const aiScene *scene);
        void parse_mesh_bones(int mesh_index, const aiMesh* mesh);
        void parse_single_bone(int bone_index, const aiBone* bone);
        int get_bone_id(const aiBone *bone);
    public:

        ModelExporter(aiNode *node, const aiScene *scene);

        std::vector<Position> get_positions(){
            return positions;
        }
        std::vector<uint32_t> get_indices(){
            return indices;
        }
        void processMesh(aiMesh* mesh, const aiScene* scene);
        void processNode(aiNode* node, const aiScene* scene);
        char* getFilename(char* filename);

        
};