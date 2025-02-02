// For license of this file, see <project-root-folder>/LICENSE.md.

#include "gui/reusable/networkproxydetails.h"

#include "gui/guiutilities.h"

#include <QNetworkProxy>

NetworkProxyDetails::NetworkProxyDetails(QWidget* parent) : QWidget(parent) {
  m_ui.setupUi(this);
  GuiUtilities::setLabelAsNotice(*m_ui.m_lblProxyInfo, false);

  m_ui.m_txtProxyPassword->setPasswordMode(true);

  connect(m_ui.m_cmbProxyType, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,
          &NetworkProxyDetails::onProxyTypeChanged);

  m_ui.m_cmbProxyType->addItem(tr("No proxy"), QNetworkProxy::ProxyType::NoProxy);
  m_ui.m_cmbProxyType->addItem(tr("System proxy"), QNetworkProxy::ProxyType::DefaultProxy);
  m_ui.m_cmbProxyType->addItem(tr("Socks5"), QNetworkProxy::ProxyType::Socks5Proxy);
  m_ui.m_cmbProxyType->addItem(tr("Http"), QNetworkProxy::ProxyType::HttpProxy);

  connect(m_ui.m_cmbProxyType, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,
          &NetworkProxyDetails::changed);
  connect(m_ui.m_txtProxyHost, &QLineEdit::textChanged, this, &NetworkProxyDetails::changed);
  connect(m_ui.m_txtProxyPassword, &QLineEdit::textChanged, this, &NetworkProxyDetails::changed);
  connect(m_ui.m_txtProxyUsername, &QLineEdit::textChanged, this, &NetworkProxyDetails::changed);
  connect(m_ui.m_spinProxyPort, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this,
          &NetworkProxyDetails::changed);
}

QNetworkProxy NetworkProxyDetails::proxy() const {
  QNetworkProxy proxy(static_cast<QNetworkProxy::ProxyType>(m_ui.m_cmbProxyType->currentData().toInt()),
                      m_ui.m_txtProxyHost->text(),
                      m_ui.m_spinProxyPort->value(),
                      m_ui.m_txtProxyUsername->text(),
                      m_ui.m_txtProxyPassword->text());

  return proxy;
}

void NetworkProxyDetails::setProxy(const QNetworkProxy& proxy) {
  m_ui.m_cmbProxyType->setCurrentIndex(m_ui.m_cmbProxyType->findData(proxy.type()));
  m_ui.m_txtProxyHost->setText(proxy.hostName());
  m_ui.m_spinProxyPort->setValue(proxy.port());
  m_ui.m_txtProxyUsername->setText(proxy.user());
  m_ui.m_txtProxyPassword->setText(proxy.password());
}

void NetworkProxyDetails::onProxyTypeChanged(int index) {
  const QNetworkProxy::ProxyType selected_type = static_cast<QNetworkProxy::ProxyType>(m_ui.m_cmbProxyType->itemData(index).toInt());
  const bool is_proxy_selected = selected_type != QNetworkProxy::ProxyType::NoProxy &&
                                 selected_type != QNetworkProxy::ProxyType::DefaultProxy;

  m_ui.m_proxyDetails->setEnabled(is_proxy_selected);
}
