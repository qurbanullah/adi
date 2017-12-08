#include <QtWidgets>
#include <QtPrintSupport/QPrintDialog>
#include <QFile>
#include <QProcess>
#include <QDebug>
#include <QRect>
#include <QDesktopWidget>

#include "include/AvouchInstaller.h"

//constructor
AvouchInstaller::AvouchInstaller(QWidget *parent)
    : QWizard(parent)
{
    setPage(Page_Start, new StartPage);
    setPage(Page_License, new LicensePage);
    setPage(Page_Partition, new PartitionPage);
    setPage(Page_User, new UserPage);
    setPage(Page_FinalSetup, new FinalSetupPage);
    setPage(Page_Conclusion, new ConclusionPage);

    setStartId(Page_Start);

#ifndef Q_OS_MAC
    setWizardStyle(ModernStyle);
#endif
    setOption(HaveHelpButton, true);

    setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo.png"));
    setPixmap(QWizard::BannerPixmap, QPixmap(":/images/banner.png"));
    setPixmap(QWizard::BackgroundPixmap, QPixmap(":/images/background.png"));

    connect(this, &QWizard::helpRequested, this, &AvouchInstaller::showHelp);

    setWindowTitle(tr("Avouch Linux Installer"));
    setMinimumSize(960, 704);
    setMaximumSize(960, 704);
}

//help function; display help on each page related to that page
void AvouchInstaller::showHelp()
{
    static QString lastHelpMessage;

    QString message;

    switch (currentId()) {
    case Page_Start:
        message = tr("This software let you install <i>Avouch&trade; Linux</i> onto your system.");
        break;
    case Page_License:
        message = tr("This software is distributed under "
                     "<i>GNU General Public License Version 2</i>."
                     " without any waranty."
                     " Please do read the terms and condition of the license");
        break;
    case Page_Partition:
        message = tr("Make sure you select a partion first; "
                     "on which you want to install "
                     "<i>Avouch&trade; Linux</i>");
        break;
    case Page_User:
        message = tr("You have to provide the user credentials here. "
                     "All fields are mandetory.");
        break;
    case Page_FinalSetup:
        message = tr("The setup will take few minutes; depending on your system hardwares. "
                     "Please wait till the installation process completes.");
        break;
    case Page_Conclusion:
        message = tr("If you reach at this page it means that "
                     "<i>Avouch&trade; Linux</i>"
                     "installed successfully");
        break;
    default:
        message = tr("This is littel help about different pages of the <i>Avouch&trade; Distribution Installer</i>.");
    }

    if (lastHelpMessage == message)
        message = tr("Sorry, I already gave what help I could. "
                     "Maybe you should try asking a human?");

    QMessageBox::information(this, tr("Avouch&trade; Installer Help"), message);

    lastHelpMessage = message;
}

