// Copyright (C) 2019  Joseph Artsimovich <joseph.artsimovich@gmail.com>, 4lex4 <4lex49@zoho.com>
// Use of this source code is governed by the GNU GPLv3 license that can be found in the LICENSE file.

#ifndef SCANTAILOR_CORE_TABBEDDEBUGIMAGES_H_
#define SCANTAILOR_CORE_TABBEDDEBUGIMAGES_H_

#include <QTabWidget>
#include <boost/intrusive/list.hpp>

#include "DebugImageView.h"

class TabbedDebugImages : public QTabWidget {
  Q_OBJECT
 public:
  explicit TabbedDebugImages(QWidget* parent = nullptr);

 private slots:

  void currentTabChanged(int idx);

 private:
  using DebugViewList = boost::intrusive::list<DebugImageView, boost::intrusive::constant_time_size<false>>;

  enum { MAX_LIVE_VIEWS = 3 };

  void removeExcessLiveViews();

  /**
   * We don't want to keep all the debug images in memory.  We normally keep
   * only a few of them.  This list holds references to them in the order
   * they become live.
   */
  DebugViewList m_liveViews;
};


#endif  // ifndef SCANTAILOR_CORE_TABBEDDEBUGIMAGES_H_
