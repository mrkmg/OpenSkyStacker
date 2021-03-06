#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <opencv2/core/core.hpp>
#include <processing/imagestacker.h>
#include <QThread>
#include "model/imagetablemodel.h"
#include "ui/processingdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void stackImages();
    void readQImage(QString filename);

public slots:
    void finishedStacking(cv::Mat image);
    void updateProgress(QString message, int percentComplete);
    void clearProgress(QString message);
    void showTableContextMenu(QPoint pos);
    void setFrameAsReference();
    void removeSelectedImages();
    void imageSelectionChanged();
    void setImage(QImage image);
    void checkImages();
    void uncheckImages();
    void processingError(QString message);

private slots:
    //void handleButtonRefImage();
    void handleButtonLightFrames();
    void handleButtonStack();
    void handleButtonDarkFrames();
    void handleButtonDarkFlatFrames();
    void handleButtonFlatFrames();
    void handleButtonBiasFrames();

private:
    void setFileImage(QString filename);
    void setMemImage(QImage image);
    void clearReferenceFrame();
    void setDefaultReferenceImage();
    void loadImagesIntoStacker();
    QImage Mat2QImage(const cv::Mat &src);
    Ui::MainWindow *ui;

    QThread *workerThread;

    ImageStacker *stacker;
    ProcessingDialog *processingDialog;

    QDir selectedDir;
    QStringList imageFileFilter;
    ImageTableModel tableModel;

    bool hasFailed = false;
    QString errorMessage;
};

#endif // MAINWINDOW_H