StartPage::StartPage(QWidget *parent)
    : QWizardPage(parent)
{

    setTitle(tr("Avouch Linux Installer"));
    setSubTitle(tr("Install the Avouch Linux into the hard disk with simple steps"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/WatermarkPixmapWelcome.png"));

    //set font
     QFont font;
     font.setPointSize(20);
     font.setBold(true);

    Top_Label = new QLabel(tr("This software let you install "
                             "<i>Avouch&trade; Linux</i> "
                             "on to your computer."));
    Top_Label->setWordWrap(true);

    Install_Label = new QLabel("Install Avouch Linux");
    Install_Label->setFont(font);
    Install_Label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    //Install_Label->setMaximumWidth(900);
    //Install_Label->setMinimumWidth(900);
    Install_Label->setPixmap(QPixmap(":/images/watermark1.png"));

    Close_Label = new QLabel("Continue Testing Avouch&trade; Linux");
    Close_Label->setFont(font);
    //Close_Label->setMinimumHeight(600);
    //Close_Label->setMaximumHeight(600);
    Close_Label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);


    Install_Button = new QPushButton("Install");
    Install_Button->setMinimumHeight(300);
    Install_Button->setMaximumHeight(300);
    Install_Button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    Close_Button = new QPushButton("Close");
    Close_Button->setMinimumHeight(300);
    Close_Button->setMaximumHeight(300);
    Close_Button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    horizontalGroupBox1 = new QGroupBox();
    QHBoxLayout *horizontalLayout1 = new QHBoxLayout;

    horizontalLayout1->addWidget(Install_Label);
    horizontalLayout1->addWidget(Close_Label);

    horizontalGroupBox1->setLayout(horizontalLayout1);
    horizontalGroupBox1->setStyleSheet("border:0;");


    horizontalGroupBox2 = new QGroupBox();
    QHBoxLayout *horizontalLayout2 = new QHBoxLayout;

    horizontalLayout2->addWidget(Install_Button);
    horizontalLayout2->addWidget(Close_Button);

    horizontalGroupBox2->setLayout(horizontalLayout2);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    //mainLayout->addWidget(Top_Label);
    mainLayout->addWidget(Install_Label);
    //mainLayout->addWidget(horizontalGroupBox1);
    //mainLayout->addWidget(horizontalGroupBox2);
    setLayout(mainLayout);

    connect(Install_Button, SIGNAL(clicked()), this, SLOT(showLicensePage()));
    connect(Close_Button, SIGNAL(clicked()), this, SLOT(close()));
}

void StartPage::createHorizontalGroupBox()
{
    horizontalGroupBox1 = new QGroupBox(tr("Horizontal layout"));
    QHBoxLayout *horizontalLayout1 = new QHBoxLayout;

    horizontalLayout1->addWidget(Install_Button);
    horizontalLayout1->addWidget(Close_Button);

    horizontalGroupBox1->setLayout(horizontalLayout1);;
}

int StartPage::showLicensePage(){

    return AvouchInstaller::Page_License;
}

int StartPage::nextId() const
{
    return AvouchInstaller::Page_License;
}

LicensePage::LicensePage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("End User License Agreement (EULA)"));
    setSubTitle(tr("Read the Endu Usel License Agreement"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/WatermarkPixmapEula.png"));

    topLabel = new QLabel(tr("This software is distributed under "
                             "<i>GNU General Public License Version 2</i>&trade; "
                             "which is cited below for information."));
    topLabel->setWordWrap(true);

    QFile file("/usr/share/licenses/gnu/gpl-2.0.txt");
    QString line;
    textEdit = new QTextEdit();
    //textEdit->setMinimumHeight(600);
    //textEdit->setMaximumHeight(600);

    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream( &file ); // Set the stream to read from myFile

           while(!stream.atEnd()){

               line = stream.readLine(); // this reads a line (QString) from the file
               //qDebug() << line;
               textEdit->append(line);

               // By default the cursor will be at the end of the file, so the file displayed will be at the end
               // By the following code we take the cursoe at the stat of the file.
               QTextCursor textCursor = textEdit->textCursor();
               textCursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor,1);
               textEdit->setTextCursor(textCursor); // The line to add

           }
      }

    file.close();

    licenseAgreementCheckBox = new QCheckBox(tr("&I have read the license terms and condition and agreed to continue"));
    registerField("evaluate.checkbox*", licenseAgreementCheckBox);
    //licenseAgreementCheckBox->setChecked(true);


    QVBoxLayout *layout = new QVBoxLayout;
    //layout->addWidget(topLabel);
    layout->addWidget(textEdit);
    layout->addWidget(licenseAgreementCheckBox);
    setLayout(layout);
}

int LicensePage::nextId() const
{
    if (licenseAgreementCheckBox->isChecked()) {
        return AvouchInstaller::Page_Partition;
    } else {
        return AvouchInstaller::Page_Partition;
    }
}

/******************* End of of License Page *****************************************/

