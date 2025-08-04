#ifndef EMATO3DPARSER_H
#define EMATO3DPARSER_H

#include <QObject>

/**
 *  Parse eplan electrical cad format (.ema) to obj mesh.
 *  - bool processEmaFile(const QString& in, QString& out):
 *      - Entry point
 *      - Processes ema data in string format, if success onto outData
 *
 *  - void parseEmaData(const QString& in, QVector<Vertex>& outVertices, QStringList& outOther)
 *      - Finds/Outs all vertex parts (indicated by 3 floats between fwd slashes)
 *      - Outs all other parts in QStringList
 *
 *  - QVector<QVector<int>> cleanAndGroupFaceIndices(const QStringList& inOther, int count)
 *      - Attempts to process non-vertex parts into valid indices, using pattern found by manually analyzing .ema file.
 *          - Pattern was partly correct, with missing information that was reprocessed in the finalized parser.
 *          - This was a messy temp function for testing.
 *
 *  - QVector<QVector<int>> triangulateStrip(const QVector<int>& inIndices)
 *      - Grops indices in 3s and converts to triangles
 *      - Skips triangles where any two vertices are the same
 *
 *  - QString buildObjString()
 *      - Builds a string in obj format from the current vertex and face data.
 *
 */

struct Vertex {
    float x, y, z;
};
// struct Face {
//     QVector<int> indices;
// };
// struct MeshSection {
//     int faceCount;
//     QVector<Face> faces;
// };
class EmaTo3dParser : public QObject
{
    Q_OBJECT
public:
    explicit EmaTo3dParser(QObject *parent = nullptr);

    bool processEmaFile(const QString& rawData, QString& outData);



    /** Getters **/
    QVector<Vertex> getVertices() const { return vertices; }
    QVector<QVector<int>> getFaces() const { return faces; }

private:
    QVector<Vertex> vertices;
    QVector<QVector<int>> faces;

    const QString PADDING = "4294967295";

    QVector<QVector<int>> triangulateStrip(const QVector<int>& stripIndices) const;
    QVector<QVector<int>> cleanAndGroupFaceIndices(const QStringList& parts, int vertexCount) const;
    QString buildObjString() const;
    void parseEmaData(const QString& rawData, QVector<Vertex>& outVertices, QStringList& outOtherParts) const;

};

#endif // EMATO3DPARSER_H
