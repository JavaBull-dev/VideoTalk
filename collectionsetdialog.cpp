#include "collectionsetdialog.h"
#include "ui_collectionsetdialog.h"

/**
 * @brief CollectionSetDialog::CollectionSetDialog
 * @param audio 被选中的音频设备的信息
 * @param camera 被选中的摄像头的信息
 * @param parent
 */
CollectionSetDialog::CollectionSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CollectionSetDialog)
{
    ui->setupUi(this);
    setWindowTitle("采集设备设置");
    ui->comboBox_audioInput->setEditable(false);
    ui->comboBox_camera->setEditable(false);

    QList<QAudioDeviceInfo> audioDevices = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    foreach (QAudioDeviceInfo devInfo, audioDevices)
    {
        QString strName = devInfo.deviceName();
        if (devInfo.isNull()) continue;
        if (strName[0] == 65533) continue;
        if(ui->comboBox_audioInput->findText(devInfo.deviceName()) != -1) continue;
        ui->comboBox_audioInput->addItem(strName);
        audioDeviceInfos.push_back(devInfo);

        if(audioDeviceInfos.size()==1)//第一个数据即为选中的数据
        {
            audio = devInfo;
        }
    }
//    qDebug("默认:%s", audio.deviceName().toUtf8().data());

    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    foreach (QCameraInfo devInfo, cameras)
    {
        if (devInfo.isNull()) continue;
        QString strName = devInfo.description();
        if(ui->comboBox_camera->findText(strName) != -1) continue;
        ui->comboBox_camera->addItem(strName);
        cameraInfos.push_back(devInfo);

        if(cameraInfos.size()==1)//第一个数据即为选中的数据
        {
            camera = devInfo;
        }
    }

//    qDebug("默认: %s", camera.description().toUtf8().data());

    connect(ui->comboBox_camera, SIGNAL(activated(int)),
            this, SLOT(comboBox_camera_select_slot(int)));
    connect(ui->comboBox_audioInput, SIGNAL(activated(int)),
            this, SLOT(comboBox_audioInput_select_slot(int)));
}

CollectionSetDialog::~CollectionSetDialog()
{
    delete ui;
}

QString CollectionSetDialog::getVideoDeviceName()
{
    return camera.description();
}

QString CollectionSetDialog::getAudioDeviceName()
{
    return audio.deviceName();
}

void CollectionSetDialog::comboBox_camera_select_slot(int index)
{
    qDebug("选中 camera %d", index);
    camera = cameraInfos.takeAt(index);
}

void CollectionSetDialog::comboBox_audioInput_select_slot(int index)
{
    qDebug("选中 audioInput %d", index);
    audio = audioDeviceInfos.takeAt(index);
}