PartitionPage::PartitionPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("<i>Partition Selection</i>&trade;"));
    setSubTitle(tr("Select the partion to install <i>Avouch&trade;</i> Linux. "
                   "The partition should be greater than 10 GB."));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/WatermarkPixmapDiskSetup.png"));

    QMessageBox *emptyFeildMsgBox = new QMessageBox(this);
    emptyFeildMsgBox->setWindowTitle("Error Massage");
    //emptyFeildMsgBox->setMinimumHeight(200);
    //emptyFeildMsgBox->setMinimumWidth(400);

    gpartedLabel = new QLabel(tr("To edit the disk drive partitions click on "
                             "<i>Edit Partitions</i> button."));
    labelDrives = new QLabel();
    disksTable = new QTableWidget();
    disksTable->setMaximumHeight(150);

    label_selecetedpartition = new QLabel(tr("Selected Partition:"));
    lineEdit_selecetedpartition = new QLineEdit;
    lineEdit_selecetedpartition->setReadOnly(true);
    label_selecetedpartition->setBuddy(lineEdit_selecetedpartition);
    registerField("evaluate.selecetedpartition*", lineEdit_selecetedpartition);

    gpartedLabel->setMinimumHeight(30);
    gpartedLabel->setMaximumHeight(30);
    gpartedLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    gpartedLabel->setMaximumWidth(500);
    gpartedLabel->setMinimumWidth(500);

    gpartedButton = new QPushButton(tr("&Edit Partitions"));
    gpartedButton->setMinimumHeight(30);
    gpartedButton->setMaximumHeight(30);
    gpartedButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    gpartedButton->setMaximumWidth(150);
    gpartedButton->setMinimumWidth(150);

    partitionTable = new QTableWidget();

    process_gparted = new QProcess(this);
    process_findpartition = new QProcess(this);
    process_format = new QProcess(this);
    process_copyfiles = new QProcess(this);
    process_chroot = new QProcess(this);



    //connect(ui->populatePartitions, SIGNAL(clicked()), this, SLOT(umountDrive()));
    connect(gpartedButton, SIGNAL(clicked()), this, SLOT(runGparted()));
    //connect(installButton, SIGNAL(clicked()), this, SLOT(selectedDrive()));
    connect(disksTable, SIGNAL(itemSelectionChanged()), this, SLOT(getPartitions()));
    connect(partitionTable, SIGNAL(itemSelectionChanged()), this, SLOT(selectedPartition()));

    //connect(partitionTable, SIGNAL(runGparted()), this, SLOT(layout->update();));

    findPartitions();
    delay(3000);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(disksTable);
    layout->addWidget(gpartedButton);
    layout->addWidget(partitionTable);
    layout->addWidget(label_selecetedpartition);
    layout->addWidget(lineEdit_selecetedpartition);
    layout->update();

    setLayout(layout);
}

void PartitionPage::delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

void PartitionPage::runGparted(){

    QString program_gparted = "/usr/bin/gparted";
    process_gparted->start("pkexec", QStringList() << program_gparted);

    if (!process_gparted->waitForFinished()){
        qDebug() << "Terminal failed:" << process_gparted->errorString();
    }
    else{
        qDebug() << "Terminal output:" << process_gparted->readAll();
    }

    process_gparted->close();
    program_gparted.clear();

    // after gparted find partition and reload table, as user may change the partitions
    partitionTable->clear();
    findPartitions();
    //delay(3000);
    partitionTable->repaint();
    qApp->processEvents();
}

void PartitionPage::findDisks(){

    QString finddisks = "/usr/bin/findpartitions";

    QFile file("/tmp/partitions.txt");

    if (!file.exists()){
        qDebug() << "File does not exists";
        process_finddisks->start("pkexec", QStringList() << finddisks);
    }
    else{
        qDebug() << "File exists";
        file.remove();
        process_finddisks->start("pkexec", QStringList() << finddisks);
    }

    process_finddisks->waitForFinished(-1);
    getDisks();
    //getPartitions();


}

void PartitionPage::findPartitions(){

    QString find_partition = "/usr/bin/findpartitions";

    QFile file("/tmp/partitions.txt");

    if (!file.exists()){
        qDebug() << "File does not exists";
        process_findpartition->start("pkexec", QStringList() << find_partition);
    }
    else{
        qDebug() << "File exists";
        file.remove();
        process_findpartition->start("pkexec", QStringList() << find_partition);
    }

    process_findpartition->waitForFinished(-1);
    getDisks();
    //getPartitions();


}

void PartitionPage::getDisks(){

    QFile file("/tmp/disks.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!file.atEnd()) {
            QString disks = file.readLine();
            //qDebug() << disks;
            processDisks(disks);
        }
    file.close();
}

void PartitionPage::processDisks(QString disks){
    QStringList totalDisks = disks.split(":");
    qDebug() << totalDisks;
    //labelDrives->setText(totalDisks);

    //qDebug() << partitions.count();
    static int row = 0;
    if(disksTable->rowCount() < (row + 1))
        disksTable->setRowCount(row + 1);

    // we only want to dispay first 7 column only
    //if(partitionTable->columnCount() < partitions.size())
    //    partitionTable->setColumnCount( partitions[0].size() );

    //Set Header Label Texts Here
    // set the columncount to 7 as we only want to display first 7 column
    disksTable->setColumnCount(3);
    disksTable->setColumnWidth(0, 240);
    disksTable->setColumnWidth(1, 240);
    disksTable->setColumnWidth(2, 240);

    disksTable->setHorizontalHeaderLabels(QString("Model; Disks;Size;").split(";"));

    for( int column = 0; column < 3; column++){
        QTableWidgetItem *newItem = new QTableWidgetItem( totalDisks.at(column) );
        disksTable->setItem(row, column, newItem);
    }
    row++;
    disksTable->setAlternatingRowColors(true);
    disksTable->setSelectionBehavior(QAbstractItemView::SelectRows);

}

