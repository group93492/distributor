#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QListWidget>
#include <QListWidgetItem>
#include <QFileIconProvider>

enum ContentType {
    ctBackFolder,
    ctFolder,
    ctFile
};

class FileManagerItem : public QListWidgetItem
{
public:
    explicit FileManagerItem(QListWidget *parent = 0);
    FileManagerItem(QIcon icon, QString text, ContentType type);
    ContentType contentType();

private:
    ContentType m_type;
};

class FileManager : public QListWidget
{
    Q_OBJECT
public:
    explicit FileManager(QWidget *parent = 0);
    QStringList selectedFolders();
    QStringList selectedFiles();

private:
    QFileIconProvider m_iconProvider;
    QString m_currentPath;

private slots:
    void clickHandler(QListWidgetItem *item);
    
signals:
    void pathChanged(QString newPath);
    void fileOpen(QString path);
    
public slots:
    void addContents(QStringList folderNames, QStringList fileNames);
    
};

#endif // FILEMANAGER_H
