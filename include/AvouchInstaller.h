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
    enum { Page_Start, Page_License, Page_Partition, Page_User, Page_FinalSetup,
           Page_Conclusion };

    AvouchInstaller(QWidget *parent = 0);

private slots:
    void showHelp();
};


class StartPage : public QWizardPage
{
    Q_OBJECT

public:
    StartPage(QWidget *parent = 0);

    int nextId() const Q_DECL_OVERRIDE;

private slots:
    void createHorizontalGroupBox();
    int showLicensePage();

private:
    QLabel *Top_Label;
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
    LicensePage(QWidget *parent = 0);

    int nextId() const Q_DECL_OVERRIDE;

private:
    QLabel *topLabel;
    QRadioButton *registerRadioButton;
    QRadioButton *evaluateRadioButton;
    QCheckBox *licenseAgreementCheckBox;
    QTextEdit *textEdit;
};

/******************* End of of LicensePage *****************************************/

class PartitionPage : public QWizardPage
{
    Q_OBJECT

public:
    PartitionPage(QWidget *parent = 0);

    int nextId() const Q_DECL_OVERRIDE;

private slots:
    void runGparted();
    void findDisks();
    void findPartitions();
    void getDisks();
    void getPartitions();
    void processDisks(QString);
    void processPartitions(QString, int);
     QString selectedDisk();
    QString selectedPartition();
    void formatDrive();
    int formatMessageBox();
    void finishMsg();
    void readTerminalData();
    void delay(int);

private:
    QLabel *label_selecetedpartition;
    QLineEdit *lineEdit_selecetedpartition;

    QLabel *labelDrives;
    QLabel *gpartedLabel;
    QPushButton *gpartedButton;
    QTableWidget *disksTable;
    QTableWidget *partitionTable;
    QString seleceted_disk;
    QString selecetedpartition;
    QProcess *process_finddisks;
    QProcess *process_getdisks;
    QProcess *process_findpartition;
    QProcess *process_gparted;
    QProcess *process_format;
    QProcess *find_partition;
    QProcess *process_copyfiles;
    QProcess *process_chroot;
    QMessageBox *msgBox;
    QMessageBox *emptyFeildMsgBox;
    int m_row;

};

/******************* End of of Partition Page *****************************************/

class UserPage : public QWizardPage
{
    Q_OBJECT

public:
    UserPage(QWidget *parent = 0);
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

private slots:
    void on_lineEdit_fullname_textEdited(const QString);
    void check_password_mismatch(const QString);
    void check_root_password_mismatch(const QString);

};

/******************* End of of User Page *****************************************/

class FinalSetupPage : public QWizardPage
{
    Q_OBJECT

public:
    FinalSetupPage(QWidget *parent = 0);

    int nextId() const Q_DECL_OVERRIDE;
    void initializePage() Q_DECL_OVERRIDE;
    void finalSetup();
    void delay( int millisecondsToWait );

public slots:
    void SlotDetectFinish();
    void handleTimeOut();


private:

    QTimer *timer1;
    QTimer *timer2;
    QLabel *topLabel;
    QLabel *pictureLabel;
    QLabel *label_procfinished;
    QTextEdit *textEdit_showProcess;
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
    int value;

    QProcess *process_final_setup;


private slots:
    int formatMessageBox();
    void readTerminalData();
    void animateImages();
};

/******************* End of of FinalSetp Page *****************************************/

class ConclusionPage : public QWizardPage
{
    Q_OBJECT

public:
    ConclusionPage(QWidget *parent = 0);

    void initializePage() Q_DECL_OVERRIDE;
    int nextId() const Q_DECL_OVERRIDE;
    void setVisible(bool visible) Q_DECL_OVERRIDE;

private slots:
    void rebootButtonClicked();

private:
    QLabel *bottomLabel;
    QCheckBox *agreeCheckBox;
    QProcess *process;
};

/******************* End of of ConclusionPage Page *****************************************/

#endif // AVOUCHINSTALLER_H

