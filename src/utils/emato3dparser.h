#ifndef EMATO3DPARSER_H
#define EMATO3DPARSER_H

#include <QObject>
struct Vertex {
    int index;
    float x, y, z;
};
struct Face {
    QVector<int> indices;
};
struct MeshSection {
    int faceCount;
    QVector<Face> faces;
};
class EmaTo3dParser : public QObject
{
    Q_OBJECT
public:
    explicit EmaTo3dParser(QObject *parent = nullptr);

    QString parseToObj(const QString& rawData);

    QString buildObjContent(const QMap<int, Vertex> &vertices, const QVector<MeshSection> &meshSections);
    QVector<MeshSection> parseMeshSections(const QString &data);
    QMap<int, Vertex> parseVertices(const QString &data);
signals:
};

#endif // EMATO3DPARSER_H
