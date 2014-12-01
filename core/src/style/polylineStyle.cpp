#include "polylineStyle.h"
#include "util/geometryHandler.h"

#include <time.h>

PolylineStyle::PolylineStyle(std::string _name, GLenum _drawMode) : Style(_name, _drawMode) {
    
    constructVertexLayout();
    constructShaderProgram();
    
}

void PolylineStyle::constructVertexLayout() {
    
    // TODO: Ideally this would be in the same location as the struct that it basically describes
    m_vertexLayout = std::shared_ptr<VertexLayout>(new VertexLayout({
        {"a_position", 3, GL_FLOAT, false, 0},
        {"a_texcoord", 2, GL_FLOAT, false, 0},
        {"a_extrudeNormal", 2, GL_FLOAT, false, 0},
        {"a_extrudeWidth", 1, GL_FLOAT, false, 0},
        {"a_color", 4, GL_UNSIGNED_BYTE, true, 0}
    }));
    
}

void PolylineStyle::constructShaderProgram() {
    
    std::string vertShaderSrcStr = stringFromResource("polyline.vs");
    std::string fragShaderSrcStr = stringFromResource("polyline.fs");
    
    m_shaderProgram = std::make_shared<ShaderProgram>();
    m_shaderProgram->buildFromSourceStrings(fragShaderSrcStr, vertShaderSrcStr);
    
}

void PolylineStyle::setup() {
    clock_t t = clock();
    m_shaderProgram->setUniformf("u_lightDirection", -1.0, -1.0, 1.0);
    m_shaderProgram->setUniformf("u_time", ((float)t)/CLOCKS_PER_SEC);
}

void PolylineStyle::buildPoint(Point& _point, std::string& _layer, Properties& _props, VboMesh& _mesh) {
    // No-op
}

void PolylineStyle::buildLine(Line& _line, std::string& _layer, Properties& _props, VboMesh& _mesh) {
    std::vector<PosNormEnormColVertex> vertices;
    std::vector<GLushort> indices;
    std::vector<glm::vec3> points;
    std::vector<glm::vec2> texcoords;
    std::vector<glm::vec2> extrudeNormals;
    
    GLuint abgr = 0xff969696; // Default road color
    float halfWidth = 0.02;
    
    if(_props.stringProps["kind"] == "highway"){
        halfWidth = 0.02;
    } else if(_props.stringProps["kind"] == "major_road"){
        halfWidth = 0.015;
    } else if(_props.stringProps["kind"] == "minor_road"){
        halfWidth = 0.01;
    } else if(_props.stringProps["kind"] == "rail"){
        halfWidth = 0.002;
    } else if(_props.stringProps["kind"] == "path"){
        halfWidth = 0.005;
    }
    
    GeometryHandler::buildDynamicPolyLine(_line, points, extrudeNormals, indices, texcoords);
    
    for (int i = 0; i < points.size(); i++) {
        glm::vec3 p = points[i];
        glm::vec2 uv = texcoords[i];
        glm::vec2 en = extrudeNormals[i];
        vertices.push_back({ p.x, p.y, p.z, uv.x, uv.y, en.x, en.y, halfWidth, abgr });
    }
    
    // Make sure indices get correctly offset
    int vertOffset = _mesh.numVertices();
    for (auto& ind : indices) {
        ind += vertOffset;
    }
    
    _mesh.addVertices((GLbyte*)vertices.data(), vertices.size());
    _mesh.addIndices(indices.data(), indices.size());
}

void PolylineStyle::buildPolygon(Polygon& _polygon, std::string& _layer, Properties& _props, VboMesh& _mesh) {
    // No-op
}
