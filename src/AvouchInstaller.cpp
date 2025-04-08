#include <QtWidgets>
#include <QtPrintSupport/QPrintDialog>
#include <QFile>
#include <QProcess>
#include <QDebug>
#include <QRect>
#include <QFileSystemWatcher>

#include "include/AvouchInstaller.h"

//constructor
AvouchInstaller::AvouchInstaller(QWidget *parent)
    : QWizard(parent)
{
    setPage(Page_Start, new StartPage);
    setPage(Page_License, new LicensePage);
    setPage(Page_Disk, new DiskPage);
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




//    QPainter paint(this);
//    paint.drawText(QPoint(10,30),"white");
//    QPen pen  = (QApplication::palette().text().color());

//    paint.setPen(pen);
}

//help function; display help on each page related to that page
void AvouchInstaller::showHelp()
{
    static QString lastHelpMessage;

    QString message;

    switch (currentId()) {
    case Page_Start:
        //message = tr("This software let you install <i>Avouch&trade; Linux</i> on to your system.");
        message = tr("This software let you install Avouch on to your system.");
        break;
    case Page_License:
        message = tr("This software is distributed under "
                     "<i>GNU General Public License Version 2</i>."
                     " without any waranty."
                     " Please do read the terms and condition of the license");
        break;
    case Page_Disk:
        message = tr("Make sure you select a disk first; "
                     "on which you want to install Avouch");
        break;
    case Page_Partition:
        message = tr("Make sure you select a Upartition first; "
                     "on which you want to install Avouch");
        break;
    case Page_User:
        message = tr("You have to provide the user credentials here. "
                     "All fields are mandetory.");
        break;
    case Page_FinalSetup:
        message = tr("The processes will take few minutes; depending on your system hardwares. "
                     "Please wait till the process completes.");
        break;
    case Page_Conclusion:
        message = tr("If you reach at this page it means that "
                     "Avouch installed successfully");
        break;
    default:
        message = tr("This is littel help about different pages of the Avouch Distribution Installer</i>.");
    }

    if (lastHelpMessage == message)
        message = tr("Sorry, I already gave what help I could. "
                     "Maybe you should try asking a human?");

    QMessageBox::information(this, tr("Avouch&trade; Distribution Installer help"), message);

    lastHelpMessage = message;
}

