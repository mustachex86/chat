#include "uimanager.h"

#include <controlcenter.h>
#include <interfaces/icontrolcenter.h>
#include <interfaces/iclientmanager.h>
#include <interfaces/iusersettings.h>
#include "userlist.h"
#include "messenger.h"
#include "messagelist.h"

#include <QAbstractListModel>
#include <QQmlEngine>
#include <QJSEngine>

namespace IPConnect
{

UiManager::UiManager() : m_cc(ControlCenter::instance())
{
	IClientManager* cm = m_cc->clientManager();
	m_usersList = new UserList(cm);
	m_messenger = new Messenger(cm);
	m_messages = new MessageList(cm);
	m_settings = m_cc->userSettings();
}

UiManager::~UiManager()
{
}

QAbstractListModel* UiManager::users()
{
	return m_usersList;
}

QAbstractListModel* UiManager::messages()
{
	return m_messages;
}

QString UiManager::theme()
{
	return m_settings->theme();
}

void UiManager::setTheme(QString color)
{
	if(color != theme())
		m_settings->setTheme(color);
	emit themeChanged();
}

QString UiManager::userName()
{
	return m_settings->name();
}

void UiManager::setUserName(QString name)
{
	if(name != userName() && !name.isEmpty() && !name.isNull())
		m_settings->setName(name);
	emit userNameChanged();
}

QString UiManager::downloadDir()
{
	return m_settings->downloadDir();
}

void UiManager::setDownloadDir(QString ddir)
{
	if(ddir != downloadDir() && !ddir.isEmpty() && !ddir.isNull())
		m_settings->setDownloadDir(ddir);
	emit downloadDirChanged();
}

void UiManager::sendMessage(int id,QString msg)
{
	m_messenger->sendMessage(id,msg);
}

void UiManager::quickConnect(QString url)
{
	if(url.isEmpty() || url.isNull())
		return;

	m_cc->clientManager()->connectManualy(url);
}

QObject* UiManager::uimanager_singleton(QQmlEngine *engine, QJSEngine *scriptEngine)
{
	Q_UNUSED(engine)
	Q_UNUSED(scriptEngine)

	UiManager *manager = new UiManager();
	return manager;
}

}
