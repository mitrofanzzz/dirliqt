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
}

void MainWindow::on_pushButton_3_clicked()
{
    QFileInfoList Filelist;
    QDir t_dir_path;
    QFileInfoList t_Filelist;


    ui->listWidget->clear();

    dir_path.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
    dir_path.setSorting(QDir::DirsFirst | QDir::Name);
    dir_path = ui->label->text();
    Filelist = dir_path.entryInfoList();
    ui->listWidget->addItem(dir_path.path());


    foreach (QFileInfo mItm, Filelist) {

//        t_dir_path.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
        t_dir_path.setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
        t_dir_path.setSorting(QDir::DirsFirst | QDir::Name);
        t_dir_path = mItm.absoluteFilePath();

        foreach (QFileInfo txt, GetListFromDir(t_dir_path)) {
           ui->listWidget->addItem(txt.absoluteFilePath());
        }



        //ui->listWidget->addItem(tItm.absoluteFilePath());
        ui->listWidget->sortItems(Qt::AscendingOrder);
    }
}

QFileInfoList GetListFromDir(QDir t_d_path) {

    QFileInfoList locFilelist;
    QDir loc_t_dir_path;
    QFileInfoList loc_t_Filelist;


    loc_t_dir_path = t_d_path;
//    loc_t_dir_path.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
    loc_t_dir_path.setFilter(QDir::AllDirs | QDir::Files | QDir::NoDotAndDotDot);
    loc_t_dir_path.setSorting(QDir::DirsFirst | QDir::Name);
//    loc_t_dir_path = mItm.absoluteFilePath();
    loc_t_Filelist = loc_t_dir_path.entryInfoList();

    foreach (QFileInfo tItm, loc_t_Filelist) {
        if (tItm.isDir()){
            result_FileList += tItm.absoluteFilePath();
            GetListFromDir(tItm.absoluteFilePath());
        } else if (tItm.isFile()){
           result_FileList += tItm.absoluteFilePath();
        }
    }
    return result_FileList;
//    ui->listWidget->sortItems(Qt::AscendingOrder);

//    foreach (QFileInfo mItm, dir_path.entryInfoList())
//    {

//        //ui->listWidget->addItem(mItm.absoluteFilePath());
//    }
}