StartPage::StartPage(QWidget *parent)
    : QWizardPage(parent)
{

    //qDebug() << "Reached hee in Start page";
    setTitle(tr("Avouch Installer"));
    setSubTitle(tr("Install Avouch Linux with simple steps"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/WatermarkPixmapWelcome.png"));

    //set font
     QFont font;
     font.setPointSize(20);
     font.setBold(true);

    Top_Label = new QLabel(tr("This software let you install "
                             "<i>Avouch&trade; Linux</i> "
                             "onto your system."));
    Top_Label->setWordWrap(true);

    pictureLabel = new QLabel();
    //pictureLabel->setMaximumSize(1000,600);
    pictureLabel->setPixmap(QPixmap(":/images/welcome.png"));

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
    mainLayout->addWidget(pictureLabel);
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

    horizontalGroupBox1->setLayout(horizontalLayout1);
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
    //licenseAgreementCheckBox->setStyleSheet("border: 1px solid white;");
    registerField("evaluate.checkbox*", licenseAgreementCheckBox);
    //licenseAgreementCheckBox->setChecked(true);
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
        return AvouchInstaller::Page_Disk;
    } else {
        return AvouchInstaller::Page_Disk;
    }
}

/******************* End of of License Page *****************************************/

DiskPage::DiskPage(QWidget *parent)
    : QWizardPage(parent)
{
    //qDebug() << "Reached hee in Disk page";
    setTitle(tr("Disk Selection"));
    setSubTitle(tr("Select the disk drive to install <i>Avouch&trade;</i>."));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/WatermarkPixmapDiskSetup.png"));

    QMessageBox *emptyFeildMsgBox = new QMessageBox(this);
    emptyFeildMsgBox->setWindowTitle("Error Massage");


    gpartedLabel = new QLabel(tr("To edit the disk drive partitions click on "
                             "<i>Edit Partitions</i> button."));
    labelDrives = new QLabel();
    disksTable = new QTableWidget();


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

    showDisksTable();
    //(1000);

    connect(gpartedButton, SIGNAL(clicked()), this, SLOT(runGparted()));
    connect(disksTable, SIGNAL(itemSelectionChanged()), this, SLOT(selectedDisk()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(gpartedButton);
    layout->addWidget(disksTable);
    setLayout(layout);
}

void DiskPage::delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

void DiskPage::runGparted(){

    //QString program_gparted = "/usr/bin/gparted";
    QString program = "pkexec";
    QStringList arguments;
    arguments << "/usr/bin/gparted";
    QProcess *run_gparted = new QProcess();

    run_gparted->start(program, arguments);

    if (!run_gparted->waitForFinished()){
        qDebug() << "Terminal failed:" << run_gparted->errorString();
    }
    else{
        qDebug() << "Terminal output:" << run_gparted->readAll();
    }

    run_gparted->close();
    run_gparted->waitForFinished(-1);

}
// function used to get all the disks installed in the system

QString DiskPage::getDisks(){

    //QString find_disks = "/usr/bin/finddisks";
    QString program = "sh";
    QStringList arguments;

    // popolate the disks name, size and model witk lsblk command
    // replace sd with /dev/sd by using sed command
    // replace hd with /dev/hd by using sed command
    // replace all sapces with : by using sed command
    // replace all :: with :
    arguments << "-c" << "lsblk -Sno NAME,SIZE,MODEL | sed -e '/sr0/d' | sed 's,^sd,/dev/sd,g' | sed 's,^hd,/dev/hd,g' |sed -e 's/ /:/g' | sed -e 's/:::/:/g' | sed -e 's/::/:/g'";
    QProcess *get_disks = new QProcess();
    get_disks->start(program, arguments);
    get_disks->waitForFinished(-1);

    // read the shell outpu and store in a variable
    QString disks = get_disks->readAllStandardOutput();
    return disks;
}

void DiskPage::showDisksTable()
{
    QString disks = getDisks();
    //qDebug() << disks;

    QStringList diskList = disks.split("\n", Qt::SkipEmptyParts);
    //qDebug() << diskList;

    qDebug() << "Total disks found are : " << diskList.size();

    if(disksTable->rowCount() < (diskList.size() + 1))
        disksTable->setRowCount(diskList.size());

    //Set Header Label Texts Here
    // set the columncount to 3 as we only want to display first 3 column
    disksTable->setColumnCount(3);
    disksTable->setColumnWidth(0, 200);
    disksTable->setColumnWidth(1, 200);
    disksTable->setColumnWidth(2, 340);
    disksTable->setRowHeight(0, 64);
    disksTable->setRowHeight(1, 64);
    disksTable->setRowHeight(2, 64);
    disksTable->setRowHeight(3, 64);
    disksTable->setRowHeight(4, 64);
    disksTable->setRowHeight(5, 64);
    disksTable->setRowHeight(6, 64);

    disksTable->setHorizontalHeaderLabels(QString("Disks; Size; Model").split(";"));

    int row = 0;

    for (int i = 0; i < diskList.size(); i++)
    {
        QString disk =  diskList[i];
        QStringList currentDisk = disk.split(":");

        for (int cols = 0; cols < currentDisk.size(); cols++)
        {
            QTableWidgetItem *newItem = new QTableWidgetItem();
            newItem->setTextAlignment(Qt::AlignCenter);
            newItem->setText(currentDisk.at(cols));

            disksTable->setItem(row, cols, newItem);
        }

        row++;
    }
    //disksTable->setStyleSheet("border: 1px solid white;");
    //disksTable->setAlternatingRowColors(true);
    disksTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    //findPartitions();
}

void DiskPage::selectedDisk()
{
    QFile adi_conf_file("/tmp/adi.conf");
//    QString program1 = "sudo";
//    QStringList arguments1;
//    arguments1 << "/usr/bin/rm" << "/tmp/partitions.txt";
//    process_rm = new QProcess();
    //QString rmfile = "sudo /usr/bin/rm /tmp/partitions.txt";

    // delete the file to ensure than no previous configuration are stored
    if (adi_conf_file.exists())
    {
        adi_conf_file.remove();
    }
    QItemSelectionModel *selmodel = disksTable->selectionModel();
    QModelIndex current = selmodel->currentIndex(); // the "current" item
    //QModelIndexList selected = selmodel->selectedIndexes(); // list of "selected" items
    emptyFeildMsgBox = new QMessageBox(this);

    int row = disksTable->currentRow();
    seleceted_disk = current.sibling(row, 0).data().toString();

    if (!seleceted_disk.isEmpty())
    {
        qDebug() << "Selected Disk is : " << seleceted_disk;
        //qDebug() << "Selected disk in find partition is : " + seleceted_disk;
        //QString find_partition = "sudo /usr/bin/findpartitions " + seleceted_disk;
        //QString filename = "/tmp/disk.conf";
        //QFile file(filename);

        /*for writing line by line to text file */
        if (adi_conf_file.open(QIODevice::ReadWrite))
        {
            QTextStream stream(&adi_conf_file);
            stream << "DISK" << "=" << seleceted_disk << Qt::endl;
        }
        adi_conf_file.close();

        // run the script to get all the partitions of the slected disk
        QString program2 = "sudo";
        QStringList arguments2;
        arguments2 << "/usr/bin/findpartitions" << seleceted_disk;
        process_findpartition = new QProcess();
        process_findpartition->start(program2, arguments2);
    }
    else
    {
        emptyFeildMsgBox->setText("Please! select a disk first");
        emptyFeildMsgBox->setStandardButtons(QMessageBox::Ok);
        emptyFeildMsgBox->exec();
    }
    //for (int i = 0; i < selected.size(); i++) {
    //    qDebug() << selected.value(i).sibling(row, 0).data();
    //}

    //lineEdit_seleceted_disk->setText(seleceted_disk);
    //find_partitions->waitForFinished(-1);

    //return seleceted_disk;
}

int DiskPage::nextId() const {

    if (seleceted_disk.isEmpty()) {
        return AvouchInstaller::Page_Disk;
    } else {
        return AvouchInstaller::Page_Partition;
    }
}

/******************* End of of Disk Page *****************************************/

PartitionPage::PartitionPage(QWidget *parent)
    : QWizardPage(parent)
{
    //() << "Reached hee in Partition page";
    setTitle(tr("Partition Selection"));
    setSubTitle(tr("Select the partition to install Avouch. "
                   "The partition should be greater than 15 GB."));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/WatermarkPixmapPartitionSetup.png"));

    QMessageBox *emptyFeildMsgBox = new QMessageBox(this);
    emptyFeildMsgBox->setWindowTitle("Error Massage");
    //emptyFeildMsgBox->setMinimumHeight(200);
    //emptyFeildMsgBox->setMinimumWidth(400);


    label_selecetedpartition = new QLabel(tr("Selected Partition:"));
    lineEdit_selecetedpartition = new QLineEdit;
    lineEdit_selecetedpartition->setReadOnly(true);
    //lineEdit_selecetedpartition->setStyleSheet("border: 1px solid white");
    label_selecetedpartition->setBuddy(lineEdit_selecetedpartition);
    registerField("evaluate.selecetedpartition*", lineEdit_selecetedpartition);

    partitionTable = new QTableWidget();

    process_format = new QProcess(this);
    process_copyfiles = new QProcess(this);
    process_chroot = new QProcess(this);

    connect(partitionTable, SIGNAL(itemSelectionChanged()), this, SLOT(selectedPartition()));

    QGridLayout *grid = new QGridLayout;
    grid->addWidget(createRadioButtonExclusiveGroup(), 0, 0);
    grid->addWidget(partitionTable);
    grid->addWidget(label_selecetedpartition);
    grid->addWidget(lineEdit_selecetedpartition);

    setLayout(grid);
    partitionTable->setVisible(false);


}
QGroupBox *PartitionPage::createRadioButtonExclusiveGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("Select the option to install Avouch, feasible to you."));
    radioButton1 = new QRadioButton(tr("Create only &one partition and install Avouch."));
    radioButton2 = new QRadioButton(tr("Create &two partitions of equal size and install Avouch on first partition."));
    radioButton3 = new QRadioButton(tr("Show me the &partitions, I will select manually (partitions will be displyeed if available)"));

    //radioButton3->setChecked(true);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radioButton1);
    vbox->addWidget(radioButton2);
    vbox->addWidget(radioButton3);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);
    return groupBox;
}