QString PartitionPage::selectedDisk(){

    QItemSelectionModel *selmodel = disksTable->selectionModel();
    QModelIndex current = selmodel->currentIndex(); // the "current" item
    //QModelIndexList selected = selmodel->selectedIndexes(); // list of "selected" items
    emptyFeildMsgBox = new QMessageBox(this);

    int row = disksTable->currentRow();
    seleceted_disk = current.sibling(row, 1).data().toString();

    if (!seleceted_disk.isEmpty()){
        qDebug() << seleceted_disk;
        //formatDrive();
    }
    else{
        emptyFeildMsgBox->setText("Please! select a disk first");
        emptyFeildMsgBox->setStandardButtons(QMessageBox::Ok);
        emptyFeildMsgBox->exec();
    }
    //for (int i = 0; i < selected.size(); i++) {
    //    qDebug() << selected.value(i).sibling(row, 0).data();
    //}


    //lineEdit_selecetedpartition->setText(selecetedpartition);


    return seleceted_disk;

}

void PartitionPage::getPartitions(){

    partitionTable->clear();
    int line_count = 0;
    QFile file("/tmp/partitions.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!file.atEnd()) {
            QString line = file.readLine();            
            line_count++;
            qDebug() << line_count;
            processPartitions(line, line_count);
        }
    file.close();
}


void PartitionPage::processPartitions(QString line, int numberOfRows)
{
    int row = 0;
    QStringList partitions = line.split(":");
    qDebug() << numberOfRows;

    //qDebug() << partitions.count();

    if(partitionTable->rowCount() < (row + 1))
        partitionTable->setRowCount(row + 1);

    // we  want to dispay first 7 columns only
    //if(partitionTable->columnCount() < partitions.size())
    //    partitionTable->setColumnCount( partitions[0].size() );

    // Set Header Label Texts Here
    // set the columncount to 7 as we only want to display first 7 column
    partitionTable->setColumnCount(7);
    partitionTable->setColumnWidth(0, 120);
    partitionTable->setColumnWidth(1, 120);
    partitionTable->setColumnWidth(2, 120);
    partitionTable->setColumnWidth(3, 120);
    partitionTable->setColumnWidth(4, 120);
    partitionTable->setColumnWidth(5, 120);
    partitionTable->setColumnWidth(6, 120);

    partitionTable->setHorizontalHeaderLabels(QString("Partition; Start Sector; End Sector; Total Sectors; Partition Size; Partition ID; File System").split(";"));

    for( int column = 0; column < partitionTable->columnCount(); column++){
        QTableWidgetItem *newItem = new QTableWidgetItem();
        newItem->setText(partitions.at(column));
        partitionTable->setItem(row, column, newItem);
        newItem->setTextAlignment(Qt::AlignCenter);
    }
    row++;
    partitionTable->setAlternatingRowColors(true);
    partitionTable->setSelectionBehavior(QAbstractItemView::SelectRows);

}

QString PartitionPage::selectedPartition(){

    QItemSelectionModel *selmodel = partitionTable->selectionModel();
    QModelIndex current = selmodel->currentIndex(); // the "current" item
    //QModelIndexList selected = selmodel->selectedIndexes(); // list of "selected" items
    emptyFeildMsgBox = new QMessageBox(this);

    int row = partitionTable->currentRow();
    selecetedpartition = current.sibling(row, 0).data().toString();

    if (!selecetedpartition.isEmpty()){
        qDebug() << selecetedpartition;
        //formatDrive();
    }
    else{
        emptyFeildMsgBox->setText("Please! select a drive first");
        emptyFeildMsgBox->setStandardButtons(QMessageBox::Ok);
        emptyFeildMsgBox->exec();
    }
    //for (int i = 0; i < selected.size(); i++) {
    //    qDebug() << selected.value(i).sibling(row, 0).data();
    //}


    lineEdit_selecetedpartition->setText(selecetedpartition);


    return selecetedpartition;

}

