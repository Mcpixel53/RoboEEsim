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

#include <unordered_map>
#include <typeinfo>
#include <QtWidgets>
#include <QGLWidget>
#include <QPoint>
#include <QPointF>
#include <QMap>
#include <QVector3D>
#include <QUrl>

#include <QException>
// #include <QtConcurrent>
#include <QtConcurrent/QtConcurrentRun>

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
// using namespace QtConcurrent;

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
		int msStep;
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

	public:
		bool doDumpFrames;
		unsigned dumpFramesCounter;
		void step();

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

		int Ifitness; //selected robot actual fitness

		PhysicalObject *pointedObject, *selectedObject;
		QVector3D pointedPoint;
		bool movingObject;

		Robot* mouseLeftButtonRobot;
		Robot* mouseRightButtonRobot;
		Robot* mouseMiddleButtonRobot;

		double elapsedTime;
		bool s_paused;
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
		void updateGraph(int iters);
		void anlStep();
		void pause();
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


	protected:
		// objects rendering
		void renderInterSegmentShadow(const Vector& a, const Vector& b, const Vector& c, double height);
		void renderSegmentShadow(const Segment& segment, double height);
		void renderSegment(const Segment& segment, double height);
		void renderWorldSegment(const Segment& segment);
		void renderWorld();
		void renderShape(const Polygon& shape, const double height, const Color& color);
		void renderSimpleObject(PhysicalObject *object);
		void paintBar(int fitness, float _x, float y);

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
		// Internal event handling
		virtual void helpActivated();
	};


