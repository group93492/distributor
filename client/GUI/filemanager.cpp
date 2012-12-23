#include "filemanager.h"
#include <QDebug>

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
    connect(this, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(clickHandler(QListWidgetItem*)));

}

QStringList FileManager::selectedFolders()
{
    QStringList returnList;
    QList<QListWidgetItem*> listOfSelectedItems = selectedItems();
    FileManagerItem *item;
    for(int i = 0; i < listOfSelectedItems.size(); i++)
    {
        item = static_cast<FileManagerItem*>(listOfSelectedItems.value(i));
        if(item->contentType() == ctFolder)
            returnList.append("/" + m_currentPath.join("/") + item->text());
    }
    return returnList;
}

QStringList FileManager::selectedFiles()
{
    QStringList returnList;
    QList<QListWidgetItem*> listOfSelectedItems = selectedItems();
    FileManagerItem *item;
    for(int i = 0; i < listOfSelectedItems.size(); i++)
    {
        item = static_cast<FileManagerItem*>(listOfSelectedItems.value(i));
        if(item->contentType() == ctFile)
            returnList.append("/" + m_currentPath.join("/") + item->text());
    }
    return returnList;
}

void FileManager::clickHandler(QListWidgetItem *item)
{
    FileManagerItem *fmItem = dynamic_cast<FileManagerItem*>(item);
    if(fmItem->contentType() == ctFolder)
    {
        m_currentPath.append(fmItem->text());
        emit pathChanged("/" + m_currentPath.join("/"));
    }
    else if(fmItem->contentType() == ctBackFolder)
    {
        m_currentPath.removeLast();
        emit pathChanged("/" + m_currentPath.join("/"));
    }
    else
        emit fileOpen("/" + m_currentPath.join("/") + fmItem->text());
}

void FileManager::addContents(QStringList FolderNames, QStringList FileNames)
{
    clear();
    if(!m_currentPath.isEmpty())
        addItem(new FileManagerItem(m_iconProvider.icon(QFileIconProvider::Folder), "..", ctBackFolder));
    for(int i = 0; i < FolderNames.size(); i++)
        addItem(new FileManagerItem(m_iconProvider.icon(QFileIconProvider::Folder), FolderNames.value(i), ctFolder));
    for(int i = 0; i < FileNames.size(); i++)
        addItem(new FileManagerItem(m_iconProvider.icon(QFileIconProvider::File), FileNames.value(i), ctFile));
}