void PartitionPage::formatDrive(){

    int retValue = formatMessageBox();
    QProgressDialog pd("Formating partition...", QString(), 0, 0);
    pd.setWindowTitle("Formating partition");
    pd.setMinimumWidth(400);
    pd.setMinimumHeight(100);

    //QString program_format = "sudo /usr/bin/mkfs.ext4 " + selecetedpartition;

    //qDebug() << "Formating drive: " << program_format;

    if(retValue == QMessageBox::No){
        qDebug() << "Terminal output:" << "User pressed No";
    }
    else if(retValue == QMessageBox::Yes){
        qDebug() << "Terminal output:" << "User pressed Yes";

        //process_format->start(program_format);

        //connect(process_format, SIGNAL(finished(int, QProcess::ExitStatus)), &pd, SLOT(accept()));
        //connect(process_format, SIGNAL(readyReadStandardOutput()), this, SLOT(readTerminalData()));

        //pd.exec();
        //readTerminalData();
        //process_format->waitForFinished(-1);
        //pd.autoClose();


        //CopyFilesWindow *cfw = new CopyFilesWindow;
        //this->hide();
        //cfw->show();
        //cfw->copyFiles(selecetedpartition);

        //UserWindow *uw = new UserWindow;
        //this->hide();
        //uw->show();
        //uw->getPartition(selecetedpartition);



     }
}

int PartitionPage::formatMessageBox(){

    QMessageBox *foematMsgBox = new QMessageBox(this);
    foematMsgBox->setText("This will erase all data from the selected partition. Do you want to continue...?");
    foematMsgBox->setInformativeText("Please! backup data before proceeding.");
    foematMsgBox->setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    foematMsgBox->setDefaultButton(QMessageBox::Yes);
    int retValue = foematMsgBox->exec();
    return retValue;

}

void PartitionPage::finishMsg(){

   qDebug() << "Exit status code is:" << process_chroot->exitStatus();

   // yet not fixed
    if (process_chroot->exitStatus()==0){
        QMessageBox::information(this, "", "Avouch Linux installed successfully. \nRestart your computer and remove any USB or DVD.");

    }
    else if (process_chroot->error()){
        QMessageBox::information(this, "", "Some error occured");
    }
    this->hide();
}


void PartitionPage::readTerminalData(){

    QByteArray data = process_format->readAllStandardOutput();
    qDebug() << "Terminal output:" << data;
    //ui->textEdit->insertPlainText(data);
    //ui->textEdit->append(QString(data));

}

int PartitionPage::nextId() const {

    if (selecetedpartition.isEmpty()) {
        return AvouchInstaller::Page_Partition;

    } else {
        return AvouchInstaller::Page_User;
    }
}

/******************* End of of Partition Page *****************************************/

