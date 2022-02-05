#ifndef AVOUCHINSTALLER_H
#define AVOUCHINSTALLER_H

#include <QWizard>
#include <QProcess>
#include <QMessageBox>
#include <QTime>
#include <QTableWidget>

class QCheckBox;
class QLabel;
class QLineEdit;
class QRadioButton;
class QCheckBox;
class QTextEdit;
class QGroupBox;
class QTime;
class QProgressBar;


class AvouchInstaller : public QWizard
{
    Q_OBJECT

public:
    enum { Page_Start, Page_License, Page_Disk, Page_Partition, Page_User, Page_FinalSetup, Page_Conclusion };

    AvouchInstaller(QWidget *parent = nullptr);

private slots:
    void showHelp();
};


class StartPage : public QWizardPage
{
    Q_OBJECT

public:
    StartPage(QWidget *parent = nullptr);

    int nextId() const Q_DECL_OVERRIDE;

private slots:
    void createHorizontalGroupBox();
    int showLicensePage();

private:
    QLabel *Top_Label;
    QLabel *pictureLabel;
    QLabel *Install_Label;
    QLabel *Close_Label;
    QPushButton *Install_Button;
    QPushButton *Close_Button;
    QGroupBox *horizontalGroupBox1;
    QGroupBox *horizontalGroupBox2;
};

/******************* End of of LicensePage *****************************************/

class LicensePage : public QWizardPage
{
    Q_OBJECT

public:
    LicensePage(QWidget *parent = nullptr);

    int nextId() const Q_DECL_OVERRIDE;

private:
    QLabel *topLabel;
    QRadioButton *registerRadioButton;
    QRadioButton *evaluateRadioButton;
    QCheckBox *licenseAgreementCheckBox;
    QTextEdit *textEdit;
};

/******************* End of of LicensePage *****************************************/

class DiskPage : public QWizardPage
{
    Q_OBJECT

public:
    DiskPage(QWidget *parent = nullptr);


    int nextId() const Q_DECL_OVERRIDE;

private slots:
    void runGparted();
    QString getDisks();
    void showDisksTable();
    void selectedDisk();
    void delay(int);

private:
    QLabel *label_seleceted_disk;
    QLineEdit *lineEdit_seleceted_disk;
    QString seleceted_disk;
    QLabel *labelDrives;
    QLabel *gpartedLabel;
    QPushButton *gpartedButton;
    QTableWidget *disksTable;    
    QProcess *process_chroot;
    QProcess *process_findpartition;
    QProcess *process_rm;
    QMessageBox *msgBox;
    QMessageBox *emptyFeildMsgBox;
    QTableWidgetItem *newItem;


};

/******************* End of of Disk Page *****************************************/

class PartitionPage : public QWizardPage
{
    Q_OBJECT

public:
    PartitionPage(QWidget *parent = nullptr);

    void initializePage() Q_DECL_OVERRIDE;
    void showEvent(QShowEvent *) Q_DECL_OVERRIDE;
    int nextId() const Q_DECL_OVERRIDE;


private slots:

    //void getPartitions();
    void showPartitionsTable(QString, int);
    QString selectedPartition();
    void formatDrive();
    int formatMessageBox();
    void finishMsg();
    void readTerminalData();
    void delay(int);
    void radioButton1Clicked();
    void radioButton2Clicked();
    void radioButton3Clicked();

private:
    QLabel *label_selecetedpartition;
    QLineEdit *lineEdit_selecetedpartition;
    QTableWidget *partitionTable;
    //QString seleceted_disk;
    QString selecetedPartition;
    QProcess *process_format;
    QProcess *process_copyfiles;
    QProcess *process_chroot;
    QMessageBox *msgBox;
    QMessageBox *emptyFeildMsgBox;
    QTableWidgetItem *newItem;

    QRadioButton *radioButton1;
    QRadioButton *radioButton2;
    QRadioButton *radioButton3;
    QGroupBox *createRadioButtonExclusiveGroup();

};

/******************* End of of Partition Page *****************************************/

class UserPage : public QWizardPage
{
    Q_OBJECT

public:
    UserPage(QWidget *parent = nullptr);
    int nextId() const Q_DECL_OVERRIDE;

private:
    QLabel *nameLabel;
    QMessageBox *emptyFeildMsgBox;

    QLabel *label_fullname;
    QLabel *label_username;
    QLabel *label_admin;
    QLabel *label_password;
    QLabel *label_repassword;
    QLabel *label_missmatch;
    QLabel *label_hostname;
    QLabel *label_rootpasswd;
    QLabel *label_rootrepasswd;
    QLabel *label_rootmissmatch;

    QLineEdit *lineEdit_fullname;
    QLineEdit *lineEdit_username;
    QLineEdit *lineEdit_password;
    QLineEdit *lineEdit_repassword;
    QLineEdit *lineEdit_hostname;
    QLineEdit *lineEdit_rootpasswd;
    QLineEdit *lineEdit_rootrepasswd;


    QString fullname;
    QString username;
    QString password;
    QString repassword;
    QString hostname;
    QString rootpasswd;
    QString rootrepasswd;
    QString instPartition;

    QCheckBox *root_paaswd_checkbox;

private slots:
    void slotLineEditFullnameTextEdited(const QString);
    void slotLineEditRootPasswdTextEdited(const QString);
    void slotLineEditRootRePasswdTextEdited(const QString);
    void checkPasswordMismatch(const QString);
    void checkRootPasswordMismatch(const QString);
    void rootCheckBoxAction(bool checked);

};

/******************* End of of User Page *****************************************/

class FinalSetupPage : public QWizardPage
{
    Q_OBJECT

public:
    FinalSetupPage(QWidget *parent = nullptr);
    void initializePage() Q_DECL_OVERRIDE;
    void finalSetup();
    void delay( int millisecondsToWait );
    void showEvent(QShowEvent *) Q_DECL_OVERRIDE;
    int nextId() const Q_DECL_OVERRIDE;

signals:
    void updateProgressValue(const int value);

public slots:
    void finalProcessFinished();
    void SlotDetectFinish();
    void handleTimeOut();
    void readyReadStandardOutput();
    void updateProgressBar(const int value);



private:

    QTimer *timer1;
    QTimer *timer2;
    QLabel *topLabel;
    QLabel *pictureLabel;
    QLabel *label_process_finished;
    QLabel *lable_show_progress;
    QTextEdit *textedit_show_process;
    QLineEdit *lineEdit_procfinished;
    QProgressBar *progressBar;

    QString instPartition;
    QString fullname;
    QString username;
    QString password;
    QString repassword;
    QString hostname;
    QString rootpasswd;
    QString rootrepasswd;
    QString rootpasswdcheckbox;
    QString string_terminal_output;

    QTimer *timer;
    QProcess *process_final_setup;

    int value;
    int count;


private slots:
    int formatMessageBox();
    void readTerminalData();
    void animateImages();
    void updateValue();
};

/******************* End of of FinalSetp Page *****************************************/

class ConclusionPage : public QWizardPage
{
    Q_OBJECT

public:
    ConclusionPage(QWidget *parent = nullptr);

    void initializePage() Q_DECL_OVERRIDE;
    int nextId() const Q_DECL_OVERRIDE;
    void setVisible(bool visible) Q_DECL_OVERRIDE;
    void showEvent(QShowEvent *) Q_DECL_OVERRIDE;

private slots:
    void rebootButtonClicked();

private:
    QLabel *bottomLabel;
    QCheckBox *agreeCheckBox;
    QProcess *process;
};

/******************* End of of ConclusionPage Page *****************************************/

#endif // AVOUCHINSTALLER_H

