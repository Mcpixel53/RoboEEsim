namespace Enki{

class Report:public QObject {

    private:
      static Report instance ;
      Report ();

    public:
      static getInstance(){Report tempInstance =Report::instance? Report::instance:new Report(); return tempInstance};
    }

}
