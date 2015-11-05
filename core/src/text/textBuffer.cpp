#include "textBuffer.h"

#include "labels/textLabel.h"
#include "gl/texture.h"
#include "gl/vboMesh.h"

namespace Tangram {

TextBuffer::TextBuffer(std::shared_ptr<VertexLayout> _vertexLayout)
    : LabelMesh(_vertexLayout, GL_TRIANGLES) {
    addVertices({}, {});
}

TextBuffer::~TextBuffer() {}

std::vector<TextBuffer::WordBreak> TextBuffer::findWords(const std::string& _text) {
    std::vector<WordBreak> words;
    unsigned int utf8state = 0;
    const char* str = _text.c_str();
    const char* end = str + strlen(str);
    int wordBegin = 0;
    int wordEnd = -1;
    int itr = 0;

    for (; str != end; ++str) {
        unsigned int byte = *(const unsigned char*)str;

        if (fonsDecUTF8(&utf8state, byte)) {
            continue;
        }

        if (std::isspace(*str)) {
            wordEnd = itr - 1;
            if (wordBegin <= wordEnd) {
                words.push_back({wordBegin, wordEnd});
            }
            wordBegin = itr + 1;
        }
        itr++;
    }

    if (!std::isspace(*(end-1))) {
        words.push_back({wordBegin, itr-1});
    }

    return words;
}

int TextBuffer::applyWordWrapping(std::vector<FONSquad>& _quads,
                                  const TextStyle::Parameters& _params,
                                  const FontContext::FontMetrics& _metrics,
                                  Label::Type _type, glm::vec2* _bbox) {
    struct LineQuad {
        std::vector<FONSquad*> quads;
        float length;
    };

    float yOffset = 0.f, xOffset = 0.f;
    int nLine = 1, lastBreak = 0;

    std::vector<LineQuad> lines;
    std::vector<TextBuffer::WordBreak> words;

    if (_params.wordWrap < _params.text.length() && _type != Label::Type::line) {
       words = findWords(_params.text);
    }

    // Approximation of the first glyph left side bearing
    float firstGlyphLSB = _quads[0].x0 * 0.5f;

    LineQuad line;
    lines.push_back(line); // atleast one line

    // Apply word wrapping based on the word breaks
    for (int iWord = 0; iWord < words.size(); iWord++) {
        int start = words[iWord].start;
        int end = words[iWord].end;
        size_t wordSize = end - start + 1;

        auto& lastLineQuads = lines[nLine - 1].quads;

        // Check if quads need to be added to next line?
        if (iWord > 0 && (lastLineQuads.size() + wordSize) > (size_t)_params.maxLineWidth) {
            auto& quad = _quads[start];
            auto& prevQuad = _quads[words[iWord-1].end];

            float spaceLength = quad.x0 - prevQuad.x1;
            yOffset += _metrics.lineHeight;
            xOffset -= quad.x0 + firstGlyphLSB - spaceLength;
            lines.push_back(LineQuad());
            nLine++;
        }

        for (int i = start; i <= end; i++) {
            auto& q = _quads[i];

            q.x0 += xOffset;
            q.x1 += xOffset;
            q.y0 += yOffset;
            q.y1 += yOffset;

            lines[nLine - 1].quads.push_back(&q);
            lines[nLine - 1].length = q.x1;

            // Adjust the bounding box on x
            _bbox->x = std::max(_bbox->x, q.x1);
        }
    }

    // Adjust the bounding box on y
    _bbox->y = _metrics.lineHeight * nLine;

    float bboxOffsetY = _bbox->y * 0.5f - _metrics.lineHeight - _metrics.descender;

    // Apply justification
    for (const auto& line : lines) {
        float paddingRight = _bbox->x - line.length;
        float padding;

        switch(_params.align) {
            case TextAlign::left: padding = 0.f; break;
            case TextAlign::right: padding = paddingRight; break;
            case TextAlign::center: padding = paddingRight * 0.5f; break;
        }

        for (auto quad : line.quads) {
            quad->x0 += padding;
            quad->x1 += padding;
            quad->y0 -= bboxOffsetY;
            quad->y1 -= bboxOffsetY;
        }
    }

    return nLine;
}


std::string TextBuffer::applyTextTransform(const TextStyle::Parameters& _params,
                                           const std::string& _string) {

    std::locale loc;
    std::string text = _string;

    // perfom text transforms
    switch (_params.transform) {
        case TextTransform::capitalize:
            text[0] = toupper(text[0], loc);
            if (text.size() > 1) {
                for (size_t i = 1; i < text.length(); ++i) {
                    if (text[i - 1] == ' ') {
                        text[i] = std::toupper(text[i], loc);
                    }
                }
            }
            break;
        case TextTransform::lowercase:
            for (size_t i = 0; i < text.length(); ++i) {
                text[i] = std::tolower(text[i], loc);
            }
            break;
        case TextTransform::uppercase:
            // TOOD : use to wupper when any wide character is detected
            for (size_t i = 0; i < text.length(); ++i) {
                text[i] = std::toupper(text[i], loc);
            }
            break;
        default:
            break;
    }

    return text;
}

bool TextBuffer::addLabel(const TextStyle::Parameters& _params, Label::Transform _transform,
                          Label::Type _type, FontContext& _fontContext) {

    if (_params.fontId < 0 || _params.fontSize <= 0.f || _params.text.size() == 0) {
        return false;
    }

    /// Apply text transforms
    const std::string* renderText;
    std::string text;

    if (_params.transform == TextTransform::none) {
        renderText = &_params.text;
    } else {
        text = applyTextTransform(_params, _params.text);
        renderText = &text;
    }

    if (!_fontContext.lock()) {
        return false;
    }

    /// Rasterize the glyphs
    auto& quads = _fontContext.rasterize(*renderText, _params.fontId,
                                         _params.fontSize, _params.blurSpread);

    size_t numGlyphs = quads.size();

    if (numGlyphs == 0) {
        _fontContext.unlock();
        return false;
    }

    auto& vertices = m_vertices[0];
    int vertexOffset = vertices.size();
    int numVertices = numGlyphs * 4;

    // Stroke width is normalized by the distance of the SDF spread, then scaled
    // to a char, then packed into the "alpha" channel of stroke. The .25 scaling
    // probably has to do with how the SDF is generated, but honestly I'm not sure
    // what it represents.
    uint32_t strokeWidth = _params.strokeWidth / _params.blurSpread * 255. * .25;
    uint32_t stroke = (_params.strokeColor & 0x00ffffff) + (strokeWidth << 24);

    FontContext::FontMetrics metrics = _fontContext.getMetrics();

    /// Apply word wrapping
    glm::vec2 bbox;
    int nLine = applyWordWrapping(quads, _params, _fontContext.getMetrics(), _type, &bbox);

    /// Generate the quads
    for (const auto& q : quads) {
        vertices.push_back({{q.x0, q.y0}, {q.s0, q.t0}, {-1.f, -1.f, 0.f}, _params.fill, stroke});
        vertices.push_back({{q.x0, q.y1}, {q.s0, q.t1}, {-1.f,  1.f, 0.f}, _params.fill, stroke});
        vertices.push_back({{q.x1, q.y0}, {q.s1, q.t0}, { 1.f, -1.f, 0.f}, _params.fill, stroke});
        vertices.push_back({{q.x1, q.y1}, {q.s1, q.t1}, { 1.f,  1.f, 0.f}, _params.fill, stroke});
    }

    _fontContext.unlock();

    m_labels.emplace_back(new TextLabel(_transform, _type, bbox, *this,
                                        { vertexOffset, numVertices },
                                        _params.labelOptions, metrics, nLine));

    // TODO: change this in TypeMesh::adVertices()
    m_nVertices = vertices.size();

    return true;
}

}
