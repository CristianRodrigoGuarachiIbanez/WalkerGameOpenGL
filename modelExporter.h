#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <fstream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
//https://www.youtube.com/watch?v=sP_kiODC25Q&t=250s
// https://github.com/assimp/assimp

struct Position{
    float x,y,z;
};

class ModelExporter{
    private:
        std::vector<Position> positions;
        std::vector<uint32_t> indices;
    public:
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