UserPage::UserPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("User Credential Page"));
    setSubTitle(tr("Enter the user credentials. The user you add here will be the <i>Administrator</i>&trade; "
                   "of the computer."));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/WatermarkPixmapUserSetup.png"));

    emptyFeildMsgBox = new QMessageBox(this);
    emptyFeildMsgBox->setWindowTitle("Error Massage");
    emptyFeildMsgBox->setMinimumHeight(200);
    emptyFeildMsgBox->setMinimumWidth(400);

    label_fullname = new QLabel(tr("Full Name:"));
    lineEdit_fullname = new QLineEdit;
    lineEdit_fullname->setMaximumWidth(500);
    label_fullname->setBuddy(lineEdit_fullname);

    label_username = new QLabel(tr("User Name:"));
    lineEdit_username = new QLineEdit;
    lineEdit_username->setMaximumWidth(500);
    lineEdit_username->setValidator(new QRegExpValidator(QRegExp("[\\w\\d_ \\.]{24}"), this));
    label_username->setBuddy(lineEdit_username);

    label_password = new QLabel(tr("Password:"));
    lineEdit_password = new QLineEdit;
    lineEdit_password->setMaximumWidth(500);
    lineEdit_password->setEchoMode( QLineEdit::Password );
    label_password->setBuddy(lineEdit_password);

    label_repassword = new QLabel(tr("Enter Pssword again:"));
    lineEdit_repassword = new QLineEdit;
    lineEdit_repassword->setMaximumWidth(500);
    lineEdit_repassword->setEchoMode( QLineEdit::Password );
    label_repassword->setBuddy(lineEdit_repassword);

    label_missmatch = new QLabel(tr(""));

    label_hostname = new QLabel(tr("Computer/Host Name:"));
    lineEdit_hostname = new QLineEdit;
    lineEdit_hostname->setMaximumWidth(500);
    label_hostname->setBuddy(lineEdit_hostname);

    label_rootpasswd = new QLabel(tr("Root Password:"));
    lineEdit_rootpasswd = new QLineEdit;
    lineEdit_rootpasswd->setMaximumWidth(500);
    lineEdit_rootpasswd->setEchoMode( QLineEdit::Password );
    label_rootpasswd->setBuddy(lineEdit_rootpasswd);

    label_rootrepasswd = new QLabel(tr("Enter Root Password again:"));
    lineEdit_rootrepasswd = new QLineEdit;
    lineEdit_rootrepasswd->setMaximumWidth(500);
    lineEdit_rootrepasswd->setEchoMode( QLineEdit::Password );
    label_rootrepasswd->setBuddy(lineEdit_rootrepasswd);
    label_rootmissmatch = new QLabel(tr(""));


    registerField("evaluate.fullname*", lineEdit_fullname);
    registerField("evaluate.username", lineEdit_username);
    registerField("evaluate.password*", lineEdit_password);
    registerField("evaluate.repassword*", lineEdit_repassword);
    registerField("evaluate.hostname*", lineEdit_hostname);
    registerField("evaluate.rootpasswd*", lineEdit_rootpasswd);
    registerField("evaluate.rootrepasswd*", lineEdit_rootrepasswd);

    QGridLayout *layout = new QGridLayout;

    layout->addWidget(label_fullname, 0, 0);
    layout->addWidget(lineEdit_fullname, 0, 1);

    layout->addWidget(label_username, 1, 0);
    layout->addWidget(lineEdit_username, 1, 1);

    layout->addWidget(label_password, 2, 0);
    layout->addWidget(lineEdit_password, 2, 1);

    layout->addWidget(label_repassword, 3, 0);
    layout->addWidget(lineEdit_repassword, 3, 1);

    layout->addWidget(label_missmatch, 3, 2);

    layout->addWidget(label_hostname, 4, 0);
    layout->addWidget(lineEdit_hostname, 4, 1);

    layout->addWidget(label_rootpasswd, 5, 0);
    layout->addWidget(lineEdit_rootpasswd, 5, 1);

    layout->addWidget(label_rootrepasswd, 6, 0);
    layout->addWidget(lineEdit_rootrepasswd, 6, 1);
    layout->addWidget(label_rootmissmatch, 6, 2);

    setLayout(layout);

    connect(lineEdit_fullname,
            SIGNAL(textChanged(const QString &)),
            this,
            SLOT(on_lineEdit_fullname_textEdited(const QString &)));

    connect(lineEdit_repassword,
            SIGNAL(textChanged(const QString &)),
            this,
            SLOT(check_password_mismatch(const QString &)));

    connect(lineEdit_rootrepasswd,
            SIGNAL(textChanged(const QString &)),
            this,
            SLOT(check_root_password_mismatch(const QString &)));

}

// This function will get the username with out spaces and to lower case,
// while user enter its full name
void UserPage::on_lineEdit_fullname_textEdited(const QString){

    //The first changes all whitespace characters to a single instance of ASCII 32, the second removes that.
    // This may also be implemented by QString::remove(' ') or QString::remove(" ")
    lineEdit_username->setText(lineEdit_fullname->text().toLower().replace(" ",""));
    lineEdit_hostname->setText(lineEdit_fullname->text().toLower().replace(" ","") + "-pc");
    //label_admin->show();

}

// This function will get the username with out spaces and to lower case,
// while user enter its full name
void UserPage::check_password_mismatch(const QString){

   if(field("evaluate.password") == field("evaluate.repassword")){
        qDebug() << "Terminal output:" << "Password matched.";
        label_missmatch->setText("<i>Password matched.</i>");
        label_missmatch->setStyleSheet("color: green;");
    }
    else{
       qDebug() << "Terminal output:" << "Password missmatch.";
       label_missmatch->setText("<i>Password missmatch.</i>");
       label_missmatch->setStyleSheet("color: red;");
   }

}

// This function will get the username with out spaces and to lower case,
// while user enter its full name
void UserPage::check_root_password_mismatch(const QString){

   if(field("evaluate.rootpasswd") == field("evaluate.rootrepasswd")){
        qDebug() << "Terminal output:" << "Password matched.";
        label_rootmissmatch->setText("<i>Password matched.</i>");
        label_rootmissmatch->setStyleSheet("color: green;");
    }
    else{
       qDebug() << "Terminal output:" << "Password missmatch.";
       label_rootmissmatch->setText("<i>Password mismatch.</i>");
       label_rootmissmatch->setStyleSheet("color: red;");
   }

}

