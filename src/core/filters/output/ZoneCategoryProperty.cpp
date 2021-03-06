// Copyright (C) 2019  Joseph Artsimovich <joseph.artsimovich@gmail.com>, 4lex4 <4lex49@zoho.com>
// Use of this source code is governed by the GNU GPLv3 license that can be found in the LICENSE file.

#include "ZoneCategoryProperty.h"

#include <QDomDocument>

#include "PropertyFactory.h"

namespace output {
const char ZoneCategoryProperty::m_propertyName[] = "ZoneCategoryProperty";

ZoneCategoryProperty::ZoneCategoryProperty(ZoneCategoryProperty::ZoneCategory zoneCategory)
    : m_zoneCategory(zoneCategory) {}

ZoneCategoryProperty::ZoneCategoryProperty(const QDomElement& el)
    : m_zoneCategory(zoneCategoryFromString(el.attribute("zoneCategory"))) {}

void ZoneCategoryProperty::registerIn(PropertyFactory& factory) {
  factory.registerProperty(m_propertyName, &ZoneCategoryProperty::construct);
}

std::shared_ptr<Property> ZoneCategoryProperty::clone() const {
  return std::make_shared<ZoneCategoryProperty>(*this);
}

QDomElement ZoneCategoryProperty::toXml(QDomDocument& doc, const QString& name) const {
  QDomElement el(doc.createElement(name));
  el.setAttribute("type", m_propertyName);
  el.setAttribute("zoneCategory", zoneCategoryToString(m_zoneCategory));
  return el;
}

std::shared_ptr<Property> ZoneCategoryProperty::construct(const QDomElement& el) {
  return std::make_shared<ZoneCategoryProperty>(el);
}

ZoneCategoryProperty::ZoneCategory ZoneCategoryProperty::zoneCategoryFromString(const QString& str) {
  if (str == "auto") {
    return AUTO;
  } else {
    return MANUAL;
  }
}

QString ZoneCategoryProperty::zoneCategoryToString(ZoneCategory zoneCategory) {
  QString str;

  switch (zoneCategory) {
    case MANUAL:
      str = "manual";
      break;
    case AUTO:
      str = "auto";
      break;
    default:
      str = "";
      break;
  }
  return str;
}
}  // namespace output