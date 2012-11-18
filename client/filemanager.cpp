#include "filemanager.h"

FileManagerItem::FileManagerItem(QListWidget *parent) :
    QListWidgetItem(parent)
{
}

FileManagerItem::FileManagerItem(QIcon icon, QString text, ContentType type) :
    QListWidgetItem(icon, text)
{
    m_type = type;
}

ContentType FileManagerItem::contentType()
{
    return m_type;
}

FileManager::FileManager(QWidget *parent) :
    QListWidget(parent)
{
    setViewMode(QListView::IconMode);
    m_currentPath = "/";
    connect(this, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(clickHandler(QListWidgetItem*)));

}

void FileManager::clickHandler(QListWidgetItem *item)
{
    FileManagerItem *fmItem = dynamic_cast<FileManagerItem*>(item);
    if(item->type() == ctFolder)
    {
        m_currentPath = m_currentPath + fmItem->text() + "/";
        emit pathChanged(m_currentPath);
    }
    else if(item->type() == ctBackFolder)
    {
        m_currentPath = m_currentPath.left(m_currentPath.indexOf("/", m_currentPath.size() - 2));
        emit pathChanged(m_currentPath);
    }
    else
        emit fileOpen(m_currentPath + fmItem->text());
}

void FileManager::addContents(QStringList FolderNames, QStringList FileNames)
{
    clear();
    addItem(new FileManagerItem(m_iconProvider.icon(QFileIconProvider::Folder), "..", ctBackFolder));
    for(int i = 0; i < FolderNames.size(); i++)
        addItem(new FileManagerItem(m_iconProvider.icon(QFileIconProvider::Folder), FolderNames.value(i), ctFolder));
    for(int i = 0; i < FileNames.size(); i++)
        addItem(new FileManagerItem(m_iconProvider.icon(QFileIconProvider::File), FileNames.value(i), ctFile));
}
