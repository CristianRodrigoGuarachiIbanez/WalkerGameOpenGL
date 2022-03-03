#include "modelExporter.h"
#include <string>
#include <cstring>



ModelExporter::ModelExporter(aiNode *node, const aiScene *scene){

    if(node->mNumMeshes != 0){
        processNode(node, scene);
        std::cout<<"Parsing nodes"<< " "<< std::to_string(node->mNumMeshes)<< std::endl;
    }else{
        std::cout<<"Parsing meshes"<< " "<< std::to_string(scene->mNumMeshes)<< std::endl;
        processScene(scene);
    }
}


int ModelExporter::get_bone_id(const aiBone *bone){

    int bone_id = 0;
    std::string bone_name(bone->mName.C_Str());

    if (bone_name_to_index_map.find(bone_name) == bone_name_to_index_map.end()) {
        // Allocate an index for a new bone
        bone_id = (int)bone_name_to_index_map.size();
        bone_name_to_index_map[bone_name] = bone_id;
    }
    else {
        bone_id = bone_name_to_index_map[bone_name];
    }
    return bone_id;
}


void ModelExporter::parse_single_bone(int mesh_index, const aiBone* bone)
{
    std::cout<<" Bone -> " << bone->mName.C_Str() <<","<<" num vertices affected by this bone-> " << ","<< bone->mNumWeights<<std::endl;

    int bone_id = get_bone_id(bone);
    //std::cout<<"bone id ->"<< bone_id<<std::endl;

    for (unsigned int i = 0 ; i < bone->mNumWeights ; i++) {
        if (i == 0) std::cout<<"/n"<<std::endl;
        
        const aiVertexWeight& vw = bone->mWeights[i];
        //std::cout<<" index -> "<<  i<< ","<<" vertex id -> " << vw.mVertexId<<","<< " weight -> " << vw.mWeight<<std::endl;

        uint global_vertex_id = mesh_base_vertex[mesh_index] + vw.mVertexId;
        std::cout<<"Vertex id -> "<< global_vertex_id; //<<std::endl;

        assert(global_vertex_id < vertex_to_bones.size());
        vertex_to_bones[global_vertex_id].AddBoneData(bone_id, vw.mWeight);
    }

    std::cout<<"/n"<<std::endl;
}

void ModelExporter::parse_mesh_bones(int mesh_index, const aiMesh* mesh)
{
    for (unsigned int i = 0 ; i < mesh->mNumBones; i++) {
        parse_single_bone(mesh_index, mesh->mBones[i]);
    }
}
void ModelExporter::parseMesh(const aiScene *scene){
    
    std::cout <<" -------------------------------------------------------"<<std::endl;
    std::cout <<"Parsing -> " << scene->mNumMeshes<<std::endl;

    int total_vertices = 0;
    int total_indices = 0;
    int total_bones = 0;

    this->mesh_base_vertex.resize(scene->mNumMeshes);

    for (unsigned int i = 0 ; i < scene->mNumMeshes ; i++) {
        const aiMesh* mesh = scene->mMeshes[i];
        int num_vertices = mesh->mNumVertices;
        int num_indices = mesh->mNumFaces * 3;
        int num_bones = mesh->mNumBones;
        mesh_base_vertex[i] = total_vertices;
        std::cout<<"Mesh -> "<< mesh->mName.C_Str()<< " vertices ->"<<num_vertices<<" indices ->" << num_indices<<" indices -> "<<num_indices<< " bones ->"<< num_bones<<std::endl;
        total_vertices += num_vertices;
        total_indices  += num_indices;
        total_bones += num_bones;

        this->vertex_to_bones.resize(total_vertices);


        if (mesh->HasBones()) {
            parse_mesh_bones(i, mesh);
        }
        std::cout<<"/n"<<std::endl;
    }
    std::cout<<" nTotal vertices -> "<<total_vertices<< " total indices -> "<< total_indices<<" total bones -> " << total_bones<<std::endl;

}

