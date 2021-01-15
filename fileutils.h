#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QDebug>

class FileUtils : public QObject
{
    Q_OBJECT
public:
    explicit FileUtils(QObject *parent = nullptr);

    static void createFile(QString filePath,QString fileName);

signals:

};

#endif // FILEUTILS_H
