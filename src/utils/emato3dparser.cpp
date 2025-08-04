#include "emato3dparser.h"
#include <QStringList>
#include <QMap>
#include <QVector>
#include <QRegularExpression>



/**
 *
 *  Currently this parser is not working since attempting conversion to C++.
 *  Incomplete due to time restraints.
 *
 **/

EmaTo3dParser::EmaTo3dParser(QObject *parent)
    : QObject{parent}
{}

QString EmaTo3dParser::parseToObj(const QString& data) {
    QMap<int, Vertex> vertices = parseVertices(data);
    QVector<MeshSection> meshSections = parseMeshSections(data);

    return buildObjContent(vertices, meshSections);
}
QMap<int, Vertex> EmaTo3dParser::parseVertices(const QString& data) {
    QMap<int, Vertex> vertices;
    QStringList lines = data.split(",", Qt::SkipEmptyParts);
    int vertexIndex = 0;

    static const QRegularExpression coordPattern(
        R"(^([+-]?\d*\.?\d+(?:[eE][+-]?\d+)?)/([-+]?\d*\.?\d+(?:[eE][+-]?\d+)?)/([-+]?\d*\.?\d+(?:[eE][+-]?\d+)?)$)"
        );

    for (int i = 0; i < lines.size() - 1; ++i) {

        QString line = lines[i].trimmed();
        if (line.isEmpty() || line.contains("*"))
            break;

        QRegularExpressionMatch match = coordPattern.match(line);
        if (match.hasMatch()) {
            Vertex v { vertexIndex,
                     match.captured(1).toFloat(),
                     match.captured(2).toFloat(),
                     match.captured(3).toFloat() };
            vertices[vertexIndex++] = v;
        }
    }
    return vertices;
}
QVector<MeshSection> EmaTo3dParser::parseMeshSections(const QString& data) {
    QVector<MeshSection> meshSections;
    QStringList sections = data.split("*", Qt::SkipEmptyParts);

    for (int i = 1; i < sections.size(); ++i) {
        QString section = sections[i].trimmed();
        if (section.isEmpty()) continue;

        QStringList parts = section.split(",", Qt::SkipEmptyParts);
        if (parts.size() < 2) continue;

        int faceCount = parts[1].toInt();
        if (faceCount <= 0) continue;

        QVector<int> faceIndices;
        for (int j = 2; j < parts.size(); ++j) {
            if (parts[j] == "4294967295") break;
            bool ok = false;
            quint32 idx = parts[j].toUInt(&ok);
            if (!ok || idx == 4294967295) break;
            faceIndices.append(idx);
        }

        QVector<Face> faces;
        for (int k = 0; k + 5 < faceIndices.size(); k += 6) {
            faces.append({ { faceIndices[k], faceIndices[k+2], faceIndices[k+4] } });
        }

        meshSections.append({faceCount, faces});
    }

    return meshSections;
}
QString EmaTo3dParser::buildObjContent(const QMap<int, Vertex>& vertices,
                                       const QVector<MeshSection>& meshSections) {
    QString objContent;
    objContent += "# Generated OBJ file from custom mesh format\n";
    objContent += QString("# %1 vertices, %2 faces\n\n")
                      .arg(vertices.size())
                      .arg(std::accumulate(meshSections.begin(), meshSections.end(), 0,
                                           [](int sum, const MeshSection& sec) {
                                               return sum + sec.faces.size();
                                           }));

    QList<Vertex> sortedVertices = vertices.values();
    std::sort(sortedVertices.begin(), sortedVertices.end(),
              [](const Vertex& a, const Vertex& b) { return a.index < b.index; });

    QMap<int, int> vertexIndexMap;
    for (int i = 0; i < sortedVertices.size(); ++i) {
        const Vertex& v = sortedVertices[i];
        objContent += QString("v %1 %2 %3\n").arg(v.x).arg(v.y).arg(v.z);
        vertexIndexMap[v.index] = i + 1;
    }
    objContent += "\n";

    if (!meshSections.isEmpty()) {
        objContent += "o Root\n";
    }

    int totalFaces = 0;
    for (int sectionIndex = 0; sectionIndex < meshSections.size(); ++sectionIndex) {
        const MeshSection& section = meshSections[sectionIndex];
        objContent += QString("# Mesh section %1 (%2 faces)\n")
                          .arg(sectionIndex + 1)
                          .arg(section.faces.size());

        for (const Face& face : section.faces) {
            QStringList faceLine;
            for (int idx : face.indices) {
                faceLine << QString::number(idx + 1);
            }
            if (faceLine.size() >= 3) {
                objContent += "f " + faceLine.join(" ") + "\n";
                ++totalFaces;
            }
        }
        objContent += "\n";
    }

    objContent += QString("# Total faces written: %1\n").arg(totalFaces);
    return objContent;
}
