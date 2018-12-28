/*
    Enki - a fast 2D robot simulator
    Copyright (C) 1999-2016 Stephane Magnenat <stephane at magnenat dot net>
    Copyright (C) 2004-2005 Markus Waibel <markus dot waibel at epfl dot ch>
    Copyright (c) 2004-2005 Antoine Beyeler <abeyeler at ab-ware dot com>
    Copyright (C) 2005-2006 Laboratory of Intelligent Systems, EPFL, Lausanne
    Copyright (C) 2006-2008 Laboratory of Robotics Systems, EPFL, Lausanne
    See AUTHORS for details

    This program is free software; the authors of any publication
    arising from research using this software are asked to add the
    following reference:
    Enki - a fast 2D robot simulator
    http://home.gna.org/enki
    Stephane Magnenat <stephane at magnenat dot net>,
    Markus Waibel <markus dot waibel at epfl dot ch>
    Laboratory of Intelligent Systems, EPFL, Lausanne.

    You can redistribute this program and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef __ENKI_VIEWER_H
#define __ENKI_VIEWER_H

#include <typeinfo>
#include <QtWidgets>
#include <QGLWidget>
#include <QPoint>
#include <QPointF>
#include <QMap>
#include <QVector3D>
#include <QUrl>

#include <enki/Geometry.h>
#include <enki/PhysicalEngine.h>

#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QDebug>
#include <QtCharts/QChart>
#include <QtCharts/QAbstractSeries>
#include <QtWidgets/QRubberBand>

using namespace QtCharts;

	/*!	\file Viewer.h
	\brief Definition of the Qt-based viewer widget
*/

class QMouseEvent;
class QWheelEvent;
class QWidget;

namespace Enki
{

	class World;

	class PhysicalObject;
	class Settings;

	class ViewerWidget : public QGLWidget
	{
		Q_OBJECT

	public:
		int timerPeriodMs;
		int mult;
		class ViewerUserData : public PhysicalObject::UserData
		{
		public:
			virtual void draw(PhysicalObject* object) const = 0;
			virtual void drawSpecial(PhysicalObject* object, int param = 0) const { }
			// for data managed by the viewer, called upon viewer destructor
			virtual void cleanup(ViewerWidget* viewer) { }

		};

		// complex robot, one per robot type stored here
		class CustomRobotModel : public ViewerUserData
		{
		public:
			QVector<GLuint> lists;
			QVector<GLuint> textures;

		public:
			CustomRobotModel();
		};

		//! Camera pose
		struct CameraPose
		{
			QPointF pos; 		//!< (x,y) position of the camera
			double altitude;	//!< altitude (z) of the camera
			double yaw; 		//!< yaw angle, mathematical orientation
			double pitch; 		//!< pitch angle, negative looking down, positive looking up

			// constructors
			CameraPose();
			CameraPose(const World *world);
			CameraPose(const QPointF& pos, double altitude, double yaw, double pitch);
		};

	protected:
		Settings* settings;
		//! A camera pose that can be updated given a target position
		struct UpdatableCameraPose: CameraPose
		{
			double userYaw;		//!< yaw controlled by the user, added to the angle of the object in tracking
			double radius;		//!< radius distance used in tracking mode to compute camera to tracked object distance

			// the camera base coordinate system
			QVector3D forward;
			QVector3D left;
			QVector3D up;

			// constructors
			UpdatableCameraPose();
			UpdatableCameraPose(const World *world);
			UpdatableCameraPose(const QPointF& pos, double altitude, double yaw, double pitch);

			// assignment to base class
			UpdatableCameraPose& operator=(const CameraPose& pose);

			// updates of base coordinate system
			void update();
			void updateTracking(double targetAngle, const QVector3D& targetPosition = QVector3D(), double zNear = 2.f);
		};
		bool s_paused;

	public:
		bool doDumpFrames;
		unsigned dumpFramesCounter;

	protected:
		World *world;

		GLuint helpWidget;
		GLuint centerWidget;
		GLuint graphWidget;
		GLuint pauseWidget;
		GLuint resumeWidget;
		GLuint settingsWidget;
		GLuint selectionTexture;
		GLuint worldList;
		GLuint worldTexture;
		GLuint wallTexture;
		GLuint worldGroundTexture;

