#pragma once
#include <glm.hpp>
#include <fstream>
#include <string>
#include <vector>

// PMXのモデルデータ
struct PMXModelData
{
    static constexpr int NO_DATA_FLAG = -1;

    struct  Vertex
    {
        // 頂点座標
        glm::vec3 position;
        // 法線
        glm::vec3 normal;
        // UV座標
        glm::vec2 uv;
        // 追加UV座標
        std::vector<glm::vec4> additionalUV;

        // ボーンウェイト
        struct  Weight
        {
            enum Type
            {
                BDEF1,
                BDEF2,
                BDEF4,
                SDEF,
            };

            Type type;
            int born1;
            int born2;
            int born3;
            int born4;
            float weight1;
            float weight2;
            float weight3;
            float weight4;
            glm::vec3 c;
            glm::vec3 r0;
            glm::vec3 r1;
        } weight;
        
        // エッジ倍率
        float edgeMagnif;
    };

    struct Surface
    {
        int vertexIndex;
    };

    struct Material
    {
        glm::vec4 diffuse;
        glm::vec3 specular;
        float specularity;
        glm::vec3 ambient;

        int colorMapTextureIndex;
		int toonTextureIndex;
		// (スフィアテクスチャは非対応)

		// 材質ごとの頂点数
		int vertexNum;
    }

    struct Bone
    {
        // ボーン名
        std::wstring name;
        // English version
        std::string nameEnglish;
        glm::vec3 position;
        int parentIndex;
        int transformationLevel;
        unsigned short flag;
        glm::vec3 coordOffset;
        int childrenIndex;
        int impartParentIndex;
        float impartRate;
        // 固定軸方向ベクトル
        glm::vec3 fixedAxis;
        // ローカルのX軸方向ベクトル
        glm::vec3 localAxisX;
        // ローカルのZ軸方向ベクトル
        glm::vec3 localAxisZ;
        int externalParentKey;
        int ikTargetIndex;
        int ikLoopCount;
        float ikUnitAngle;

        struct IKLink
        {
            int index;
            bool existAngleLimited;
            glm::vec3 limitAngleMin;
            glm::vec3 limitAngleMax;
        };
        std::vector<IKLink> ikLinks;
    };

    std::vector<Vertex> vertices;
    std::vector<Surface> surfaces;
    std::vector<std::wstring> texturePaths;
    std::vector<Material> materials;
    std::vector<Bone> bones;
};

class PMXLoader
{
public:
    bool LoadPMX(PMXModelData& data, const std::wstring& _filePath);
private:
    bool getPMXStringUTF16(std::ifstream& _file, std::wstring& output);
};