void ModelExporter::processScene(const aiScene * scene){

    parseMesh(scene);

}
// ------------------------------- nur für 3d Modelle -------------------------



void ModelExporter::processMesh(aiMesh* mesh, const aiScene* scene) {
   
            for(unsigned int i = 0; i < mesh->mNumVertices; i++) {
                Position vertex;
                vertex.x = mesh->mVertices[i].x;
                vertex.y = mesh->mVertices[i].y;
                vertex.z = mesh->mVertices[i].z;
                positions.push_back(vertex);
            }

            for(unsigned int i = 0; i < mesh->mNumFaces; i++) {
                aiFace face = mesh->mFaces[i];
                assert(face.mNumIndices == 3);
                for(unsigned int j = 0; j < face.mNumIndices; j++) {
                    indices.push_back(face.mIndices[j]);
                }
            }
        }

void ModelExporter::processNode(aiNode* node, const aiScene* scene) {
    
    //std::cout<<"Parsing meshes"<< " "<< std::to_string(scene->mNumMeshes)<< std::endl;
    int total_vertices = 0;
    int total_indices = 0;
    int total_bones = 0;
    for(unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        int num_vertices = mesh->mNumVertices;
        int num_indices = mesh-> mNumFaces *3;
        int num_bones = mesh->mNumBones;
        processMesh(mesh, scene);
        std::cout<<"Mesh -> "<< mesh->mName.C_Str()<< " vertices ->"<<num_vertices<<" indices ->" << num_indices<<" indices -> "<<num_indices<< " bones ->"<< num_bones<<std::endl;
        total_vertices += num_vertices;
        total_indices  += num_indices;
        total_bones += num_bones;

        std::cout<<" nTotal vertices ->"<<total_vertices<< " total indices ->"<< total_indices<<" total bones ->" << total_bones<<std::endl;

    }

    for(unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

char* ModelExporter::getFilename(char* filename) {
    int len = strlen(filename);
    char* lastSlash = filename; // first character
    for(int i = 0; i < len; i++) {
        if(filename[i] == '/' || filename[i] == '\\') {
            lastSlash = filename+i+1; //spring the slash
        }
    }
    return lastSlash;
} 


int main(int argc, char** argv) {
    if(argc <= 0) {
        return 1;
    }
    if(argc < 2) {
        std::cout << "Usage: " << argv[0] << " <modelfilename>" << std::endl;
        return 1;
    }
  
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(argv[argc-1], aiProcess_Triangulate | aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph | aiProcess_JoinIdenticalVertices | aiProcess_ImproveCacheLocality);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE, !scene->mRootNode) {
        std::cout << "Error while loading model with assimp: " << importer.GetErrorString() << std::endl;
        return 1;
    }
    ModelExporter model(scene->mRootNode, scene);

    std::string filename = std::string(model.getFilename(argv[argc-1]));
    std::string filenameWithoutExtension = filename.substr(0, filename.find_last_of('.')); 
    std::string outputFilename = "../models/"+filenameWithoutExtension + ".bmf";
    std::cout <<outputFilename<<std::endl;

    std::ofstream output(outputFilename, std::ios::out | std::ios::binary);
    std::cout << "Writing bmf file..." << std::endl;
    uint64_t numVertices = model.get_positions().size();
    uint64_t numIndices = model.get_indices().size();
    output.write((char*)&numVertices, sizeof(uint64_t));
    output.write((char*)&numIndices, sizeof(uint64_t));
    for(uint64_t i = 0; i < numVertices; i++) {
        output.write((char*)&model.get_positions()[i].x, sizeof(float));
        output.write((char*)&model.get_positions()[i].y, sizeof(float));
        output.write((char*)&model.get_positions()[i].z, sizeof(float));
    }
    for(uint64_t i = 0; i < numIndices; i++) {
        output.write((char*)&model.get_indices()[i], sizeof(uint32_t));
    }
    output.close();
}