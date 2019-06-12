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
#include <QtCharts/QScatterSeries>
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
	class ViewerChart;

	const int maxShowing = 20;
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
		QTimer * timer;
		// bool g_paused;

		//sampling const
		int s_const = 200;
		//loggin const
		int l_const = 200;
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
		GLuint selectedTexture;
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
		ViewerChart* charthighlighted;
		std::string showingObjects[maxShowing];
		Color colorSel[maxShowing] = {Color(0 , 0 , 0),Color(0 , 0 , 1),Color(0.541176 , 0.168627 , 0.886275),Color(0.647059 , 0.164706 , 0.164706),Color(0.498039 , 1 , 0),Color(0.823529 , 0.411765 , 0.117647),Color(0.913725 , 0.588235 , 0.478431),
		Color(0 , 1 , 1),Color(1 , 0 , 0),Color(0.662745 , 0.662745 , 0.662745),Color(0 , 0.392157 , 0),Color(1 , 0.843137 , 0),Color(0.333333 , 0.419608, 0.184314),Color(1 , 0.54902, 0), Color(0.6 , 0.196078, 0.8), Color(0.545098 , 0 , 0),
		Color(0.560784 , 0.737255 , 0.560784),Color(0.282353 , 0.239216 , 0.545098), Color(0.184314 , 0.309804 , 0.309804), Color(0.184314 , 0.309804 , 0.309804)};
		Robot* mouseLeftButtonRobot;
		Robot* mouseRightButtonRobot;
		Robot* mouseMiddleButtonRobot;

		double elapsedTime;
		bool s_paused;
	public:
		ViewerWidget(World *world, QWidget *parent = 0);
		~ViewerWidget();
		Settings* getSettings();
		void putSettings(Settings*);
		World* getWorld() const;
		CameraPose getCamera() const;
		QVector3D getPointedPoint() const;
		PhysicalObject* getPointedObject() const;
		PhysicalObject* getSelectedObject() const;
		bool isTrackingActivated() const;
		bool isMovableByPicking(PhysicalObject* object) const;
		int getLconst(){return l_const;}
		void setMovableByPicking(PhysicalObject* object, bool movable = true);
		void removeExtendedAttributes(PhysicalObject* object);

	signals:
		void hideGraph();
		void anlStep();
		void pause();
		void updateGraph(int);
		void logData(int);
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
		void selectedUpdate(std::vector<std::string> * highlightedRobots);
		void enSelected(bool mode);
		void addInfoMessage(const QString& message, double persistance = 5.0, const QColor& color = Qt::black, const QUrl& link = QUrl());
		void showHelp();
		void setLconst(int that){l_const = that;};


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
	    Settings(QString ruta, QWidget *parent = 0);
			void setVarDialog(QDialog* varD){vars=varD;  connect(buttons[2], SIGNAL(clicked()), vars, SLOT(show()));};
	signals:
			void settingsChanged(QString arg);

	private:
//	    void createMenu();f
			QString route;
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
			QDialog *vars;
	    QMenu *fileMenu;
	    QAction *exitAction;
	};
// class ViewerChart;
// class QAnalytics;
	/////// Analytics_Module

struct roboStat{
	std::string id;
	std::vector<double>* vectD;
	std::vector<std::string>* vectS;

	roboStat(std::string name, std::vector<double>* list):vectD(list),vectS(NULL),id(name){}
	roboStat(std::string name, std::vector<std::string>* list):vectS(list),vectD(NULL),id(name){}
	int size(){int size = vectD==NULL? vectS->size(): vectD->size(); return size;}
	bool isString() {return (vectD==NULL);}
	//	roboStat():id("NULL"){}
	};


	class eChart;
	class GThread: public QObject{
		Q_OBJECT
		public:
			GThread(std::vector<roboStat>* _lista, int n, std::string _mod, int _k, std::vector<roboStat>* _fitness = NULL, int _pos= -1, QObject *parent = 0);
			~GThread();

			// void initiate(std::vector<roboStat>* lista, int n, const std::string mod);
			// void init(){};


		signals:
			void addpoints(float x, float y);
			void addpoints(QVector<QPointF> *);
			void finished();
			void selectedUpdate(std::vector<std::string> * highlightedRobots);

		public slots:
			void threadUpdate(float x, bool sel);
			void iniLoop();
			std::vector<std::string>* getSlist(){return Slist;}

		protected:
			void g_Step();
			void finish();
			// void run() override;
			std::vector<double> retOrdRoboStats(int n, std::vector<double> *tempOut );


		private:
			// QMutex mutex;
			// QWaitCondition condition;
			std::vector<std::string> *Slist;
			float it;
			eChart * chart;
			std::vector<roboStat>* lista;
			std::vector<roboStat>* fitness;
			int cant, state, num;
			std::string mod;
			bool restart;
    	bool aborta;
			bool selected;
			int pos;
			int k; //sampling variable

};