void PartitionPage::delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

void PartitionPage::initializePage(){

    connect(radioButton1, SIGNAL(clicked()), this, SLOT(radioButton1Clicked()));
    connect(radioButton2, SIGNAL(clicked()), this, SLOT(radioButton2Clicked()));
    connect(radioButton3, SIGNAL(clicked()), this, SLOT(radioButton3Clicked()));

    //partitionTable->clear();
    int partitions_count = 0;
    QFile file("/tmp/partitions.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!file.atEnd()) {
            QString line = file.readLine();
            partitions_count++;
            //qDebug() << line;
            showPartitionsTable(line, partitions_count);
        }
    file.close();
    file.remove();
}


void PartitionPage::showPartitionsTable(QString line, int numberOfPartitions)
{
    partitionTable->repaint();
    //int row = 0;
    QStringList partitions = line.split(":");
    //qDebug() << numberOfPartitions;

    //qDebug() << partitions.count();

    if(partitionTable->rowCount() < (numberOfPartitions + 1))
        partitionTable->setRowCount(numberOfPartitions);

    // we  want to dispay first 7 columns only
    //if(partitionTable->columnCount() < partitions.size())
    //    partitionTable->setColumnCount( partitions[0].size() );

    // Set Header Label Texts Here
    // set the columncount to 7 as we only want to display first 7 column
    partitionTable->setColumnCount(7);
    partitionTable->setColumnWidth(0, 110);
    partitionTable->setColumnWidth(1, 110);
    partitionTable->setColumnWidth(2, 110);
    partitionTable->setColumnWidth(3, 110);
    partitionTable->setColumnWidth(4, 100);
    partitionTable->setColumnWidth(5, 100);
    partitionTable->setColumnWidth(6, 100);

    partitionTable->setHorizontalHeaderLabels(QString("Partition; Start Sector; End Sector; Total Sectors; Partition Size; Partition ID; File System; ").split(";"));
    for( static int row = 0; row < partitionTable->rowCount(); ++row ){
        for( int column = 0; column < partitionTable->columnCount(); ++column ){
            newItem = new QTableWidgetItem();
            newItem->setText(partitions.at(column));
            partitionTable->setItem(row, column, newItem);
            newItem->setTextAlignment(Qt::AlignCenter);
        }
    }

    partitionTable->setStyleSheet("");
    //partitionTable->setAlternatingRowColors(true);
    partitionTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    partitions.clear();
}