		typedef QMap<const std::type_info*, ViewerUserData*> ManagedObjectsMap;
		typedef QMapIterator<const std::type_info*, ViewerUserData*> ManagedObjectsMapIterator;
		ManagedObjectsMap managedObjects;
		typedef QMap<const std::type_info*, const std::type_info*> ManagedObjectsAliasesMap;
		typedef QMapIterator<const std::type_info*, const std::type_info*> ManagedObjectsAliasesMapIterator;
		ManagedObjectsAliasesMap managedObjectsAliases;

		struct InfoMessage
		{
			QString message;
			double persistance;
			QColor color;
			QUrl link;

			InfoMessage(const QString& message, double persistance, const QColor& color, const QUrl& link);
		};
		typedef std::list<InfoMessage> MessageList;
		MessageList messageList;
		int messageListWidth;
		int messageListHeight;
		const QFontMetrics fontMetrics;

		struct ExtendedAttributes
		{
			bool movableByPicking;

			ExtendedAttributes():movableByPicking(false){};
		};
		std::map<PhysicalObject*, ExtendedAttributes> objectExtendedAttributesList;

		bool mouseGrabbed;
		QPoint mouseGrabPos;
		double wallsHeight;
		UpdatableCameraPose camera; //!< current camera pose
		bool trackingView; //!< to know if camera is in tracking mode
		CameraPose nonTrackingCamera; //!< copy of global camera when in tracking view

		QProgressBar fitnessBar ; //!<shows quality meassure

		PhysicalObject *pointedObject, *selectedObject;
		QVector3D pointedPoint;
		bool movingObject;

		Robot* mouseLeftButtonRobot;
		Robot* mouseRightButtonRobot;
		Robot* mouseMiddleButtonRobot;

		double elapsedTime;

	public:
		ViewerWidget(World *world, QWidget *parent = 0);
		~ViewerWidget();

		Settings* getSettings();
		World* getWorld() const;
		CameraPose getCamera() const;
		QVector3D getPointedPoint() const;
		PhysicalObject* getPointedObject() const;
		PhysicalObject* getSelectedObject() const;
		bool isTrackingActivated() const;
		bool isMovableByPicking(PhysicalObject* object) const;

		void setMovableByPicking(PhysicalObject* object, bool movable = true);
		void removeExtendedAttributes(PhysicalObject* object);

	signals:
		void hideGraph();
		//void sliderMove(int ammount);
	public slots:
		void setCamera(const QPointF& pos, double altitude, double yaw, double pitch);
		void setCamera(double x, double y, double altitude, double yaw, double pitch);
		void setWallHeight(double _wallsHeight);
		void setManagedObjectsAliasesMap(ManagedObjectsAliasesMap map);
		void centerCameraWorld();
		void restartDumpFrames();
		void setDumpFrames(bool doDump);
		void setTracking(bool doTrack);
		void toggleTracking();
		void addInfoMessage(const QString& message, double persistance = 5.0, const QColor& color = Qt::black, const QUrl& link = QUrl());
		void showHelp();
		void speedSim(int timerSpeed);


	protected:
		// objects rendering
		void renderInterSegmentShadow(const Vector& a, const Vector& b, const Vector& c, double height);
		void renderSegmentShadow(const Segment& segment, double height);
		void renderSegment(const Segment& segment, double height);
		void renderWorldSegment(const Segment& segment);
		void renderWorld();
		void renderShape(const Polygon& shape, const double height, const Color& color);
		void renderSimpleObject(PhysicalObject *object);

		// helper functions for coordinates
		void glVertex2Screen(int x, int y);
		void computeInfoMessageAreaSize();

		// hooks for subclasses
		virtual void renderObjectsTypesHook();
		virtual void renderObjectHook(PhysicalObject *object);
		virtual void displayObjectHook(PhysicalObject *object);
		virtual void sceneCompletedHook();

		// Qt-OpenGL setup and drawing
		virtual void initializeGL();
		virtual void paintGL();
		virtual void resizeGL(int width, int height);

		// scene rendering and picking
		virtual void renderScene(double left, double right, double bottom, double top, double zNear, double zFar);
		virtual void picking(double left, double right, double bottom, double top, double zNear, double zFar);
		virtual void displayMessages();
		virtual void displayWidgets();
		virtual bool checkWidgetEvent( QMouseEvent *event);
		virtual bool clickWidget(QMouseEvent *event);
		virtual bool clickWidgetBottom(QMouseEvent *event);