#include <QFile>
#include <QTextStream>

	class QAnalytics: public QObject {
		Q_OBJECT

	private:
		// static QAnalytics* instance;

	public:
		QAnalytics(int maxIt){ maxIt=maxIt; internalLogic = 1;}
		~QAnalytics() {file->close();}
		std::unordered_map <std::string, std::vector<roboStat> > getVarList() {return varList;}
		void initLogModule(QWidget *);
		QDialog * createLogSett(int);
		QSpinBox * getLogSpinn(){return logSpinn;};
		// static QAnalytics* getInstance() {if (QAnalytics::instance) return QAnalytics::instance; else qDebug("NOOOOORL");}
		// void  getVarList() {qDebug("size: %d; %2.2f ",varList->size(),varList->at(0));}

	public slots:
		QStringList*  getListVars();
		std::vector<roboStat>*  getListVar(const std::string& name ) { if (varList.count(name.c_str())==0) return NULL; else return &varList.at(name.c_str());}//qDebug("Retrieving ''%s'' %d",name.c_str(),varList.at(name.c_str())->size());
		virtual void step(){};
		int robots(){return numRobots;}
		void log(std::string logText);
		void logData(int iterations);
		void updateLogname(const QString);

	protected:
		// std::vector<double> * varList = NULL;
		QMap<QString, QCheckBox*> logMap;
		QSpinBox * logSpinn;
		int numRobots = 0;
		std::vector<std::string> logList;
		std::unordered_map <std::string, std::vector<roboStat>> varList;
		QString logName = "proba.log";
		QFile *file;
	//	template <typename T>
		void registaer(std::string name, std::vector<double>* list, std::string var);
		void registaer(std::string name, std::vector<std::string>* list, std::string var);
		// void registaer(std::string name, std::vector<double> *list){varList = list;};

	//
	signals:
		// void notifyLconst(int);
	// 	void newTopQ(double iter, double quality);
	// 	void newAvgQ(double iter, double quality);

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
			eChart(QString title , int nRobo, int unic = 0, bool dots = false, QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
		    //eChart( QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0):QChart(QChart::ChartTypeCartesian,parent,wFlags);
				~eChart();

		public slots:
				void addPoint(float it, float quality);
				void addPoint(QVector<QPointF>*);
				void zoomAction(bool enabled);

		protected:
			bool sceneEvent(QEvent *event);

		private:
			const QStringList cor= {"black","blue","blueviolet","brown","chartreuse","chocolate","darksalmon","cyan","red","darkgray","darkgreen","gold","darkolivegreen","darkorange","darkorchid","darkred","darkseagreen","darkslateblue","darkslategray","darkslategrey","darkturquoise","darkviolet","deeppink","deepskyblue","dimgray","dimgrey","dodgerblue","firebrick","floralwhite","forestgreen","fuchsia","gainsboro","ghostwhite","gold","goldenrod","gray","green","greenyellow","grey","honeydew","hotpink","indianred","indigo","ivory","khaki","lavender","lavenderblush","lawngreen","lemonchiffon","lightblue","lightcoral","lightcyan","lightgoldenrodyellow","lightgray","lightgreen","lightgrey","lightpink","lightsalmon","lightseagreen","lightskyblue","lightslategray","lightslategrey","lightsteelblue","lightyellow","lime","limegreen","linen","magenta","maroon","mediumaquamarine","mediumblue","mediumorchid","mediumpurple","mediumseagreen","mediumslateblue","mediumspringgreen","mediumturquoise","mediumvioletred","midnightblue","mintcream","mistyrose","moccasin","navajowhite","navy","oldlace","olive","olivedrab","orange","orangered","orchid","palegoldenrod","palegreen","paleturquoise","palevioletred","papayawhip","peachpuff","peru","pink","plum","powderblue","purple","red","rosybrown","royalblue","saddlebrown","salmon","sandybrown","seagreen","seashell","sienna","silver","skyblue","slateblue","slategray","slategrey","snow","springgreen","steelblue","tan","teal","thistle","tomato","transparent","turquoise","violet","wheat","white","whitesmoke","yellow","yellowgreen"};
				QList<QAbstractSeries*> m_series;
				QList<QAbstractSeries*>::const_iterator c_series;
				QStringList m_titles;
				QValueAxis *m_axis;
				qreal m_step;
				qreal m_x;
				qreal m_y;
				qreal m_ylow;
				int	RANGEinc = 10000;
				int RANGE = RANGEinc;
				bool gestureEvent(QGestureEvent *event);
				bool m_isZooming;

};


//using namespace std;
// Widget grafo

	class ViewerChart: public QChartView{
		Q_OBJECT

	public:
    ViewerChart( eChart *chart, QWidget *parent = nullptr);
		~ViewerChart();

		void setChart( eChart *_chart){chart = _chart; QChartView::setChart(_chart); }
		bool sel;
		GThread * getGthread(){return gthread;}
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
			void change(const std::string params[], std::vector<roboStat>* lista, std::vector<roboStat>* fitness= NULL);
			void ecUpdate(int it);

	signals:
			void zoomSignal(bool act);
			void changeSignal();
			void threadUpdate(float i, bool sel);
			void enSelected(bool mode);

	private:
			GThread* gthread;
			QThread* thread;
	    bool m_isTouching;
			eChart * chart;
	};


class gPopup: public QDialog{
	Q_OBJECT

  public:
		gPopup(ViewerChart *vChart,bool *revert, QWidget *parent);
		// ~gPopup();


	public slots:
		void manage(const QString changed);

	private:
		QFormLayout *layout;
		QComboBox *yVars;
		QComboBox *xVars;
		QComboBox *modificador ;
		QSpinBox *t_gAmm;
		QSpinBox *t_gAmm2;
		QSlider *calidadeSpin;
		QDialogButtonBox *buttonBox ;
		QCheckBox *checkbox;

};


///// Main viewer
class ViewerWindow : public QMainWindow
	{
	    Q_OBJECT

	public:
//TODO specify mandatory charts in constructor
	    ViewerWindow(ViewerWidget *_viewer, QAnalytics* anl);
			~ViewerWindow();

			// static ViewerWindow getinstance(if (!instance) instance = new ViewerWindow(); return instance;);
			ViewerWidget* getViewer() {return this->viewer;}
			QAnalytics* getAnl() {return this->anl;}


	public slots:
			void hideGraph();
			void manageSettings(QString);
			void manageGraphs();
			void pauseRun(){ s_paused =! s_paused; };
			void speedSim(int timerSpeed);
			// QStringList * getVariables(){ return new QStringList("variables"); };

	private:
			static ViewerWindow instance;
	    void createActions();
	    void createStatusBar();
	    void createDockWindows();
			void getChoices(ViewerChart *parent);
			void changeGraphLayout(QString arg);
			void loadSettings();
			void saveSettings();
			QAction * hideDock;
			QString m_sSettingsFile;
			QLineEdit *m_pEdit;
			QStringList *variables;
			const int chMAX;
			bool s_paused;
			bool e_paused;

	protected:
			virtual void timerEvent(QTimerEvent * event);
			QWidget *chartLayout;
	    ViewerWidget *viewer;
			QAnalytics *anl;
			int timerPeriodMs;
			int timer; //timer for engine step
			int activeGraphs = 3;
			// QWidget  *charts[6];  //TODO quitar
			// QDockWidget *dockChart2;
			/*ViewerChart *anlChart1;
			ViewerChart *anlChart2;*/
//			virtual void keyPressEvent(QKeyEvent* event);

	    //QChartView *indAnlChart;
	    //QListWidget *paragraphsList;
		//	virtual void timerEvent(QTimerEvent * event);


	    //QMenu *viewMenu;
	};

}//Namespace
#endif
