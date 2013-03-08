#include "CmQtDockOverlayWidget.h"

#include <QtGui/QPainter>
#include <QtGui/QPen>
#include <QtGui/QPolygon>
#include <QtGui/QMouseEvent>
#include <QtCore/QRect>

namespace CamelotEditor
{
	QtDockOverlayWidget::QtDockOverlayWidget(QWidget* parent)
		:QWidget(parent), mHighlightedDropLocation(CM_WINDROP_NONE), mDropOverlayEnabled(false), mHighlightedTabDropLocation(-1), mTabDropOverlayEnabled(false)
	{ 
		setPalette(Qt::transparent);
		setAttribute(Qt::WA_TransparentForMouseEvents);
		hide();
	}

	void QtDockOverlayWidget::highlightDropLocation(WindowDragDropLocation dropLocation)
	{
		mHighlightedDropLocation = dropLocation;
		repaint();
	}

	void QtDockOverlayWidget::enableDropOverlay(std::vector<QPolygon> dragLocations, const QPoint& offset)
	{ 
		mDragLocations = dragLocations;
		mOverlayOffset = offset;

		if(!mDropOverlayEnabled)
		{
			show();

			mDropOverlayEnabled = true; 
			repaint();
		}
	}

	void QtDockOverlayWidget::disableDropOverlay()
	{
		if(mDropOverlayEnabled)
		{
			hide();

			mDropOverlayEnabled = false; 
			repaint();
		}
	}

	void QtDockOverlayWidget::highlightTabDropLocation(INT32 dropLocation)
	{
		mHighlightedTabDropLocation = dropLocation;
		repaint();
	}

	void QtDockOverlayWidget::enableTabDropOverlay(std::vector<QPolygon> dragLocations, const QPoint& offset)
	{
		mTabDropLocations = dragLocations;
		mTabOverlayOffset = offset;

		if(!mTabDropOverlayEnabled)
		{
			show();

			mTabDropOverlayEnabled = true; 
			repaint();
		}
	}

	void QtDockOverlayWidget::disableTabDropOverlay()
	{
		if(mTabDropOverlayEnabled)
		{
			hide();

			mTabDropOverlayEnabled = false; 
			repaint();
		}
	}

	void QtDockOverlayWidget::paintEvent(QPaintEvent *event)
	{
		if(mDropOverlayEnabled)
		{
			drawDragLocations(mDragLocations, mHighlightedDropLocation);
		}

		if(mTabDropOverlayEnabled)
		{
			drawTabDropLocations(mTabDropLocations, mHighlightedTabDropLocation);
		}
	}

	void QtDockOverlayWidget::drawDragLocations(const std::vector<QPolygon>& dragLocations, WindowDragDropLocation highlightedLocation)
	{
		QPainter painter(this);
		painter.translate(mOverlayOffset);
		painter.setRenderHint(QPainter::Antialiasing);
		painter.setPen(QColor(208, 208, 208));
		painter.setClipping(false);

		int idx = 0;
		for(auto iter = dragLocations.begin(); iter != dragLocations.end(); ++iter)
		{
			painter.drawPolygon(*iter);

			if(idx == (int)highlightedLocation)
			{
				QPainterPath highlightedPoly;
				highlightedPoly.addPolygon(*iter);

				painter.fillPath(highlightedPoly, QColor(190, 190, 190, 128));
			}
			else
			{
				QPainterPath highlightedPoly;
				highlightedPoly.addPolygon(*iter);

				painter.fillPath(highlightedPoly, QColor(210, 210, 210, 128));
			}

			++idx;
		}
	}

	void QtDockOverlayWidget::drawTabDropLocations(const std::vector<QPolygon>& dropLocations, INT32 highlightedLocation)
	{
		QPainter painter(this);
		painter.translate(mTabOverlayOffset);
		painter.setRenderHint(QPainter::Antialiasing);
		painter.setPen(QColor(208, 208, 208));
		painter.setClipping(false);

		int idx = 0;
		for(auto iter = dropLocations.begin(); iter != dropLocations.end(); ++iter)
		{
			painter.drawPolygon(*iter);

			if(idx == (int)highlightedLocation)
			{
				QPainterPath highlightedPoly;
				highlightedPoly.addPolygon(*iter);

				painter.fillPath(highlightedPoly, QColor(190, 190, 190, 128));
			}
			else
			{
				QPainterPath highlightedPoly;
				highlightedPoly.addPolygon(*iter);

				painter.fillPath(highlightedPoly, QColor(210, 210, 210, 128));
			}

			++idx;
		}
	}
}