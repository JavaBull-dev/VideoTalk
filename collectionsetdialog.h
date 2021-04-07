#ifndef COLLECTIONSETDIALOG_H
#define COLLECTIONSETDIALOG_H

#include <QDialog>
#include <QAudioDeviceInfo>
#include <QCameraInfo>
#include <QVector>

namespace Ui {
class CollectionSetDialog;
}

class CollectionSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CollectionSetDialog(QWidget *parent = nullptr);
    ~CollectionSetDialog();
    QString getVideoDeviceName();
    QString getAudioDeviceName();
private:
    Ui::CollectionSetDialog *ui;
    QVector<QAudioDeviceInfo> audioDeviceInfos;
    QVector<QCameraInfo> cameraInfos;
    QAudioDeviceInfo audio;
    QCameraInfo camera;
private slots:
    void comboBox_camera_select_slot(int index);
    void comboBox_audioInput_select_slot(int index);
};

#endif // COLLECTIONSETDIALOG_H
