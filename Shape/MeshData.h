#pragma once

// template <unsigned int Vertex_Attribute_Count, 
//           unsigned int Vertex_Count,
//           unsigned int Index_Count
//           >
// struct MeshData {
//     static constexpr unsigned int VA_Count = Vertex_Attribute_Count;
//     static constexpr unsigned int V_Count = Vertex_Count;
//     static constexpr unsigned int I_Count = Index_Count;

//     float VertexData[VA_Count * V_Count];
//     unsigned int Indices[I_Count];

//     MeshData() :
// };


struct MeshData
{
    float* VertexData;
    unsigned int VertexDataSize;
    unsigned int* IndexData;
    unsigned int IndexCount;
};

