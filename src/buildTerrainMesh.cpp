#include "buildTerrainMesh.h"

void buildTerrainMesh(ofMesh& terrainMesh, const ofShortPixels& heightmap, unsigned int xStart, unsigned int yStart, unsigned int xEnd, unsigned int yEnd, glm::vec3 scale)
{
    using namespace glm;

    // x = s
    // y = f(s,t), determined by pixel values from heightmap
    // z = t
    // s and t are the pixel coordinates in the heightmap

    int width = xEnd - xStart;
    int depth = yEnd - yStart;


    // define vertices
    for (int y = yStart; y < yEnd; y++) {
        for (int x = xStart; x < xEnd; x++) {
            int h = heightmap.getColor(x, y).r;
            terrainMesh.addVertex(vec3(x, static_cast<float>(h) / USHRT_MAX, y) * scale); // cast before integer division
            //terrainMesh.addColor(ofFloatColor(0, 0, 0));
        }
    }

    // index buffer
    // how many we have in a row?
    // fenceposting issues
    for (int y = 0; y < depth - 1; y++) {
        for (int x = 0; x < width - 1; x++) {
            terrainMesh.addIndex(x + y * width);              
            terrainMesh.addIndex((x + 1) + y * width);        
            terrainMesh.addIndex(x + (y + 1) * width);       
            terrainMesh.addIndex((x + 1) + y * width);           
            terrainMesh.addIndex((x + 1) + (y + 1) * width);       
            terrainMesh.addIndex(x + (y + 1) * width);           
        }
    }

    terrainMesh.flatNormals();

    for (size_t i{ 0 }; i < terrainMesh.getNumNormals(); i++)
    {
        terrainMesh.setNormal(i, -terrainMesh.getNormal(i));
    }
}