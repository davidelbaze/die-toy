#include "MainWindow.h"

#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QCommandLineParser>
#include <QCommandLineOption>


int main(int argc, char *argv[])
{
    // Create and name our app
    QApplication app(argc, argv);
    app.setApplicationName("DieToy");
    app.setApplicationVersion("0.6");

    // -- Begin arg parsing -- //
    
    QCommandLineParser parser;
    parser.setApplicationDescription("DieToy : An application to manipulate images of chip dies.");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption dieImageOption(QStringList() << "i" << "image",
                                      QCoreApplication::translate("main", "Die image to load."),
                                      QCoreApplication::translate("main", "filename"));
    QCommandLineOption ddfOption(QStringList() << "d" << "dieDescription",
                                 QCoreApplication::translate("main", "Die description file to load."),
                                 QCoreApplication::translate("main", "filename"));
    parser.addOption(dieImageOption);
    parser.addOption(ddfOption);
   
    parser.process(app);

    QString dieImageFilename = parser.value(dieImageOption);
    QString dieDescriptionFilename = parser.value(ddfOption);
    
    // -- End arg parsing -- //
    
    
    // Create and resize the main window
    MainWindow win;
    const QSize desktopSize = QDesktopWidget().availableGeometry().size();
    const QSize winSize = desktopSize * 0.7f;
    const QPoint position((desktopSize.width() - winSize.width()) * 0.5f, 
                          (desktopSize.height() - winSize.height()) * 0.5f);
    win.resize(winSize);
    win.move(position);
    win.show();

    
    // Now that the show() message has been called, tell the window all about the commandline
    if (dieImageFilename != "")
    {
        const bool success = win.loadImage(dieImageFilename);
        if (!success)
        {
            qWarning() << "Unable to image file " << dieDescriptionFilename;
        }
        
    }
    if (dieDescriptionFilename != "")
    {
        const bool success = win.loadDescriptionJson(dieDescriptionFilename);
        if (!success)
        {
            qWarning() << "Unable to load die description file " << dieDescriptionFilename;
        }
    }
    
    
    return app.exec();
}