		// Qt events handling
		virtual void keyPressEvent(QKeyEvent* event);
		virtual void mousePressEvent(QMouseEvent *event);
		virtual void mouseReleaseEvent(QMouseEvent * event);
		virtual void mouseMoveEvent(QMouseEvent *event);
		virtual void mouseDoubleClickEvent(QMouseEvent *event);
		virtual void wheelEvent(QWheelEvent * event);
		public:
		virtual void timerEvent(QTimerEvent * event);

		// Internal event handling
		virtual void helpActivated();
	};
//Settings
	class Settings : public QDialog
	{
	    Q_OBJECT

	public:
	    Settings();

	signals:
			void settingsChanged(QString arg);

	private:
//	    void createMenu();
	    void createHorizontalGroupBox();
	    void createGridGroupBox();
	    void createFormGroupBox();

	    enum { NumGridRows = 3, NumButtons = 4 };

	   // QMenuBar *menuBar;
	    QGroupBox *horizontalGroupBox;
	    QGroupBox *gridGroupBox;
	    QGroupBox *formGroupBox;
	    QTextEdit *smallEditor;
	    QTextEdit *bigEditor;
	    QLabel *labels[NumGridRows];
	    QLineEdit *lineEdits[NumGridRows];
	    QPushButton *buttons[NumButtons];
	    QDialogButtonBox *buttonBox;

	    QMenu *fileMenu;
	    QAction *exitAction;
	};
/////// Grafo
	class eChart : public QChart
	{
		Q_OBJECT

		public:
		    eChart(int maxIterations = 2500, QString title = "", QLineSeries* _series = new QLineSeries, QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
		    virtual ~eChart();

		public slots:
				void addPoint(double it, double quality);
				void zoomAction(bool enabled);

		protected:
			bool sceneEvent(QEvent *event);

		private:
				QLineSeries *m_series;
				QStringList m_titles;
				QValueAxis *m_axis;
				qreal m_step;
				qreal m_x;
				qreal m_y;
				int	RANGEinc = 1500;
				int RANGE = RANGEinc;
				bool gestureEvent(QGestureEvent *event);
				bool m_isZooming;

};

// Widget grafo
	class viewerChart: public QChartView{
		Q_OBJECT

	public:
    viewerChart(eChart *chart, QWidget *parent = 0);

	protected:
	    virtual bool viewportEvent(QEvent *event);
	    virtual void mousePressEvent(QMouseEvent *event);
	    virtual void mouseMoveEvent(QMouseEvent *event);
	    virtual void mouseReleaseEvent(QMouseEvent *event);
	    virtual void keyPressEvent(QKeyEvent *event);

	signals:
			void zoomSignal(bool act);

	private:
	    bool m_isTouching;

	};

	/////// Analytics_Module

	class QAnalytics: public QObject {
		Q_OBJECT

	public:
		QAnalytics(){ internalLogic = 1;}

		signals:
		void newTopQ(double iter, double quality);
		void newAvgQ(double iter, double quality);

	private:
		int internalLogic;
	};


///// Main viewer
class ViewerWindow : public QMainWindow
	{
	    Q_OBJECT

	public:
//TODO specify mandatory charts in constructor
	    ViewerWindow(ViewerWidget *_viewer, eChart* chart, eChart* _chart);
			~ViewerWindow();
			ViewerWidget* getViewer();

	public slots:
			void hideGraph();
			void changeDock();
			void manageSettings(QString);

	private:
	    void createActions();
	    void createStatusBar();
	    void createDockWindows();
			void changeGraphLayout(QString arg);
			QAction * hideDock;
			void loadSettings();
			void saveSettings();
			QString m_sSettingsFile;
			QLineEdit *m_pEdit;

	protected:
	    ViewerWidget *viewer;
			QWidget *analise;
			viewerChart  *charts[6];
			// QDockWidget *dockChart2;
			/*viewerChart *anlChart1;
			viewerChart *anlChart2;*/
//			virtual void keyPressEvent(QKeyEvent* event);

	    //QChartView *indAnlChart;
	    //QListWidget *paragraphsList;
		//	virtual void timerEvent(QTimerEvent * event);


	    //QMenu *viewMenu;
	};

}//Namespace
#endif