QString PartitionPage::selectedPartition(){

    QItemSelectionModel *selmodel = partitionTable->selectionModel();
    QModelIndex current = selmodel->currentIndex(); // the "current" item
    //QModelIndexList selected = selmodel->selectedIndexes(); // list of "selected" items
    emptyFeildMsgBox = new QMessageBox(this);

    int row = partitionTable->currentRow();
    selecetedPartition = current.sibling(row, 0).data().toString();

    if (!selecetedPartition.isEmpty()){
        qDebug() << "Selected partition is : " << selecetedPartition;
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


    lineEdit_selecetedpartition->setText(selecetedPartition);
    // write the fiels text to the adi.conf file in apend mode
    QFile adi_conf_file("/tmp/adi.conf");

    /*for writing line by line to text file */
    if (adi_conf_file.open(QIODevice::Append))
    {
        QTextStream stream(&adi_conf_file);
        stream << "DRIVE" << "=" << selecetedPartition << Qt::endl;
    }
    adi_conf_file.close();


    return selecetedPartition;

}

void PartitionPage::formatDrive(){

    int retValue = formatMessageBox();
    QProgressDialog pd("Formating partition...", QString(), 0, 0);
    pd.setWindowTitle("Formating partition");
    pd.setMinimumWidth(400);
    pd.setMinimumHeight(100);

    //QString program_format = "sudo /usr/bin/mkfs.ext4 " + selecetedpartition;

    //qDebug() << "Formating drive: " << program_format;

    if(retValue == 0){
        qDebug() << "Terminal output:" << "User pressed No";
    }
    else if(retValue == 1){
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

//        int r = QMessageBox::Warning()
//    QMessageBox *foematMsgBox = new QMessageBox(this);
//    foematMsgBox->setText("This will erase all data from the selected partition. Do you want to continue...?");
//    foematMsgBox->setInformativeText("Please! backup data before proceeding.");
//    foematMsgBox->setStandardButtons(QMessageBox::No | QMessageBox::Yes);
//    foematMsgBox->setDefaultButton(QMessageBox::Yes);
//    int retValue = foematMsgBox->exec();
//    return retValue;

    if (QMessageBox::Yes == QMessageBox::question(this, tr("Warning"), tr("Please! backup data before proceeding.\nThis will erase all data from the selected partition.\n\nDo you want to continue...?")))
    {
        return 1;
    }
    return 0;
}

void PartitionPage::finishMsg(){

   qDebug() << "Exit status code is:" << process_chroot->exitStatus();

   // yet not fixed
    if (process_chroot->exitStatus()==0){
        QMessageBox::information(this, "", "Avouch installed successfully. \nRestart your computer and remove any USB or DVD.");

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

void PartitionPage::radioButton1Clicked(){
    QMessageBox::information(this, "", "If you continue the changes written below will be writen to the disk. "
                                       "\n \nWARNING: This will destroy all data on all partitions. "
                                       "\n \nThe software is provided without any warranty.");

    QFile adi_conf_file("/tmp/adi.conf");

    /*for writing line by line to text file */
    if (adi_conf_file.open(QIODevice::Append))
    {
        QTextStream stream(&adi_conf_file);
        stream << "DISKPARTOPT" << "=" << "1P" << Qt::endl;
    }
    adi_conf_file.close();
    wizard()->button(QWizard::NextButton)->setEnabled(true);
}

void PartitionPage::radioButton2Clicked(){
    QMessageBox::information(this, "", "If you continue the changes written below will be writen to the disk. "
                                       "\n \nWARNING: This will destroy all data on all partitions. "
                                       "\n \nThe software is provided without any warranty.");

    QFile adi_conf_file("/tmp/adi.conf");

    /*for writing line by line to text file */
    if (adi_conf_file.open(QIODevice::Append))
    {
        QTextStream stream(&adi_conf_file);
        stream << "DISKPARTOPT" << "=" << "2P" << Qt::endl;
    }
    adi_conf_file.close();
    wizard()->button(QWizard::NextButton)->setEnabled(true);
}
void PartitionPage::radioButton3Clicked(){
    QMessageBox::information(this, "", "If you continue the changes written below will be writen to the disk. "
                                       "\n \nWARNING: This will destroy all data on selected partition. "
                                       "\n \nThe software is provided without any warranty.");

    QFile adi_conf_file("/tmp/adi.conf");
    // copy all the text from the adi.con to buffer with out the DISKPARTOPT variable
    // and the nresize the file size to zero and write the buffer into the file
    if(adi_conf_file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QString s;
        QTextStream stream(&adi_conf_file);
        while(!stream.atEnd())
        {
            // copy all the text to a string without the variable DISKPARTOPT
            QString line = stream.readLine();
            if(!line.contains("DISKPARTOPT"))
                s.append(line + "\n");
        }
        // set the size of the file to zero (delete all the text)
        adi_conf_file.resize(0);
        // write the buffer stream to the text file with out variable DISKPARTOPT
        stream << s;
        adi_conf_file.close();
    }
    partitionTable->setVisible(true);
    //qDebug() << "Partition Table visibeled";
}

void PartitionPage::showEvent(QShowEvent *) {
    wizard()->button(QWizard::BackButton)->setDisabled(true);
}

int PartitionPage::nextId() const {
        wizard()->button(QWizard::BackButton)->setDisabled(true);
        return AvouchInstaller::Page_User;
}

/******************* End of of Partition Page *****************************************/

UserPage::UserPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("User Credential Page"));
    setSubTitle(tr("Enter the user credentials."
                   "The user you add here will be <i>Administrator</i> of the computer."));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/WatermarkPixmapUserSetup.png"));

    emptyFeildMsgBox = new QMessageBox(this);
    emptyFeildMsgBox->setWindowTitle("Error Massage");
    emptyFeildMsgBox->setMinimumHeight(200);
    emptyFeildMsgBox->setMinimumWidth(400);

    label_fullname = new QLabel(tr("Full Name:"));
    lineEdit_fullname = new QLineEdit;
    lineEdit_fullname->setMaximumWidth(500);
    lineEdit_fullname->setMinimumSize(200, 40);
    label_fullname->setBuddy(lineEdit_fullname);

    label_username = new QLabel(tr("User Name:"));
    lineEdit_username = new QLineEdit;
    lineEdit_username->setMaximumWidth(500);
    lineEdit_username->setMinimumSize(200, 40);
    lineEdit_username->setValidator(new QRegularExpressionValidator(QRegularExpression("[\\w\\d_ \\.]{24}"), this));
    label_username->setBuddy(lineEdit_username);

    label_hostname = new QLabel(tr("Computer / Host Name:"));
    lineEdit_hostname = new QLineEdit;
    lineEdit_hostname->setMaximumWidth(500);
    lineEdit_hostname->setMinimumSize(200, 40);
    label_hostname->setBuddy(lineEdit_hostname);

    label_password = new QLabel(tr("Password:"));
    lineEdit_password = new QLineEdit;
    lineEdit_password->setMaximumWidth(500);
    lineEdit_password->setMinimumSize(200, 40);
    lineEdit_password->setEchoMode( QLineEdit::Password );
    label_password->setBuddy(lineEdit_password);

    label_repassword = new QLabel(tr("Enter Pssword again:"));
    lineEdit_repassword = new QLineEdit;
    lineEdit_repassword->setMaximumWidth(500);
    lineEdit_repassword->setMinimumSize(200, 40);
    lineEdit_repassword->setEchoMode( QLineEdit::Password );
    label_repassword->setBuddy(lineEdit_repassword);

    root_paaswd_checkbox = new QCheckBox(tr("&Use same password for administrator (root) password."));

    label_missmatch = new QLabel(tr(""));

    label_rootpasswd = new QLabel(tr("Root Password:"));
    lineEdit_rootpasswd = new QLineEdit;
    lineEdit_rootpasswd->setMaximumWidth(500);
    lineEdit_rootpasswd->setMinimumSize(200, 40);
    lineEdit_rootpasswd->setEchoMode( QLineEdit::Password );
    label_rootpasswd->setBuddy(lineEdit_rootpasswd);

    label_rootrepasswd = new QLabel(tr("Re-enter root Password:"));
    lineEdit_rootrepasswd = new QLineEdit;
    lineEdit_rootrepasswd->setMaximumWidth(500);
    lineEdit_rootrepasswd->setMinimumSize(200, 40);
    lineEdit_rootrepasswd->setEchoMode( QLineEdit::Password );
    label_rootrepasswd->setBuddy(lineEdit_rootrepasswd);
    label_rootmissmatch = new QLabel(tr(""));


//    lineEdit_fullname->setStyleSheet("border: 1px solid white");
//    lineEdit_username->setStyleSheet("border: 1px solid white");
//    lineEdit_hostname->setStyleSheet("border: 1px solid white");
//    lineEdit_password->setStyleSheet("border: 1px solid white");
//    lineEdit_repassword->setStyleSheet("border: 1px solid white");
//    lineEdit_rootpasswd->setStyleSheet("border: 1px solid white");
//    label_rootrepasswd->setStyleSheet("border: 1px solid white");




    registerField("evaluate.fullname*", lineEdit_fullname);
    registerField("evaluate.username", lineEdit_username);
    registerField("evaluate.hostname*", lineEdit_hostname);
    registerField("evaluate.password*", lineEdit_password);
//    registerField("evaluate.rootpasswdcheckbox*", root_paaswd_checkbox);
    registerField("evaluate.repassword*", lineEdit_repassword);
    registerField("evaluate.rootpasswd*", lineEdit_rootpasswd);
    registerField("evaluate.rootrepasswd*", lineEdit_rootrepasswd);

    QGridLayout *layout = new QGridLayout;

    layout->addWidget(label_fullname, 0, 0);
    layout->addWidget(lineEdit_fullname, 0, 1);

    layout->addWidget(label_username, 1, 0);
    layout->addWidget(lineEdit_username, 1, 1);

    layout->addWidget(label_hostname, 2, 0);
    layout->addWidget(lineEdit_hostname, 2, 1);

    layout->addWidget(label_password, 3, 0);
    layout->addWidget(lineEdit_password, 3, 1);

    layout->addWidget(label_repassword, 4, 0);
    layout->addWidget(lineEdit_repassword, 4, 1);
    layout->addWidget(label_missmatch, 4, 2);

    layout->addWidget(root_paaswd_checkbox, 5,1);

    layout->addWidget(label_rootpasswd, 6, 0);
    layout->addWidget(lineEdit_rootpasswd, 6, 1);

    layout->addWidget(label_rootrepasswd, 7, 0);
    layout->addWidget(lineEdit_rootrepasswd, 7, 1);
    layout->addWidget(label_rootmissmatch, 7, 2);

//    root_paaswd_checkbox->setChecked(true);
//    label_rootpasswd->setVisible(false);
//    lineEdit_rootpasswd->setVisible(false);
//    label_rootrepasswd->setVisible(false);
//    lineEdit_rootrepasswd->setVisible(false);
//    label_rootmissmatch->setVisible(false);

    setLayout(layout);


    connect(lineEdit_fullname,
            SIGNAL(textChanged(const QString &)),
            this,
            SLOT(slotLineEditFullnameTextEdited(const QString &)));

    connect(lineEdit_repassword,
            SIGNAL(textChanged(const QString &)),
            this,
            SLOT(checkPasswordMismatch(const QString &)));

//    connect(lineEdit_password,
//            SIGNAL(textChanged(const QString &)),
//            this,
//            SLOT(slotLineEditRootPasswdTextEdited(const QString &)));

//    connect(lineEdit_repassword,
//            SIGNAL(textChanged(const QString &)),
//            this,
//            SLOT(slotLineEditRootRePasswdTextEdited(const QString &)));

    connect(lineEdit_rootrepasswd,
            SIGNAL(textChanged(const QString &)),
            this,
            SLOT(checkRootPasswordMismatch(const QString &)));


    connect(root_paaswd_checkbox,
            SIGNAL(clicked(bool)),
            this,
            SLOT(rootCheckBoxAction(bool)));

    // get the text from the text fields
     //instPartition = lineEdit_rootrepasswd->text();
//    fullname = lineEdit_fullname->text();
//    username = lineEdit_username->text();
//    hostname = lineEdit_hostname->text();
//    password = lineEdit_password->text();
//    repassword = lineEdit_repassword->text();
//    rootpasswd = lineEdit_rootpasswd->text();
//    rootrepasswd = lineEdit_rootrepasswd->text();



}

// This function will get the username with out spaces and to lower case,
// while user enter its full name
void UserPage::slotLineEditFullnameTextEdited(const QString){

    //The first changes all whitespace characters to a single instance of ASCII 32, the second removes that.
    // This may also be implemented by QString::remove(' ') or QString::remove(" ")
    lineEdit_username->setText(lineEdit_fullname->text().toLower().replace(" ",""));
    lineEdit_hostname->setText(lineEdit_fullname->text().toLower().replace(" ","") + "-pc");
    //label_admin->show();

}

void UserPage::slotLineEditRootPasswdTextEdited(const QString){

    //The first changes all whitespace characters to a single instance of ASCII 32, the second removes that.
    // This may also be implemented by QString::remove(' ') or QString::remove(" ")
    if(root_paaswd_checkbox->isChecked())
    {
    lineEdit_rootpasswd->setText(lineEdit_password->text().toLower().replace(" ",""));
    //label_admin->show();
    }
}
void UserPage::slotLineEditRootRePasswdTextEdited(const QString){

    //The first changes all whitespace characters to a single instance of ASCII 32, the second removes that.
    // This may also be implemented by QString::remove(' ') or QString::remove(" ")
    if(root_paaswd_checkbox->isChecked())
    {
    lineEdit_rootrepasswd->setText(lineEdit_repassword->text().toLower().replace(" ",""));
    //label_admin->show();
    }
}

// This function will get the username with out spaces and to lower case,
// while user enter its full name
void UserPage::checkPasswordMismatch(const QString){

   if(field("evaluate.password") == field("evaluate.repassword")){
        qDebug() << "Terminal output:" << "Password matched.";
        label_missmatch->setText("<b>&#10004;</b>");
        label_missmatch->setStyleSheet("color: green;");
    }
    else{
       qDebug() << "Terminal output:" << "Password missmatch.";
       label_missmatch->setText("<b>&#10006;</b>");
       label_missmatch->setStyleSheet("color: red;");
   }

}

void UserPage::rootCheckBoxAction(bool checked){

    if(checked)
       {
           lineEdit_rootpasswd->setText(lineEdit_password->text());
           lineEdit_rootrepasswd->setText(lineEdit_repassword->text());
           label_rootpasswd->setVisible(false);
           lineEdit_rootpasswd->setVisible(false);
           label_rootrepasswd->setVisible(false);
           lineEdit_rootrepasswd->setVisible(false);
           label_rootmissmatch->setVisible(false);
       }
       else
       {
            lineEdit_rootpasswd->clear();
            lineEdit_rootrepasswd->clear();
            label_rootpasswd->setVisible(true);
            lineEdit_rootpasswd->setVisible(true);
            label_rootrepasswd->setVisible(true);
            lineEdit_rootrepasswd->setVisible(true);
            label_rootmissmatch->setVisible(true);
       }
}

// This function will get the username with out spaces and to lower case,
// while user enter its full name
void UserPage::checkRootPasswordMismatch(const QString){

   if(field("evaluate.rootpasswd") == field("evaluate.rootrepasswd")){
        qDebug() << "Terminal output:" << "Password matched.";
        label_rootmissmatch->setText("<b>&#10004;</b>");
        label_rootmissmatch->setStyleSheet("color: green;");
    }
    else{
       qDebug() << "Terminal output:" << "Password missmatch.";
       label_rootmissmatch->setText("<b>&#10006;</b>");
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
    else if (field("evaluate.rootpasswd") != field("evaluate.rootrepasswd")){

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
    //progressBar->setMinimum(0);
    //progressBar->setMaximum(0);
    //progressBar->setValue(0);
    //progressBar->setVisible(true);
    //value=0;

    topLabel->setWordWrap(true);
    pictureLabel = new QLabel();
    //pictureLabel->setMaximumSize(1000,600);
    pictureLabel->setPixmap(QPixmap(":/images/1.png"));
    textedit_show_process = new QTextEdit;
    //lable_show_progress = new QLabel();


    label_process_finished = new QLabel();
    lineEdit_procfinished = new QLineEdit;
    //label_procfinished->setBuddy(lineEdit_procfinished);
    registerField("evaluate.procfinished*", label_process_finished);



    QVBoxLayout *layout = new QVBoxLayout;    
    layout->addWidget(progressBar);
    layout->addWidget(pictureLabel);
    layout->addWidget(topLabel);
    layout->addWidget(textedit_show_process);
    //layout->addWidget(lable_show_progress);
    layout->addWidget(label_process_finished);
    //layout->addWidget(lineEdit_procfinished);
    setLayout(layout);

    progressBar->reset();

    connect(this, SIGNAL(updateProgressValue(int)), this, SLOT(updateProgressBar(int)));

    timer = new QTimer(this);

    count = 0;

    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));


}

void FinalSetupPage::updateProgressBar(const int value){

    progressBar->setValue(value);

}// Update ProgressBar

void FinalSetupPage::initializePage(){

    //QProgressDialog pd("Finalizing settings. Please! wait...", QString(), 0, 0);
    //pd.setWindowTitle("Final Settings");
    //pd.setMinimumWidth(400);
    //pd.setMinimumHeight(100);

    //instPartition = field("evaluate.selecetedpartition").toString();
    fullname = field("evaluate.fullname").toString();
    username = field("evaluate.username").toString();
    password = field("evaluate.password").toString();
    repassword = field("evaluate.repassword").toString();
    hostname = field("evaluate.hostname").toString();
    rootpasswdcheckbox = field("evaluate.rootpasswdcheckbox").toString();
    rootpasswd = field("evaluate.rootpasswd").toString();
    rootrepasswd = field("evaluate.rootrepasswd").toString();


    //qDebug() << "Imported Partition is: " << instPartition;
    qDebug() << "Imported username is: " << username;
    qDebug() << "Imported password is: " << password;
    qDebug() << "Imported hostname is: " << hostname;
    qDebug() << "Imported fullname is: " << fullname;
    qDebug() << "Imported root password is: " << rootpasswd;

    QString filename = "/tmp/adi.conf";
    QFile file(filename);

    /*for writing line by line to text file */
    if (file.open(QIODevice::Append))
    {
        QTextStream stream(&file);
        //stream << "DRIVE" << "=" << instPartition << Qt::endl;
        stream << "USERNAME" << "=" << username << Qt::endl;
        stream << "PASSWORD" << "=" << password << Qt::endl;
        if (rootpasswdcheckbox == "true")
        {
            stream << "ROOTPASSWD" << "=" << password << Qt::endl;
        }
        else {
            stream << "ROOTPASSWD" << "=" << rootpasswd << Qt::endl;
        }
        stream << "HOSTNAME" << "=" << hostname << Qt::endl;
        stream << "FULLNAME" << "=" << fullname << Qt::endl;
    }
    file.close();

    timer->start(5000);

    timer1 = new QTimer(this);
    timer1->start(30000);
    connect(timer1, SIGNAL(timeout()), this, SLOT(animateImages()));

    //connect(process_final_setup, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(SlotDetectFinish()));


    //connect(process_final_setup, SIGNAL(finished(int, QProcess::ExitStatus)), &pd, SLOT(accept()));
    //connect(process_final_setup, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(SlotDetectFinish(int *exitCode, QProcess::ExitStatus *exitSatus)));

    //connect(progressBar, SIGNAL(valueChanged(int)), this, SLOT(handleTimeOut()));
    //connect(process_final_setup, SIGNAL(finished(int)), this, SLOT(finalProcessFinished()));

    wizard()->button(QWizard::BackButton)->setDisabled(true);
    process_final_setup = new QProcess;
    //QString program_final_setup = "sudo /usr/bin/adiscript " + instPartition + " " + username + " " + password + " " + rootpasswd + " " + hostname + " " + fullname;
    const QString program = "sudo";
    const QStringList args = {"/usr/bin/adiscript"};
    qDebug() << "Command is : " << program << args;

    int retValue = formatMessageBox();

        if(retValue == QMessageBox::No){
            qDebug() << "Terminal output:" << "User pressed No";
            wizard()->close();
        }
        else if(retValue == QMessageBox::Yes){
            qDebug() << "Terminal output:" << "User pressed Yes, Starting terminal process...";
            process_final_setup = new QProcess();
            process_final_setup->QProcess::start(program, args, QIODevice::ReadWrite);
            connect(process_final_setup, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
            connect(process_final_setup, SIGNAL(finished(int)), this, SLOT(finalProcessFinished()));

        }

    //label_procfinished->setText("Installation completed");

    //pd.exec();
    //pd.autoClose();
    //process_final_setup->waitForFinished(-1);
}

int FinalSetupPage::formatMessageBox(){

    QMessageBox *foematMsgBox = new QMessageBox(this);
    foematMsgBox->setText("This will destroy all data from the partition <b>" + instPartition +
                          "</b>. Please! backup your data before proceeding.");
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
    //textEdit_showProcess->append(QString(data));

}

void FinalSetupPage::readyReadStandardOutput()
{
    string_terminal_output.append(process_final_setup->readAllStandardOutput());
    textedit_show_process->setText(string_terminal_output);
    //lable_show_progress->setText(string_terminal_output);

    // put the slider at the bottom
    textedit_show_process->verticalScrollBar()
            ->setSliderPosition(
                textedit_show_process->verticalScrollBar()->maximum());
    textedit_show_process->setReadOnly(true);
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
    fileList << ":/images/1.png" << ":/images/2.png" << ":/images/3.png" << ":/images/4.png";

    for(int i=0; i < fileList.size(); ++i){

       QImage image1(fileList[i]);
       pictureLabel->setPixmap(QPixmap::fromImage(image1));
       delay(9000);
     }
}

void FinalSetupPage::handleTimeOut()
{
     for(value=1; value < 100; value++){
        progressBar->setValue(value);        
        delay(6000);
      }
}

void FinalSetupPage::finalProcessFinished()
{
    // Set the encoding status by checking output file's existence
    QString fileName = "/mnt/etc/avouch-release";

    if (!QFile::exists(fileName)) {
        label_process_finished->setText("Avouch Linux installation status: Successful!");
        FinalSetupPage::SlotDetectFinish();
    }
    else {
        label_process_finished->setText("Avouch Linux installation status: Failed!!");
    }
}

void FinalSetupPage::updateValue() {

    if(count == 5000) {
        timer->stop();
        return;
    }// if
    count++;
    emit updateProgressValue(count);

}// updateValue

void FinalSetupPage::SlotDetectFinish(){
    //qDebug() << "Exit Code is: " << exitCode;
    //qDebug() << "Exit Status is: " << exitSatus;
    label_process_finished->setText("Installation completed");
    label_process_finished->setStyleSheet("color: green;");
    count = 6000;
    progressBar->setValue(100);
    //progressBar->close();
    wizard()->button(QWizard::NextButton)->setEnabled(true);
    //wizard()->button(QWizard::BackButton)->setDisabled(true);
    //FinalSetupPage::isComplete();
}
void FinalSetupPage::showEvent(QShowEvent *) {
    wizard()->button(QWizard::BackButton)->setDisabled(true);
}


int FinalSetupPage::nextId() const{
    return AvouchInstaller::Page_Conclusion;
}

/******************* End of of Final Setup Page *****************************************/

ConclusionPage::ConclusionPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Installation of <i>Avouch</i>&trade; completed"));
    setSubTitle(tr("You may now reboot the system."));

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


void ConclusionPage::initializePage()
{
    QString licenseText;

    if (wizard()->hasVisitedPage(AvouchInstaller::Page_FinalSetup)) {
        licenseText = tr("Avouch installed successfully. Now you can restart your computer.");
    } else {
        licenseText = tr("Avouch installation is not seccessfull.");
    }

    bottomLabel->setText(licenseText);


}

void ConclusionPage::showEvent(QShowEvent *) {
    wizard()->button(QWizard::BackButton)->setDisabled(true);
}

int ConclusionPage::nextId() const {
    return -1;
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
    const QString program = "/usr/bin/reboot";
    const QStringList args = {};
    qDebug() << "Shutdown command is : " << program << args;
    qDebug() << "Rebooting System...";
    process = new QProcess();
    process->QProcess::start(program, args, QIODevice::ReadWrite);

}