int UserPage::nextId() const {

    if(field("evaluate.password") != field("evaluate.repassword")){

        qDebug() << "Terminal output:" << "Password missmatch.";
        emptyFeildMsgBox->setText("Password missmatch. Please! enter password correctly.");
        emptyFeildMsgBox->setStandardButtons(QMessageBox::Ok);
        emptyFeildMsgBox->exec();
        lineEdit_password->clear();
        lineEdit_repassword->clear();
        return AvouchInstaller::Page_User;
    }
    else if(field("evaluate.rootpasswd") != field("evaluate.rootrepasswd")){

        qDebug() << "Terminal output:" << "Password for root missmatch.";
        emptyFeildMsgBox->setText("Password for root missmatch. Please! enter password correctly.");
        emptyFeildMsgBox->setStandardButtons(QMessageBox::Ok);
        emptyFeildMsgBox->exec();
        lineEdit_rootpasswd->clear();
        lineEdit_rootrepasswd->clear();
        return AvouchInstaller::Page_User;
}

    else {
        return AvouchInstaller::Page_FinalSetup;
    }

}

/******************* End of of User Page *****************************************/

FinalSetupPage::FinalSetupPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Final Setup Page"));
    setSubTitle(tr("Final installation is in progress. This will take few minutes "
                   "depending upon system hardwares"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/WatermarkPixmapCopyingFiles.png"));

    topLabel = new QLabel(tr("Installation Progress:"));
    progressBar = new QProgressBar(this);
    progressBar->setMinimum(0);
    progressBar->setMaximum(0);
    //progressBar->setValue(0);
    progressBar->setVisible(true);
    value=0;

    topLabel->setWordWrap(true);
    pictureLabel = new QLabel();
    pictureLabel->setMaximumSize(1000,600);
    pictureLabel->setPixmap(QPixmap(":/images/1.png"));
    textEdit_showProcess = new QTextEdit;

    label_procfinished = new QLabel();
    lineEdit_procfinished = new QLineEdit;
    //label_procfinished->setBuddy(lineEdit_procfinished);
    registerField("evaluate.procfinished*", label_procfinished);



    QVBoxLayout *layout = new QVBoxLayout;
    //layout->addWidget(topLabel);
    //layout->addWidget(progressBar);
    layout->addWidget(pictureLabel);
    layout->addWidget(textEdit_showProcess);
    layout->addWidget(label_procfinished);
    layout->addWidget(lineEdit_procfinished);
    setLayout(layout);

}

void FinalSetupPage::initializePage(){

    QProgressDialog pd("Finalizing settings. Please! wait...", QString(), 0, 0);
    pd.setWindowTitle("Final Settings");
    pd.setMinimumWidth(400);
    pd.setMinimumHeight(100);

    instPartition = field("evaluate.selecetedpartition").toString();
    fullname = field("evaluate.fullname").toString();
    username = field("evaluate.username").toString();
    password = field("evaluate.password").toString();
    repassword = field("evaluate.repassword").toString();
    hostname = field("evaluate.hostname").toString();
    rootpasswd = field("evaluate.rootpasswd").toString();
    rootrepasswd = field("evaluate.rootrepasswd").toString();

    qDebug() << "Imported Partition is: " << instPartition;
    qDebug() << "Imported username is: " << username;
    qDebug() << "Imported password is: " << password;
    qDebug() << "Imported hostname is: " << hostname;
    qDebug() << "Imported fullname is: " << fullname;
    qDebug() << "Imported root password is: " << rootpasswd;

    timer1 = new QTimer(this);
    timer1->start(30000);
    connect(timer1, SIGNAL(timeout()), this, SLOT(animateImages()));
    connect(progressBar, SIGNAL(valueChanged(int)), this, SLOT(handleTimeOut()));

    process_final_setup = new QProcess;
    QString program_final_setup = "sudo /usr/bin/adiscript " + instPartition + " " + username + " " + password + " " + rootpasswd + " " + hostname + " " + fullname;
    qDebug() << "chroot options are: " << program_final_setup;

    int retValue = formatMessageBox();


        if(retValue == QMessageBox::No){
            qDebug() << "Terminal output:" << "User pressed No";
            wizard()->close();

        }
        else if(retValue == QMessageBox::Yes){

            qDebug() << "Terminal output:" << "User pressed Yes, Starting terminal process...";
            process_final_setup->start(program_final_setup);


            connect(process_final_setup, SIGNAL(readyReadStandardOutput()), this, SLOT(readTerminalData()));
            connect(process_final_setup, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(SlotDetectFinish()));

            //connect(process_final_setup, SIGNAL(finished(int, QProcess::ExitStatus)), &pd, SLOT(accept()));
            //connect(process_final_setup, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(SlotDetectFinish(int *exitCode, QProcess::ExitStatus *exitSatus)));
         }

    //label_procfinished->setText("Installation completed");

    pd.exec();
    pd.autoClose();
    process_final_setup->waitForFinished(-1);
}

int FinalSetupPage::formatMessageBox(){

    QMessageBox *foematMsgBox = new QMessageBox(this);
    foematMsgBox->setText("This will erase all data from the partition <b>" + instPartition + "</b>. Please! backup your data before proceeding.");
    foematMsgBox->setInformativeText("Do you want to continue...?");
    foematMsgBox->setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    foematMsgBox->setDefaultButton(QMessageBox::Yes);
    int retValue = foematMsgBox->exec();
    return retValue;

}

void FinalSetupPage::readTerminalData(){

    QByteArray data = process_final_setup->readAllStandardOutput();
    qDebug() << "Terminal output:" << data;
    //ui->textEdit->insertPlainText(data);
    textEdit_showProcess->append(QString(data));

}

void FinalSetupPage::delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

void FinalSetupPage::animateImages(){

    QStringList fileList;
    fileList << ":/images/1.png" << ":/images/2.png" << ":/images/3.png" << ":/images/4.png" << ":/images/5.png";

    for(int i=0; i < fileList.size(); ++i){

       QImage image1(fileList[i]);
       pictureLabel->setPixmap(QPixmap::fromImage(image1));
       delay(5000);
     }
}

void FinalSetupPage::handleTimeOut()
{
     for(value=1; value < 100; value++){
        progressBar->setValue(value);        
        delay(10000);
      }
}

void FinalSetupPage::SlotDetectFinish(){
    //qDebug() << "Exit Code is: " << exitCode;
    //qDebug() << "Exit Status is: " << exitSatus;
    label_procfinished->setText("Installation completed, you may now proceed");
    label_procfinished->setStyleSheet("color: green;");
    progressBar->setValue(100);
    progressBar->close();
}
int FinalSetupPage::nextId() const{

    //if (process_final_setup->waitForFinished(-1)){
        return AvouchInstaller::Page_Conclusion;
    //}
    //else{
    //    return AvouchInstaller::Page_FinalSetup;
    //}
}

/******************* End of of Final Setup Page *****************************************/

ConclusionPage::ConclusionPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Installation completed"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/WatermarkPixmapCompleted.png"));

    bottomLabel = new QLabel;
    bottomLabel->setWordWrap(true);

    //agreeCheckBox = new QCheckBox(tr("Reboot Computer"));

    //registerField("conclusion.agree", agreeCheckBox);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(bottomLabel);
    //layout->addWidget(agreeCheckBox);
    setLayout(layout);
}

