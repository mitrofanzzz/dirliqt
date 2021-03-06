#include "mainwindow.h"
#include "ui_mainwindow.h"

QDir dir_path;
// QDir t_dir_path;
QFileInfoList result_FileList;

QFileInfoList GetListFromDir(QDir t_d_path);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->hide();
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QFileDialog *setdir = new QFileDialog;
    setdir->setFileMode(QFileDialog::DirectoryOnly);
    QString path = setdir->getExistingDirectory(this, tr("Open Directory"), "c:/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->label->setText(path);
    ui->statusBar->showMessage((ui->label->text()), 0);
    ui->pushButton_3->setDisabled(false);
}

void MainWindow::on_pushButton_3_clicked()
{
    QFileInfoList Filelist;
    QDir t_dir_path;
    QFileInfoList t_Filelist;
    QStringList list;

    result_FileList.clear();

    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_4->setDisabled(true);

    ui->label_2->setText("Wait");
    dir_path.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
    dir_path.setSorting(QDir::DirsFirst | QDir::Name);
    dir_path = ui->label->text();

    GetListFromDir(dir_path);

    qint32 nrow = result_FileList.count();
    ui->label_2->setText("Ready");
    ui->statusBar->showMessage((QString::number(nrow) + QString(" lines got.")), 0);
    ui->pushButton->setDisabled(false);
    ui->pushButton_2->setDisabled(false);
    ui->pushButton_4->setDisabled(false);
}

QFileInfoList GetListFromDir(QDir t_d_path) {

    QFileInfoList locFilelist;
    QDir loc_t_dir_path;
    QFileInfoList loc_t_Filelist;


    loc_t_dir_path = t_d_path;
    loc_t_dir_path.setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
    loc_t_dir_path.setSorting(QDir::DirsFirst | QDir::Name);
    loc_t_Filelist = loc_t_dir_path.entryInfoList();

    foreach (QFileInfo tItm, loc_t_Filelist) {
        if (tItm.isDir()){
            result_FileList += tItm.absoluteFilePath();
            GetListFromDir(tItm.absoluteFilePath());
        } else if (tItm.isFile()){
           result_FileList += tItm.absoluteFilePath();
        }
        QCoreApplication::processEvents();

    }
    return result_FileList;
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->progressBar->show();
    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    ui->label_2->setText("Please wait ");
    ui->statusBar->showMessage("Please wait...", 0);

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                 ui->label->text(),
                                 tr("List (*.csv *.txt )"));
    if (fileName != ""){

        QFile file(fileName);
        if (file.open(QFile::WriteOnly | QFile::Truncate)){
            QTextStream data( &file );
            QStringList strList;
            qint32 nrow = result_FileList.count();
            qint32 counter = 0;
            QString num_row = QString::number(nrow);
            ui->progressBar->setMinimum(0);
            ui->progressBar->setMaximum(nrow);

            strList << "\" " + QString ("Path") + "\" ";
            strList << "\" " + QString ("File") + "\" ";
            strList << "\" " + QString ("Size (Bytes)") + "\" ";
            strList << "\" " + ui->label->text().toUtf8() + "\" ";

            data << strList.join(";") << "\n";

            foreach (QFileInfo txt, result_FileList){
                counter++;
                strList.clear();

                if (txt.isDir()){
                    strList << "\" " + txt.absoluteFilePath().toUtf8() + "\" ";
                    strList << QString ("DIR");
                } else {
                    strList << "\" \" ";
                    strList << "\" " + txt.completeBaseName().toUtf8() + "." + txt.completeSuffix().toUtf8() + "\" ";
                    strList << "\" " + (QString::number ( txt.size())) + "\" ";
                }
                data << strList.join( ";" )+"\n";
                ui->progressBar->setValue(counter);
                QCoreApplication::processEvents();
            }
            ui->statusBar->showMessage(("File saved successfully."), 0);
            file.close();
            ui->pushButton->setDisabled(false);
            ui->pushButton_2->setDisabled(false);
            ui->pushButton_3->setDisabled(true);
            ui->pushButton_4->setDisabled(true);
        }
    } else {
        ui->pushButton->setDisabled(false);
        ui->pushButton_2->setDisabled(false);
        ui->pushButton_3->setDisabled(true);
        ui->pushButton_4->setDisabled(true);
        ui->statusBar->showMessage(("Save file dialog cancelled."), 0);
        ui->label_2->setText("Path:");
    }
}