//Settings
	class Settings : public QDialog
	{
	    Q_OBJECT
			int maxIterations = 10000;
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

class eChart;
	/////// Analytics_Module
	struct roboStat{
	std::string id;
	std::vector<double>* vect;
	roboStat(std::string name, std::vector<double>* list):vect(list),id(name){}
	//	roboStat():id("NULL"){}

	};

	class GThread: public QObject{
		Q_OBJECT
		public:
			GThread(std::vector<roboStat>* _lista, int n, std::string _mod, QObject *parent = 0);
			~GThread();

			// void initiate(std::vector<roboStat>* lista, int n, const std::string mod);
			// void init(){};


		signals:

			void addpoints(float x, float y);
			void addpoints(QVector<QPointF> *);

			void finished();

		public slots:
				void threadUpdate(float x);
				void iniLoop();

		protected:
			void g_Step();
			// void run() override;
			void finish();
			std::vector<double> retOrdRoboStats(int n);


		private:
			// QMutex mutex;
			// QWaitCondition condition;
			float it;
			eChart * chart;
			std::vector<roboStat>* lista;
			int cant, state, num;
			std::string mod;
			bool restart;
    	bool aborta;

};

	class QAnalytics: public QObject {
		Q_OBJECT

	public:
		QAnalytics(int maxIt){ maxIt=maxIt; internalLogic = 1;}
		std::unordered_map <std::string, std::vector<roboStat> > getVarList() {return varList;}
		// void  getVarList() {qDebug("size: %d; %2.2f ",varList->size(),varList->at(0));}

	public slots:
		QStringList*  getListVars();
		std::vector<roboStat>*  getListVar(const std::string& name ) { if (varList.count(name.c_str())==0) return NULL; else return &varList.at(name.c_str());}//qDebug("Retrieving ''%s'' %d",name.c_str(),varList.at(name.c_str())->size());
		virtual void step(){};


		int robots(){return numRobots;}


	protected:
		// std::vector<double> * varList = NULL;
		int numRobots = 0;
		std::unordered_map <std::string, std::vector<roboStat>> varList;
	//	template <typename T>
		void registaer(std::string name, std::vector<double>* list, std::string var);
		// void registaer(std::string name, std::vector<double> *list){varList = list;};


	signals:
		void newTopQ(double iter, double quality);
		void newAvgQ(double iter, double quality);

	private:
		int internalLogic;
		int maxIt;
	};

/////////////////////////////////////////////////////////TODO move to another class

/////// Grafo
	class eChart : public QChart
	{
		Q_OBJECT

		public:
			eChart(QString title , int nRobo, int unic = 0, QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
		    //eChart( QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0):QChart(QChart::ChartTypeCartesian,parent,wFlags);
				~eChart();

		public slots:
				void addPoint(float it, float quality);
				void addPoint(QVector<QPointF>*);
				void zoomAction(bool enabled);

		protected:
			bool sceneEvent(QEvent *event);

		private:
			const QStringList cor= {"black","aqua","blue","blueviolet","brown","chartreuse","chocolate","coral","cornflowerblue","cyan","darkblue","darkcyan","darkgoldenrod","darkgray","darkgreen","darkmagenta","darkolivegreen","darkorange","darkorchid","darkred","darksalmon","darkseagreen","darkslateblue","darkslategray","darkslategrey","darkturquoise","darkviolet","deeppink","deepskyblue","dimgray","dimgrey","dodgerblue","firebrick","floralwhite","forestgreen","fuchsia","gainsboro","ghostwhite","gold","goldenrod","gray","green","greenyellow","grey","honeydew","hotpink","indianred","indigo","ivory","khaki","lavender","lavenderblush","lawngreen","lemonchiffon","lightblue","lightcoral","lightcyan","lightgoldenrodyellow","lightgray","lightgreen","lightgrey","lightpink","lightsalmon","lightseagreen","lightskyblue","lightslategray","lightslategrey","lightsteelblue","lightyellow","lime","limegreen","linen","magenta","maroon","mediumaquamarine","mediumblue","mediumorchid","mediumpurple","mediumseagreen","mediumslateblue","mediumspringgreen","mediumturquoise","mediumvioletred","midnightblue","mintcream","mistyrose","moccasin","navajowhite","navy","oldlace","olive","olivedrab","orange","orangered","orchid","palegoldenrod","palegreen","paleturquoise","palevioletred","papayawhip","peachpuff","peru","pink","plum","powderblue","purple","red","rosybrown","royalblue","saddlebrown","salmon","sandybrown","seagreen","seashell","sienna","silver","skyblue","slateblue","slategray","slategrey","snow","springgreen","steelblue","tan","teal","thistle","tomato","transparent","turquoise","violet","wheat","white","whitesmoke","yellow","yellowgreen"};
				QList<QLineSeries*> m_series;
				QList<QLineSeries*>::const_iterator c_series;
				QStringList m_titles;
				QValueAxis *m_axis;
				qreal m_step;
				qreal m_x;
				qreal m_y;
				int	RANGEinc = 10000;
				int RANGE = RANGEinc;
				bool gestureEvent(QGestureEvent *event);
				bool m_isZooming;

};
//using namespace std;
// Widget grafo
	class viewerChart: public QChartView{
		Q_OBJECT

	public:
    viewerChart( eChart *chart, QWidget *parent = nullptr);
		void setChart( eChart *_chart){chart = _chart; QChartView::setChart(_chart); }

				//eChart* chart() {return chart;};
	protected:
			std::vector<roboStat>* lista;
			std::string mod;

			int cant; // ammount of robots to show or index
			virtual bool viewportEvent(QEvent *event);
	    virtual void mousePressEvent(QMouseEvent *event);
	    virtual void mouseMoveEvent(QMouseEvent *event);
	    virtual void mouseReleaseEvent(QMouseEvent *event);
	    virtual void keyPressEvent(QKeyEvent *event);

	public slots:
			void change(const std::string params[], std::vector<roboStat>* lista);
			void ecUpdate(int it);

	signals:
			void zoomSignal(bool act);
			void changeSignal();
			void threadUpdate(float i);
	private:
			GThread* gthread;
	    bool m_isTouching;
			eChart * chart;
	};


	/*Value RetrieveValue(std::string key)
	{
	     //get value
	      std::string value = get_value(key, etc);
	      return { value };
	}

	struct Value
	{
	    std::string _value;

	    template<typename T>
	    operator T() const   //implicitly convert into T
	    {
	       std::stringstream ss(_value);
	       T convertedValue;
	       if ( ss >> convertedValue ) return convertedValue;
	       else throw std::runtime_error("conversion failed");
	    }
	}
*/


///// Main viewer
class ViewerWindow : public QMainWindow
	{
	    Q_OBJECT

	public:
//TODO specify mandatory charts in constructor
	    ViewerWindow(ViewerWidget *_viewer, QAnalytics* anl);
			~ViewerWindow();
			ViewerWidget* getViewer();

	public slots:
			void hideGraph();
			void manageSettings(QString);
			void manageGraphs();
			void pauseRun(){ s_paused =! s_paused; };
			void speedSim(int timerSpeed);
			// QStringList * getVariables(){ return new QStringList("variables"); };

	private:
	    void createActions();
	    void createStatusBar();
	    void createDockWindows();
			void getChoices(viewerChart *parent);
			void changeGraphLayout(QString arg);
			QAction * hideDock;
			void loadSettings();
			void saveSettings();
			QString m_sSettingsFile;
			QLineEdit *m_pEdit;
			QStringList *variables;
			const int chMAX;
			bool s_paused;

	protected:
			virtual void timerEvent(QTimerEvent * event);

	    ViewerWidget *viewer;
			QWidget *chartLayout;
			QAnalytics *anl;
			int timerPeriodMs;
			int timer; //timer for engine step
			// QWidget  *charts[6];  //TODO quitar
			int activeGraphs = 3;
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
