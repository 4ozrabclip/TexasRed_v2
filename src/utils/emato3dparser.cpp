#include "emato3dparser.h"
#include <QStringList>
#include <QMap>
#include <QVector>
#include <QRegularExpression>


/**
 *
 *  This parser has been converted from my original attempt at this parser, which was done solo by me.
 *  Vertexes are correct, however the face blocks headers were incorrectly analyzed at the time.
 *
 *  The previous commit was meant to be the final product of the parser, converted to QT C++.
 *  However that wasn't working and I didn't understand the logic fully since it was completed and redesigned by my ex-coworker.
 *
 *
 **/

EmaTo3dParser::EmaTo3dParser(QObject *parent)
    : QObject{parent}
{}

bool EmaTo3dParser::processEmaFile(const QString& rawData, QString& outData)
{
    static const QRegularExpression regex(R"(<Stream Id="62491"><!\[CDATA\[(.*?)\]\]></Stream>)", QRegularExpression::DotMatchesEverythingOption);
    static const QRegularExpressionMatch match = regex.match(rawData);

    if (!match.hasMatch()) return false;


    QStringList nonVertexParts;

    parseEmaData(rawData, vertices, nonVertexParts);

    faces = cleanAndGroupFaceIndices(nonVertexParts, vertices.size());

    if (faces.isEmpty()) return false;

    outData = buildObjString();

    return true;
}

QVector<QVector<int> > EmaTo3dParser::cleanAndGroupFaceIndices(const QStringList &parts, int vertexCount) const
{
    QVector<int> validIndices;
    bool inPaddingBlock = false, inFaceBlock = false, faceBlockInitial = false;

    QString faceBlockIndicator;

    size_t i = 0;
    while (i < parts.size())
    {
        const QString& part = parts[i];
        if (inFaceBlock && faceBlockInitial) {
            faceBlockIndicator = part;
            faceBlockInitial = false;
        } else if (inFaceBlock && part == faceBlockIndicator) {
            inFaceBlock = false;
        } else if (inFaceBlock) {
            bool ok;
            int idx = part.toInt(&ok);
            if (ok) validIndices.append(idx);
        } else if (inPaddingBlock) {
            if (part == "*") {
                inPaddingBlock = false;
                inFaceBlock = true;
                faceBlockInitial = true;
            }
        } else if (part == PADDING) {
            inPaddingBlock = true;
        }
        ++i;
    }

    return triangulateStrip(validIndices);

}
QVector<QVector<int>> EmaTo3dParser::triangulateStrip(const QVector<int>& stripIndices) const
{
    QVector<QVector<int>> triangles;
    for (int i = 0; i < stripIndices.size() - 2; ++i) {
        int v0 = stripIndices[i];
        int v1 = stripIndices[i + 1];
        int v2 = stripIndices[i + 2];
        QVector<int> triangle = (i % 2 == 0) ? QVector<int>{v0, v1, v2} : QVector<int>{v0, v2, v1};

        if (v0 != v1 && v1 != v2 && v0 != v2)
            triangles.append(triangle);
    }
    return triangles;
}
QString EmaTo3dParser::buildObjString() const
{
    QString result;
    QTextStream out(&result);

    out << "# EMA 3D Mesh Export\n";
    out << "# Vertices: " << vertices.size() << "\n";
    out << "# Faces: " << faces.size() << "\n\n";

    for (const Vertex& v : vertices)
        out << QString("v %1 %2 %3\n").arg(v.x, 0, 'f', 6).arg(v.y, 0, 'f', 6).arg(v.z, 0, 'f', 6);

    out << "\n";
    for (const QVector<int>& face : faces) {
        out << "f";
        for (int idx : face)
            out << " " << (idx + 1);
        out << "\n";
    }

    return result;
}

void EmaTo3dParser::parseEmaData(const QString& rawData, QVector<Vertex>& outVertices, QStringList& outOtherParts) const
{
    const QStringList parts = rawData.split(",", Qt::SkipEmptyParts);

    for (int i = 0; i < parts.size() - 1; ++i)
    {
        QString trimmedPart = parts[i].trimmed();
        if (trimmedPart.contains("/"))
        {
            constexpr short neededCoordsSize = 3;
            const QStringList coords = trimmedPart.split("/");
            if (coords.size() == neededCoordsSize)
            {
                bool ok1, ok2, ok3;
                float x = coords[0].toFloat(&ok1);
                float y = coords[1].toFloat(&ok2);
                float z = coords[2].toFloat(&ok3);
                if (ok1 && ok2 && ok3)
                {
                    outVertices.append({x, y, z});
                }
            }
        }
        else
        {
            outOtherParts.append(trimmedPart);
        }
    }
}
