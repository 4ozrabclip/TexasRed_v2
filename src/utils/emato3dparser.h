#ifndef EMATO3DPARSER_H
#define EMATO3DPARSER_H

#include <QObject>
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

    QVector<Vertex> getVertices() const { return vertices; }
    QVector<QVector<int>> getFaces() const { return faces; }


private:
    QVector<Vertex> vertices;
    QVector<QVector<int>> faces;

    const QString PADDING = "4294967295";

    QString getUniqueFilename(const QString& basePath) const;
    QVector<QVector<int>> triangulateStrip(const QVector<int>& stripIndices) const;
    QVector<QVector<int>> cleanAndGroupFaceIndices(const QStringList& parts, int vertexCount) const;
    QString buildObjString() const;
    void parseEmaData(const QString& rawData, QVector<Vertex>& outVertices, QStringList& outOtherParts) const;

};

#endif // EMATO3DPARSER_H