int ConclusionPage::nextId() const
{
    return -1;
}

void ConclusionPage::initializePage()
{
    QString licenseText;

    if (wizard()->hasVisitedPage(AvouchInstaller::Page_FinalSetup)) {
        licenseText = tr("<u>Avouch&trade; Linux:</u> "
                         "Installed successfully. Now you can restart your computer.");
    } else {
        licenseText = tr("<u>Avouch&trade; Linux:</u> "
                         "installation is not seccessfull.");
    }

    bottomLabel->setText(licenseText);


}

void ConclusionPage::setVisible(bool visible)
{
    QWizardPage::setVisible(visible);

    if (visible) {
        wizard()->setButtonText(QWizard::CustomButton1, tr("&Reboot"));
        wizard()->setOption(QWizard::HaveCustomButton1, true);
        connect(wizard(), &QWizard::customButtonClicked,
                this, &ConclusionPage::rebootButtonClicked);
    } else {
        wizard()->setOption(QWizard::HaveCustomButton1, false);
        disconnect(wizard(), &QWizard::customButtonClicked,
                   this, &ConclusionPage::rebootButtonClicked);
    }
}

void ConclusionPage::rebootButtonClicked()
{
    QProcess process;
    qDebug() << "Rebooting System...";
    process.startDetached("sudo /usr/bin/shutdown -r now");

}

